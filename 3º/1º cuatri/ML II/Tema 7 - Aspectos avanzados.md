Dividimos este tema en: **Aprendizaje de representaciones**, que estudia cómo las redes codifican información (véase [[Representación del Conocimiento y Razonamiento I]]), y los **Modelos Generativos**, centrados en la creación de nuevos datos (principalmente GANs).
## 7.1 Aprendizaje de representaciones
El aprendizaje profundo no solo es clasificación, es fundamentalmente el proceso de aprender una **representación jerárquica de los datos** que sea útil para resolver tareas.
### 1. Concepto de representación
Una representación es un sistema formal que hace explícitas ciertas entidades o tipos de información.
- **Representaciones jerárquicas:** Las redes profundas construyen representaciones en niveles. Igual que el lenguaje humano tiene una jerarquía de abstracción (palabras -> frases -> significados), las redes aprenden características simples que se combinan para formar conceptos complejos.
- **Eficiencia de profundidad:** Ciertas funciones requerirían un número exponencial de neuronas en una red plana ("shallow", véase [[Tema 4 - Redes de neuronas]]) para ser aproximadas, mientras que una red profunda lo logra eficientemente gracias a esta jerarquía.
### 2. Estudio de caso: AlexNet (2012)
El análisis de AlexNet nos permite entender qué aprende realmente una red:
- **Primera capa (Convolucional)**: Aprende **filtros de Gabor** y detectores de color/bordes.
	- *Funcionamiento:* La convolución es una **correlación cruzada**. Matemáticamente, el producto escalar $w · p = ||w||||p||cos \alpha$ es máximo cuando la entrada $p$ se alinea con el filtro $\omega (\alpha=0)$. Es decir, los filtros se activan cuando "ven" un patrón idéntico a ellos mismos.
	- **Capas profundas:** Las activaciones muestran que emergen detectores de objetos complejos (caras, texturas) sin que nadie haya etiquetado explícitamente "ojos" o "ruedas".
	- **Espacio latente (Embedding Space):** La última capa totalmente conectada (4096 dimensiones en AlexNet) es el **descriptor** de la imagen.
		- *Propiedad clave:* La distancia euclídea (L2) en este espacio mide la **similitud semántica**. Imágenes con píxeles muy diferentes (ej. un elefante de perfil y otro de frente) estarán cerca en este espacio latente, mientras que la distancia de píxeles (L2 directa) fallaría estrepitosamente.
### 3. Estrategias de aprendizaje
Para mejorar la eficiencia de datos y la generalización, existen cuatro estrategias principales para aprender representaciones:
#### A. Transfer Learning (Aprendizaje por transferencia)
- **Idea:** Reutilizar el conocimiento adquirido en una tarea $T1$ (donde hay muchos datos, ej. ImageNet) para resolver una tarea $T2$ (con pocos datos)
- **Fundamento**: Muchos factores que explican las variaciones en $T1$ (bordes, texturas) son útiles para $T2$
#### B. Multi-task Learning (Aprendizaje multi-tarea)
- **Idea:** Resolver múltiples tareas simultáneamente (ej. segmentación semántica + estimación de profundidad + normales de superficie) usando una **representación compartida**.
- **Ventajas:** Puede mejorar la tasa de acierto, eficiencia de inferencia y generalización.
- **Riesgo: Transferencia Negativa** -> Si las tareas no están relacionadas o interfieren entre sí (gradientes conflictivos), el rendimiento empeora. Depende críticamente de dónde se bifurca la red (si se comparten pocas o muchas capas).
#### C. Self-supervised learning (Aprendizaje auto-supervisado)
- **Idea**: Entrenar con datos **sin etiquetar** generando las etiquetas automáticamente a partir de los propios datos (tareas pretexto)
- **Ejemplos de tareas pretexto**:
	- *Inpainting:* Tapar un trozo de imagen y pedir a la red que lo reconstruya
	- *Puzzles*: Desordenar parches de la imagen y pedir a la red que los ordene
	- *Colorización*: Predecir el color de una imagen en blanco y negro.
