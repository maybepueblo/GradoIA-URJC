## 1. Definición y Conceptos Básicos

**¿Qué es la Ingeniería del Software?**

Es la disciplina de ingeniería encargada de todos los aspectos relacionados con la producción de software. Abarca desde sus etapas más tempranas de especificación del sistema hasta el mantenimiento tras su puesta en marcha.

**Roles principales:**

- **Cliente:** Patrocina el desarrollo del sistema, define las necesidades y el presupuesto.
- **Usuario:** Utiliza el sistema de software para cubrir necesidades.
- **Ingeniero de Software:** Construye el sistema bajo una obligación contractual.

**Actividades clave:**

- Producción de software.
- Planificación y gestión (coste, recursos, restricciones legales).
- Procesos técnicos: requisitos, diseño, implementación y testing.

---

## 2. Orígenes y Crisis del Software

**Contexto Histórico:**

- En los años 60, el objetivo era crear sistemas con calidad y terminar con las malas prácticas.
- La **Conferencia NATO (1968)** reconoció oficialmente la "crisis del software".

**La Crisis del Software (1965-1985):**

Surgió debido al sobrecoste de los proyectos. Se define por la dificultad en escribir programas libres de defectos, comprensibles y verificables (Dijkstra, 1968).

**Causas:**

- Los proyectos no terminaban en plazo ni ajustados a coste.
- El software no cumplía las especificaciones.
- Código poco mantenible y había poca especialización de los ingenieros.
- Carencia de metodologías para sistemas complejos.

**Consecuencias:**
- Baja calidad y productividad.
- Tiempo y presupuesto excedido.
- Confiabilidad cuestionable y software ineficiente.
- Rigidez del software para evolucionar (nuevas "releases").

---

## 3. Mitos del Software

### Sobre la Gestión

- **Mito:** "La empresa ya dispone de estándares y procedimientos establecidos conocidos por todos".
    - **Realidad:** Muchas empresas no utilizan procesos ni metodologías aceptadas como en otras ingenierías.  
- **Mito:** "Si cometemos un error o vamos con retraso, siempre podemos añadir más gente".
    - **Realidad:** Añadir personas a un proyecto atrasado lo retrasa aún más debido a la sobrecarga de comunicación (_communication overhead_).

### Sobre el Cliente

- **Mito:** "Una declaración general de objetivos basta para empezar; los detalles se dan luego".
    - **Realidad:** Una mala definición inicial es la principal causa de trabajo inútil; se requiere una descripción formal y detallada.
- **Mito:** "Los requisitos cambian, pero el software es flexible y los cambios se acomodan fácil".
    - **Realidad:** El impacto del coste varía según el momento en que se presente el cambio.

### Sobre los Desarrolladores

- **Mito:** "Cuanto antes empecemos a programar, antes acabaremos".
    - **Realidad:** Cuanto más pronto se codifica, más se tarda en terminar. Entre el 50% y el 70% del esfuerzo se realiza después de la primera entrega al cliente.
- **Mito:** "Lo único que importa es que la aplicación funcione; la documentación no se usa".
    - **Realidad:** La documentación es base del desarrollo y guía fundamental para el mantenimiento.

---

## 4. Malas Prácticas vs. Ingeniería del Software

**Malas Prácticas Habituales:**

- Planificación imprecisa y falta de recopilación de datos históricos.
- Pasar directamente a la codificación sin documentar suficiente.
- No vigilar la calidad, incurriendo en **deuda técnica** (_technical debt_).
- Procesos improvisados y sacrificio de calidad para cumplir plazos.
- Ausencia de pruebas y revisiones.

**Propuestas de la Ingeniería del Software (IS):**

- Aplicar métodos, técnicas y herramientas establecidas.
- Adoptar estándares de desarrollo (IEEE, ISO, UNE).
- Construir equipos adecuados y capturar el conocimiento (decisiones de diseño).
- **Beneficios:** Reducción de costes, riesgos y tiempo; mejora de la calidad y satisfacción del cliente.

---

## 5. Complejidad del Software

Según F. Brooks (1987), la complejidad del software es una propiedad **esencial** y no accidental.

- **Complejidad Accidental:** Se debe a la manera en que intentamos solucionar el problema (tecnología).
- **Complejidad Esencial:** Es inherente al problema en sí mismo.

**Fuentes de complejidad:**

1. **Dominio del problema:** Problemas del mundo real con cientos de requisitos (funcionales y no funcionales) a veces contradictorios. Dificultad para modelar el problema.
2. **Proceso de desarrollo:** Dificultad de control, incidencias y problemas de comunicación (diferencia entre lo que el usuario necesita y lo que el desarrollador entiende).
3. **Complejidad del código:**
    - Software de miles de líneas sin modularizar.
    - Clases con tamaño excesivo (_God Class_) y dependencias cíclicas.
    - Código muerto (_dead code_) y duplicidad.
    - Antipatrones (_anti-patterns_) y elementos inestables.
    
---

## 6. Principios Fundamentales de la IS

**Gestión y Requisitos:**

- Determinar el problema antes de escribir especificaciones.
- Elegir la solución que mejor se adapte al cliente y evaluar costes.
- Dedicar esfuerzo a la captura y elicitación de requisitos, involucrando al cliente (uso de prototipos).

**Arquitectura y Diseño:**

- Evaluar alternativas de diseño y estilos arquitectónicos (capas, cliente/servidor, microservicios, eventos).
- Considerar requisitos funcionales y no funcionales (calidad).

**Testing y Calidad:**

- Las pruebas (_testing_) son fundamentales; el equipo de pruebas debe ser diferente al de desarrollo.
- **Regla de Pareto:** El 80% de los errores son causados por el 20% de los módulos.
- Usar herramientas de QA (_Quality Assurance_) y puertas de calidad (_quality gates_) antes de subir código.
- El testing temprano ahorra errores.

**Documentación:**

- Documentar todo el proceso: desde requisitos hasta el código y errores solucionados.
- Documentar el proceso de diseño y arquitectura (clave para el mantenimiento).
- Mantener la documentación actualizada.

**Equipo:**

- El equipo es clave: requiere personal cualificado, motivación y un buen jefe de proyectos.