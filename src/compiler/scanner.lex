%{
    #include <iostream>
    using namespace std;
    #define YY_DECL extern "C" int yylex()
%}
%%
[+-]?[0-9]+ cout << "INT" << endl;
%%
