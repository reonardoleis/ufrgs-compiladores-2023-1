etapa7: y.tab.c lex.yy.c
	gcc -o etapa7 lex.yy.c
	
y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm lex.yy.c y.tab.c y.tab.h etapa7

test: 
	export DEBUG=1 && make clean && make && ./etapa7 input.txt out__.txt && export DEBUG=0

test-nd:
	export DEBUG=0 && make clean && make && ./etapa7 input.txt out__.txt && export DEBUG=0

run:
	make clean && make && ./etapa7 input2.txt any && gcc out.s && ./a.out