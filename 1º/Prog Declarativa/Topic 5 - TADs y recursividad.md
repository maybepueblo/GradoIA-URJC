**Recursive functions and data types - Funciones recursivas y tipos de datos**

En resumidas cuentas, el tema 5 busca explicar lo siguiente:
- Cómo están definidos los tipos recursivos
- Cómo se definen las funciones recursivas
- Los dos tipos de funciones recursivas más importantes: generales y recursivas por cola

#### Tipos recursivos

###### El tipo llamado *list* (*lista*)

Las listas son estructuras de datos que representan una serie de valores del mismo tipo. Cabe denotar que tienen una longitud finita (no son eternas). Podemos definirlas de forma recursiva tal que así:

- Una lista es una secuencia vacía
- Una lista es una secuencia no vacía que tiene un valor y otra lista, cada una representa la cabeza (*head*) y la cola (*tail*) de la lista, respectivamente. 

Entonces, el tipo **IntList**, que representa una lista de números enteros, debe cumplir la siguiente ecuación:

- IntList = 1 + Int * IntList

En Scala las implementamos de la siguiente manera, veamos con la forma genérica de List(A):

```scala
object StdDefinition: 
	enum List[A]: // Enumeramos los elementos que componen a nuestra lista
		case NonEmpty(head: A, tail: List[A]) // Si tiene algo dentro, vemos             como se compone por un valor que llamamos la cabeza y otro valor que             procede, que es el resto de la lista.
 		case Empty() // Si está vacía pues está vacía
```

Sin embargo, en la librería estándar de Scala se definen las listas vacías como un objeto, no como una clase. Esto nos fuerza a declarar la lista con el parámetro, lo cual nos puede dar problemas a veces. Veamos la implementación básica: 

```
object ActualStdDefinition:
	enum List[+A]:
		case ::(head: A, tail: List[A])
		case Nil
```

###### **Azúcar sintáctico**

Por supuesto podemos escribir las listas de forma más compactas (menos complicadas de leerlas):

```
// Menos bonito
val l1: List[Int] = ::(1, ::(2, ::(3, Nil)))

// Más verboso (se lee mejor)
val l2: List[Int] = 1 :: 2 :: 3 :: Nil
val l3: List[Int] = List(1, 2, 3)
 ```

También podemos hacer pattern matching:

```
// Menos bonito
l1 match
	case Nil => 0
	case ::(head, tail) => 1

// Más verboso
l1 match
	case Nil => 0
	case head :: tail => 1

// También tenemos esta manera
l1 match
	case List() => 0
	case List(h1, h2, h3) => 1
	case _ => 2
```

#### Funciones recursivas

Como las listas se definen recursivamente, las funciones que actúan sobre listas son también recursivas. Por ejemplo, vamos a implementar una función recursiva que da el tamaño de una lista. Pero antes, vamos a implementar la lista de forma imperativa para comparar:

```
// Usando variables mutables
def lengthI[A](list: List[A]): Int =
	var out: Int = 0 // Definimos el contador
	var aux: List[A] = list // Definimos la variable lista
	while (aux != Nil) // Mientras que la lista no llegue al valor final que es      // Nil, seguiremos contando
		aux = aux.tail // Vamos igualando a cada iteración aux al valor final de         la lista que ya sabemos que se llama tail
		out += 1 // Si hemos aumentado, pues aumentamos el contador también
	out // Imprimimos el contador
```

La función recursiva en cambio se ve como:

```
def lengthR[A](list: List[A]): Int =
	list match
		case Nil => 0 // Definimos qué pasaría si estamos en un valor vacío
		case _ :: tail => 1 + lengthR(tail) // Definimos que si es un valor que          no sea el valor vacío Nil pues pasamos hacia tail, sumamos uno al                contador intrínseco a la función y luego volvemos a recorrer en la               función inicial hasta llegar a un Nil eventualmente
```

Hay que darnos cuenta de lo siguiente:

- La función recursiva la definimos de forma orientada a tipos: vamos paso por paso, analizando los tipos que tenemos disponibles a rellenar, y los tipos a rellenar. Básicamente podemos hacer lo mismo que en temas anteriores: rellenar interrogantes. 
- La función recursiva es menos eficiente, ya que la pila colapsará con listas muy largas.
#### Funciones recursivas por colas

Si usamos este tipo de funciones, resolvemos el problema con la pila. Normalmente usamos funciones auxiliares para crearlas:

```
// Usamos lo que conocemos como tail-recursive functions
def LengthTR[A](list: List[A]) : Int =
	@annotation.tailrec
	def lengthAux(out: Int, aux: List[A]): Int =
		aux match // Hacemos literalmente la misma función que vimos antes
			case Nil => out
			case _ :: tail => lenghtAux(out+1, tail)
	lengthAux(0, list) // Iniciamos la función auxiliar con un contador de           // tamaño de cero y la lista que hayamos conseguido
```

Podríamos comprobar los problemas de seguridad frente a la pila que nos dan las funciones recursivas calculando la longitud the una gran lista. Para comprobar, creemos una función que dado un número nos de una lista de ese tamaño:

```
// Primero de forma imperativa
def constantList[A](value: A, length: Int): List[A] =
	var out: List[A] = Nil // Definimos una lista que en su inicio viene vacía
	for (i <- 1 to length)
		out = value :: out // Ahora, le damos un valor iterando la constructora          de las listas infinitamente hasta tener la longitud que le hemos dado
	out
```

```
// Ahora de forma recursiva
def constantList[A](value: A, length: Int): List[A] =
	
	def constantAux(out: List[A], i: Int): List[A] =
		if (i == 0) out // Si el entero que le hemos dado es 0, pues nada
		else constantAux(value :: out, i-1) // Si hay un valor, volvemos a la            función auxiliar de forma recursiva para darle este nuevo valor y además         poder componer la lista poco a poco
	
	constantAux(Nil, length)
```

Si ahora probásemos cada función veríamos que la *tail-recursive* y la *imperative* no nos dan problema, mientras que la recursiva base sí nos da problema por *Overflow*.
#### Unit Testing con el scalatest

Hacemos primero y muy importante un import

```
import $ivy.`org.scalatest::scalatest:3.2.16`
import org.scalatest.{Filter => _, _}, flatspec._, matchers._
```

A partir de ahora, haremos un uso extensivo del testing. Usaremos la librería que acabamos de importar. En particular para cada función implementaremos un catálogo de pruebas que ponen a prueba a una función en diferentes casos. Este catálogo recibe a la función como parámetro para aplicarla al testing. Veamos un posible test para la función *length*

```
class TestLength(lengthF: List[Int] => Int) extends AnyFlatSpec with should.Matchers:
	"length" should "work" in:
		lengthF(List()) shouldBe 0
		lengthF(List(1)) shouldBe 1
		lengthF(List(1, 2, 3, 4)) shouldBe 4
```

El método *shouldBe* es un **matcher**. La librería da un catálogo extensivo de ellos. De manera similar, el scalatest soporta diferentes estilos de testeo. El elegido aquí fue AnyFlatSpec. Para ejecutar el test podemos usar el método de scalatest *run*:

```
run(TestLength(lengthR))
```

**Ejemplo 1: Sumar**

Vamos a implementar una función que sume todos los números de una lista

```
class TestSum(sum: List[Int] => Int) extends AnyFlatSpec with should.Matchers:
	"sum" should "work" in:
		sum(List()) shouldBe 0
		sum(List(1)) shouldBe 1
		sum(List(1, 2, 3, 4)) shouldBe 10
```

Ahora definamos la función sum:

```
def sum(list: List[Int]): Int =
	list match
		case Nil => O // Caso lista vacía
		case head :: tail => head + sum(tail) // Sumamos el head por el                  recorrido del siguiente miembro de la lista
```

Y hacemos finalmente el testing:

```
run(TestSum(sum))
```

¿Qué tal si lo hacemos con funciones recursivas por cola?

```
def sumTR(list: List[Int]): Int =

	def sumAux(acc: Int, list: List[Int]): Int =
		list match
			case Nil => acc // Caso vacío será el valor que tengamos hasta el                momento
			case head :: tail => sumAux(head + acc, tail) // Caso con valor,                 será la suma de la cabeza con el valor que teníamos y componemos el              resto de la lista para repetir 

	sumAux(0, list)
```

Ahora probamos de nuevo

```
run(TestSum(sumTR))
```

**Ejemplo 2: Multiplicando elementos de la lista**

Vamos a multiplicar los elementos de una lista. Si la lista está vacía, devolveremos uno para los enteros:

```
class TestProduct(product: List[Int] => Int) extends AnyFlatSpec with should.Matchers:
	"product" should "work" in:
		product(List()) shouldBe 1
		product(List(1)) shouldBe 1
		product(List(1, 2, 3, 4)) shouldBe 24
		product(List(1, 0, 3, 4)) shouldBe 0
```

Veamos la implementación recursiva:

