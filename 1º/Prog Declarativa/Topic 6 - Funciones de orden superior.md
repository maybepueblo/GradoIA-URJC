**Funciones de orden superior y programación modular**

En este tema, veremos que las funciones de orden superior son dispositivos de modularidad esencial, y introduciremos las funciones de orden superior más comunes que operan en torno a diferentes estructuras de datos.

#### **FoldRight** : dividir y conquistar

Las funciones de orden superior brillan a la hora de romper monolitos, es decir, romper pequeños bloques y condesar el código mucho más. Veamos las siguientes funciones presentes en el [[Topic 5 - TADs y recursividad]] para ilustrarnos a través de ella:

```
def sum(list: List[Int]): Int =
	list match
		case Nil => 0 
		case head :: tail => head + sum(tail)
```

```
def multiply(list: List[Int]): Int =
	list match
		case Nil => 1
		case head :: tail => head * multiply(tail)
```

Estas funciones tienen mucho en común: lo único que las diferencia son los valores que devuelve cada función cuando la lista está vacía y la función usada para combinar números (el operador de la suma '+' o el de la multiplicación * respectivamente) Podemos olvidar estas diferencias y llegar a una función más genérica que programa la lógica que comparten estas dos funciones. 

```
def combine(list: List[Int])(nil: Int, cons: (Int, Int) => Int): Int =
	list match
 		case Nil => nil // En el caso vacío, tenemos que pensar que será el              valor que tengamos almacenado en la variable nil, sin importar cuál es.          Así, si quisiésemos usarla para hacer la función multiply, cuando                llamamemos a la función tendríamos que decir que nil = 1 
		case head :: tail => cons(head, combine(tail)(nil, cons)) // Si no               estamos en el valor Nil, tendremos que combinar la cabeza de la lista            con una función recursiva que use la cola para terminar no teniendo lado         en el apartado derecho
```

Esta función que acabamos de hacer nos permite hacer una función *multiply* y una función *sum* mucho más asequibles y comprensibles. Haciéndolas de esta manera, decimos que las estamos programando de forma modular. 

```
def sum(list: List[Int]): Int =
	combine(list)(0, (a, b) => a + b)
```

```
def multiply(list: List[Int]): Int =
	combine(list)(1, _ * _) // En este caso, podemos decir que el valor a            devolver si estamos en nil es 1 y la cons es igual a la multiplicación de        dos valores cualesquiera
```

Pero no hemos de limitarnos a números enteros. En su versión genérica, la función *combine* es de hecho la función de orden superior *foldRight* para las listas.

```
def foldRight[A, B](list: List[A])(nil: B, cons: (A, B) => B): B =
	list match
		case Nil => nil
		case head :: tail => cons(head, foldRight(tail)(nil, cons))
```

Podríamos explicarlo de forma gráfica tal y como lo tiene puesto Juanma en su GitHub. 

![[Pasted image 20240426095944.png]]

Podemos entender el foldRight como una implementación de tipo divide y conquista. Primero, divide tu problema en subproblemas, luego, resuélvelos, finalmente, compón esas soluciones para obtener la solución al problema general. Si los subproblemas son lo suficientemente simples se pueden resolver directamente; si no, los resolvemos recursivamente. En el caso de las listas:

- El problema obtiene un valor de tipo B para una lista dada
- El único subproblema corresponde a la cola de la lista
- Los argumentos de la función foldRight nos dicen cómo obtener la solución para la lista vacía (el problema que no podemos descomponer más) y cómo obtener la solución desde la solución al subproblema. 

Sabiendo esto, la implementación de la función *sum* y la de *multiply* son exactamente lo mismo que antes cuando usábamos *combine*, pero lo podemos explicar de forma diferente:

```
def sum(list: List[Int]): Int =
	foldRight[Int, Int](list)(
		0, // la solución directa a la lista vacía
		(head: Int, subsol: Int) => head * subsol // la composición
	)
```

#### Funciones de orden superior en la API de Scala

La función de orden superior foldRight, como todas las FOS, son parte de una librería de Scala. Comúnmente, son implementadas como un miembro de los métodos. Para las listas, la API de Scala ofrece algo como esto:

