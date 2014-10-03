This document serves as a design document for a recursive descent parser (RD)
that computes FIRST sets for context free grammars (CFGs).

# Build

$ make        # outputs executable `first`
$ make clean  # removes .o and other intermediates
$ make test   # makes executables and runs on test cases

# Design

## Input language

The inputs are CFGs which should be read and stored in an appropriate data
structure. FIRST sets are computed for each NT.

### Tokens in the language

There are 6 tokens in the language.

1.  NT    [A-Z]
2.  T     [a-z]
3.  GOES  '-->'
4.  SEMI  ';'
5.  OR    '|'
6.  EOL   '\n'

### Grammar of the language

This is the grammar that defines the format of the input files the program will
need to parse. Since the input files contain CFGs, this is actually the grammar
for CFGs; it's a grammar for a grammar.

> prod_list        :  prod_list production
>                  |  production
>
> production       :  NT GOES production_body SEMI EOL >
> production_body  :  production_body OR rule
>                  |  rule
>
> rule             :  NT rule
>                  |  T rule
>                  |  EOL

In order to facilitate ease of notation later in this document,
abbreviations are defined for the input token names here. All are prefaced with
`I` to denote they belong to the input language and not the actual CFG being
parsed.

1.  prod_list       = IPL
2.  production      = IP
3.  production_body = IPB
4.  rule            = IR

So we have:

> IPL  :  IPL IP
>      |  IP
>
> IP   :  NT GOES IPB SEMI EOL
>
> IPB  :  IPB OR IR
>      |  IR
>
> IR   :  NT IR
>      |  T IR
>      |  EOL

### Interpretation

First, the input files are going to be lists of productions, with one or more
production in each list/file.

> prod_list        :  prod_list production
>                  |  production

Each production starts with a `NT GOES`, contains a `production_body`, and is
concluded by a `SEMI EOL` seqeunce.

> production       :  NT GOES production_body SEMI EOL

The `production_body` will consist of one or more rules, where each rule is
separated by an `OR` token.

> production_body  :  production_body OR rule
>                  |  rule

A rule has one of three forms:

1.  `NT rule`
2.  `T rule`
3.  `EOL` (should be interpreted as representing epsilon)

> rule             :  NT rule
>                  |  T rule
>                  |  EOL

## Requirements

1.  Recognize all tokens in the input language (CFGs)
2.  Create an LL grammar for the input language
3.  Translate LL grammar into recursive descent parser
    -   should be able to process all given test input files
4.  Build data structure to store grammar for RDP
    -   parse test inputs and output grammar from data structure to test
5.  Write algorithm to compute FIRST sets from stored grammar

## Brainstorm

### Req1

This req. is relatively simple to meet. Simply set up the appropriate regexes in
a lex specification and output the name of the token as it is processed,
interpreting newlines as actual line breaks in the printed output to ensure
clarity. This should be able to handle all the test inputs and output
appropriate token names. It's not necessary to pay any attention to proper
states for actually building up the grammar here.

### Req2

Is the input language already specified by an LL grammar? We can show that a
grammar is not LL by looking at predict sets; PREDICT sets for a given
non-terminal are disjoint for an LL grammar. 

#### Converting to LL

If the grammar is not LL, it will need to be converted into an LL grammar using
one or both of the following 2 methods. The second method is more reliable and
is used exclusively for this assignment.

1.  Eliminate common prefixes:
    A  --> BaCD | BaCE
    BECOMES
    A  --> BaCA'
    A' --> D | E
2.  Convert left recursion to right recursion:
    A  --> Aa1 | Aa2 | ... | b1 | b2 | ...
    BECOMES
    A  --> b1A' | b2A' | ...
    A' --> a1A' | a2A' | ... | $\epsilon$

Note that in the second (more reliable) method, a new NT called NT' is always
created, then two distinct sub-rules apply:

1.  If form of rule is `NT T`, move to RHS of `NT'` production, remove `NT` from
    left, and add `NT'` to right of `T`.
2.  If form of rule is `T`, leave on RHS of `NT` but add a `NT'` to the right.

#### PREDICT sets for input lang. grammar

PREDICT sets are computed in one of two ways, depending on the presence of
epsilon in the first set of the terminal token.

> PREDICT(A --> a) = ...
>
> FIRST(a)                                 if $\epsilon$ not in FIRST(a)
> (FIRST(a) - {$\epsilon$}) U FOLLOW(A)    otherwise

While PREDICT sets are a foolproof way of determining if a grammar is not LL,
some of the productions in our input language grammar are clearly left
recursive. In particular:

> IPL  :  IPL IP
>      |  IP
> IPB  :  IPB OR IR
>      |  IR

These can be converted right away to right recursive. For the first (prod_list),
we introduce IPL' and convert

FROM:

> IPL  :  IPL IP
>      |  IP

TO:

> IPL  : IP IPL'
> IPL' : IP IPL' | $\epsilon$

And for the second (production_body), we introduce IPB' and convert

FROM:

> IPB  :  IPB OR IR
>      |  IR

TO:

> IPB  :  IR IPB'
> IPB' :  OR IR IPB' | $\epsilon$

At this point, we have the grammar shown below. It is not immediately apparent
that the other two productions are left recursive, but let's prove that our
grammar is now LL using PREDICT sets just to be sure. Note: e = $\epsilon$ below.

