## Etapas
Conocemos el modelado conceptual como el proceso de representar el mundo real en un esquema que pueda ser entendido y utilizado para diseñar una base de datos. Este proceso se divide en dos etapas principales:
- **Analizar requisitos**
	- Describimos el mundo real, identificando elementos importantes a ser representados en nuestra base de datos.
		- *Ejemplo* -> Si diseñamos una base de datos para una empresa, necesitamos identificar cosas como empleados, departamentos, proyectos, etc.
- **Conceptualizar**
	- Tomamos la descripción y la transformamos en un esquema conceptual normalizado. 
	- Esto significa pues que hemos organizado los elementos identificados en el análisis de requisitos en un formato estructurado, usando conceptos como entidades, atributos y relaciones.
## MC
Aquí definimos cómo vamos a representar los datos en la bd. Aquí usamos herramientas como el [[Modelo E - R extendido]]. 
### Pasar de un esquema descriptivo a conceptual
Usamos la lingüistica para esto, analizando frases en lenguaje natural para identificar los elementos del modelo. Nos guiamos por las siguientes pautas:
- **Sustantivos**
	- Representan entidades. Por ejemplo en "Los departamentos solicitan empleados", tanto "departamentos" como "empleados" son entidades.
	- Los nombres propios serían ejemplares de una entidad.
- **Verbos transitivos o frases verbales**
	- Interrelaciones entre entidades. Por ejemplo en "Los departamentos solicitan empleados" el verbo "solicitar" indica relación entre "departamentos" y "solicitados"
- **Preposiciones o frases preposicionales**
	- Interrelaciones o asociaciones entre entidad y atributos. Por ejemplo en "El área del departamento", "área" podría ser un atributo o una entidad relacionada.
- **Otros**
	- **Verbos "ser" y "tener"**
		- "ES UN" es generalización. Por ejemplo "tanto un analista como un programados son empleados" siendo analista y programados tipos especializados.
		- "TIENE" da relación entre entidades o asocia atributos a entidades.
			- Relación: "Los empleados tienen un jefe"
			- Atributo: "Los empleados tienen nombre y apellido"
	- **Número de entidades (sing/pl)**
		- Indica cardinalidad de relaciones.
			- *Ejemplo* -> "Un empleado participa en uno o varios proyectos" y "En un proyecto participan varios empleados" indica una relación de N:M.
	- **Objeto de datos como entidad o atributo**
		- Consideramos un objeto como entidad en lugar de atributo en los siguientes casos:
			- Si el objeto tiene otros atributos asociados. Por ejemplo si las áreas de un depar tienen atributos como "responsable" o "fecha" es mejor crear la entidad. 
			- Si está relacionado con otras entidades. Si el "área" fuera un atributo de "departamento" no podríamos representar relaciones entre "área" y empleados.
	- **Atributos repetidos en distintas entidades**
		- Si un mismo atributo aparece en varias entidades es posible que exista una interrelación no identificada entre estas entidades. 
			- *Ejemplo* -> Si "nombre" aparece en "empleados" y "clientes" podría haber una relación entre estas dos entidades que no se ha detectado.