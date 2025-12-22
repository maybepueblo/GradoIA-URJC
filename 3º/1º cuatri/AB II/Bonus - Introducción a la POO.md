Se da una breve pincelada a los [[Paradigmas de programación]]. 
## Complejidad del software
Viene dado por lo siguiente:
- El problema
- Gestionar el desarrollo
- Flexibilidad de las herramientas -> Si es muy flexible se puede usar de más maneras equívocas
- Impredecible -> Puede cambiar un software plenamente por cambiar un bit
### Tratar la complejidad
- **Abstraer** -> Obviar detalles/implementación y quedarte con la esencia de la idea
- **Descomponer** -> Divide y vencerás básicamente
- **Jerarquizar** -> Ordenamos los elementos, dando prioridades a los mismos
## Características de la POO
Basada en el concepto de los objetos que observamos. La esencia de un objeto te lo dan sus propiedades, esto lo denominamos métodos/comportamiento. Un objeto que:
- Recibe mensajes y responde a los mismos
- Tiene identidad
- Tiene un estado -> Serie de propiedades con una serie de valores
- Tiene un comportamiento definido

**Conceptos:**
- **Objeto** -> Abstracción de la realidad
- **Atributo** -> Propiedades que definen lo que observamos
- **Métodos** -> Operan sobre los valores de los atributos
- **Estado** -> Conjunto de valores que tiene en un estado determinado en un objeto
## UML - Lenguaje Unificado de Modelado
Lenguaje muy intuitivo que permite entender fielmente cómo se implementa un software. Es gráfico y permite visualizar, especificar, construir y documental los componentes de un sistema POO.

>[!NOTE] 
>Revisar cómo se representan todas las características siguientes en UML
## Abstracción
Se definen interfaces para comunicarse con las clases de los objetos (las partes públicas de las mismas).  Estas están compuestas por métodos (funciones) que pueden aplicarse sobre el objeto y que pueden verse como los mensajes posible.

**Cliente-servidor**
Hay un cliente que hace una petición y un servidor que le responde. Hay un contrato entre ellos que establece las responsabilidades del servidor, siempre teniendo en cuenta que el orden de las operaciones del cliente se llama protocolo.

**Calidad de una abstracción**
Revisamos los siguientes aspectos_
- **Acoplamiento** -> Que dependa poco de otra abstracción
- **Cohesión** -> Los elementos de una misma clase tienen que estar muy relacionados
- **Suficiencia y completitud** -> Lo que tengas en una clase debe ser suficiente para completar su propósito
- **Primitividad** -> Tienen que ser lo más básicas posibles sus operaciones
## Encapsulación
Ocultar los detalles de lo que haya dentro de una abstracción.
## Jerarquía
Nos permite ordenar abstracciones, hay entre objetos o entre clases e interfaces.

**De objetos**
- **Asociación** -> Uno contiene a otro
- **Dependencia o uso** -> Uno usa otro
## Modularidad
Capacidad de dividir un programa en agrupaciones de frases llamadas módulos.