> IPL  : IP IPL'
> IPL' : IP IPL' | e
>
> IPB  :  IR IPB'
> IPB' :  OR IR IPB' | e
>
> IP   :  NT GOES IPB SEMI EOL
>
> IR   :  NT IR
>      |  T IR
>      |  EOL

 SYMBOL      FIRST        FOLLOW
 ----------  ----------   ----------
 IPL         {NT}         {$}
 IPL'        {NT,e}       {FOLLOW(IPL)} = {$}
 IPB         {NT,T,EOL}   {SEMI}
 IPB'        {OR,e}       {FOLLOW(IPB)} = {SEMI}
 IP          {NT}         {FIRST(IPL'),FOLLOW(IPL),FOLLOW(IPL')} = {NT,$}
 IR          {NT,T,EOL}   {FIRST(IPB'),FOLLOW(IPB),FOLLOW(IPB')} = {OR,SEMI}

  NUM  PRODUCTION                       PREDICT
 ----  ------------------------------   ------------------------
   1   IPL  :  IP IPL'                  FIRST(IP)    = {NT}
   2   IPL' :  IP IPL'                  FIRST(IP)    = {NT}
   3   IPL' :  e                        FOLLOW(IPL') = {$}
   4   IPB  :  IR IPB'                  FIRST(IR)    = {NT,T,EOL}
   5   IPB' :  OR IR IPB'               FIRST(OR)    = {OR}
   6   IPB' :  e                        FOLLOW(IPB') = {SEMI}
   7   IP   :  NT GOES IPB SEMI EOL     FIRST(NT)    = {NT}
   8   IR   :  NT IR                    FIRST(NT)    = {NT}
   9   IR   :  T IR                     FIRST(T)     = {T}
  10   IR   :  EOL                      FIRST(EOL)   = {EOL}

Since the PREDICT sets of each non-terminal are disjoint amongst themselves, we
know the grammar is LL(1).

Finally, if we want to use states, we construct a DFA for the grammar defined
by the productions above, introducing one additional state, IE, for "input
expecting EOL token". This will be used when processing production #7, in order
to handle the SEMI EOL termination.

  NUM  PRODUCTION                       PREDICT
 ----  ------------------------------   ------------------------
   1   IPL  :  IP IPL'                  {NT}
   2   IPL' :  IP IPL'                  {NT}
   3   IPL' :  e                        {$}
   4   IPB  :  IR IPB'                  {NT,T,EOL}
   5   IPB' :  OR IR IPB'               {OR}
   6   IPB' :  e                        {SEMI}
   7   IP   :  NT GOES IPB SEMI IE      {NT}
   8   IE   :  EOL                      {EOL}
   9   IR   :  NT IR                    {NT}
  10   IR   :  T IR                     {T}
  11   IR   :  EOL                      {EOL}

FIRST(IE) = {EOL}    FOLLOW(IE) = {NT,$}    PREDICT(IE) = {EOL}

The states in this design doc are translated to slightly more readable forms in
the actual lex specification:

 SYMBOL   STATE
 -------  -------
 IPL      PLIST (INITIAL)
 IPL'     PLIST_MORE
 IPB      PBODY
 IPB'     PBODY_MORE
 IP       PROD
 IR       RULE
 IE       EXP_EOL

### Req3 (Recursive Descent Parser)

After the above transformations, we have the final LL(1) grammar to use for the
recursive descent parser:

PLIST  :  PROD PLIST'              {NT}
PLIST' :  PROD PLIST'              {NT}
PLIST' :  e                        {$}
PBODY  :  RULE PBODY_MORE          {NT,T,EOL}
PBODY_MORE :  OR RULE PBODY_MORE   {OR}
PBODY_MORE :  e                    {SEMI}
PROD   :  NT GOES PBODY SEMI EOL   {NT}
RULE   :  NT RULE                  {NT}
RULE   :  T RULE                   {T}
RULE   :  EOL                      {EOL}

For this req., simply translate each production in the LL(1) version of the
grammar above into a function. There will be 10 functions, one for each
production.

### Req4 (Data Structures)

The grammars look a lot like linked lists to start off with. This probably
makes a great deal of sense. We will also want something to store sets with, so
some sort of set data structure is also likely to be useful. For the linked
list, we'll want to use single linking and have each node contain a char array,
since it will be holding the RHS of the production.

1.  Array of singly linked list of nodes with 1 data slot for char array.
2.  Set

It turned out that after implementing the first data structure (called Plist)
in the code, for "production list", a simple `plist_unique_add` suffices to
implement a set-like data structure for FIRST sets.

### Req5 (Algorithms)

FIRST sets are computed by passing over all non-terminals, applying the 4 rules
below until a pass produces no additional rules.

Initially FIRST(A) (for all A) is empty

1.  For productions A --> cb, where c is a terminal
    -   Add { c } to FIRST(A)
2.  For productions A --> e
    -   Add { e } to FIRST(A)
3.  For productions A --> aBb, where a --> *e AND NOT e $\in$ FIRST(B)
    -   Add FIRST(aB) to FIRST(A)
4.  For productions A --> a, where a --> *e
    -   Add FIRST(a) and { e } to FIRST(A)

# Testing

There are test modules for each data structure used. For the actual first set
computation, outputs were compared manually using the given executable for this
lab.
