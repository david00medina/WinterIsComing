# Makefile basico para no andar repitiendo comandos para generar,
# compilar y ejecutar. A ampliar para testear y en siguientes fases.

# make milex	[genera] lexico desde milex.l
# make F=n.x	[genera] y ejecuta lexico sobre n.x; via stdin: make<n.x

all:
					$(MAKE) bison
					$(MAKE) flex
					$(MAKE) compile
					./wic $(F)

bison: 		wic.y
					bison -d wic.y

flex: 		wic.l
					flex wic.l
					gcc -o wic lex.yy.c -lfl

compile:	wic $(F)
					gcc -o wic wic.tab.c lex.yy.c -lfl

# "No rule to make target" T si no encuentra ni puede crear T.
# Por supuesto, no regenera milex si no es necesario.
#all:
#   $(MAKE) grammar
#   $(MAKE) lex
#   g++ -std=c++11 -Wall -Wextra compiler/grammar.tab.c compiler/lex.yy.c compiler/main.cpp
#   ./a.out < sample_input

#grammar:
#   bison -d compiler/grammar.yytext

#lex:
#   flex compiler/lex.l