```
object Standard {
	class List[A]{
		def foldRight[B](b: B)(f: (B, A) => B): B = ???
	}
}
```

Así que las invocaciones del foldRight estándar no recibe una lista como parámetro, pero es un método de invocación común en la instancia List:

```
List(1, 2, 3).foldRight(0)(_ + _)
```

Usamos las funciones de orden superior en vez de nuestras funciones caseras una vez que se han explicado.

#### El Hall de la Fama de las FOS

A parte de las funciones que hemos visto, hay muchas FOS más, veamos algunos ejemplos:

```
def foldLeft[A, B](list: List[A])(b: B)(f: (B, A) => B): B = ???
def filter[A](list: List[A])(f: A => Boolean): List[A] = ???
def map[A, B](list: List[A])(f: A => B): List[B] = ???
def flatMap[A, B](list: List[A])
```

Pero la mayoría de estas funciones no solo funcionan con las listas, si no también con la estructura de datos *either*, *option* y muchas más. Veamos con por ejemplo option y either:

```
// FOS orientadas a Option
def fold[A, B](opt: Option[A])(none: B)(some: A => B): B = ???
def filter[A](opt: Option[A])(f: A => Boolean): Option[A] = ???
def map[A, B](opt: Option[A])(f: A => B): Option[B] = ???  
def flatMap[A, B](opt: Option[A])(f: A => Option[B] ): Option[B] = ???
```

```
// FOS orientadas a Either
def fold[A, B, C](opt: Either[A, B])(left: A => C, right: B => C): C = ???
def filter[A, B](opt: Either[A, B])(f: B => Boolean): Either[A, B] = ???
def map[A, B, C](opt: Either[A, B])(f: B => C): Either[A, C] = ???  
def flatMap[A, B, C](opt: Either[A, B])(f: B => Either[A, C] ): Either[A, C] = ???
```

#### FoldLeft : un bucle mucho mejor

La función de orden superior *foldLeft* es la forma funcional de implementar algoritmos imperativos comunes.

```
// Longitud de una lista
def length[A](list: List[A]): Int =
	var out: Int = 0
	for (e <- list)
		out += 1
	out 
```

```
// Lista invertida 
def reverse[A](list: List[A]): List[A] =
	var out: List[A] = List()
	for (e <- list)
		out = e :: out
	out
```

La siguiente implementación se abstrae de todas las diferencias que tienen estas funciones de arriba, y se declaramos dos parámetros adicionales: el valor inicial de una variable mutable, y la función actualizada ejecutada en cada paso del bucle.

```
def foldLeft[A, B](list: List[A])(initial: B)(update: (B, A) => B): B =
	var out: B = initial // Valor inicial que o bien puede ser el 0 que vemos se     usa en la función de longitud o bien puede ser la lista que le demos por         parámetro si queremos basarnos en reverse
	for (elem <- list) // Desde principio de la lista al final de la misma
		out = update(out, elem) // Bucle que va actualizando de forma recursiva
	out
```

De manera similar, la función foldLeft se usa normalmente donde una función recursiva por cola se necesita. Su implementación recursiva es naturalmente recursiva por cola:

```
@annotation.tailrec
def foldLeft[A, B](list: List[A])(out: B)(update: (B, A) => B): B =
	list match
		case Nil => out
		case head :: tail => 
			foldLeft(tail)(update(out, head))(update)
```

Usando foldLeft podemos implementar funciones con mucha más abstracción, usando constructores que están cerca del problema origen sin importarnos las variables mutables, la recursion por cola, etc. También dirige a implementaciones muy concisas y fáciles de leer. Para ilustrarlo, veamos algunas implementaciones que se reducen a nada de las funciones recursivas del tema anterior:

```
// Tamaño de una lista
def length[A](list: List[Int]): Int =
	foldLeft(list)(0)((out: Int, _ : A) => out +  1)
```

```
// Suma de los elementos de una lista 
def sum(list: List[Int]): Int =
	foldLeft(list)(0)(_ + _)
```

