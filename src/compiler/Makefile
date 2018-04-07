all: scanner clean

scanner:
	flex scanner.lex
	g++ lex.yy.c -o scanner -lfl

clean:
	rm lex.yy.c
