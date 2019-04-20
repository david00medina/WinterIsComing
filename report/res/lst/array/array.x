,.
	En este bloque se declara un array de cada tipo de variable sin asignacion de espacio en memoria
.,

int[] entero
real[] real
char[] string
bool[] booleano

,.
	En este bloque se declara un array de cada tipo con asignacion de espacio en memoria (de tamano 5 cada uno)
.,

int[5] entero5
real[5] real5
char[5] string5
bool[5] booleano5

,.
	En este bloque se declara un array de cada tipo y se instancia cada uno de los valores de los elementos que lo componen
.,

int[] entero2 = new int[2]{ 0, 1}
real[] real2 = new real[2]{0.0, 1.0}
char[] string2_ab = "ab"	..Declaracion con asignacion alternativo al tipo string
char[] string2_cd = new char[2]{'c','d'}
bool[] booleano2 = new bool[2]{true, false}