- **Constrastive learning (Aprendizaje por contraste)**: Técnica dominante actualmente. Consiste en acercar en el espacio latente las representaciones de parejas "positivas" (ej. dos recortes de la misma imagen) y alejar las "negativas" (recortes de imágenes distintas)
#### D. Domain Adaptation
- **Idea**: Entrenar un modelo usando datos de un **dominio fuente** (ej. simulador, videojuegos) y aplicarlo a un **dominio objetivo** (mundo real), reduciendo la brecha entre ambos mediante técnicas adversarias (Adversarial Domain Adaptation).
## 7.2 Modelos Generativos
A diferencia del aprendizaje supervisado discriminativo (predecir $y$ dado $x$), los modelos generativos aprenden la **distribución de los datos** para crear nuevos ejemplos $x_{new}$
### 1. Variables latentes y propiedades deseables
El objetivo es mapear un espacio de variables latentes $z$ (simple, ej. ruido gaussiano) al espacio de datos $x$ complejos. Un buen modelo generativo debe tener:
- **Muestreo eficiente:** Generar datos rápido
- **Alta calidad:** Indistinguibles de los reales
- **Cobertura:** Capaz de generar toda la variedad de datos reales (no solo unos pocos tipos)
- **Espacio latente desentrelazado**: Modificar una dimensión de $z$ debería cambiar una propiedad semántica específica (ej. color de pelo) sin afectar al resto
### 2. GANs (Generative Adversarial Networks)
Sistema compuesto por dos redes neuronales que compiten en un juego de suma cero (**Minmax problem**).
- **Generador ($G$)** Toma ruido aleatorio $z$ y genera una imagen falsa $x^*=G(z)$. Intenta **engañar** al discriminador.
- **Discriminador ($D$)**: Recibe imágenes reales $x$ y generadas $x^*$. Intenta clasificar si son reales (1) o falsas (0).
**Función de pérdida (Minmax)**: El entrenamiento busca parámetros $\theta$ (generador) y $\ohm$ (discriminador) tal que:$$\underset{G}{min}\space\underset{D}{max}\space V(D,G)=E_{x\sim P_{data}}[log D(x)]+E_{z\sim p_z}[log(1-D(G(z)))]
$$
- El discriminador quiere maximizar el acierto ($log D(x)$ alto para reales, $log(1-D(G(z)))$ alto para falsas)
- El generador quiere minimizar esa cantidad (que $D(G(z))$ sea cercano a 1)
### 3. DCGAN (Deep Convolutional GAN)
Arquitectura estándar para generar imágenes estables
- **Características clave**:
	- Uso de **Batch Normalization** en ambos (excepto capa de salida del Generador y entrada del Discriminador).
	- **Leaky ReLU** en el Discriminador (para evitar gradientes muertos)
	- **Tanh** en la salida del Generador (para escalar píxeles entre -1 y 1)
	- Reemplazo de pooling por **Convoluciones con Stride** (discriminador) y **Convoluciones transpuestas** (generador).
### 4. Problemas de las GANs
- **Mode Collapse (Colapso de modo)**: El generador descubre una imagen que engaña bien al discriminador y la produce constantemente, ignorando la entrada $z$ y perdiendo variedad.
- **Mode Dropping**: El generador es incapaz de generar ciertos tipos de datos (ej. genera caras pero nunca con barba)
- **Desvanecimiento del gradiente:** Si el discriminador es **demasiado bueno**, distingue perfectamente reales de falsas. La función de pérdida se aplana y el generador deja de recibir gradientes útiles para aprender.
### 5. Wasserstein GAN (WGAN)
Soluciona el problema de estabilidad y gradientes
- **Cambio fundamental:** No usa la entropía cruzada. Usa la **distancia de Wasserstein** (Earth Mover's distance)
- **Implementación:**
	1. Elimina el sigmoide final del discriminador (ahora llamado "crítico")
	2. La función de pérdida es simplemente la diferencia de esperanzas: $D(x)-D(G(z))$
	3. **Restricción de Lipschitz:** Para que funcione, los pesos del discriminador deben limitarse (clipping) a un rango pequeño (ej. $[-0.01, 0.01]$). Esto evita que la función crezca abruptamente.
### 6. Variantes avanzadas
- **Conditional GANs (cGAN)**: Se introduce información extra (etiqueta de clase o imagen) tanto en el generador como en el discriminador para controlar qué se genera.
	- *Ejemplo:* **Pix2Pix** (traducción de imagen a imagen, ej. mapa -> foto satélite)
- **CycleGAN**: Permite traducir entre dominios **sin datos emparejados** (ej. convertir caballos en cebras sin tener la foto exacta del mismo caballo siendo cebra). Usa la "Cycle consistency loss": $x \rightarrow G(x) \rightarrow F(G(x)) \approx x$
- **StyleGAN:** Arquitectura avanzada que inyecta el ruido y el estilo en diferentes escalas, logrando un realismo fotográfico y control sobre estilos gruesos (pose) y finos (color de ojos).