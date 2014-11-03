%{
#include <stdio.h>
#include <stdlib.h>
#include "uncool.tab.h"
int linect = 1;
%}
%%
Bool		{return BOOL_T;}
class		{return CLASS_T;}
else		{return ELSE_T;}
false		{return FALSE_T;}
fi		{return FI_T;}
if		{return IF_T;}
in		{return IN_T;}
in_int		{return IN_INT;}
Int		{return INT_T;}
isvoid		{return ISVOID_T;}
let		{return LET_T;}
loop		{return LOOP_T;}
new		{return NEW_T;}
not		{return NOT_T;}
out_int		{return OUT_INT;}
out_string	{return OUT_STRING;}
pool		{return POOL_T;}
String		{return STRING_T;}
tel		{return TEL_T;}
then		{return THEN_T;}
true		{return TRUE_T;}
while		{return WHILE_T;}
\<		{return LT;}
\=		{return EQ;}
\<\=		{return LE;}
\>\=		{return GE;}
\>		{return GT;}
\<\>		{return NE;}
\<\-		{return ASSIGN;}
\+		{return '+'; }
\-		{return '-'; }
\*		{return '*'; }
\~		{return '~'; }
\.		{return '.'; }
\,		{return ','; }
\{		{return '{';}
\}		{return '}';}
\(		{return '(';}
\)		{return ')';}
\[		{return '[';}
\]		{return ']';}
\;		{return ';';}
\:		{return ':';}
[a-z][A-Za-z0-9_]*	{return ID;}
[A-Z][A-Za-z0-9_]*	{return TYPE;}
[0-9]*		{return INT_CONST;}
\"[^"]*\"	{return STRING_CONST;}
\-\-.*		;
[ \t]		;
[\n]		linect++;
.		{printf("Illegal character: %s\n",yytext); }	
%%
