# SER502-Spring2018-Team4

## Team Members
- @baozelin, Zelin Bao
- @caoyuan0816, Yuan Cao
- @yiruhu, Yiru Hu 
- @lanzhige, Zhang Lei

## Implement plan
Zelin Bao: bytecode generator, help documents and testing<br />
Yuan Cao: interpreter and bash scripts<br />
Yiru Hu: bytecode generator, help documents and testing<br />
Lei Zhang: scanner, parser and cmake files

## System Requirement
## Platform
- Linux (native)

## Tools
[Doxygen](https://en.wikipedia.org/wiki/Doxygen), a tool for writing software reference documentation. The documentation is written within code, and is thus relatively easy to keep up to date. Doxygen can cross reference documentation and code, so that the reader of a document can easily refer to the actual code. <br />
We use _doxygen_ to comments our code and create a documentation.

[CMake](https://cmake.org/)  is an open-source, cross-platform family of tools designed to build, test and package software. CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.<br />
We use CMake to generate the makefiles.

[Flex](https://www.gnu.org/software/flex/ ) is a fast lexical analyser generator. It is a tool for generating programs that perform pattern-matching on text. Flex is a free (but non-GNU) implementation of the original Unix lex program.<br />
We use bison to  convert a sequence of characters into a sequence of tokens.

[Bison](https://www.gnu.org/software/bison/) is a general-purpose parser generator that converts an annotated context-free grammar into a deterministic LR or generalized LR (GLR) parser employing LALR(1) parser tables. Bison is upward compatible with Yacc: all properly-written Yacc grammars ought to work with Bison with no change. <br />
We use bison to  analyze a sequence of tokens to determine its grammatical structure.

[valgrind](http://valgrind.org/) is an instrumentation framework for building dynamic analysis tools. There are Valgrind tools that can automatically detect many memory management and threading bugs, and profile your programs in detail. You can also use Valgrind to build new tools. <br />
(todo ..descirpt ..)

## Install Luna
-  Download SER502-Spring2018-Team4-master.zip from Github
   ~$ wget https://github.com/lanzhige/SER502-Spring2018-Team4/archive/master.zip
-  ~$ tar xvf master.tar.gz 
-  Make sure your current dir is `.../SER502-Spring2018-Team4/src/interpreter`
- ~$ ./build.sh

## Build and Run Directions

## YouTube Video Link

## Language Luna
Luna is a lightweight, static typing, lua-like programming language. Luna provide a Flex and Bison based compiler and a stack based interpreter which called `lunac` and `luna`.

## Grammar 
A means 0 or more As, and [A] means an optional A
program ::= {functiondef} "main" '(' [var ',' var] ')' block "end"
block ::= {stat} [retstat]
stat ::= ';' |
         var '=' expr |
         var '=' list_expr|
         id '=' expr |
         id unary_op |
         functioncall |
         "do" block "end" |
         "while" '(' exp ')' "do" block "end" |
         "if" '(' exp ')' block ["else" block] "end" |
         "for" id "in" id "do" block "end" |
         "for" id "in" list_expr "do" block "end" |
         "for" id '=' num ',' num ',' num "do" block "end
retstat ::= "return" id
var ::= type id
functioncall ::= id args
args ::= '(' [explist] ')'
explist ::= expr | expr ',' explist
exp ::= "false" | "true" | expr boolop expr
expr ::= term {expr_op term} | functioncall
list_expr ::= '[' [num] {',' num} ']'
term ::= num {term_op num}
functiondef ::= type "function" funcbody
funcbody ::= '(' [parlist] ')' block "end"
parlist ::= '...' | type id {',' type id}
expr_op ::= '+' | '-'
term_op ::= '*' | '/'
unary_op ::= '++' | '--'
boolop ::= '<' | '<=' | '>' | ">=" | "==" | "!="
type ::= "bool" | "int" | "double" | "list"
num ::= ['-'] digit{digit}
floatnum ::= num | num '.' digit{digit}
digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
id ::= [a-z|A-Z]

## Byte Code
`1.  
2. assignment operation  
ldv  
ldc  
asn  
dup  
3. arithmetic operation  
add  
sub  
mul  
div  
4. logic operation  
and   
or  
not  
jmp  
jz  
halt  
ret`  




## How to write a Luna program
Here are some examples to start Luna programming:
```
//return sum of two values
function int sum(int x, int y)
    int z = 0
    z = x + y
    return z
end

```
