%{
/* lu.l
 *
 * lex input file for luna scanner
 */

#include <stdio.h>
#include "global.h"
#include "rule.h"
int line_no = 1;
int commenteof();
%}

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]

%%

{L}{I}{S}{T}   return(LIST);
{D}{O}    return(DO);
{E}{L}{S}{E}   return(ELSE);
{E}{N}{D}   return(END);
{F}{O}{R}   return(FOR);
{F}{U}{N}{C}{T}{I}{O}{N} return(FUNCTION);
{R}{E}{T}{U}{R}{N} return(RETURN);
{I}{F}    return(IF);
{I}{N}    return(IN);
{M}{A}{I}{N}  return(MAIN);
{T}{H}{E}{N}   return(THEN);
{W}{H}{I}{L}{E} return(WHILE);
{I}{N}{T} return(INT);
{D}{O}{U}{B}{L}{E} return(DOUBLE);
{B}{O}{O}{L} return(BOOL);
{T}{R}{U}{E} return(TRUE);
{F}{A}{L}{S}{E} return(FALSE);
[a-zA-Z]([a-zA-Z0-9])*  return(IDENTIFIER);

"="    return(ASSIGNMENT);
":"    return(COLON);
","    return(COMMA);
[0-9]+    return(DIGSEQ);
"=="    return(EQUAL);
">="    return(GE);
">"    return(GT);
"["    return(LBRAC);
"<="    return(LE);
"("    return(LPAREN);
"<"    return(LT);
"-"    return(MINUS);
"!="    return(NOTEQUAL);
"+"    return(PLUS);
"]"    return(RBRAC);
[0-9]+"."[0-9]+   return(REALNUMBER);
")"    return(RPAREN);
";"    return(SEMICOLON);
"/"    return(SLASH);
"*"    return(STAR);
"++"   return(INCO);
"--"   return(DECO);

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
}

"(*"   |
"{"    { register int c;
     while ((c = input()))
     {
      if (c == '}')
       break;
      else if (c == '*')
      {
       if ((c = input()) == ')')
        break;
       else
        unput (c);
      }
      else if (c == '\n')
       line_no++;
      else if (c == 0)
       commenteof();
     }
    }

[ \t\f]    ;

\n  line_no++;

.   { fprintf (stderr,
      "'%c' (0%o): illegal charcter at line %d\n",
      yytext[0], yytext[0], line_no);
    }

%%

int commenteof()
{
  fprintf (stderr, "unexpected EOF inside comment at line %d\n",
    line_no);
  exit (1);
}

int openFile(int argc, char** argv){
  if (argc != 2){
    printf("the input file format is not correct!\n");
    exit(1);
  }

  yyin = fopen(argv[1], "r");
  if (!yyin){
    printf("open input file failed!\n");
    exit(1);
  }
  return 0;
}

int yywrap ()
{
 return (1);
}
