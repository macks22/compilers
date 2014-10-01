%{
#include "tokens.h"
int lineno = 1;
%}

NT_TOKEN    [A-Z]
T_TOKEN     [a-z]
GOES_TOKEN  "-->"
SEMI_TOKEN  ";"
OR_TOKEN    "|"
EOL_TOKEN   "\n"

%%

{NT_TOKEN}                  {return NT;}
{T_TOKEN}                   {return T;}
{GOES_TOKEN}                {return GOES;}
{SEMI_TOKEN}                {return SEMI;}
{OR_TOKEN}                  {return OR;}
{EOL_TOKEN}                 {lineno++;
                             return EOL;}
.                           ;

%%
