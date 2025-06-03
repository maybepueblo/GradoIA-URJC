## Entidades
Tiene que haber al menos un atributo, se le reconoce como identificador principal
## Interrelación
Puede no haber atributos en este campo

**Propiedades**
- **Nombre** : la distingue del resto
- **Grado**: número de entidadesal que la conectamos
- **Papel/Rol** de cada relación, manera de leerlo, no es obligatorio
- **Cardinalidad**: Número mínimo y máximo de ejemplares de una entidad que pueden estar interrelacionados con un ejemplar de la otra, u otras entidades que participan en la interrelación
- **Tipo de correspondencia**
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
## Dependencia en Existencia y en Identificación
Como los tipos de entidad, los tipos de interrelación los clasificamos en:
- **Regulares**: dos tipos de entidad regulares.
- **Débiles**: un tipo de entidad débil con uno regular.
Son bastante descriptivos los nombres pero el de existencia marca una necesidad en la interrelación entre entidades y el de identificación, que es un tipo especial de existencia, da otro sentido, individualizando cada entidad de otras (para dar más info).
## Generalización/Especialización
Consideramos un caso especial de asociación entre varias entidades y una entidad general. La asociación corresponde a la noción de es_un

![[EjGen_Esp.png]]
Estas jerarquías en el modelado surgen de dos formas distintas surgen de formas distintas:
- **Generalización** -> Dos o más entidades comparten varios atributos y/o interrelaciones, de donde deducimos existencia de una entidad de nivel superior.
- **Especialización** -> Entidad con ciertos atributos/interrelaciones para unos ejemplares, pero no para otros.
**Herencia** -> atributo, interrelación, del supertipo pasa a ser un atributo o interrelación de los subtipos de forma implícita.

![[Pasted image 20250226115838.png|1000]]
Veamos estas restricciones de forma individual:
- **Exclusividad**
	- Si cada ejemplar de dicho tipo de entidad sólo puede participar en uno de los tipos de la interrelación a la vez, desde que esté en los dos ya no podrá ser del otro.
- **Exclusión**
	- No puede estar impartiendo y recibiendo el mismo curso a la vez.
- **Inclusividad**
	- Si participa en uno de los tipos ha de participar necesariamente en la otra.
- **Inclusión**
	- Un ejemplar asociado a otro tipo de ejemplar ha de estar unido al mismo ejemplar mediante ambas interrelacioens
## Agregación
Permite representar tipos de entidad compuestos obtenidos por unión de otros más simples. 

Nos referimos a él como el todo, mientras que los componentes son las partes. En la agregación las cardinalidades min y max del tipo de entidad agregada siempre son (1, 1) y por eso no se indican.
- **Compuesto/Componente**
	- Deja representar que un todo o agregado se obtiene por la unión de diversas partes o componentes.
- **Miembro/Colección**
	- Permite representarlo como una colección de miembros, siendo todos de un mismo tipo de entidad y todos con el mismo rol.
