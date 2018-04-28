# SER502-Spring2018-Team4

## Team Members
- [@baozelin](https://github.com/caoyuan0816), Zelin Bao
- [@caoyuan0816](https://github.com/yiruhu), Yuan Cao
- [@yiruhu](https://github.com/lanzhige), Yiru Hu 
- [@lanzhige](https://github.com/baozelin), Zhang Lei

## YouTube Video Link

## Language Luna
Luna is a lightweight, static typing, lua-like programming language. Luna provide a Flex and Bison based compiler and a stack based interpreter which called `lunac` and `luna`.

## Compile and Install Luna
### Platform
- Linux
- MacOS
- Windows (git-bash)

### Prerequierment
- cmake (with c & c++ compiler support) (with c++11 feature)
- flex
- bison
- git (to clone project, you can also download project from [here](https://github.com/lanzhige/SER502-Spring2018-Team4/archive/master.zip))

### Fetch Project Source Code
- `git clone ://github.com/lanzhige/SER502-Spring2018-Team4.git`
- `cd SER502-Spring2017-Team10`

### Compile
- `./build.sh`, if the build process is failed, there will be an error message in the screen.

### Install
- `cd build && sudo make install && cd ..`, now you can use `luna` and `lunac` anywhere.

## Tools We used to Develop Language Luna
[CMake](https://cmake.org/)  is an open-source, cross-platform family of tools designed to build, test and package software. CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.<br />
We use CMake to generate the makefiles.

[Flex](https://www.gnu.org/software/flex/ ) is a fast lexical analyser generator. It is a tool for generating programs that perform pattern-matching on text. Flex is a free (but non-GNU) implementation of the original Unix lex program.<br />
We use bison to  convert a sequence of characters into a sequence of tokens.

[Bison](https://www.gnu.org/software/bison/) is a general-purpose parser generator that converts an annotated context-free grammar into a deterministic LR or generalized LR (GLR) parser employing LALR(1) parser tables. Bison is upward compatible with Yacc: all properly-written Yacc grammars ought to work with Bison with no change. <br />
We use bison to  analyze a sequence of tokens to determine its grammatical structure.

[valgrind](http://valgrind.org/) is an instrumentation framework for building dynamic analysis tools. There are Valgrind tools that can automatically detect many memory management and threading bugs, and profile your programs in detail. You can also use Valgrind to build new tools. <br />
(todo ..descirpt ..)

[Doxygen](https://en.wikipedia.org/wiki/Doxygen), a tool for writing software reference documentation. The documentation is written within code, and is thus relatively easy to keep up to date. Doxygen can cross reference documentation and code, so that the reader of a document can easily refer to the actual code. <br />
We use _doxygen_ to comments our code and create a documentation.

## Language Design
### Grammar 
A means 0 or more As, and [A] means an optional A
```
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
```
### Byte Code
```
1. Assignment Instrction 
LDV  /*Load the variable into stack*/
LDC  /*Load the constant into stack*/
ASN  /*Assignment instruction*/
DUP  /*Duplicate the top item on the stack*/

2. Arithmetic instrction  
ADD  /*Addition*/
SUB  /*Subtraction*/
MUL  /*Multiplication*/
DIV  /*Division*/

3. Compare instruction
GT  /*Greater than*/
GE  /*Greater than or equal to*/
LT  /*Less than*/
LE  /*Less than or equal to*/
EQ  /*Equal to*/
NEQ /*Not equal to*/

4. Jump intrution
JMP  /*Jump to specified number of line*/
JZ  /*Jump if zero*/

5. Output instruction
HALT  /*The stack element is out of the stack and output*/

6. Function call instrction
RET  /*Function call and return*/
CALL /*Call function*/

```

## Examples
### Fibonacci (`./data/fibonacci.lu`)
```
function int fibonacci(int n)
    if (n==1)
        return 1
    end
    if (n==2)
        return 1
    end
    return fibonacci(n-2) + fibonacci(n-1) //Recursion call
end

main()
    int res = fibonacci(3)
    print(res)
end
```
Byte-code will be generated: (lunac data/fibonacci.lu && cat data/fibonacci.luo)
```
fibonacci
LDV n
LDC 1
EQ
JZ 6
LDC 1
RET
LDV n
LDC 2
EQ
JZ 12
LDC 1
RET
LDV n
LDC 2
SUB
CALL fibonacci 1
LDV n
LDC 1
SUB
CALL fibonacci 1
ADD
RET
main
LDC 3
CALL fibonacci 1
ASN res
LDV res
CALL print 1
```
Run the bytecode file by luna virtual machine: (luna data/fibonacci.luo)
```
2
```

## Implementation Plan
Lei Zhang: scanner, parser, AST generating.
Zelin Bao: bytecode generator(for, if, while blocks), testing<br />
Yiru Hu: bytecode generator(others), testing<br />
Yuan Cao: interpreter(stack-based virtual machine) and bash scripts<br />

