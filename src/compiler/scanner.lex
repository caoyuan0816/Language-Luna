%{
    #include <iostream>
    using namespace std;
    #define YY_DECL extern "C" int yylex()
%}
%%
true|false cout << "BOOL" << endl;
[+-]?[0-9]+ cout << "INT" << endl;
([+-]?[0-9])?.[0-9]+ cout << "DOUBLE" << endl;
[a-zA-Z_]+[a-zA-Z_0-9]* cout << "VAR" << endl;
\+ cout << "PLS" << endl;
\- cout << "SUB" << endl;
\* cout << "MUL" << endl;
\/ cout << "DIV" << endl;
= cout << "EQL" << endl;
== cout << "CMP_EQL" << endl;
\< cout << "CMP_LT" << endl;
\> cout << "CMP_BG" << endl;
\<= cout << "CMP_LT_EQL" << endl;
\>= cout << "CMP_BG_EQL" << endl;
%%
