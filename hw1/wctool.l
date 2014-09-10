%{
    int charcnt = 0, wordcnt = 0, linecnt = 0;
%}

word    [^ \t\n]+

%%

{word}          {wordcnt++; charcnt += strlen(yytext); }
[\n]            {charcnt++; linecnt++; }
.               {charcnt++; }

%%

main() {
    yylex();
    printf("Characters: %d, Words: %d, Lines: %d\n",
           charcnt, wordcnt, linecnt);
}
