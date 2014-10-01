%{

%}

NT_TOKEN    [A-Z]
T_TOKEN     [a-z]
GOES_TOKEN  "-->"
SEMI_TOKEN  ";"
OR_TOKEN    "|"
EOL_TOKEN   "\n"

%%

{NT_TOKEN}                  {printf("NT ");    }
{T_TOKEN}                   {printf("T ");    }
{GOES_TOKEN}                {printf("GOES "); }
{SEMI_TOKEN}                {printf("SEMI "); }
{OR_TOKEN}                  {printf("OR ");   }
{EOL_TOKEN}                 {printf("EOL\n"); }

%%
