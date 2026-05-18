## 1. Cinemática: Concepto General

La cinemática es la rama de la mecánica que estudia el movimiento de un cuerpo sin considerar masas ni fuerzas. 

En robótica, la **cinemática de posición** busca las relaciones entre la localización del elemento terminal y las coordenadas articulares del robot, y tiene dos enfoques complementarios:

**Cinemática directa:** dados los ángulos articulares y la geometría de los eslabones, determinar la posición y orientación del elemento terminal. Es decir: (q₁, q₂, ..., qₙ) → (x, y, z, α, β, γ).

**Cinemática inversa:** dada la posición y orientación deseada del elemento terminal, determinar los ángulos articulares necesarios. Es decir: (x, y, z, α, β, γ) → (q₁, q₂, ..., qₙ).

Ambas dependen también de las características estructurales del robot: sus grados de libertad y el tipo de articulaciones.

---
## Grado de Libertad (GDL)

Un **grado de libertad** es cada parámetro independiente necesario para definir completamente la posición y orientación de un robot en el espacio. Los robots manipuladores industriales suelen tener **6 GDL**.

Ejemplos intuitivos: un punto en una línea tiene 1 GDL; un punto en un plano tiene 2 GDL (X e Y); un objeto libre en el espacio tiene 6 GDL (3 traslaciones + 3 rotaciones).

La **cadena cinemática** es el conjunto de eslabones y articulaciones del robot. Decimos que una articulación controla la posición relativa de los dos eslabones que conecta. Las articulaciones más comunes son:
- **De revolución:** permiten un giro alrededor de un eje (1 GDL).
- **Prismáticas:** permiten un desplazamiento lineal a lo largo de un eje (1 GDL).

Ambas restringen el movimiento a una única dirección, por lo que aportan exactamente 1 GDL cada una.
### Espacio de trabajo
Es el conjunto de posiciones y orientaciones que puede alcanzar el elemento terminal. Delimita el alcance del robot y puede dar lugar a **singularidades** o a problemas sin solución en cinemática inversa, cuando el objetivo está fuera de dicho espacio.

---
## Cinemática Directa

### Método Geométrico
Para robots con pocos GDL se pueden usar relaciones trigonométricas directas. Por ejemplo, para un robot planar de 2 eslabones (longitudes l₁ y l₂) con articulaciones de revolución q₁ y q₂:
- x = l₁·cos(q₁) + l₂·cos(q₁ + q₂)
- y = l₁·sin(q₁) + l₂·sin(q₁ + q₂)
Es un método **no sistemático**, válido para casos sencillos pero difícil de generalizar.
### Matriz de Transformación Homogénea
Para robots más complejos se utiliza el álgebra matricial. La posición relativa entre dos eslabones consecutivos se describe mediante una **matriz de transformación homogénea** 4×4, que combina rotación y traslación:

$$^{(i-1)}_i A= \begin{pmatrix} r_{11} & r_{12} & r_{13} & d_x \\ r_{21} & r_{22} & r_{23} & d_y\\ r_{31} & r_{32} & r_{33} & d_z \\ 0  & 0 & 0 & 1 \end{pmatrix}$$

La posición total del extremo respecto a la base se obtiene multiplicando en cadena todas las matrices de cada eslabón:

$$⁰ᵢT = ⁰₁A · ¹₂A · ²₃A · ... · ⁽ⁱ⁻¹⁾ᵢA
$$
### Método de Denavit-Hartenberg (D-H, 1955)

Es el método **sistemático** estándar para obtener la cadena cinemática. Consiste en asignar sistemas de coordenadas a cada eslabón de forma conveniente, de modo que el paso de un sistema al siguiente quede descrito por solo **4 parámetros**:

|Parámetro|Descripción|
|---|---|
|**θᵢ**|Ángulo de rotación alrededor del eje Zᵢ₋₁|
|**dᵢ**|Desplazamiento a lo largo del eje Zᵢ₋₁|
|**aᵢ**|Distancia a lo largo del eje Xᵢ|
|**αᵢ**|Ángulo de rotación alrededor del eje Xᵢ|

La matriz de cada eslabón resulta de combinar 4 transformaciones elementales (rotación en Z, traslación en Z, traslación en X, rotación en X):
$$ {}^{i-1}_{i}A = \begin{bmatrix} \cos\theta_i & -\cos\alpha_i \cdot \sin\theta_i & \sin\alpha_i \cdot \sin\theta_i & a_i \cdot \cos\theta_i \\ \sin\theta_i & \cos\alpha_i \cdot \cos\theta_i & -\sin\alpha_i \cdot \cos\theta_i & a_i \cdot \sin\theta_i \\ 0 & \sin\alpha_i & \cos\alpha_i & d_i \\ 0 & 0 & 0 & 1 \end{bmatrix} $$
#### Pasos del algoritmo D-H:
1. **Asignar sistemas de referencia** siguiendo las reglas de D-H (numeración de eslabones, ejes Z sobre los ejes de articulación, ejes X en la normal común, sistema dextrógiro).
2. **Construir la tabla D-H** con los cuatro parámetros (θᵢ, dᵢ, aᵢ, αᵢ) para cada articulación.
3. **Calcular las matrices ⁱ⁻¹ᵢA** de cada eslabón sustituyendo los parámetros.
4. **Multiplicar todas las matrices** para obtener la matriz T total, que da la posición y orientación del extremo respecto a la base.
#### Ejemplo: Robot cilíndrico de 4 GDL
La tabla D-H resultante es:

| Art. | θᵢ  | dᵢ  | aᵢ  | αᵢ  |
| ---- | --- | --- | --- | --- |
| 1    | θ₁  | L₁  | 0   | 0°  |
| 2    | 90° | d₂  | 0   | 90° |
| 3    | 0°  | d₃  | 0   | 0°  |
| 4    | θ₄  | L₄  | 0   | 0°  |

Multiplicando las cuatro matrices se obtiene la matriz T final, que expresa la posición (dx, dy, dz) y orientación del extremo en función de los parámetros articulares θ₁, d₂, d₃ y θ₄.

---

## 4. Cinemática Inversa

La cinemática inversa busca los valores articulares que producen una posición y orientación deseadas en el extremo del robot. Es más útil en la práctica que la cinemática directa (permite programar el robot para alcanzar objetos en posiciones concretas), pero presenta mayor dificultad computacional y varios problemas inherentes:

- **Múltiples soluciones:** puede haber varias configuraciones articulares que alcancen el mismo punto en el espacio.
- **Sin solución:** si el objetivo está fuera del espacio de trabajo del robot.

Dado su complejidad matemática, habitualmente se resuelve **por software**. También tiene aplicaciones en animación de personajes para videojuegos.

---

## 5. Cinemática del Movimiento

Más allá de la posición, la cinemática del movimiento estudia cómo se desplaza el robot considerando **posición, velocidad y aceleración**. Es fundamental para garantizar movimientos suaves y continuos, y para evitar cambios bruscos de aceleración que pudieran dañar el sistema. Tiene aplicación en robots que siguen trayectorias complejas para evitar obstáculos, y en robótica blanda (_soft robotics_), donde el control del movimiento es esencial para la seguridad humana.