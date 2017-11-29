CC = gcc -g
LEX = flex
YACC = bison -y
OBJECTS = main.o y.tab.o lex.yy.o tree.o check.o

turing : $(OBJECTS)
		$(CC) -o turing $(OBJECTS)

lex.yy.c : scan.l
		$(LEX) scan.l
lex.yy.o : lex.yy.c

y.tab.o : y.tab.c tree.h
y.tab.c : project3.y
		$(YACC) project3.y
y.tab.h : project3.y
		$(YACC) -d project3.y

scan : scan.o lex.yy.o
		$(CC) -o scan scan.o lex.yy.o
scan.o : scan.c

tree.o : tree.c tree.h

main.o : main.c tree.h

check.o : check.c tree.h ST.h y.tab.h

clean :
		rm lex.yy.c y.tab.c *.o
		rm turing