# Building, testing, executing

Run `make` to build the `lexer` binary, which will by default be placed into the
the bin directory. 4 test cases are included in the tests folder. The expected
outputs are all included in tests/test-guide.md. These can be run with
`make test`, but the output is not matched automatically; it must be compared
by hand.

The lexer was also written with logging in mind, and it can be called with the
`-v` flag to enable verbose output. By default, `lexer` expects input from
stdin. It is best to place the input in a file and pipe it in (see below). If a
more interactive style is desired (perhaps to test a CFG), then it can be called
without input and run until an interrupt is sent (perhaps with <Ctrl-C>). Note
that productions must still be entered first. As soon as a non-production string
is encountered, the lexer will switch to the string testing state.

$ make
$ ./bin/lexer < tests/test0.txt
$ ./bin/lexer -v < tests/test0.txt
$ ./bin/lexer

# Design

The lexer uses a very simble data structure, which is a table built from 3
dynamic char arrays (called vectors in this implementation). There is one array
for each position in the productions: `left`, `mid`, `right`. Several states are
employed in the Lex specification to emulate the state machine given in the
problem specification. Details can be found in the first section of the Lex spec
`lexer.l`.

During the first phase of execution (CFG, or DFA construction), the productions
are processed one at a time. Each is handled as its separate tokens, rather than
as a whole production. The first production encountered is considered to be the
start state `start`. For each production with an empty RHS, (1) the non-terminal
on the LHS is placed into the set of `final_states` and (2) the non-terminal is
placed in `first` and the same position in `mid` and `right` are filled with
null characters. For any production with a non-empty RHS, all 3 positions are
placed in their respective vectors. DFA construction is considered complete when
a terminal character is encountered at the start of a line.

Initially, the first phase was designed so the non-terminal characters could be
placed directly into the `left` and `right` vectors, but the possibility of
multi-character tokens made it impossible to use a char array, which the vectors
are. It would be possible to use larger char arrays or switch to linked lists in
order to represent the arbitrary-length non-terminals. However, this would
sacrificing space efficiency and introducing complexity in the code. Instead,
the Adler 32 Checksum algorithm was used to hash the non-terminals into 32 bit
unsigned integer values. These were then stored in the original char arrays. The
choice to use char arrays rather than arrays of type uint32_t was one of
convenience. The general rule is that at about 70-80% capacity in the hash
space, collisions will become quite likely. Since a char can have 255 possible
values (8 bits), input CFGs will start to have problems around 180 non-terminals
in the language.

At this point, the second phase begins (DFA string testing). Each line
encountered now is parsed as a string of terminal characters, one at a time.
For each character, an attempt is made to look up a production in the table in
which the left non-terminal is the current state `curstate` and the terminal is
the character being processed. If one is found, the state is changed to the
non-terminal in the RHS of the production. If for any character before the EOL,
no production can be found, a global reject flag is set, to indicate the string
has bene rejected. Then processing continues to the EOL as usual. This is done
to consume tokens. Optimizations here would include skipping the production
search process if the reject flag is set. However, this doesn't really hurt
anything as it is.

Once an EOL is encountered, the string is tested to see if it is in the
language.  If `curstate` is in the set of `final_states`, then the string is
accepted, otherwise it is rejected.

# Initial planning and problem exploration

1.  read input to construct DFA
    *   have 5 types of tokens for DFA section
        1.  terminal (lowercase letters and single digits)
        2.  nonterminal (starts with uppercase letters, followed by alphanumeric)
        3.  productions (-->)
        4.  whitespace (tabs and spaces)
        5.  EOL (\n)
    *   DFA input ends at first input not of CFG format
        -   CFG format has 2 possible forms
            1.  (term)\w*-->\w*(nonterm)\w+(term)\n
            2.  (term)\w*-->\w*\n
    *   DFA can be stored as a table
        -   data structure choice?
            +   arrays are ok, but have to make tradeoffs (use lots of space vs.
                keep it small and cap size of possible languages & DFAs we can
                deal with)
            +   linked list is viable
            +   a general graph would also work well
            +   SIMPLEST OPTION: 3 dynamic arrays - one for each position in a
                production (left, mid, right)

    A --> a B
    B --> a B
    B -->

produces (pre-hashing example):

    left mid right
    ---- --- -----
    A    a   B
    B    a   B
    B    \0  \0

2.  read subsequent lines as inputs to just-constructed DFA
    *   return accept/reject for each based on DFA
    *   must traverse DFA structure to find appropriate productions