```
def product(list: List[Int]): Int =
	list match
		case Nil => 1
		case head :: tail => head * product(tail) 
```

Sabemos también que es una bobería el valor 0, ya que hará todo cero desde que esté presente, hagamos una implementación que tenga esto en cuenta:

```
def product2(list: List[Int]): Int =
	list match
		case Nil => 1 // Caso vacío
		case 0 :: _ => 0 // Desde que haya un cero nos da igual lo demás, es 0
		case head :: tail => head * product2(tail) // Caso recursivo cuando hay          algún valor todavía
```

Ahora, veamos cómo podríamos implementarlo de forma recursiva por cola:

```
def productTR(list: List[Int]): Int =

	def productAux(list: List[Int]): Int =
		list match 
			case Nil => 1
			case 0 :: _ => 0
			case head :: tail => head * productAux(tail)

	productAux(list)
```

**Ejemplo 3: membresía**

Vamos a implementar una función que dado una lista y un elemento devuelve si dicho elemento pertenece a la lista o no.

```
class TestMember(member: (List[Int], Int) => Boolean) extends AnyFlatSpec with should.Matchers:
    "member" should "work" in:
        member(List(), 6) shouldBe false
        member(List(1), 1) shouldBe true
        member(List(1, 2, 3, 4), 5) shouldBe false
        member(List(2, 2, 2), 2) shouldBe true
```

Ahora hemos de definir la función de forma recursiva:

```
def member(list: List[Int], value: Int): Boolean =
    list match 
        case Nil => false
        case head :: tail => head == value || member(tail, value)
```

Podríamos hacerlo directamente entorno a cierto valor específicamente:

```
def member(list: List[Int], value: Int): Boolean =
    list match
        case Nil => false
        case `value` :: _ => true
        case _ :: tail => member(tail, value)
```

Veamos cómo lo hacemos de forma recursiva por cola:

```
def memberTR(list: List[Int], value: Int): Boolean =

    def memberAux(list: List[Int], value: Int): Boolean =
        list match
            case Nil => false
            case head :: tail => head == value || memberAux(tail, value)

    memberAux(list, value)
```

**Ejemplo 4: Último elemento**

Vamos a implementar una función que devuelva el último elemento de una lista. Una lista vacía por si acaso, no tiene elementos, y por tanto, no tiene un último elemento:

```
class TestLast(last: List[Int] => Option[Int]) extends AnyFlatSpec with should.Matchers:
    "last" should "work" in:
        last(List()) shouldBe None
        last(List(1)) shouldBe Some(1)
        last(List(1, 2, 3)) shouldBe Some(3)
```

Veamos cómo se define de forma recursiva: 

```
@annotation.tailrec
def last(list: List[Int]): Option[Int] =
    list match
        case Nil => None // Caso vacío, no tenemos ningún elemento
        case head :: Nil => Some(head) // Caso donde estamos justo antes del fin
        case head :: tail => last(tail) // Caso donde todavía queda lista
```

Definamos la misma función de forma recursiva por cola: (Mismo perro, diferente collar)

```
def lastTR(list: List[Int]): Option[Int] =
    def lastAux(list: List[Int]): Option[Int] =
        list match
            case Nil => None
            case head :: Nil => Some(head)
            case head :: tail => lastAux(tail)

    lastAux(list)
```

**Ejemplo 5: Añadir último elemento**

Ahora, una función que nos deje insertar un elemento al final de la lista:

```
class TestInsertLast(insertLast: (List[Int], Int) => List[Int]) extends AnyFlatSpec with should.Matchers:
	"insertLast" should "work" in:
		insertLast(List(),0) shouldBe List(0)
		insertLast(List(1), 1) shouldBe List(1, 1)
		insertLast(List(1, 2, 3), 4) shouldBe List(1, 2, 3, 4)
```

Veamos como se implementa de forma recursiva:

```
def insertLast(list: List[Int], elem: Int): List[Int] =
	list match
		case Nil => List(elem)
		case head :: tail => head :: insertLast(tail, elem)
```

Ahora de forma recursiva por cola: 

```
def insertLastTR(list: List[Int], elem: Int): List[Int] =
	def insertLastAux(list: List[Int], elem: Int): List[Int] =
		list match 
			case Nil => List(elem)
			case head :: tail => head :: insertLastAux(tail, elem)
	insertLastAux(list, elem)
```

**Ejemplo 6: Listas invertidas**

Implementemos una función que recibe una lista y devuelve su invertida:

