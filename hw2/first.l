%{

%}

/* Before the first non-terminal is parsed; used in place of _prod_list_
 * would have used PLIST here.
 * Equivalent to IPL in design doc.
 *
 * INITIAL = expecting NT to begin first production.
 */

/* At least one production encountered so far; only valid finish state.
 * IPL' in design doc.
 */
%s PLIST_MORE

/* Encountered first NT and expecting a GOES.
 * IP in design doc.
 */
%s PROD

/* Encountered GOES, now expecting T or NT to start a rule.
 * IPB in design doc.
 */
%s PBODY

/* Encountered first T or NT of rule, now expecting more T/NT tokens, or an EOL
 * to indicate the rule is complete.
 * IR in design doc.
 */
%s RULE

/* Encountered first rule, now expecting an OR or a SEMI.
 * IPB' in design doc.
 */
%s PBODY_MORE

/* Encountered a SEMI, now expecting an EOL; all else is discarded.
 * IE in design doc.
 */
%s E_EOL

NT_TOKEN    [A-Z]
T_TOKEN     [a-z]
GOES_TOKEN  "-->"
SEMI_TOKEN  ";"
OR_TOKEN    "|"
EOL_TOKEN   "\n"

%%

<INITIAL>{NT_TOKEN}         {printf("PLIST:NT ");
                             BEGIN PROD;}

<PROD>{GOES_TOKEN}          {printf("PROD:GOES ");
                             BEGIN PBODY;}

<PBODY>{NT_TOKEN}           {printf("PBODY:NT ");
                             BEGIN RULE;}
<PBODY>{T_TOKEN}            {printf("PBODY:T ");
                             BEGIN RULE;}

<RULE>{NT_TOKEN}            {printf("RULE:NT ");}
<RULE>{T_TOKEN}             {printf("RULE:T ");}
<RULE>{EOL_TOKEN}           {printf("RULE:EOL\n");
                             BEGIN PBODY_MORE;}

<PBODY_MORE>{OR_TOKEN}      {printf("PBODY_MORE:OR ");
                             BEGIN RULE;}
<PBODY_MORE>{SEMI_TOKEN}    {printf("PBODY_MORE:SEMI ");
                             BEGIN E_EOL;}

<E_EOL>{EOL_TOKEN}          {printf("E_EOL:EOL\n");
                             BEGIN PLIST_MORE;}

<PLIST_MORE>{NT_TOKEN}      {printf("PLIST_MORE:NT ");
                             BEGIN PROD;}

<PLIST_MORE><<EOF>>         {printf("ACCEPTED\n"); yyterminate();}
%%
