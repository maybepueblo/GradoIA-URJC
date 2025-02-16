Ordenador de Von Neumann, simulador de alta importancia para saber cómo es un ordenador que ejecuta todo a nivel máquina sin tener sistema operativo. Son instrucciones de bajo nivel que promueven todo lo que pase posteriormente.
## Ordenador
Formado por varios cpus y varios dispositivos conectados por buses (controlador con parte hardware y software). Teniendo memoria compartida, lo cual es el problema, ya que cuando varios intenten acceder al mismo recurso, provoca problemas de compatibilidad y demás, esto propicia el desarrollo de los sistemas operativos.

Provocaban apagones constantes en sus primeros inicios debido al coste de una máquina. Ahora es al revés, el hardware es barato, mientras que la mano de obra se ha tenido que encarecer, habiendo un superávit de hardware.

Tenemos una secuencia de arranque principal donde un programa grabado en ROM carga en la RAM el conjunto de programas del sistema operativo esenciales (Kernel)

Una vez cargado queda a la espera de que un evento mediante una "interrupción". Cuando esto sucede el SO aparta el proceso que estaba en ejecución y ejecuta el código asociado a la interrupción. 
## Almacenamiento
Para que un proceso esté en ejecución, debe de estar en memoria dispuesto para su uso. El encargado de hacer que cambie el proceso es el SO, que va variando las instrucciones. Cuando un proceso sale, se guarda el estado del mismo en el que se apaga, para luego volver a recuperarlo tal y como figuraba en su momento.

Lo que más ralentiza es tener una menor cantidad de memoria. A mayor memoria mejor va el ordenador. Esto se debe a cuando un ordenador tiene que buscar una instrucción en tu disco. Es un proceso muy costoso, porque tenemos que relegarlo en un driver ajeno que busca el archivo y cuando lo ha ubicado, tiene que realizar una interrupción para luego poder enviarlo a la cpu para que esta procese el dato recibido. 
