## Diseño relacional
### Metodología
Podemos abordarlo de dos formas:
- **Directo** -> Relaciones, atributos y restricciones a partir del análisis del mundo real
- **Metodológicamente** -> Partir de esquema conceptual (como un modelo E/R) y transformarlo en un esquema relacional
En ambos casos puede haber errores, es esencial analizar el esquema final usando **normalización**
### Transformación de un Esquema E/R a un Esquema Relacional
Queremos convertir un E/R a uno lógico relacional normalizado. Las reglas de transformación son fundamentales para este proceso. 

**Reglas básicas**
- **Entidades**: Cada entidad se convierte en una relación con sus atributos
- **Interrelaciones**:
	- **N:M**: Se transforma en una nueva relación
	- **1:N**: Se propaga la clave de la entidad del lado "1" a la relación del lado "N" (regla general)
	- **1:1**: Se propaga la clave en uno o ambos sentidos, o crear una nueva relación
### Atributos multivaluados y compuestos
- **Multivaluados** -> Se transforman en una nueva relación
- **Compuestos** -> Se descomponen en atributos simples
### Generalizaciones (Tipos y Subtipos)
Existen tres opciones para transformar generalizaciones
- **Opción A** -> Una sola tabla con un atributo discriminante
- **Opción B** -> Tablas separadas para el tipo y los subtipos
- **Opción C** -> Tablas independientes para cada subtipo
### Específico y físico
Optimiza el esquema lógico para mejorar el rendimiento. Algunas técnicas incluyen:
- **Índices:** Mejoran el acceso a datos
- **Cluster:** Agrupa tablas relacionadas para acelerar consultas
- **Particionamiento**: Divide tablas grandes en partes más manejables
## Normalización
### Introducción
Es proceso para eliminar redundancias y anomalías en las bases de datos. Un diseño inadecuado puede causar:
- **Anomalías de inserción:** No se pueden insertar datos sin información redundante
- **Anomalías de borrado**: Se pierde información al borrar datos
- **Anomalías de modificación:** Inconsistencias al actualizar datos
### Dependencias funcionales
Una dependencia funcional (X→Y) indica que el valor de X determina el valor de Y.
**Ejemplo** -> En una tabla `Estudiante`, `Cod_E -> Nombre_E`, `Ciudad`

**Cierre de un descriptor (Algoritmo de Ullman)**
Calcula todos los atributos determinados por un descriptor X.
**Ejemplo:**
- Dado DF={A→B,B→C,C→D}, el cierre de A es A+={A,B,C,D}

**Claves Candidatas**
Conjunto K es clave si:
1. K -> todos los atributos de la relación
2. Ningún subconjunto de K cumple lo anterior
### Formas Normales
#### 1FN
Todos los atributos son atómicos (sin grupos repetitivos)
#### 2FN
Está en 1FN. Todos los atributos no principales dependen completamente de la clave.
#### 3FN
Está en 2FN. No hay dependencias transitivas (atributos no principales que dependen de otros no principales)
#### FNBC (Forma Normal de Boyce - Codd)
Todos los determinantes son claves candidatas
### Proceso de descomposición
Una descomposición ha de ser:
- **Sin pérdida de información:** La unión natural de las relaciones resultantes debe reconstruir la original
- **Conservación de dependencias:** Todas las DF originales deben preservarse
**Ejemplo de descomposición sin pérdida:**
- Dado R(A,B,C) con DF = {A -> B}
	- R1(A, B) y R2(A, C) es una descomposición sin pérdida porque A es clave común de R1 y R2 además de ser clave en la relación.