También podríamos usar la función foldRight para implementarlos:

```
// Tamaño con foldRight
def length[A](list: List[A]): Int =
	list.foldRight(0)((head: Int, tail: Int) => tail + 1)
```

```
// Caso de la suma
def sum(list: List[Int]): Int =
	list.foldRight(0)((head: Int, tail: Int) => head + tail)
```

```
// Caso de la lista invertida
def reverse[A](list: List[A]): List[A] =
	list.foldRight(List[A]()):(head: A, tail: List[A]) => tail.appended(head)
```

Funcionalmente, ambas versiones son equivalentes, pero los que usan foldLeft son más eficientes. En particular, la versión de reverse, tal y como vemos, es mucho más compleja de lo que debería.

#### Implementando foldRight con foldLeft

La implementación que le dimos en un inicio a foldRight no era recursiva por cola, así que esto colapsará la pila. En pos de darle una mejor implementación, es mejor primero invertir la lista y usar foldLeft tal y como muestro ahora:

```
def foldRightTR[A, B](list: List[A])(nil: B)(cons: (A, B) => B): B =
	foldLeft(list.reverse)(nil): // Aplicamos el módulo reverse a la lista           utilizando foldLeft
		(acc: B, a: A) => cons(a, acc) // Luego podemos aplicarle un foldRight
```

#### Implementando foldLeft con foldRight

Esto también es posible pero más arriesgado. Empezamos desde la implementación recursiva por cola de FoldLeft. Primero, ordenamos los argumentos tal que ahora se devuelva una función en vez de un valor de tipo B:

```
def foldLeftAux[A, B](list: List[A])(update: (B, A) => B): B => B =
	list match
		case Nil => identity[B]
		case head :: tail => out => foldLeftAux(tail)(update)(update(out, head))
```

Esto lo hicimos para exponer el patrón de recursividad de foldRight. La solución se obtiene simplemente dándonos cuenta de que foldLeft(tail)(update) es la solución de la cola

```
def foldLeftAux[A, B](list: List[A])(update: (B, A) => B): B => B =
	list.foldRight(identity[B] _):
		case (head, tailSol) => out => tailSol(update(out, head))
```

La escritura original podría implementarse de la siguiente manera:

```
def foldLeft[A, B](list: List[A])(out: B)(update: (B, A) => B): B =
	list.foldRight(identity[B] _){
		case (head, tailSol) =>
			out => tailSol(update(out, head))
	}(out)
```

#### La función de orden superior llamada *map*

La función *map* es una de las FOS esenciales. Su propósito es el de aplicar una función a los elementos de la estructura de datos, de tal manera que la relación entre estos elementos no cambia. La única cosa que debe ser modificada es el contenido de las estructuras de datos, no su forma. Esta condición se expresa en las siguientes ecuaciones:

1. map(list)(identity) == list para toda list: List[A]
2. map(map(list)(f))(g) == map(list)(g compose f) en toda lista y f: A => B, g: B => C

Básicamente, a la función map le damos una lista sobre la que queremos actuar y la función que aplicaremos para actuar sobre ella, de tal forma que si a un map le aplicamos otro map pues haremos la composición de la función del segundo map que hemos aplicado sobre el otro y su función en torno a la misma lista. 

La implementación para las listas se puede ver de esta manera: 

```
def map[A, B](list: List[A])(f: A => B): List[B] =
	list match
		case Nil => Nil
		case head :: tail => f(head) :: map(tail)(f) // Como vemos, aplicamos la         función a head, que ya tenemos dicho valor, y por el otro lado en la             cola de la lista, es decir, la parte que no tenemos, vamos poco a poco           aplicando nuevamente la función map
```

La función map es polimórfica en A y B pero no podemos pasar funciones genéricas como parámetros. Podemos crear versiones polimórficas, pero para mantenernos simples, vamos a definir el catalogo de testing de map.

