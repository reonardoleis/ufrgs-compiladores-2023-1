etapa1: y.tab.c lex.yy.c
	gcc -o etapa3 lex.yy.c
	
y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c y.tab.c y.tab.h etapa3