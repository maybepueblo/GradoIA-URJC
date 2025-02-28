**Modelo**
- Construcción mental a partir de lo real, en la que reproducimos componentes principales y relaciones de esta realidad analizada.
**Modelo de datos**
- Conceptos, reglas y convenciones que permiten describir y manipular datos del mundo real a posteriormente almacenar.
**Esquema**
- Representación de un mundo real

Los modelos de datos tienen dos tipos, unos conceptuales y otros lógicos. Cuando toque definir modelos conceptuales ([[Modelo E - R extendido]]), los cuales se abstraen de la implementación, no tendrán parte dinámica, sólo estática:
- Esto es así porque es un modelo abstracto, no cercano a la operación y por tanto no nos interesa la operativa.
Veamos una comparativa entre estos tipos de modelos:

| **CONCEPTUALES**             | LÓGICOS (CONVENCIONALES)          |
| ---------------------------- | --------------------------------- |
| No se implementan en SGBD    | Implementados en SGBD comerciales |
| Independientes de SGBD       | Dependen de este                  |
| Abstracción                  | Más próximos al ordenador         |
| Mayor semántica              | Menor semántica                   |
| Alto nivel                   | Implementación                    |
| Interfaz usuario/informático | Interfaz informático/sistema      |
|                              | Mediación entre externo e interno |
¿Cómo podríamos decir que se relaciona un modelo de datos y un lenguaje de datos entonces? Se relacionan en que un lenguaje de datos es la suma de un modelo de datos más la sintaxis. Veamos algunos ejemplos:
- SQL = MD Relacional + Sintaxis
- QUEL = MD Relacional + Sintaxis
- OQL = M Objetos + Sintaxis




