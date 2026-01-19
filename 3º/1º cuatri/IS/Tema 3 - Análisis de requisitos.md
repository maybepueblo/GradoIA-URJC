## 1. Definición y Conceptos Básicos

¿Qué es un requisito software?

Son las funciones, características y restricciones que debe cumplir el producto final. Es decir, una capacidad o característica que debe poseer un sistema.

**Estudio de viabilidad:**

Elemento previo fundamental, determinado primariamente por el coste.

**El Contrato:**

Se firma un contrato por el cual regirse, poniendo un límite para evitar la saturación de trabajo. Esto brinda una base sólida para el diseño software y reduce los riesgos de implementación.

---

## 2. Ingeniería de Requisitos (IR)

Es el proceso de recopilación, análisis y documentación de los requisitos. Sus tareas principales son:

- **Obtener requisitos (Elicitación):** Identificar y analizar las necesidades del cliente.
- **Analizar y negociar requisitos:** Refinar la obtención de necesidades y el negocio, identificando restricciones.
- **Gestionar y documentar/especificar:** Documentar estas necesidades de forma precisa y no ambigua, y clasificar los requisitos.
- **Validar y verificar requisitos:** Comprobar que sean detallados, no ambiguos y no duplicados.    
- **Evolución de requisitos:** Actualizar e identificar nuevas necesidades ante cambios.    

> [!QUOTE] Importancia (Ley de Brooks)
> 
> "La parte más difícil de construir un sistema es saber qué construir... Ninguna otra parte del trabajo afecta tanto al sistema si se hace mal, ni es tan difícil de corregir más adelante".

---

## 3. Tipos de Requisitos

### Según el nivel de abstracción

1. **Requisitos de Usuario:** Servicios en lenguaje natural.
    - _Ejemplo: El sistema debe poder identificar al mejor goleador._
2. **Requisitos del Sistema:** Restricciones y descripciones técnicas.
    - _Ejemplo: Una de las funciones es identificar a los mejores goleadores por partido en base a unos datos almacenados en tiempo real._
3. **Especificación Software (ERS):** Lo que necesitamos; sirve de base para el diseño e implementación.
    - _Ejemplo: Al registrar al mejor goleador almacenamos su nombre, edad, num goles por partido, media de goles y minutos jugados por partido._  

### Según su naturaleza

- **Funcionales:** Todo lo que debe hacer el sistema (servicios y reacciones a entradas).
- **No funcionales:** No aportan funcionalidad nueva, pero mejoran aspectos de su funcionamiento (seguridad, rendimiento, etc.).
- **De Dominio:** Restricciones derivadas del dominio de aplicación (legales, físicas, éticas).

---

## 4. Entendimiento del Problema

Es crucial entender el dominio del sistema antes de construirlo.

### Modelo de Dominio

Describimos los conceptos y términos importantes, así como objetos y operaciones.

- **Análisis:**
    - Entrevistar a expertos del dominio.
    - Producir un **glosario de términos**.
    - Describir objetos y operaciones importantes.
    - Uso de diagramas de análisis.

### Modelo de Negocio

Describe los procesos asociados al negocio para comprenderlos:

- Cómo se realiza un proceso de negocio.
- Para cada proceso definir: trabajadores, operaciones y responsabilidades.
- Identificar casos de negocio y actores.
- **Representación:** Se usan diagramas de casos de uso y de actividades.

> [!NOTE] Relaciones en Casos de Uso (UML)
> 
> - **`<<extend>>`**: Agrega comportamiento opcional.
>     
> - **`<<include>>`**: Incluye comportamiento obligatorio (reutilización).
>     

---

## 5. Análisis y Modelado (Profundización)

Para estructurar el sistema antes del diseño detallado, se usan conceptos de análisis:

### Clases de Análisis

Son abstracciones de las clases reales del diseño:

- **Interfaz (Límite):** Interacción sistema-actores (Pantallas).
- **Control:** Lógica de negocio y coordinación.
- **Entidad:** Información persistente (Datos).

### Paquetes de Análisis

Organizan elementos buscando **alta cohesión** (relación fuerte interna) y **bajo acoplamiento** (poca dependencia externa).

---

## 6. Calidad del Software (ISO 25010)

Los Requisitos No Funcionales (RNF) definen la calidad. Según la ISO 25010 se clasifican en:

1. **Adecuación Funcional**
2. **Eficiencia de Desempeño**
3. **Compatibilidad**
4. **Usabilidad**
5. **Fiabilidad**
6. **Seguridad**
7. **Mantenibilidad**
8. **Portabilidad**

**Evaluación (ATAM):** Método para analizar compromisos (_trade-offs_). _Ejemplo: Aumentar seguridad puede reducir rendimiento_.

---

## 7. Recomendaciones de Especificación

- **Redacción:** Precisa y no ambigua.
- **Identificación:** Separar claramente RF, RNF y restricciones.
- **Unicidad:** Los RF y de dominio se seleccionan una vez; los RNF pueden afectar a varias partes.