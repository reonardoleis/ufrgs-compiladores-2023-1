etapa4: y.tab.c lex.yy.c
	gcc -o etapa4 lex.yy.c
	
y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c y.tab.c y.tab.h etapa4