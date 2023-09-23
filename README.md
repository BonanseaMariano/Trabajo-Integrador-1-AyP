<p align="center">
  <img src="Logo.png" alt="Logo UNPSJB" style="max-width:20%;"/>
</p>

<br>
Licenciatura en Informática<br>
Sede Puerto Madryn<br>
Algorítmica y Programación</u><br>
Fecha: 29/09/2023<br><br><br>
Trabajo Integrador Nº1<br>
Alumnos:<br>
Andres, Ariel Sebastian.<br>
Bonansea Camaño, Mariano Nicolas.<br>
Cordoba,Tahiel Luis.<br>
Rivero, Lucia Jazmin.<br>


<br>
<br>
<br>
<br>
<br>
<br>
Aclaraciones:<br>

* El Programa se encuentra pensado y probado para un entorno windows, ya que este utiliza la libreria "Windows.h" para poner colores en la terminal.

* El texto azul que dice "//Cheat de numero a adivinar" (en la terminal) esta colocado para facilitar las pruebas (o debugging) del juego aportando la respuesta del numero generado aleatoriamente. El mismo puede ser removido en cualquier momento sin afectar al resto del programa.

* El programa fue construido de manera tal que se pueda alternar ciertos parametros en las constantes definidas modificando sus valores y sin afectar a la jugabilidad (Como la cantidad de jugadores a mostrar en el ranking, digitos del numero, cantidad de intentos, etc.), con el objetvo de poder hacer el juego mas moldeable a ciertas preferencias (por defecto estas corresponden a las consignas del trabajo integrador). 

* Se asume que el usuario colocara el TIPO de dato correspondiente en cada ingreso de datos (el cual se encuentra aclarado en cada caso) solicitado ya que las validaciones pueden romperse si se coloca otro tipo (por ejemplo en el ingreso de la opcion de jugar nuevamente si se selecciona un numero de opcion distinto de 0 o 1 (si o no) la validacion funciona y vuelve a solicitar el ingreso del usuario, pero si este coloca un string o un char la validacion se rompe). 

* En el ingreso del intento del jugador por adivinar el numero no se permite que el numero comience con ceros (00345 por ejemplo), ya que debido al ingreso de enteros por "scanf()" estos no se consideran como digitos, lo que no permite pasar la validacion de colocar un numero de exactamente 5 cifras. Igualmente cabe aclarar que ningun numero a adivinar generado aleatoriamente inicializara con ceros adelante para solventar este inconveniente. 
