%{
#include "tokens.h"
int lineno = 1;
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
%s PLIST_MORE_S

/* Encountered first NT and expecting a GOES.
 * IP in design doc.
 */
%s PROD_S

/* Encountered GOES, now expecting T or NT to start a rule.
 * IPB in design doc.
 */
%s PBODY_S

/* Encountered first T or NT of rule, now expecting more T/NT tokens, or an EOL
 * to indicate the rule is complete.
 * IR in design doc.
 */
%s RULE_S

/* Encountered first rule, now expecting an OR or a SEMI.
 * IPB' in design doc.
 */
%s PBODY_MORE_S

/* Encountered a SEMI, now expecting an EOL; all else is discarded.
 * IE in design doc.
 */
%s EXP_EOL_S

NT_T    [A-Z]
T_T     [a-z]
GOES_T  "-->"
SEMI_T  ";"
OR_T    "|"
EOL_T   "\n"

%%

<INITIAL>{NT_T}             {BEGIN PROD_S; return NT;}

<PROD_S>{GOES_T}            {BEGIN PBODY_S; return GOES;}

<PBODY_S>{NT_T}             {BEGIN RULE_S; return NT;}
<PBODY_S>{T_T}              {BEGIN RULE_S; return T; }
<PBODY_S>{EOL_T}            {BEGIN RULE_S; return EOL; }

<RULE_S>{NT_T}              {return NT;}
<RULE_S>{T_T}               {return T;}
<RULE_S>{EOL_T}             {BEGIN PBODY_MORE_S; return EOL; }

<PBODY_MORE_S>{OR_T}        {BEGIN RULE_S; return OR; }
<PBODY_MORE_S>{SEMI_T}      {BEGIN EXP_EOL_S; return SEMI; }

<EXP_EOL_S>{EOL_T}          {BEGIN PLIST_MORE_S; return EOL; }

<PLIST_MORE_S>{NT_T}        {BEGIN PROD_S; return NT; }

{NT_T}                      {return NT;}
{T_T}                       {return T;}
{GOES_T}                    {return GOES;}
{SEMI_T}                    {return SEMI;}
{OR_T}                      {return OR;}
{EOL_T}                     {lineno++;}
.                           ;

%%
