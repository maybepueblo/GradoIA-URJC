## Redes Bayesianas

### Introducción y Conceptos Básicos

- Las redes bayesianas son herramientas y gráficos probabilísticos que resultan de gran valor para modelar, comprender y resolver problemas que involucran sucesos inciertos, basándose en opiniones de expertos o en la extracción de datos empíricos.
    
- A estas estructuras también se las conoce bajo múltiples denominaciones, tales como redes de Bayes, redes de creencias, redes de decisión o simplemente modelos bayesianos.
    
- Tienen un amplio rango de aplicación analítica (descriptiva, diagnóstica, predictiva y prescriptiva) para tareas como el modelado causal, el razonamiento, la toma de decisiones bajo incertidumbre y la detección de anomalías.
    
- En la visualización gráfica de estas redes, cada variable (ya sea de naturaleza continua o discreta) está representada por un nodo.
    
- Las influencias directas entre las distintas variables se modelan utilizando enlaces o arcos conectados entre los nodos.
    
- La ausencia de un enlace directo entre dos nodos no implica que sean variables completamente independientes, puesto que podrían conectarse indirectamente a través de terceros nodos o volver su dependencia dependiente de las nuevas evidencias que se incorporen al modelo.
    

### Representación del Conocimiento

- El sistema de Judea Pearl estructura el conocimiento mediante modelos causales compuestos por "nodos concepto" y las relaciones de influencia causa-efecto establecidas en la red, formando comúnmente grafos dirigidos sin ciclos conocidos como poliárboles.
    
- A nivel estructural, un conjunto de nodos $X_{i}$ toma valores concretos contenidos dentro de dominios finitos delimitados $D_{i}$.
    
- **Separabilidad Direccional**: Este es un principio de descomposición esencial en las redes bayesianas, el cual establece que la influencia de un nodo $Z$ sobre un nodo $X$ depende de manera exclusiva del nodo intermedio $Y$.
    
- Siguiendo el principio anterior, si un nodo $Y$ separa a $X$ del resto de nodos $w_{1},...,w_{n}$, la probabilidad se puede simplificar algorítmicamente a $P(x|y,w_{1},...,w_{n})=P(x|y)$.
    
- Para cuantificar estas influencias condicionales, se emplean matrices de probabilidad condicional sustentadas en juicios estadísticos y humanos.
    
- Las redes posibilitan tres flujos distintos de evaluación lógica: el razonamiento predictivo (desde las causas hacia los efectos), el razonamiento de diagnóstico (desde los efectos hacia las causas subyacentes) y el razonamiento intercausal (evaluando relaciones matemáticas entre causas concurrentes).
    

### Mecanismos de Inferencia Probabilística

- El razonamiento base de toda inferencia en este sistema es el teorema de Bayes clásico: $P(A|B)=\frac{P(B|A)\cdot P(A)}{P(B)}$.
    
- Para facilitar el cómputo de la red, la suma de las probabilidades divisoras se agrupa dentro de una constante de normalización $\alpha$, simplificando la expresión final a $P(A|B)=\alpha\cdot P(B|A)\cdot P(A)$.
    
- El mecanismo de inferencia global descompone la credibilidad final de un nodo aprovechando la premisa de separabilidad direccional abordada en el apartado anterior.
    
- Frente a un nuevo evento de evidencia $e$, el nodo $X$ es capaz de particionar analíticamente dicha evidencia en dos porciones: $e_{x}^{+}$ (representa la evidencia de los antecesores o causas de X) y $e_{x}^{-}$ (representa la evidencia de los sucesores o efectos derivados de X).
    
- La credibilidad o creencia final sobre un suceso específico procesado por un nodo se define matemáticamente como la ecuación $Cr(x)=P(x|e)=\alpha\cdot\pi(x)\cdot\lambda(x)$.
    
- El parámetro inferior $\lambda(x)$ engloba la probabilidad de la evidencia originada en los efectos del nodo, estipulada como $\lambda(x)=P(e_{x}^{-}|x)$.
    
- El parámetro superior $\pi(x)$ recoge la probabilidad propia del nodo teniendo en consideración la evidencia que envían sus nodos causas, descrita como $\pi(x)=P(x|e_{x}^{+})$.
    
- En implementaciones prácticas, la propagación de estas variables es estrictamente unidireccional: los valores $\pi$ transitan únicamente desde arriba hacia abajo (flujo causa-efecto), mientras que los valores $\lambda$ solo fluyen desde abajo hacia arriba (flujo efecto-causa).
    

## Modelo MYCIN

### Introducción al Sistema

- MYCIN es un sistema experto desarrollado en la Universidad de Stanford en la década de los años 70.
    
- Operacionalmente, se trata de un sistema basado de manera íntegra en reglas, diseñado específicamente para facilitar procesos de toma de decisiones.
    
- Su propósito original en la medicina era actuar como un sistema de consulta técnica para realizar un diagnóstico preciso y determinar un tratamiento certero frente a enfermedades de tipo infeccioso, alojando unas 500 reglas de validación en su código.
    
- Para efectuar el diagnóstico, el sistema interroga iterativamente al clínico sobre los síntomas exactos presentes en el paciente y los compara de forma automática con su base de datos de infecciones documentadas.
    
- Una vez procesados los síntomas, el algoritmo despliega una lista de posibles enfermedades subyacentes, ordenando a estas según su severidad intrínseca y la probabilidad porcentual de afectación del paciente.
    
- Simultáneamente, el sistema sugiere un abanico de tratamientos óptimos recomendados para el usuario, que engloba antibióticos, la ejecución de cirugías preventivas o correctivas y procedimientos médicos anexos.
    
