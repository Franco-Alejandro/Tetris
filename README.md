# Tetris

One of my first experiences with SDL and C++

_Juego: Tetris, las piezas caen, si se completa una linea se otorgan 10 puntos, cada 100 puntos aumenta la velocidad a la que caen las piezas (se pasa de nivel). Teclas: izquierda, derecha, y abajo para movimiento (flechas), para girar utilice flecha hacia arriba (gira a la derecha) y Z (gira a la izquierda)_

*Recuerde compilar el proyecto en x86, dado que la carpeta .vs no se encuentra en el repositorio es posible que el memory usage sea mas que lo usual (siendo esto ultimo de 60mb aproximadamente)*

Tetris

Para este proyecto decidí utilizar la librería SDL2 para los input, sonido y gráficos dado que al haber trabajado con la misma ya tenía el setup en mi computadora, y conozco sus funciones básicas. 

Para empezar voy a tener una clase denominada “Tetrómino”, la misma clase va a ser abstracta y tiene tres  funciones básicas:

-Devolver una posición

-Rotar a la derecha

-Rotar a la izquierda

Las piezas están definidas en un arreglo bidimensional de 4x4, y cada pieza es una clase HIJA de TETROMINO. 

El arreglo bidimensional (para las piezas: cube,  I, L, espejoL, N, espejoN, y T) estaría lleno por: 0 representando espacios vacíos, 1 para los bloques.

Ejemplo para T:

{0,0,0,0}

{0,0,1,0}

{0,0,1,1}

{0,0,1,0}

T rotada:

{0,0,0,0}

{0,0,0,0}

{0,1,1,1}

{0,0,1,0}

Para trabajar con las rotaciones pertinentes guardamos el estado de rotación en un enum.
Cada objeto va a tener las impresiones de las distintas rotaciones guardadas en un arreglo de 3 dimensiones (excepto el cubo o square porque no tiene rotaciones). La primera dimension es el estado de rotación actual y los otros la posicion en el arreglo de 4x4


En cuanto al tablero, vamos a tener otra clase denominada “board”  que va a:

-	Tener un array de 10x20, de tipo char, que comienza con todas las posiciones LIBRES. A medida que se llena cada cuadro, cambian de estado. (Los estados posibles estan guardados en un enum, estos son libre y ocupado)
-	Contener una función que inicializa el board (llena todo en libre)
-	Contener otra función que GUARDE piezas, es decir, cambia el estado de los cubos a ocupado, dependiendo del Tetrómino (se tiene que llevar un Tetrómino, pero este solo le da el valor en una posición específica para evitar ser cambiado)
-	Una función que libere UNA LINEA del arreglo a medida que se cambian totalmente a OCUPADO y este mismo puede volver a dibujar el tablero bajando las piezas. Puede actuar en conjunto otra función que vea cuantas líneas se deban eliminar y llame a la de liberar UNA LINEA cuando sea necesario 
-	Un método que chequee si un bloque esta vacío o no para poder luego detectar colisiones 
-	También vamos a necesitar métodos de get para los bloques, que simplemente retornen el valor de la posición. Es útil en caso de que se quiera cambiar el color de los bloques almacenados o el array almacene valores respecto a un sprite 
-	Una función q devuelva un boolean que nos permita ver si el movimiento es posible o no utilizando los métodos anteriores para chequear colisiones


Se crearon dos clases para la implementación gráfica. Window y Rect. La primera crea la ventana, la limpia, actualiza la pantalla y toma los input con SDL para cerrar el juego. Solo maneja la ventana e inicialización de procesos de la SDL.
Rect, por otro lado, hereda de window el RENDERIZADOR para no crear otro (solo se puede utilizar un renderizador por ventana), y se encarga de manjear los sprites que seran impresos en la pantalla (cubos, score, background). Los métodos que ambas clases tienen permiten:
-	Cargar imagenes
-	Limpiar pantalla
-	Actualizar pantalla
-	Inicializar SDL y sus componentes
-	Liberar texturas
- Dibjar texturas en una posición
- variables de alto y ancho de la textura, posiciones en pixeles de donde se renderizara la misma

Otra de las clases será nombrada GAME y tendrá todos los datos de board, tetrómino y de rect, y en ella se relacionaran 

Esta clase tendrá:
-	PosX y posY de DONDE cae en el tablero el Tetrómino
-	Una función que pregunte  al principio si la pieza puede entrar en el tablero, para tirar GameOver 
-	Variables como altura de un cubo en pixeles, próximas posiciones del Tetrómino, próximo Tetrómino(y la rotación del mismo)
-	Tiene un objeto board y punteros a los Tetróminos
-	Una función que inicia el juego obteniendo dos piezas y seteando nivel y tiempo de espera
- Una función que se encargará de dibujar los puntos, los cubos, y el tablero.
-	Una función RAND para generar la pieza al azar
- Hay otro método que se encarga de borrar el tetromino actual, y apuntar la referencia a la siguiente pieza
-	La función que dibuja se lleva las texturas y leyendo el board y las piezas para luego renderizarlas
-	Un método  que transforma coordenadas de matriz a coordenadas pixel en el tablero
-	Un contador de nivel y uno de lineas borradas. El puntaje es igual a 100 puntos por nivel y 10 por linea eliminada
- Un metodo que toma los eventos, entonces un switch (con los casos de las teclas presionadas) debe hacer lo pertinente, acelerar la pieza, moverla y rotarla.

Nuestro main inicializa las texturas, los datos de la pantalla, la musica, las variables board y game, y toma el tiempo(SDL_GetTicks();). Tiene un main loop que se encarga de decir cuando el juego ha de guardar la pieza en board y cuando ha de bajar la pieza un  bloque

La SDL nos permite tomar la ventana, y las teclas, entonces con un WHILE podemos decir que: “mientras no se cierre la ventana, el juego continua” 

