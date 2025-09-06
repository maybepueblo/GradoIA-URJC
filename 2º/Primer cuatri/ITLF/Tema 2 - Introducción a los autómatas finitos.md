**Objetivo** --> Estudiar el mecanismo idóneo para resolver problemas automáticamente. En un problema concreto, hemos de concebir un programa que dados unos datos, nos dé la respuesta correcta (por ahora sólo serán problemas de "Si" o "No")

#### El problema

Un autómata se conforma por los siguientes elementos:
- **Cinta de entrada** para introducir datos
- **"Programa"**
- **Memoria** para los datos

##### Cinta de entrada 

Se almacenan elementos de un alfabeto. Son controladas por el "programa". Este va leyendo de la cinta de izquierda a derecha un elemento cada vez. Una vez se lee un elemento, ya no se vuelve a leer

##### El programa

Se considera en su forma abstracta, en forma de estados y una función de transición:

- Definimos el comportamiento en función del estado que esté el automata, parte de la memoria y el símbolo leído en la cinta.
- El estado al final de la ejecución del programa da la respuesta del autómata.

Debe de admitir un grafo el programa (aunque sea infinito).

##### Memoria

Contiene información pero asumimos que viene de un alfabeto finito (es decir, está limitado).
- Lee y almacena
- Dependiendo de la información a leer y a almacenar, definimos el autómata.

#### Autómata

