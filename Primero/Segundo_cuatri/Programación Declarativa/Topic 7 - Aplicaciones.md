Si bien esta sección no cae como tal en el examen, es digna de atención por si hay algo de teoría o inclusive como conocimiento en sí.

#### Tipos de colecciones

Los tipos de colecciones se pueden clasificar en dos dimensiones generales:

- **Mutable / Inmutable** -> Las colecciones mutables se pueden modificar in situ mientras que las inmutables devuelven una nueva instancia cuando se actualizan.
- **Sequences / Sets / Maps** -> Colecciones ordenadas o no y colecciones claves respectivamente.

Hay muchas implementaciones de secuencias, sets y mapas:

![[Pasted image 20240517150606.png]]

![[Pasted image 20240517150620.png]]

¿Pero cómo elegimos a partir de tantos tipos de colecciones e implementaciones? Pues de acuerdo a la funcionalidad que demandamos de esa colección, como si por ejemplo ha de estar ordenado, puede haber elementos repetidos, puede haber elementos asociados a claves, etc. En pos de escoger la implementación adecuada del tipo de colección tenemos que tener en cuenta la complejidad de la implementación correspondiente.

En este caso nos vamos a centrar solamente en colecciones de tipo inmutable solamente.

#### Mapas - Diccionarios

Los mapas son colecciones de valores clave:

```
// Un mapa de string a int

Map(("a", 1), ("b", 2), ("c", 3))
```

Para pares por clave escribimos con una tupla con la siguiente sintaxis:

```
// mapa con sintaxis ->
"a".->(1)

val m: Map[String, Int] = Map("a" -> 1, "b" -> 3)
```

```
// Otra forma de hacerlo con el método toMap
val m2: Map[String, Int] = List(("a", 1), ("d", 4)).toMap
```

Podemos así mismo aplicar operaciones básicas sobre los mapas:

```
// recuperar claves existentes con apply
m.apply("a") // o m("a")

// claves existentes con get
m.get("a") // Devuelve un tipo Option

// Si usas un apply con llaves no existentes habrá una excepción

```

```
// recuperar todas las llaves y todos los valores
m.keys // Todas las claves
m.values // Todos los valores
```

La implementación básica de estos iterables viene dada por una colección y el tipo general `view`. Este es una colección vaga que nos da eficiencia, no detallaremos en estos apuntes su funcionamiento. Lo único que necesitamos de esto es que podemos convertirlo a cualquier tipo de colección con conversores como el `toList`, `toSet` o `toMap`:

```
m.keys.toSet // Convertidas las claves a un conjunto
m.values.toList // Convertidos los valores a una lista
```

Podemos también convertir valores opcionales a colecciones de tipos:

```
Some(1).toList
Some(1).toSet
```

Las HOF `map` y `filter` también están disponibles para los mapas

```
// Valores mapeados
m.view.mapValues((v: Int) => v > 0)
```

```
// Mapear entradas completas, no solo valores
m.map((k: String, v: Int) => k.length + v)
```

```
// Filter también devuelve un iterable general
m-filter((k: String, v: Int) => k > "a")
```

Podemos obtener un mapa de una lista de pares con `toMap`:

```
val m1: Map[String, Int] = Map("a" -> 1, "b" -> 3, "a" -> 5, "c" -> 6, "b" -> 0)
```

Cabe destacar que solo un valor se guarda para cada clave, si queremos todos los valores, hemos de usar `groupBy`:

```
List("a" -> 1, "b" -> 3, "a" -> 5, "c" -> 6, "b" -> 0)
	.groupBy((k, v) => k) 
	.view.mapValues(l => l.map(_._2))
```

#### Conjuntos (Sets)

Los conjuntos son colecciones desordenadas de elementos únicos. Los siguientes conjuntos son iguales:

```
// construir un set con ocurrencias repetidas
val s1 = Set(1, 1, 2, 3, 6, 3)

// Sin ocurrencias repetidas
val s2 = Set(1, 2, 3, 6)

// igualdad de conjuntos
s1 == s2 // Son iguales porque se ignoran las ocurrencias repetidas

// En cambio si comparamos listas, pues NO son iguales
List(1, 1, 2, 3, 6, 3) == List(1, 2, 3, 6)
```

Operaciones comunes sobre conjuntos: `filter`, `flatMap` y `map`:

