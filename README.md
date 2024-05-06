# TAREA-2


---
### Buscador de peliculas
**Descripcion**
Este sistema permite que el usuario poder cargar un archivo `.csv` el cual contiene datos de peliculas y filtrar las peliculas mediante los datos. Los criterios de estos filtros son **ID**, **género**, **director**, **década**, **rango de calificaciones**, **década y género**. Al filtrar por estos datos se mostrara en pantalla el nombre de la pelicula y algunos de los datos correspondientes a la pelicula.

### Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Usa el link de abajo que te llevará directamente a la aplicación
3. [Repl.it](https://replit.com/join/ctgbhfqkwi-oscarruizf).
4. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Carga el archivo con peliculas correctamente.
- Hace busqueda de una pelicula segun la **ID** de la pelicula.
- Genera una busqueda de las diferentes peliculas de cierto/a **genero**, **decada**, **director** y **decada y genero**.
- Sale del programa correctamente.

### Problemas conocidos:
- Si al momento que se solicita al usuario ingresar un numero para hacer una busqueda mediante una decada. Si el usuario ingresa una letra se produce un error en el programa. 

### A mejorar:
- El poder preguntar al usuario si quiere buscar nuevamente mediante el criterio en el que estaba y asi no salir al menu principal.

### Ejemplo de uso:

  **Paso 1: Cargar peliculas**

Se comienza cargando las peliculas que se encuentras en el archivo.

````c
Ingrese su opción: 1
ID: tt0068646, Título: The Godfather, Director(es): [Francis Ford Coppola], Año: 1972
.........
ID: tt0040982, Título: You Gotta Stay Happy, Director(es): [H.C. Potter, Walter Lantz], Año: 1948
Presione una tecla para continuar...
````
El sistema al ingresar la opción 1 carga todas las peliculas del archivo y muestra todas las peliculas que fueron cargadas y luego de ese proceso se le pide al usuario presionar cualquier tecla y asi volvera al menu de opciones.


**Paso 2: Buscar por id**

Se genera una busqueda de una pelicula en especifico segun su ID.
````c
Ingrese su opción: 2
Ingrese el id de la película: tt0068646
Título: The Godfather, Director(es): [Francis Ford Coppola], Año: 1972
Presione una tecla para continuar...
````
Y muestra en pantalla la pelicula con algunos datos de esta.


**Paso 3: Buscar por director**

Se genera una busqueda de todas las peliculas del director ingresado.
````c
Ingrese su opción: 3
Ingrese el director que desea buscar: Francis Ford Coppola
Título: The Godfather, Director(es): [Francis Ford Coppola], Año:1972
Título: The Godfather Part II, Director(es): [Francis Ford Coppola], Año:1974
Título: Apocalypse Now, Director(es): [Francis Ford Coppola], Año:1979
Título: The Godfather Part III, Director(es): [Francis Ford Coppola], Año:1990
Título: The Conversation, Director(es): [Francis Ford Coppola], Año:1974
Título: Tucker: The Man and His Dream, Director(es): [Francis Ford Coppola], Año:1988
Título: The Rainmaker, Director(es): [Francis Ford Coppola], Año:1997
Título: Rumble Fish, Director(es): [Francis Ford Coppola], Año:1983
Título: The Outsiders, Director(es): [Francis Ford Coppola], Año:1983
Presione una tecla para continuar...
````
Se muestra en pantalla las peliculas que a echo ese director.


**Paso 4: Buscar por género**

Se genera una busqueda de diferentes peliculas segun el genero que ingrese el usuario.
````c
Ingrese su opción: 4
Ingrese el género que desea buscar: War
Título: Casablanca, Director(es): [Michael Curtiz], Año: 1942, Generos: [Drama, Romance, War]
...
Título: A Bridge Too Far, Director(es): [Richard Attenborough], Año: 1977, Generos: [Drama, History, War]
Presione una tecla para continuar...
````
Se muestran en pantalla las peliculas que pertenezcan a ese genero.


**Paso 5: Buscar por década**

Se le pide al usuario ingresar una decada, como en el ejemplo que se muestra y se busca las peliculas estrenadas en esa decada.
````c
Ingrese su opción: 5
Ingrese la década a buscar (ejemplo: 1980): 1970
Películas de la década de 1970:
Título: The Godfather, Director(es): [Francis Ford Coppola], Año: 1972
...
Título: Charlotte's Web, Director(es): [Charles Nichols, Iwao Takamoto], Año: 1973
Presione una tecla para continuar...
````
Se muestran todas las peliculas publicadas en la decada.


**Paso 6: Buscar por rango de calificaciones**

Se le dan opciones de rangos al usuario los cuales son rangos de calificaciones.
````c
Ingrese su opción: 6
Elija el rango de calificaciones a buscar:
1) 6.0-6.4
2) 6.5-6.9
3) 7.0-7.4
4) 7.5-7.9
5) 8.0-8.4
6) 8.5-8.9
7) 9.0-9.4
Ingrese su respuesta: 7
Título: The Godfather, Director(es): [Francis Ford Coppola], Año: 1972, Rating: 9.20
Título: 12 Angry Men, Director(es): [Sidney Lumet], Año: 1957, Rating: 9.00
Título: Schindler's List, Director(es): [Steven Spielberg], Año: 1993, Rating: 9.00
Título: The Godfather Part II, Director(es): [Francis Ford Coppola], Año: 1974, Rating: 9.00
Título: The Shawshank Redemption, Director(es): [Frank Darabont], Año: 1994, Rating: 9.30
Título: The Lord of the Rings: The Return of the King, Director(es): [Peter Jackson], Año: 2003, Rating: 9.00
Título: The Dark Knight, Director(es): [Christopher Nolan], Año: 2008, Rating: 9.00
Presione una tecla para continuar...
````
Y segun lo que ingreso el rango que escogio el usuario se mostraran las peliculas con ese rango de calificación.


**Paso 7:  Buscar por década y género**

En este paso se le pide al usuario ingresar una decada y un genero y se buscaran las peliculas las cuales hayan sido publicadas en esa decada y que sean de el genero ingresado.
````c
Ingrese su opción: 7
Ingrese la decada de la película (ejemplo: 1980): 1990
Ingrese el género de la película: Drama
ID: tt0110912, Título: Pulp Fiction, Director(es): [Quentin Tarantino], Año: 1994, Generos: [Crime, Drama]
...
ID: tt0119256, Título: Sydney, Director(es): [Paul Thomas Anderson], Año: 1996, Generos: [Crime, Drama]
Presione una tecla para continuar...
````
Y luego se muestra en pantalla todas las peliculas que hayan pasado el filtro de la decada y el genero solicitado.


### Contribuciones

## Milovan Fuentes:
- Diseño de la interfaz.
- Diseño funciones.
- Etc.
- Desarrollo de partes del programa.
- **Auto-evaluación**: 3 (Aporte excelente)

## Oscar Ruiz:
- Diseño de la interfaz.
- Diseño funciones.
- Etc.
- Desarrollo de partes del programa.
- **Auto-evaluación**: 3 (Aporte excelente)
