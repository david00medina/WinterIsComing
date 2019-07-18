all:
					mkdir build
					$(MAKE) bison
					$(MAKE) flex #$(F)
					$(MAKE) compile

bison:
					bison -d -v -t src/flex-bison/wic.y
					mv wic.tab.* src/flex-bison

flex:
					flex src/flex-bison/wic.l
					mv lex.yy.* src/flex-bison

compile:
					#gcc -o wic build/lex.yy.c build/wic.tab.c -lfl -lm
					/usr/bin/g++ -std=gnu++11 -c src/flex-bison/wic.tab.c src/flex-bison/lex.yy.c
					mv *.o build
					ar rvs include/libwic.a build/wic.tab.o build/lex.yy.o

					/usr/bin/g++ -std=gnu++11 -Wall -Wextra -g -o wic \
					src/Main.cpp include/libwic.a \
					src/symbol-table/SymbolTable.cpp \
					src/code-generator/CodeGenerator.cpp \
					src/ast/AbstractSyntaxTree.cpp \
					src/ast/node/ASTNode.cpp  \
					src/ast/node/node-subtypes/symbol-table-node/ASTSymbolTableNode.cpp \
					src/ast/node/node-subtypes/operator-node/ASTOperatorNode.cpp \
					src/ast/node/node-subtypes/operator-node/ASTArithmeticNode.cpp \
					src/ast/node/node-subtypes/operator-node/ASTRelationalNode.cpp \
					src/ast/node/node-subtypes/leaf-node/ASTLeafNode.cpp \
					src/ast/node/node-subtypes/clause-node/ASTClauseNode.cpp \
					src/error-manager/ErrorManager.cpp \
					src/ast/node/node-subtypes/structural-node/ASTStructuralNode.cpp

					mkdir bin
					mv wic bin

					#mv *.a *.o build

clean:
					rm -rf bin build wic *.s wic.output *.o
