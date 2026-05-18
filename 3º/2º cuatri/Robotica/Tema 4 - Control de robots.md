## Control automático
Un sistema posee control automático cuando regula magnitudes físicas de forma autónoma. Existen dos configuraciones principales:
- **Lazo abierto:** Funciona sin realimentación y se utiliza en procesos predecibles. El temporizador es el elemento más común en esta configuración.
- **Lazo cerrado:** Utiliza realimentación mediante un **sensor (H)** para medir la salida y compararla con la **consigna**. La diferencia entre ambas genera el **error**, que permite corregir el sistema.

Comparativa de Configuraciones

| **Característica**               | **Lazo abierto** | **Lazo cerrado** |
| -------------------------------- | ---------------- | ---------------- |
| **Uso de sensores**              | No necesario     | Necesario        |
| **Corrección de errores**        | No               | Sí               |
| **Complejidad**                  | Baja             | Alta             |
| **Robustez ante perturbaciones** | Baja             | Alta             |

---
## Modelado y análisis dinámico
Para controlar un sistema, este se simplifica mediante una **planta (G)** y se modela con ecuaciones diferenciales que describen cómo cambian sus variables en el tiempo.
- **Transformada de Laplace:** Es una herramienta esencial que convierte ecuaciones diferenciales en algebraicas, pasando del dominio del tiempo ($t$) al de la frecuencia ($s$).
- **Función de Transferencia ($G(s)$):** Es el cociente entre la salida ($Y(s)$) y la entrada ($U(s)$) en el dominio de Laplace.
- **Estabilidad:** Un sistema es estable si, ante una entrada acotada, su salida también lo está. Esto se cumple si todos los **polos** (raíces del denominador de $G(s)$) tienen parte real negativa.

**Sistemas de Segundo Orden**
Se definen por su **frecuencia natural ($\omega_n$)** y su **factor de amortiguamiento ($\zeta$)**. Según el valor de $\zeta$, el sistema puede ser:
- **Oscilatorio:** $\zeta = 0$.
- **Subamortiguado:** $0 < \zeta < 1$.
- **Críticamente amortiguado:** $\zeta = 1$.
- **Sobreamortiguado:** $\zeta > 1$.

---
## Estrategias de Control Clásico
La regulación busca mejorar la estabilidad, precisión y respuesta transitoria del sistema.
### Control Todo o Nada (On/Off)
- **Simple:** Aplica acción máxima por debajo de la consigna y nula por encima.
- **Limitación:** Genera "microencendidos" que pueden dañar el sistema.
- **Con Histéresis:** Define un rango aceptable para reducir el número de conmutaciones, aunque permite oscilaciones dentro de dicho rango.
### Control PID
Es el más versátil y utilizado en la industria. Se compone de tres acciones:
- **Proportional (P):** Reacciona al **presente**. Reduce el error y aumenta la velocidad, pero no elimina el error por completo.
- **Integral (I):** Reacciona al **pasado**. Acumula el error a lo largo del tiempo y logra eliminar el error en régimen permanente, aunque puede aumentar la inestabilidad.
- **Derivativa (D):** Reacciona al **futuro** (tendencia). Anticipa cambios y mejora la estabilidad, pero es muy sensible al ruido de medición.
### Ajuste de Parámetros
El ajuste de los valores $K_p$, $K_i$ y $K_d$ puede realizarse mediante **métodos empíricos** (como Ziegler-Nichols o ajuste manual) o **analíticos** (basados en modelos matemáticos y especificaciones de diseño).
## Control avanzado
Para sistemas complejos (no lineales o con gran incertidumbre), se emplean estrategias de **Control Avanzado**:
- **Control en Cascada:** Usa un lazo interno para estabilizar parte del sistema antes del lazo externo.
- **Control Adaptativo:** Ajusta los parámetros en tiempo real según las condiciones cambiantes.
- **Control Robusto:** Diseñado para garantizar estabilidad ante perturbaciones o errores de modelado.
- **Control Predictivo:** Utiliza modelos matemáticos o **redes neuronales** para predecir el comportamiento futuro y optimizar la acción de control.