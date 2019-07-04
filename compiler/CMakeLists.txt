cmake_minimum_required(VERSION 3.13)
project("WiC - Compiler")
set (CMAKE_CXX_STANDARD 11)

add_custom_target(Makefile COMMAND make all
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# Add main.cpp file of project root directory as source file
#set(SOURCE_FILES src/Main.cpp libwic.a
#        src/ast/AbstractSyntaxTree.cpp src/ast/node/ASTNode.cpp
#        src/ast/node/node-subtypes/operator-node/ASTOperatorNode.cpp
#        src/ast/node/node-subtypes/operator-node/ASTArithmeticNode.cpp
#        src/ast/node/node-subtypes/operator-node/ASTRelationalNode.cpp
#        )
#
## Add executable target with source files listed in SOURCE_FILES variable
#add_executable(simple_example ${SOURCE_FILES})