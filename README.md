# Informe de Procesadores de Lenguaje
## Estructura del proyecto
En este repositorio los archivos se organizan siguiendo el siguiente esquema:
* _src/_. Es donde se encuentra el código fuente del documento LATEX, es decir, todos aquellos archivos con extensión _.tex_
* _res/_. Aquí se encuentran todos los recursos que vayan a ser utilizados por el documento LATEX:
	* _res/pics_. Aquí se alojan las fotos o figuras que se mostrarán en el informe.
	* _res/lst_. Todos los códigos fuente de nuestro lenguaje deben ubicarse en esta carpeta (_listados_).
* _doc/_. Aquí se encuentra el archivo PDF compilado por LATEX.
* _refs/_. Todas las referencias bibliográficas se almacenan en un fichero _.bib_ que aloja todas las citas que hagamos en nuestro documento como si se tratase de una base de datos con todas las fuentes que utilicemos en el desarrollo de este documento.

## ¿Cómo hacer commits?
En primer lugar debe crearse una rama propia donde se harán los commits de cada uno de los autores del documento. Cada autor hará sobre su rama personal los commits que considere oportunos.

Cuando los cambios hayan sido comprobados se mergeará la rama de cada autor con la rama _master_.