- La arquitectura profunda de MYCIN cuenta con tres partes en estrecha interacción: el propio "sistema de consulta" para recomendaciones terapéuticas, el "sistema de explicaciones" (que narra lógicamente cómo ha deducido su respuesta y qué conclusiones ha extraído de la consulta), y el "sistema de adquisición de conocimiento", una interfaz vanguardista para que médicos expertos sin nociones de programación pudieran actualizar la base de datos autónomamente.
    

### Representación del Conocimiento e Incertidumbre

- En lugar de emplear sistemas lógicos inmensamente complejos, MYCIN modela afirmaciones sobre los pacientes utilizando formulación proposicional estructurada en tripletas: concepto-atributo-valor (ejemplo: paciente.fiebre = alta).
    
- El conjunto dinámico de reglas dentro de la base de conocimiento enlaza múltiples tripletas para generar deducciones operativas mediante la notación teórica: $c_{i}.a_{j}=v_{k},...,c_{h}.a_{r}=v_{d}\rightarrow c_{l}.a_{s}=v_{m}$.
    
- MYCIN construye árboles lógicos interconectando las premisas de dichas reglas en dirección hacia su objetivo final propuesto.
    
- La metodología de barrido del árbol consiste en tres pasos fundamentales que se repiten: identificar todas las reglas relacionadas con el objetivo central, expandir la búsqueda hacia reglas correlacionadas con las premisas individuales que subyacen al objetivo y, finalmente, detener la búsqueda cuando un dato sea conocido empíricamente o deba consultarse externamente al usuario.
    
- Para separarse de los límites de las probabilidades meramente estadísticas puras en favor del criterio médico humano y para modelar la "ignorancia temporal" sin comprometer la predicción global, el sistema desecha el uso clásico estadístico e introduce una métrica de pesos probatorios subjetivos.
    
- Esta nueva heurística subjetiva de medida toma el nombre de "Factor de Certeza" (FC), y se bifurca en dos variables matemáticas: una Medida de Credibilidad (MC) y una Medida de Incredibilidad a favor de refutar la hipótesis (MI).
    
- Ambas medidas actúan como vectores opuestos integrados en una misma magnitud algebraica donde $FC(h,e)=MC(h,e)-MI(h,e)$.
    
- Cualquier afirmación analizada posee, por ende, un $FC(h)$ con rangos numéricos continuos entre $-1$ (evidencia abrumadora de falsedad) y $+1$ (seguridad fáctica y total de veracidad).
    

### Mecanismos de Inferencia

- Para operar lógicamente con los Factores de Certeza calculados, MYCIN introduce un mecanismo de propagación ascendente en su estructura de árbol (de abajo hacia arriba, desde las premisas obtenidas hasta su resolución).
    
- El proceso matemático para esta propagación de evidencias aglutina dos procesos secuenciales diferentes: la "Propagación Vertical" y la "Acumulación Horizontal".
    
- **Propagación Vertical**: Proceso para extrapolar matemáticamente el Factor de Certeza deducido desde las premisas iniciales hasta arribar finalmente a la conclusión total de cada regla.
    
- Al evaluar un bloque de premisas conectadas conjuntamente ($FC(e)$), el sistema selecciona el máximo entre ambos componentes si se usa un operador lógico de disyunción OR: $FC(A\vee B)=max(FC(A),FC(B))$.
    
- Análogamente, cuando evalúa una serie de premisas conectadas por un operador condicional lógico estricto AND o conjunción, opta por el peso mínimo penalizador: $FC(A\wedge B)=min(FC(A),FC(B))$.
    
- Una vez deducido el subtotal para las premisas, la certeza de la conclusión final se calcula por multiplicidad: $FC(h)=FC(e)*FC(h,e)$, asumiendo implícitamente que $FC(e)>0$ de lo contrario sería cancelada por completo equivaliendo a un rotundo cero.
    
- **Acumulación Horizontal**: Aplica como procedimiento algorítmico aglutinante cuando confluyen convergencias lógicas procedentes de varias reglas independientes sobre una misma hipótesis a evaluar.
    
- Para unificar estos choques de evidencia en un mismo plano, los factores confirmantes positivos se consolidan separadamente de los factores de incredibilidad (negativos), calculando una sola vez el cruce total final unificado para el diagnóstico.
    
- Si ambas reglas presentan el mismo perfil direccional (es decir, $FC1*FC2>0$), estas se potencian algebraicamente sin llegar nunca al desborde matemático según la ecuación límite: $FC=FC1+FC2-|FC1|*FC2$.
    
- Ante cruces conflictivos de signos contrarios o indeterminados que no cumplan la premisa previa, el sistema emplea la técnica de ponderación: $FC=\frac{FC1+FC2}{1-min(|FC1|,|FC2|)}$.
    

### Ventajas y Desventajas del Modelo MYCIN

| **Aspecto**              | **Consideraciones Técnicas**                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Ventajas Principales** | MYCIN otorga un entorno e interfaz de naturaleza extremadamente intuitiva y posee una fácil computación interna para un rendimiento ágil. Confiere una altísima facilidad y apertura para modelar directamente las métricas de certeza extrayendo el juicio directo de estadistas o expertos.                                                                                                                                                                                         |
| **Problemas Clásicos**   | Es estructuralmente susceptible a sufrir posibles inconsistencias o fisuras derivadas de contradicciones lógicas presentes en el conocimiento original insertado por el experto humano. A esto hay que sumarle una grave limitación subyacente de su algoritmo: no evalúa explícitamente posibles correlaciones secundarias presentes de antemano entre sus premisas base, y tampoco reconoce correlaciones implícitas ligadas estrictamente a sus conclusiones finales diagnósticas. |