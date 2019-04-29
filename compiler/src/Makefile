# Makefile basico para no andar repitiendo comandos para generar,
# compilar y ejecutar. A ampliar para testear y en siguientes fases.

# make milex	[genera] lexico desde milex.l
# make F=n.x	[genera] y ejecuta lexico sobre n.x; via stdin: make<n.x

all:
					$(MAKE) bison
					$(MAKE) flex $(F)
					$(MAKE) compile

bison:
					bison -d wic.y

flex:
					flex wic.l

compile:
					gcc -o wic lex.yy.c wic.tab.c -lfl -lm
					#gcc -c wic.tab.c lex.yy.c
					#ar rvs wic.a wic.tab.o lex.yy.o
					#g++ -std-c++=11 -Wall -Wextra main.cpp wic.a

clean:
					rm wic.tab.* lex.yy.c wic

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
