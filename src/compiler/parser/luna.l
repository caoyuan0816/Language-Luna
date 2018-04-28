%{
/* lu.l
 *
 * lex input file for luna scanner
 */

#include <stdio.h>
#include "common.h"
#include "tokens.h"

int line_no = 1;
int commenteof();
int makeThisNode(int type);
%}

A [a]
B [b]
C [c]
D [d]
E [e]
F [f]
G [g]
H [h]
I [i]
J [j]
K [k]
L [l]
M [m]
N [n]
O [o]
P [p]
Q [q]
R [r]
S [s]
T [t]
U [u]
V [v]
W [w]
X [x]
Y [y]
Z [z]

%%

{L}{I}{S}{T}   return makeThisNode(LIST);
{D}{O}    return makeThisNode(DO);
{E}{L}{S}{E}   return makeThisNode(ELSE);
{E}{N}{D}   return makeThisNode(END);
{F}{O}{R}   return makeThisNode(FOR);
{F}{U}{N}{C}{T}{I}{O}{N} return makeThisNode(FUNCTION);
{R}{E}{T}{U}{R}{N} return makeThisNode(RETURN);
{I}{F}    return makeThisNode(IF);
{I}{N}    return makeThisNode(IN);
{M}{A}{I}{N}  return makeThisNode(MAIN);//TODO: maybe should be modified
{T}{H}{E}{N}   return makeThisNode(THEN);
{W}{H}{I}{L}{E} return makeThisNode(WHILE);
{I}{N}{T} return makeThisNode(INT);
{D}{O}{U}{B}{L}{E} return makeThisNode(DOUBLE);
{B}{O}{O}{L} return makeThisNode(BOOL);
{T}{R}{U}{E} return makeThisNode(TRUE);
{F}{A}{L}{S}{E} return makeThisNode(FALSE);
[a-zA-Z]([a-zA-Z0-9])*  return makeThisNode(IDENTIFIER);

"="    return makeThisNode(ASSIGNMENT);
":"    return makeThisNode(COLON);
","    return makeThisNode(COMMA);
[0-9]+    return makeThisNode(INTNUM);
"=="    return makeThisNode(EQUAL);
">="    return makeThisNode(GE);
">"    return makeThisNode(GT);
"["    return makeThisNode(LBRAC);
"<="    return makeThisNode(LE);
"("    return makeThisNode(LPAREN);
"<"    return makeThisNode(LT);
"-"    return makeThisNode(MINUS);
"!="    return makeThisNode(NOTEQUAL);
"+"    return makeThisNode(PLUS);
"]"    return makeThisNode(RBRAC);
[0-9]+"."[0-9]+   return makeThisNode(REALNUMBER);
")"    return makeThisNode(RPAREN);
"/"    return makeThisNode(SLASH);
"*"    return makeThisNode(STAR);
"++"   return makeThisNode(INCO);
"--"   return makeThisNode(DECO);

"/*" {
  register int c;
  while ((c=input())){
    if(c=='*'){
      if((c=input())=='/')
        break;
      else
        unput(c);
    } else if (c=='\n')
      line_no++;
    else if (c == 0)
      commenteof();
  }
}

"//" {
  register int c;
  while ((c=input())!='\n'){
    if (c==0) break;
  }
  line_no++;
}

[ \t\f]    ;

\n  line_no++;

.   { fprintf (stderr,
      "'%c' (0%o): illegal charcter at line %d\n",
      yytext[0], yytext[0], line_no);
    }

%%

int makeThisNode(int type){
  yylval = makeNewNode();
  yylval->line_no = line_no;

  yylval->literal = (char *)malloc(sizeof(char) * strlen(yytext) + 1);
  strcpy(yylval->literal, yytext);

  return type;
}

int commenteof()
{
  fprintf (stderr, "unexpected EOF inside comment at line %d\n",
    line_no);
  exit (1);
}

int openFile(int argc, char** argv){

  yyin = fopen(argv[1], "r");
  if (!yyin){
    printf("Output file cannot be opened.\nPlease check your file path.\n");
    exit(1);
  }
  return 0;
}

int yywrap ()
{
 return (1);
}