```
class TestMap(
    map: List[Int] => (Int => Boolean) => List[Boolean]
) extends AnyFlatSpec with should.Matchers:

    val isEven: Int => Boolean = _ % 2 == 0

    "mapping an empty list" should "return an empty list" in:
        map(List())(isEven) shouldBe List()
    
    "mapping an non-empty list" should "only change its content" in:
        map(List(1))(isEven) shouldBe List(false)
        map(List(1,2))(isEven) shouldBe List(false, true)
        map(List(1,2,3))(isEven) shouldBe List(false, true, false)
```

Para hacer testing, habríamos de pasarle a map los valores de Int y Boolean (aunque podríamos saltárnoslo ya que Scala infiere los tipos por nosotros).

Si queremos implementar map, vemos que su implementación se parece a la de foldRight. Asimismo, podemos darle una implementación más modular usando esta FOS más básica:

```
// Sabiendo que foldRight se define así:
/*
def foldRight[A, B](list: List[A])(nil: B)(cons: (A, B) => B): B = 
    list match {
        case Nil => nil
        case head :: tail => cons(head, foldRight(tail)(nil)(cons))
    }
*/

def mapFR[A, B](list: List[A])(f: A => B): List[B] =
	list.foldRight(Nil: List[B])((a, l) => f(a) :: l)
```

#### *map* para *Option*

La implementación de la función map dada arriba sirve sobre listas, pero también podemos mapear valores opcionales y muchas otras estructuras de datos. La implementación de la estructura de datos *Option* debe de satisfacer el siguiente test:

```
class TestMapOption(
    map: Option[Int] => (Int => Boolean) => Option[Boolean]
) extends AnyFlatSpec with should.Matchers:
    
    val isEven: Int => Boolean = _ % 2 == 0

    "mapping the `None` value" should "return `None`" in:
        map(None)(isEven) shouldBe None
    
    "mapping a `Some` value" should "only change its content" in:
        map(Option(3))(isEven) shouldBe Some(false)
        map(Option(1))(isEven) shouldBe Some(false)
        map(Option(2))(isEven) shouldBe Some(true)
```

Veamos la implementación:

```
def mapOpt[A, B](maybeA: Option[A])(f: A => B): Option[B] = 
    maybeA match
        case None => None
        case Some(a) => Some(f(a))
```

Como podemos ver, el programa consiste en que dado un dato *option* pues devolvemos un option, ¿cómo? muy fácilmente de hecho. 

Si el dato que recibimos de maybeA es vacío o ninguno, entonces el valor de la optionB es vacía o ninguna también. En caso de que sí haya un valor, tenemos que decir que algún valor llegado (Some(a)) se transforme a la aplicación de la función f que dado un dato A tenemos un dato B, lo que rellena el option de B.

Ahora si hiciésemos un test podríamos ver que efectivamente sí funciona y se cumple el test que habíamos establecido.

#### Filtrado de elementos

No como map, la función de orden superior `filter`, nos permite cambiar el tamaño de la estructura de datos, eliminando esos elementos que no satisfacen un predicado dado.

```
def filterR[A](list: List[A])(predicate: A => Boolean): List[A] = 
    list match
        case Nil => Nil 
        case head :: tail if predicate(head) => 
            head :: filterR(tail)(predicate)
        case _ :: tail => 
            filterR(tail)(predicate)
```

Como podemos ver, tenemos la función `filterR`, que dada una lista y un predicado que busca que dado A tenemos un booleano, nos da otra lista filtrada.

Es decir, que si se cumple A pues entonces se satisface la condición y se rellena la lista. Esto lo podemos ver reflejado en el pattern matching que hacemos a posteriori, donde rellenamos en función de ello, teniendo un caso base Nil donde no hay nada y por tanto devolvemos nada.

En caso de que sí haya algo siendo ese algo una lista con un elemento de cabeza y otro de cola, recordemos [[Topic 5 - TADs y recursividad]], pues tenemos que si el predicado se cumple cuando le damos la cabeza, entonces simplemente hemos de aplicar el predicado a head y la función filter de forma recursiva a la cola para que siga verificando si esto funciona.

El último caso simplemente sirve de la misma manera, si no nos importa el primer dato que tenemos en nuestro head :: tail pues inmediatamente aplicamos filter nuevamente a la cola de nuestra lista.