```
// filtrado de elementos
Set(1,2,3,4).filter(_ > 2)
```

```
// Mapear elementos
Set(1, 2, 3, 4).map(_ + 1)
```

```
// Flatmap de elementos
Set(1, 2, 3, 4).flatMap(e => Set(e, -e))

val s3 = Set(1, 2, 3).map((e) => Set(e, -e))
s3.flatten
```

También hay operaciones específicas como son:

- **subsetOf**

```
Set(1, 2) subsetOf Set(4, 2, 3, 1)
Set(1, 2) subsetOf Set(4)
```

- **diff**

```
Set(1, 2, 3) diff Set(2, 3)
Set(1, 2, 3) diff Set(2, 3, 7)
```

- **union**

```
Set(1, 2, 3) union Set(4, 5, 1)
```

#### Data queries

Segunda parte del tema 7, en la cual las librerías de Scala nos permiten hacer data queries. Las siguientes clases pueden modelar la estructura de una organización que consiste en departamentos, empleados y tareas de los empleados:

```

// departments

case class Department(id: Department.Id)
object Department:
    type Id = String

// tasks 

case class Task(id: Task.Id, hours: Int)
object Task:
    type Id = String

// Employees

case class Employee(id: Employee.Id, dpt: Department.Id)
object Employee:
    type Id = String

// The whole organization

case class Organization(
    departments: Map[Department.Id, Department], 
    tasks: Map[Task.Id, Task],
    employees: Map[Employee.Id, Employee], 
    knows: List[(Employee.Id, Task.Id)])

```

Esta implementación es un ejemplo de lo que llamamos un modelo de datos plano. La clave de estos modelos es que son entidades diferentes refiriéndose entre ellas usando claves. Esto es una posible instancia del modelo:

```

val org: Organization = Organization(
    Map(
        "Product"  -> Department("Product"),
        "Quality"  -> Department("Quality"),
        "Research" -> Department("Research"),
        "Sales"    -> Department("Sales")),
    
    Map("build"    -> Task("build", 3), 
        "abstract" -> Task("abstract", 5), 
        "design"   -> Task("design", 2),
        "call"     -> Task("call", 1),
        "program"  -> Task("program", 3)),
    
    Map("Alex"     -> Employee("Alex", "Product"), 
        "Bert"     -> Employee("Bert", "Product"), 
        "Cora"     -> Employee("Cora", "Research"), 
        "Drew"     -> Employee("Drew", "Research"), 
        "Edna"     -> Employee("Edna", "Research"), 
        "Fred"     -> Employee("Fred", "Sales")),
    
    List(
        ("Alex", "build"),
        ("Bert", "build"),
        ("Cora", "abstract"),
        ("Cora", "build"),
        ("Cora", "design"),
        ("Drew", "abstract"),
        ("Drew", "design"),
        ("Edna", "abstract"),
        ("Edna", "call"),
        ("Edna", "design"),
        ("Fred", "call")))

```

Los modelos de datos planos son muy cercanos a los datos relacionales comunes usados en SQL. Este es el modelo equivalente racionalmente a la base de datos de la organización:

![[Pasted image 20240517153410.png]]

De acorde con esto:

- La organización representa a la base de datos entera.
- Los miembros de esta clase corresponden a diferentes tablas de la base de datos, representada como mapeados o conjuntos. Tenemos cuatro tablas que bien se pueden observar arriba.
- El tipo clave de Map puede entenderse como la primera clave de la tabla. El tipo dato especifica la columna de la tabla. 
- Si la clave principal consiste en muchas claves, tal y como en `knows`, usamos tuplas.
- Si la tabla consiste solo de claves, usamos conjuntos en vez de mapeados.

#### Queries básicas

Las queries complejas construyen sobre las básicas que están directamente relacionadas con la estructura de los datos de modelo. En particular, están identificadas desde la clave primaria y la clave extranjera en el modelo relacional. Podemos identificar las siguientes queries en el database de la organización:

