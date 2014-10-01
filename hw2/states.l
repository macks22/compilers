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
%s EXP_EOL

NT_T    [A-Z]
T_T     [a-z]
GOES_T  "-->"
SEMI_T  ";"
OR_T    "|"
EOL_T   "\n"

%%

<INITIAL>{NT_T}             {printf("PLIST:NT ");
                             BEGIN PROD;}

<PROD>{GOES_T}              {printf("PROD:GOES ");
                             BEGIN PBODY;}

<PBODY>{NT_T}               {printf("PBODY:NT ");
                             BEGIN RULE;}
<PBODY>{T_T}                {printf("PBODY:T ");
                             BEGIN RULE;}

<RULE>{NT_T}                {printf("RULE:NT ");}
<RULE>{T_T}                 {printf("RULE:T ");}
<RULE>{EOL_T}               {printf("RULE:EOL\n");
                             BEGIN PBODY_MORE;}

<PBODY_MORE>{OR_T}          {printf("PBODY_MORE:OR ");
                             BEGIN RULE;}
<PBODY_MORE>{SEMI_T}        {printf("PBODY_MORE:SEMI ");
                             BEGIN E_EOL;}

<EXP_EOL>{EOL_T}            {printf("EXP_EOL:EOL\n");
                             BEGIN PLIST_MORE;}

<PLIST_MORE>{NT_T}          {printf("PLIST_MORE:NT ");
                             BEGIN PROD;}

<PLIST_MORE><<EOF>>         {printf("ACCEPTED\n"); yyterminate();}
%%
