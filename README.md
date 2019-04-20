# Procesadores de Lenguaje
Este repositorio contiene la documentación y código necesarios para el correcto desarrollo e implementación de un compilador del lenguaje que hemos denominado _WiC_.

## Estructura del proyecto

Este repositorio se estructura en los siquientes directorios:
  * __compiler.__ Esta carpeta contiene el código fuente del compilador _WiC_.
  * __report.__ Contiene la documentación del compilador desarrollado.

## ¿Cómo hacer commits?
En primer lugar debe clonarse el proyecto en un directorio de nuestra elección:
```
git clone https://github.com/david00medina/informe-pl.git
```

Debe crearse una rama propia donde se harán los commits de cada uno de los autores del documento:
```
git branch mi_rama
git checkout mi_rama
git push --set-upstream origin mi_rama
```

Cada autor hará sobre su rama personal los commits que considere oportunos ejecutando estos comandos desde el directorio raíz del proyecto:
```
git add *
git commit -m "Mensaje del commit"
git push
```

Cuando los cambios hayan sido comprobados se mergeará la rama de cada autor con la rama _master_.
