## 1. Introducción y Objetivos

Objetivos del diseño:

El diseño busca acercar el modelo de análisis al de implementación, refinándolo y descomponiéndolo en subsistemas para su desarrollo en paralelo. Su fin último es producir la arquitectura software del sistema.

Modelo de Vistas "4+1" (Kruchten, 1995):

Describe los intereses de los diferentes stakeholders. Se modela con diagramas UML:

1. **Vista Lógica (Conceptual):** Diagramas de clase, objetos, estados.
2. **Vista de Procesos:** Diagramas de actividad, comunicación, secuencia.
3. **Vista de Implementación (Física):** Diagramas de componentes.
4. **Vista de Despliegue (Física):** Diagramas de despliegue.
5. **Vista de Casos de Uso:** Unifica las anteriores.

---

## 2. Diagramas Dinámicos en UML

Modelan el comportamiento del sistema a lo largo del tiempo.

### Diagramas de Secuencia

Muestran la interacción de objetos ordenados temporalmente.

- **Elementos:**
    - **Línea de vida (_Lifeline_):** Objeto o actor participante (ej. `nombreobjeto:nombreclase`). 
    - **Barras de activación:** Indican cuándo el participante está activo (opcionales).
    - **Mensajes:** Síncronos (esperan respuesta), Asíncronos (no bloquean) y de Retorno.

### Diagramas de Actividad

Describen flujos de trabajo o lógica de negocio como una secuencia. Usan nodos de inicio/fin, acciones (rectángulos), decisiones (rombos) y flujos (flechas).

### Diagramas de Máquinas de Estado

Muestran los estados por los que pasa un objeto y las transiciones motivadas por eventos. Son útiles para objetos con ciclos de vida complejos.

---

## 3. Diagramas de Estructura e Implementación

### Diagrama de Despliegue

Describe la disposición física de los recursos (hardware/software).

- **Nodo:** Unidad computacional (servidor, dispositivo) que puede contener componentes. Se suelen indicar direcciones IP o protocolos de comunicación (TCP/IP, HTTP).

### Diagrama de Componentes

Modelan el empaquetado físico en unidades reutilizables (librerías, ejecutables, ficheros). Implementan interfaces y clases del diseño.

### Diagrama de Paquetes

Organizan el diseño en subsistemas o capas. No debe haber paquetes vacíos (salvo en análisis) y definen espacios de nombres.

---

## 4. Estilos Arquitectónicos

Ayudan a organizar paquetes y clases siguiendo principios de diseño.

1. **Capas (_Layers_):** Organización vertical. Un paquete superior usa servicios del inferior (relación `<<import>>`). Ej. Presentación -> Negocio -> Datos.
2. **Cliente/Servidor:** Tres capas horizontales (_tiers_) distribuidas comúnmente en máquinas distintas.
3. **Eventos (Publish-Subscribe):** Comunicación horizontal desacoplada mediante generación y consumo de eventos .
4. **Pipe & Filter:** Proceso de datos a través de filtros secuenciales (común en procesamiento de streams).
5. **MVC (Modelo-Vista-Controlador):** Separa datos (Modelo), interfaz (Vista) y lógica de control (Controlador).

---

## 5. Vista Estática: Diagrama de Clases

Describe la estructura del sistema (conceptos del mundo real o software).

**Elementos de una clase:**

- **Atributos:** Datos del objeto. Visibilidad: Privado (`-`), Protegido (`#`), Público (`+`).
- **Operaciones/Métodos:** Comportamiento.

**Relaciones entre clases:**

- **Asociación:** Conexión semántica básica. Tiene multiplicidad (1..*, 0..1), roles y navegabilidad.
- **Agregación (Rombo blanco):** "Todo/Parte" débil. La parte puede vivir sin el todo.
- **Composición (Rombo negro):** "Todo/Parte" fuerte. La parte muere si desaparece el todo.
- **Dependencia (`<<use>>`):** Un cambio en el elemento independiente afecta al dependiente.
- **Generalización (Herencia):** Relación "es un tipo de".
- **Realización:** Una clase implementa el comportamiento definido por una interfaz.

---

## 6. Patrones de Diseño (Clásicos)

Soluciones reutilizables a problemas recurrentes en un contexto determinado.

### A. Patrones Creacionales (Instanciación)

- **Builder:** Centraliza la creación de objetos complejos paso a paso.
- **Singleton:** Garantiza una única instancia de una clase.
- **Abstract Factory:** Crea familias de objetos relacionados sin especificar sus clases concretas.
- **Prototype:** Crea nuevos objetos clonando una instancia existente.

### B. Patrones Estructurales (Composición)

- **Adapter (Wrapper):** Adapta una interfaz incompatible para que pueda ser usada por otro cliente.
- **Facade:** Proporciona una interfaz unificada y simple a un subsistema complejo.

### C. Patrones de Comportamiento (Interacción)

- **Observer:** Define una dependencia uno-a-muchos. Cuando un objeto cambia, notifica a sus dependientes automáticamente.
- **Publish-Suscribe:** Los remitentes envían mensajes no programados a suscriptores.
- **Mediator:** Encapsula la comunicación entre objetos para reducir el acoplamiento (comunicación indirecta).
- **Strategy:** Permite elegir el algoritmo (estrategia) a usar en tiempo de ejecución.

---

## 7. Patrones de Diseño de IA

Resuelven problemas específicos de sistemas inteligentes e integran IA con ingeniería software tradicional.

- **Layered Caching Strategy:** Usa una caché para responder rápido a _queries_ frecuentes antes de llamar al LLM, permitiendo _fine-tuning_ con los datos guardados.
- **Multiplexing AI Agents:** Descompone una tarea compleja y la asigna a un "panel de expertos" (agentes o modelos pequeños especializados).
- **Graph of Thoughts (GoT):** Modela el razonamiento como un grafo arbitrario (refinar, agregar, retroceder pensamientos) para mejorar la salida.
- **RAG con Knowledge Graphs:** Integra grafos de conocimiento para dar precisión y contexto a los LLMs .

---

## 8. Model Context Protocol (MCP)

Estándar _open-source_ para conectar asistentes de IA a sistemas externos (datos, herramientas).

**Arquitectura:**

1. **MCP Host:** Aplicación de IA (ej. Claude Desktop) que inicia la conexión.
2. **MCP Client:** Mantiene la conexión con el servidor (dentro del Host).
3. **MCP Server:** Proporciona acceso a recursos (BD, ficheros, servicios).

**Características:**

- **Capas:** Transporte (HTTP/Stdio) y Datos (JSON-RPC 2.0).
- **Herramientas (Tools):** Funciones ejecutables por el LLM (ej. `searchFlights`).
- **Prompts:** Plantillas reutilizables para estandarizar interacciones.
- **Sampling:** El servidor puede pedir al Host que complete algo usando el LLM (Human-in-the-loop o razonamiento del modelo).
- **Elicitación:** Mecanismo estructurado para que el servidor pida información al usuario a través del cliente.