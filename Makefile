etapa4: y.tab.c lex.yy.c
	gcc -o etapa4 lex.yy.c
	
y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c y.tab.c y.tab.h etapa4

test: 
	export DEBUG=1 && make clean && make && ./etapa4 input.txt out__.txt && export DEBUG=0

test-nd:
	export DEBUG=0 && make clean && make && ./etapa4 input.txt out__.txt && export DEBUG=0