```

object BasicQueries:

    // Entities
    
    def departments(org: Organization): List[Department] = 
        org.departments.values.toList

    def departmentIds(org: Organization): List[Department.Id] = 
        org.departments.keys.toList
    
    def getDepartment(id: Department.Id)(org: Organization): List[Department] = 
        org.departments.get(id).toList

    def employees(org: Organization): List[Employee] = 
        org.employees.values.toList

    def employeeIds(org: Organization): List[Employee.Id] = 
        org.employees.keys.toList

    def getEmployee(id: Employee.Id)(org: Organization): List[Employee] = 
        org.employees.get(id).toList

    // tasks, taskIds and getTask of the organization

    def tasks(org: Organization): List[Task] =
        org.tasks.values.toList

    def tasksIds(org: Organization): List[Task.Id] =
        org.tasks.keys.toList

    def gettasks(id: Task.Id)(org: Organization): List[Task] =
        org.tasks.get(id).toList
    
    // 1-N relationships
    
    def employeeIds(dpt: Department.Id)(org: Organization): List[Employee.Id] = 
        org.employees.filter(_._2.dpt == dpt).map(_._1).toList
    
    // N-M relationships

    def capabilities(emp: Employee.Id)(org: Organization): List[Task.Id] = 
        org.knows.filter(_._1 == emp).map(_._2)
    
    // performerIds

import BasicQueries._
```

Si quisiéramos hacer un test, sería de esta manera:

```
class Test(
    f: Organization => Department.Id => List[Employee.Id]
) extends AnyFlatSpec with should.Matchers:

    "m" should "work" in: 
        f(org)("Sales") shouldBe List("Fred")

        f(org)("Research") shouldBe List("Cora", "Edna", "Drew")
```

```
def test(org: Organization)(dpt: Department.Id): List[Employee.Id] =
    org.employees
        .filter((eId, e) => e.dpt == dpt)
        .keys.toList
```

#### Queries de ejemplo

Esta sección básicamente profundiza un poco en las posibles queries. Como no son algo que vaya a caer en el examen, solamente veremos dos ejemplos:

**Ejemplo 1 - ¿Cuales son las tareas de la organización que no puede ejecutar ningún empleado?**

```
class TestImpossibleTasks(
    impossibleTasks: Organization => List[Task.Id]
) extends AnyFlatSpec with should.Matchers:
    
    "impossibleTasks" should "work" in:
        impossibleTasks(org) shouldBe 
            List("program")
```

Veamos cómo se implementa de manera funcional:

```
def impossibleTasks(org: Organization): List[Task.Id] =
    org.knows.foldLeft(ListBuffer.from(taskIds(org))):
        (impTasks, entry) => impTasks subtractOne entry._2
    .toList
```

Podemos hacerlo mejor con funciones de alto nivel de conjuntos y HOFs:

```
def impossibleTasks(org: Organization): List[Task.Id] =
    val possibleTasks = org.knows.map(entry => entry._2)
    taskIds(org) diff possibleTasks
```

Esta implementación muestra la intención de la función de forma más nítida, es más declarativa. Además, es más provechosa ya que construye sobre métodos base de la librería de Scala.

**Ejemplo 2 - ¿Cuáles son los departamentos cuyos empleados pueden todos ser capaces de hacer una tarea dada?**

```
class TestExpertDepsIn(
    expertDpts: Task.Id => Organization => List[Department.Id]
) extends AnyFlatSpec with should.Matchers:
    
    "expertDpts" should "work" in:
        expertDpts("abstract")(org).toSet shouldBe 
            Set("Quality", "Research")
```

Esta función hecha de manera imperativa es un rollo, veamos de forma funcional a través de HOFs:

```
def expertDepsIn(tsk: Task.Id)(org: Organization): List[Department.Id] = 
    departmentIds(org).filter:
        dpt => employeeIds(dpt)(org).forall:
            emp => capabilities(emp)(org).contains(tsk)
```

Y así de fácil.

#### Juegos

En esta sección se trata el uso de Scala como lenguaje orientado a objetos para replicar el Wordle dentro de Scala. Si bien puede ser útil tenerlo como conocimiento, en esta ocasión no vamos a investigar más en profundidad este temario. 

Recomiendo encarecidamente sin embargo, una ojeada al GitHub de Juanma, dónde tiene todo publicado y es un muy buen entreno para usarlo a posteriori.

Para más información, mirad en la siguiente página web:

[jserranohidalgo/urjc-gia-pd: Functional programming course @urjc (github.com)](https://github.com/jserranohidalgo/urjc-gia-pd)

Muchas gracias por leer! 