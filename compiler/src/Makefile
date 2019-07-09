all:
					mkdir build
					$(MAKE) bison
					$(MAKE) flex #$(F)
					$(MAKE) compile

bison:
					bison -d -v -t flex-bison/wic.y
					mv wic.tab.* build

flex:
					flex flex-bison/wic.l
					mv lex.yy.* build

compile:
					#gcc -o wic build/lex.yy.c build/wic.tab.c -lfl -lm
					/usr/bin/g++ -std=gnu++11 -c build/wic.tab.c build/lex.yy.c
					mv *.o build
					ar rvs include/libwic.a build/wic.tab.o build/lex.yy.o

					/usr/bin/g++ -std=gnu++11 -Wall -Wextra -g -o wic \
					Main.cpp include/libwic.a \
					symbol-table/SymbolTable.cpp \
					code-generator/CodeGenerator.cpp \
					ast/AbstractSyntaxTree.cpp \
					ast/node/ASTNode.cpp  \
					ast/node/node-subtypes/symbol-table-node/ASTSymbolTableNode.cpp \
					ast/node/node-subtypes/operator-node/ASTOperatorNode.cpp \
					ast/node/node-subtypes/operator-node/ASTArithmeticNode.cpp \
					ast/node/node-subtypes/operator-node/ASTRelationalNode.cpp \
					ast/node/node-subtypes/leaf-node/ASTLeafNode.cpp \
					ast/node/node-subtypes/clause-node/ASTClauseNode.cpp \
					error-manager/ErrorManager.cpp \
					ast/node/node-subtypes/structural-node/ASTStructuralNode.cpp \

					#mv *.a *.o build

clean:
					rm -rf build wic *.s wic.output *.o