Entonces se cumple el siguiente test:

```
class TestFilterList(
    filter: List[Int] => (Int => Boolean) => List[Int]
) extends AnyFlatSpec with should.Matchers:
    
    val isEven: Int => Boolean = _ % 2 == 0

    "filter" should "work" in:
        filter(List())(isEven) shouldBe List()
        filter(List(1))(isEven) shouldBe List()
        filter(List(1,3,5))(isEven) shouldBe List()
        filter(List(2,4,6))(isEven) shouldBe List(2,4,6)
```

Además, cabe destacar que si usamos foldRight podemos obtener una implementación más modular:

```
def filterFR[A](list: List[A])(predicate: A => Boolean): List[A] = 
    list.foldRight(List[A]()):
        (head, filteredTail) => 
            if (predicate(head)) head :: filteredTail
            else filteredTail
```

#### Filtrado de valores opcionales

Sólo tenemos un valor posible, así que implementar el filtrado es muy fácil en este caso:

```
// Código de testing
class TestFilterOption(
    filter: Option[Int] => (Int => Boolean) => Option[Int]
) extends AnyFlatSpec with should.Matchers:
    
    val isEven: Int => Boolean = _ % 2 == 0

    "filter" should "work" in:
        filter(None)(isEven) shouldBe None
        filter(Some(1))(isEven) shouldBe None
        filter(Some(2))(isEven) shouldBe Some(2)
```

```
// Filter para valor de tipo Option
def filter[A](maybeA: Option[A])(predicate: A => Boolean): Option[A] = 
    maybeA match
	    // En el caso de que no haya nada, pues nada
        case None => None
        // Si hay algo y ese algo cumple el predicado, entonces devolvemos ese           algo, si no, devolvemos nada
        case Some(a) if predicate(a) => Some(a)
        case _ => None
```

Ahora si hacemos un test, nos debería funcionar a la perfección.

```
run(TestFilterOption(filter))
```

#### FlatMapping de estructuras de datos

Consideramos un párrafo representado como una lista de frases, donde cada frase es modelada como una cadena compuesta por palabras separadas por espacios en blanco. Queremos obtener una lista de todas las palabras en cada frase:

```
def words(paragraph: List[String]): List[String] = 
	???
```

Compongamos el test:

```
class TestWords(words: List[String] => List[String]) extends AnyFlatSpec with should.Matchers:

	val paragraph1 = List(
		"En un lugar",
		"de la Mancha",
		"de cuyo nombre no",
		"quiero acordarme")

	"words" should "work" in:
		words(paragraph1) shouldBe
			List("En", "un", "Lugar", "de", "la", "Mancha", "de", "cuyo",                    "nombre", "no", "quiero", "acordarme")
```

Podríamos intentar mapear un párrafo con una función que separa cada frase en las palabras por las que se compone:

```
val paragraph: List[String] = List("en un lugar", "de la Mancha")

map(paragraph)((sentence: String) => sentence.split(" ").toList)
```

Pero esto es equívoco, pues obtenemos una lista de listas de strings, no una lista de strings y ya. La solución se encuentra en concatenar todas las listas y obtendremos lo que queremos. La función siguiente `flatten` consigue esta concatenación:

```
def flatten[A](listOflists: List[List[A]]): List[A] =
	listOflists.foldRight(List[A]()):
		(list, flattenedTail) =>
			list ++ flattenedTail
```

La función `flatten` viene incluida en la API de Scala, con lo cual la implementación de la función inicial `words` es la siguiente:

```
def words(paragraph: List[String]): List[String] =
	paragraph
		.map(sentence => sentence.split(" ").toList)
		.flatten
```

Si ahora hacemos un run del test pues todo se cumple:

```
run(TestWords(words))
```

Cabe destacar que la combinación de la función de orden superior `map` y la función `flatten` es tan común que tiene un nombre propio: `flatMap`

```
def flatMap[A](list: List[A])(f: A => List[A]): List[A] =
	list.map(f).flatten
```