```
class TestReverse(reverse: List[Int] => List[Int]) extends AnyFlatSpec with should.Matchers:
    "reverse" should "work" in:
        reverse(List()) shouldBe List()
        reverse(List(1)) shouldBe List(1)
        reverse(List(1, 2)) shouldBe List(2, 1)
        reverse(List(1, 3, 4, 5)) shouldBe List(5, 4, 3, 1)
```

Veamos cómo se implementa de forma recursiva:

```
def reverseR(list: List[Int]): List[Int] =
    list match
        case Nil => List() // Lista vacía, pues no hace falta invertirla
        case head :: tail => insertLast(reverseR(tail), head) 
        // En este caso usamos la función anterior de insertar un valor al final         de la lista, donde si lo tenemos, al final de la lista (tail), añadimos          el valor inicial
```

Si tenemos curiosidad, se implementa de la siguiente forma de manera recursiva por cola:

```
def reverseTR(list: List[Int]): List[Int] =
    def reverseAux(listA: List[Int], list: List[Int]): List[Int] =
        list match
            case Nil => listA
            case head :: tail => reverseAux(head :: listA, tail)

    reverseAux(Nil, list) 
```

**Ejemplo 7: Concatenar listas**

Vamos a concatenar listas:

```
class TestConcatenate(concatenate: (List[Int], List[Int]) => List[Int]) 
extends AnyFlatSpec with should.Matchers:
    "concatenate" should "work" in:
        concatenate(List(), List()) shouldBe List()
        concatenate(List(1), List(1)) shouldBe List(1, 1)
        concatenate(List(1, 2, 3), List(4, 5, 6)) shouldBe List(1, 2, 3, 4, 5, 6)
        
```

Veamos cómo se hace de forma recursiva: 

```
def concatenateR(l1: List[Int], l2: List[Int]): List[Int] =
    l1 match 
        case Nil => l2 // En el caso de que l1 esté vacía, decimos que la lista          es directamente l2, pues da igual el valor de l2, será ella la lista
        case head :: tail => (head :: concatenateR(tail, l2)) // En el caso de           que haya una lista llena, lo que haremos es meter el primer elemento y           concatenar poco a poco el resto con l2
```

Ahora, tenemos que ver cómo se hace de forma recursiva por cola:

```
def concatenateTR(l1: List[Int], l2: List[Int]): List[Int] =
    def conAux(aux: List[Int], l2: List[Int]): List[Int] =
        l2 match 
            case Nil => aux // Ahora lo que hacemos es decir que nuestra lista               inicial será la lista 1 y miraremos cuidadosamente
            case head :: tail => conAux(head :: aux, tail)

    conAux(l2, conAux(Nil, l1))
```



#### Árboles binarios

Vamos a ver una estructura de datos que puede ser definida como el siguiente dato de tipo algebraico:

```
// type Tree[A] = 1 + Tree[A] * A * Tree[A]

enum Tree[A]:
    case Empty()
    case Node(left: Tree[A], root: A, right: Tree[A])

object Tree:
    
    def void[A]: Tree[A] = 
        Empty()
    
    def leaf[A](a: A): Node[A] = 
        Node(Empty(), a, Empty())
    
    def right[A](a: A, tree: Tree[A]): Node[A] = 
        Node(Empty(), a, tree)
    
    def left[A](tree: Tree[A], a: A): Node[A] = 
        Node(tree, a, Empty())
    
    def node[A](left: Tree[A], a: A, right: Tree[A]): Node[A] = 
        Node(left, a, right)
```

Los árboles hemos de explicarlo de una forma bastante simple para fomentar su entendimiento pues un objeto árbol es verdaderamente un contenedor de listas que entendemos como ramas. Veamos un poco el panorama:

El enum de tipo tree lo que nos presenta es la posibilidad de dos casos: vacío o algún tipo de elemento, que ahora detallaremos.

- `void` Elemento del arbol que trata al mismo cuando este objeto está vacío.
- `leaf` Caso del árbol donde solamente tenemos como contenido el dato A, sin tener ninguna ramificación presente.
- `right` Caso donde no sólo tenemos el dato A, sino que también tenemos una ramificación derecha tree que podemos entender como otra lista dentro de la lista.
- `left` Lo mismo que right pero por la izquierda.
- `node` En este caso tenemos todos los datos, notamos tanto la presencia de A como la presencia de ramas por la derecha y por la izquierda.

Para ver ejercicios de esto, es mejor ver la sección dedicada a ejercicios que tengo de esta asignatura -> [[Ejercicios Scala]]