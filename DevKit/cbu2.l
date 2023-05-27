%{
#include <string.h>
#include "cbu2.h"
#define MAXSYM 100
#define MAXSYMLEN 20
char symtbl[MAXSYM][MAXSYMLEN];
int lineno = 1;
int insertsym(char *);
int maxsym = 0;
char s[MAXSYMLEN];
int temp;
%}

sp          [ \t]
ws          {sp}+
nl          \n
eletter     [A-Za-z]
hletter     [\xb0-\xfe][\xa0-\xfe]
letter      ({eletter}|{hletter})
digit       [0-9]
id          {letter}({letter}|{digit})*
%%
{ws}        {/* do nothing */}
{nl}        {lineno++; }
\+          {return(ADD); }
더하기      {return(ADD); }
\-          {return(SUB); }
빼기        {return(SUB); }
\*          {return(MUL); }
곱하기      {return(MUL); }
\/          {return(DIV); }
나누기      {return(DIV); }
:=          {return(ASSGN); }
;           {return(STMTEND); }
시작        {return(START); }
끝          {return(END); }
if          {return(IF); }
else        {return(ELSE); }
\(          {return(LPAREN); }
\)          {return(RPAREN); }
\<          {return(LT); }
\>          {return(GT); }
\<\=        {return(LTE); }
\>\=        {return(GTE); }
\=\=        {return(EQ); }
\!\=        {return(NEQ); }
\{          {return(LBRACE); }
\}          {return(RBRACE); }
{id}        {temp=insertsym(yytext); yylval=MakeNode(ID, temp); return(ID);}
-?{digit}+  {sscanf_s(yytext, "%d", &temp, sizeof(temp)); yylval=MakeNode(NUM, temp); return(NUM);}
.           {printf("invalid token %s\n", yytext); }
%%

int insertsym(s)
char *s;
{
    int i;

    for (i = 0; i < maxsym; i++) {
        if (strcmp(s, symtbl[i]) == 0) return (i);
    }
    if (i < MAXSYM - 1) {
        strcpy_s(symtbl[maxsym], sizeof(symtbl), s);
        maxsym++;
        return (maxsym - 1);
    }
    else
    {
        printf("symbol table overflow\n");
    }
    return (0);
}

int yywrap() {
    return 1;
}
