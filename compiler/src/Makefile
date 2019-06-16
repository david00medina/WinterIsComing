# Makefile basico para no andar repitiendo comandos para generar,
# compilar y ejecutar. A ampliar para testear y en siguientes fases.

# make milex	[genera] lexico desde milex.l
# make F=n.x	[genera] y ejecuta lexico sobre n.x; via stdin: make<n.x

all:
					mkdir build
					$(MAKE) bison
					$(MAKE) flex #$(F)
					$(MAKE) compile

bison:
					bison -d flex-bison/wic.y
					mv wic.tab.* build

flex:
					flex flex-bison/wic.l
					mv lex.yy.* build

compile:
					#gcc -o wic build/lex.yy.c build/wic.tab.c -lfl -lm
					g++ -std=gnu++11 -c build/wic.tab.c build/lex.yy.c
					mv *.o build
					ar rvs build/wic.a build/wic.tab.o build/lex.yy.o

					g++ -std=gnu++11 -Wall -Wextra Main.cpp build/wic.a symbol-table/SymbolTable.cpp \
					code-generator/CodeGenerator.cpp ast/AbstractSyntaxTree.cpp ast/nodes/ASTNode.cpp  \
					ast/nodes/ASTSymbolTableNode.cpp ast/nodes/ASTOperatorNode.cpp ast/nodes/ASTLeafNode.cpp -o wic

					#mv *.a *.o build

clean:
					rm -rf build wic christian.s

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
