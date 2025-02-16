# Diseño conceptual
## Entidades
Tiene que haber al menos un atributo, se le reconoce como identificador principal
## Interrelación
Puede no haber atributos en este campo

**Propiedades**
- Nombre : la distingue del resto
- Grado: número de entidadesal que la conectamos
- Papel/Rol de cada relación, manera de leerlo, no es obligatorio
- Cardinalidad: Número mínimo y máximo de ejemplares de una entidad que pueden estar interrelacionados con un ejemplar de la otra, u otras entidades que participan en la interrelación
- Tipo de correspondencia
	- 1:1 -> Empleado dirige un departamento y un departamento tiene su director
	- 1:N -> Empleado pertenece a departamento y un departamento puede tener múltiples empleados
	- N:M -> Empleado puede trabajar en muchos proyectos y en un proyecto pueden trabajar muchos empleados
## Atributos 

>[!NOTE]
>Los siguientes tipos de atributos que se van a listar pueden ser intercalables. Es decir, pueden compartir propiedades y estar estrechamente relacionados. Siendo por ejemplo un atributo tanto opcional como multivaluado, o así.
### Compuesto
Aquel que se define sobre más de un dominio
### Multivaluado
Puede tomar varios valores para una misma entidad particular. Por tanto, puede recibir más de un valor. Lo señalamos poniendo una flecha hacia el nombre del dato.
### Opcionales
Si queremos incluir la inexistencia de valores tenemos que señalarlo con líneas discontinuas
### Derivado
Sus valores se obtienen a partir de otros ya existentes. Tenemos que explicar en el esquema cómo se calcula dicho valor. Por ejemplo podríamos decir que para un curso que tiene ediciciones, para hallar el num_ediciones que es un derivado, se haría contando las ediciones que ha tenido ese curso