## 1. Introducción a los SBC

Definición:

Los SBC (Knowledge-Based Systems) son sistemas que incorporan una base de conocimiento y algoritmos para simular el razonamiento humano, considerándose que poseen cierta "inteligencia".

**Características:**

- Se aplican en dominios diversos (médico, militar, transporte).
- A menudo dependen de sensores para extraer contexto3.
- Usan un **motor de inferencias** para razonar sobre reglas y heurísticas.
- Evolucionaron hacia la **Ingeniería del Conocimiento** (años 70-80) y los Sistemas Expertos (SE).

**Ejemplos Históricos:**

- **DENDRAL (1971):** Análisis químico.
- **MYCIN (70s):** Enfermedades infecciosas.
- **Hearsay:** Reconocimiento de voz.
- **PROSPECTOR:** Análisis geológico.

---

## 2. Representación del Conocimiento

Existen diversas técnicas para estructurar la información en un dominio determinado.

### Técnicas Clásicas

- **Ontologías:** Usan lenguajes como OWL, RDF.
- **Redes Semánticas:** Grafos de conocimiento (ej. _Animal -> es un -> Mamífero_).
- **Reglas:** Estructuras lógicas tipo `IF (condición) THEN (consecuencia)`.
- **Lógica Booleana:** Forma Normal Conjuntiva.

### Redes Neuronales y LLMs

- **LLMs (Large Language Models):** Usan la arquitectura **Transformer** (Google, 2017), que procesa datos en secuencia mediante mecanismos de atención.
    - **Attention ("Attention is all you need"):** Clave para manejar dependencias entre palabras. Usa _Queries_ (Q), Claves (K) y Valores (V).
- **CNN (Redes Neuronales Convolucionales):** Efectivas para imágenes, aprenden características profundas mediante capas de convolución y _pooling_.
- **RNN (Redes Recurrentes):** Capturan dependencias a largo plazo en secuencias.

---

## 3. Tipos de Aprendizaje y Ciclo de Vida

**Tipos de Aprendizaje:**

1. **Supervisado:** Datos de entrenamiento etiquetados (entrada + respuesta deseada).
2. **No supervisado:** Datos sin etiquetar; busca patrones o estructuras.
3. **Semi-supervisado:** Combina ambos.
4. **Por refuerzo (RL):** Aprende interactuando con un entorno mediante recompensas y castigos.

**Machine Learning (ML) vs. Deep Learning (DL):**

- **ML:** Entrena computadoras para tomar decisiones. Modelos lineales, árboles, etc..
- **DL:** Tecnología avanzada de ML que simula el cerebro humano usando redes neuronales profundas con múltiples capas ocultas.

Ciclo de Vida ML:

Adquisición de datos -> Preparación -> Modelado -> Evaluación -> Despliegue -> Operaciones.

---

## 4. Entrenamiento con LLMs

Los LLMs siguen fases específicas debido a su complejidad:

1. **Pre-training:** Entrenamiento con un gran corpus de datos para aprender el lenguaje (computacionalmente costoso).
2. **Fine-tuning:** Ajuste del modelo pre-entrenado con tareas específicas y _datasets_ etiquetados más pequeños.
3. **Prompt Engineering:**
    - **Zero-shot:** Sin ejemplos.
    - **Few-shot:** Con algunos ejemplos en el prompt.
    - **RAG (Retrieval Augmented Generation):** Aumenta el prompt con datos de una base de conocimiento externa (ej. base de datos vectorial) para dar contexto y reducir alucinaciones.

---

## 5. Diseño y Arquitectura Software

El diseño de sistemas de IA/SBC sigue principios de arquitectura software, adaptando patrones.

### Modelado de Algoritmos (UML)

- Las estrategias de búsqueda se modelan con el **Patrón Strategy** (ej. `RouteStrategy` con subclases `Walking`, `PublicTransport`).
- Los estados se definen como atributos de clase.

### Estilos Arquitectónicos

- **Capas (Layers):** División horizontal o vertical de responsabilidades.
- **Pipe & Filter:** Ideal para el pre-procesado de datos (_Data Transformation_ -> _Feature Extraction_). La salida de un filtro es la entrada del siguiente.
- **Plataformas:** Uso de herramientas como Apache Kafka para datos en tiempo real.

### Arquitectura ML

Se divide fundamentalmente en dos fases:

1. **Entrenamiento:** Crea el modelo predictivo.
2. **Inferencia:** Usa el modelo para predecir.

### Recomendaciones de Diseño

- Evitar relaciones cruzadas o cíclicas entre paquetes.
- No dejar paquetes vacíos y dividir responsabilidades claramente (Vista, Modelo, Controlador).
- **Diseño de Agentes (RL):** Se pueden modelar clases como `Environment`, `Agent`, `Policy` (política de decisiones), `Reward` y `Action`.