Si queremos usar `flatMap` la función resultante es aún más fácil:

```
def words(paragraph: List[String]): List[String] =
	paragraph.flatMap: sentence =>
		sentence.split(" ").toList
```

#### FlatMapping de valores opcionales

Nuevamente, podemos hacerlo con valores opcionales, vamos a definir primero la función para luego hacer su respectivo testing:

```
def flatMap[A, B](maybeA: Option[A])(cont: A => Option[B]): Option[B] =
	maybeA match
		case None => None
		case Some(a) => cont(A)
```

Muy fácil de entender, veamos la clase `TestFlatMapOption`:

```
class TestFlatMapOption(flatMap: Option[Int] => (Int => Option[Boolean])) => Option[Boolean]) extends AnyFlatSpec with should.Matchers:

	def isPositiveEven(i: Int): Option[Boolean] =
		if (i > 0) Some(i % 2 == 0)
		else None

	"flatMap" should "work" in:
		flatMap(None)(isPositiveEven) shouldBe None
		flatMap(Some(5))(isPositiveEven) shouldBe Some(false)
		flatMap(Some(-1))(isPositiveEven) shouldBe None
		flatMap(Some(0))(isPositiveEven) shouldBe Some(true)
		flatMap(Some(4))(isPositiveEven) shouldBe Some(true)
```

Ahora si ejecutamos el testing, ha de darnos bien:

```
run(TestFlatMapOption(flatMap))
```

#### Todo junto: un problema de modularidad

Como antes, comenzamos desde una lista de frases, pero ahora queremos tener cuidado con los espacios extra posibles entre cada palabra. Además, queremos obtener no las palabras en sí, sino su longitud. Así, vamos a llamar a nuestra función `lengths`:

```
def lengths(paragraph: List[String]): List[Int] = ???
```

```
class TestLengths(lengths: List[String] => List[Int]) extends AnyFlatSpec with should.Matchers:

	val paragraph1 = List(
		"En un lugar",
		"de  la Mancha", 
		"de cuyo nombre no",
		"quiero      acordarme")

	"lengths" should "work" in:
		lengths(paragraph1) shouldBe
			List(2, 2, 5, 2, 2, 6, 2, 4, 6, 2, 6, 9)
```

Podríamos implementar esta función de forma imperativa con variables mutables:

```
def lengthsM(paragraph: List[String]): List[Int] =
	var out: List[Int] = List()

	for (sentence <- paragraph)
		val words: List[String] =
			sentence.split(" ").toList
		for (word <- words)
			if (word != " ")
				out = word.length :: out

	out.reverse
```

Podemos hacerlo mejor evidentemente con el uso de funciones de orden superior, que nos daría una versión mucho más concisa y entendible con mucha más reusabilidad.

```
def lengthsHOF(paragraph: List[String]): List[Int] =
	paragraph
		.flatMap(_.split(" ").toList)
		.filter(_ != "")
		.map(_.length)
```

Ahora si ejecutamos el test va perfecto:

```
run(TestLengths(lengthsHOF))
```

Esta solución sirve como contraste a la versión mutable en varias cosas:

- Es más **modular**. La versión mutable no.
- Los componentes de funciones de orden superior son muy genéricos y independientes del dominio, siendo típicos de librerías estándar, así que el nivel de reutilizar y de comodidad de esta última solución es muy alta.
- Las soluciones basadas en HOF son más comprensibles: modelan la solución al problema en términos de transformaciones estándar que están compuestas entre sí usando composición de funciones. Además, estas transformaciones están también en el punto exacto de abstracción, es decir, es natural especificar la solución en términos de estas funciones.

#### For-comprensiones

La combinación de `map`, `flatMap` y `filter` son tan comunes que Scala tiene una sintaxis especial para ellas: for-comprehensions:

```
def lengthsFC(paragraph: List[String]): List[Int] =
	for sentence <- paragraph
		word <- sentence.split(" ).toList if word != ""
	yield word.length
```

Y ahora si tomamos el mismo test de arriba, pues funciona:

```
run(TestLengths(lengthsFC))
```

