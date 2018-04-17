#
FLEX=flex
FLEXFLAGS=
BISONFLAGS=-d
BISON=bison
COMPILER_DIST=luna
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-g -Wall
CVS=cvs

COMPILER_HEADER=global.h

COMPILER_SOURCE=global.h\
		global.c\
		lu.l\
		lu.y\
		rule.c\
		lex.yy.c

COMPILER_OBJS=  lex.yy.o\
		rule.o

COMPILER_AUTOFILES=     y.tab.c\
			lex.yy.c\
			rule.c\
			y.tab.h\
			rule.h

.SUFFIXES:.c

all: $(COMPILER_DIST)

%.o:%.c $(COMPILER_HEADER)
	$(CC) $(CFLAGS) -c $<

lex.yy.c: lu.l rule.c
	$(FLEX) $(FLEXFLAGS) lu.l

rule.c: lu.y
	$(BISON) $(BISONFLAGS) -o rule.c $<

$(COMPILER_DIST):$(COMPILER_OBJS) $(COMPILER_HEADER)
	gcc -o $(COMPILER_DIST) $(LDFLAGS) $(COMPILER_OBJS)

clean:
	rm -f *.o
	rm -f $(COMPILER_DIST)
	rm -f $(COMPILER_AUTOFILES)
