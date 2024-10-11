#### Implementaciones

##### Estáticas

##### Dinámicas

- **Lista enlazada simple**:

Todo elemento tiene un siguiente salvo el último:

| e1  | e2  | e3  | NULL |
| --- | --- | --- | ---- |

No necesito saber el tamaño del array. Si quisiésemos insertar un elemento e4, solamente tenemos que identificar el último elemento anterior, crear un nuevo nodo con nuestro elemento a añadir y luego enlazarlo. Como el añadido es el último, nuevamente añadimos el NULL al final.

| e1  | e2  | e3  | e4  | NULL |
| --- | --- | --- | --- | ---- |

Esto tiene una [[Complejidad Algorítmica]] de O(n) pues tenemos que averiguar el lugar donde hemos de insertar el elemento. 

En cambio, si quisiésemos añadir por cabecera (al principio de nuestra lista), la complejidad es de O(1), pues tenemos una acción instantánea que no se fija en el largo de nuestro array.

Nuevamente podemos entender esto pensando en las siguientes relaciones:

- Leer final de lista --> O(n) mientras que leer inicio de lista --> O(1)
- Borrar elemento final --> O(n) mientras que borrar inicial -->  O(1)

>[!NOTE] Structs y demás
>¡Ojo! A la hora de definir structs que hagan referencia a otro elemento que sea del mismo tipo de dicho struct, hemos de tener en cuenta que con esta estructura:
>```c
>typedef struct {
>	tElemento info;
>	tNodo *sig;
>} tNodo;
>```
>Esto no se puede hacer, pues es incorrecto, ya que antes de definir tNodo no sabemos que existe, en vez de definirlo como arriba, para que funcione, vamos a hacerlo así:
>```c
>typedef struct Nodo {
>	tElemento info;
>	struct Nodo * sig;
>} tNodo;
>```
>De esta forma podemos al fin referenciar a nuestro propio struct de manera correcta.

Veamos cómo sería insertar por cabecera:

```c
typedef struct Nodo {
	tElemento info;
	struct Nodo * sig;
} tNodo;

typedef tNodo * tLista;

void inCabecera (tLista * lista, tElemento elem) {
	tNodo * nodo = (tNodo *) malloc (1*sizeof(tNodo)); // Tenemos cajita
	asignarElemento(&(nodo -> info), elem);
	nodo -> sig = *lista;
	lista = nodo;
}
```

