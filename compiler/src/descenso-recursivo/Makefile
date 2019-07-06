all:
	mkdir build
	flex -o ./build/lex.yy.c ./FLEX/descenso_recursivo.l 
	gcc ./build/lex.yy.c ./Analizador/main.c -ll -o ./build/descenso.out

clean:
	rm -rf build
