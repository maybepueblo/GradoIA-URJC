## 12.1. Introducción a las Subastas

Una subasta involucra un subastador y N subasteros, con un protocolo que define cómo se inicia, qué acciones son posibles y cómo se adjudica el bien. El subastador puede fijar un **precio reserva** (mínimo privado por debajo del cual no vende).

Los principales tipos de subasta son:

**Subasta inglesa** — el precio sube progresivamente; gana la oferta más alta si supera el precio mínimo del subastador. Es _first-price open-cry_.

**Subasta holandesa** — el precio baja automáticamente con el tiempo; quien acepta primero se lleva el bien. También es _first-price open-cry_. Fue usada originalmente en mercados de flores.

**Subasta one-shot** — cada participante hace una sola oferta. Hay dos variantes: de mejor precio (gana quien más ofrece y paga su propia oferta) y de segundo precio o **Vickrey** (gana quien más ofrece pero paga el segundo precio más alto).

Respecto al tipo de bienes, se distinguen bienes de **valor público** (igual para todos), **valor privado** (diferente para cada participante) y **valor correlacionado** (depende de las preferencias propias y ajenas). El tema se centra en subastas one-shot de valor privado.

---

## 12.2. Subastas Vickrey

El objetivo es diseñar una subasta one-shot que cumpla tres propiedades simultáneamente:

1. **Compatibilidad con los incentivos**: declarar el valor real es la estrategia dominante de cada agente.
2. **Eficiencia en la asignación**: el bien se adjudica al agente con mayor valoración real, maximizando la suma de valoraciones.
3. **Presupuesto débilmente equilibrado**: el mecanismo no tiene que poner dinero de su bolsillo.

Antes de presentar Vickrey, se retoma el **comercio bilateral justo** del Tema 11 como contraejemplo: aunque tiene presupuesto equilibrado y es eficiente en ciertos equilibrios, **no es compatible con los incentivos** bajo ninguna noción de equilibrio, por lo que los agentes nunca declaran sus valores reales.

La **subasta Vickrey** resuelve esto formalmente así:

- La regla de asignación χ adjudica el bien al agente con la oferta más alta (v̂⁽¹⁾).
- El pago del ganador es el precio de la segunda oferta más alta (p⁽²⁾); los demás pagan una cuota de entrada k (normalmente 0).
- La utilidad de cada agente es xᵢ · vᵢ − pᵢ.

Se demuestra mediante un ejemplo (v₁=3, v₂=4, k=1) que declarar el valor real es **estrategia dominante** para cada agente, siendo (3,4) el equilibrio en estrategias dominantes. Además:

- Es **eficiente**: como cada uno declara su valor real, el bien va al agente que más lo valora.
- Tiene **presupuesto débilmente equilibrado**: la suma de pagos es p⁽²⁾ + (N−1)·k > 0. Si se incluye al subastador como jugador 0, el presupuesto es exactamente equilibrado.

---

## 12.3. Subastas VCG

La subasta Vickrey solo sirve para un bien indivisible. Para escenarios con múltiples bienes se necesitan **subastas combinatorias**, donde los agentes pujan por combinaciones de bienes ("paquetes") y sus valoraciones pueden ser superaditivas (el conjunto vale más que la suma de sus partes).

### El mecanismo VCG (Vickrey-Clarke-Groves)

Generaliza la subasta Vickrey mediante dos reglas:

**Regla de elección:** χ(v̂) = arg max_x Σᵢ v̂ᵢ(x) → se elige el resultado que maximiza la suma de valoraciones declaradas.

**Regla de pagos (coste social del agente i):** ℘ᵢ(v̂) = Σⱼ≠ᵢ v̂ⱼ(χ(v̂₋ᵢ)) − Σⱼ≠ᵢ v̂ⱼ(χ(v̂))

Es decir, cada agente paga la diferencia entre lo que obtendrían los demás **sin él** y lo que obtienen **con él**. Esto equivale al "coste social" que impone su presencia.

### Ejemplo: álbum de cromos (3 agentes, 2 bienes: M y CR)

Con las valoraciones dadas, VCG asigna M al agente 1 y CR al agente 2 (ninguno al 3), y los pagos resultan ser 1, 4 y 0 respectivamente, reflejando el impacto real de cada agente en el bienestar colectivo.

### Compatibilidad con los incentivos — demostración

Para maximizar su utilidad, el agente i quiere que VCG elija el x que maximice vᵢ(x) + Σⱼ≠ᵢ v̂ⱼ(x). Pero precisamente eso es lo que hace la regla de elección VCG cuando v̂ᵢ = vᵢ, independientemente de lo que declaren los demás. Por tanto, **declarar el valor real es siempre estrategia dominante**, lo que hace a VCG incentivo-compatible.

### Relación con Vickrey

La subasta Vickrey es un **caso especial de VCG** con un solo bien: el resultado no monetario coincide (gana quien más ofrece) y el pago también (la segunda oferta más alta), ya que sin el ganador el mejor resultado para los demás sería la segunda oferta.

### Ejemplo: red de transporte

Se aplica VCG para elegir la ruta de coste mínimo de A a F. El resultado es la ruta ABEF. Los pagos muestran que los agentes "esenciales" (pivotales) reciben utilidad positiva, mientras los no esenciales obtienen utilidad 0. Este ejemplo además **no tiene presupuesto equilibrado**.

### Propiedades generales de VCG

- **Eficiencia ex-post**: gracias a la compatibilidad con los incentivos, en equilibrio todos declaran sus valores reales y la elección maximiza el bienestar social real.
- **Presupuesto débilmente equilibrado**: se garantiza en entornos donde eliminar un agente no reduce el bienestar de los demás (p.ej. subastas simples), pero no en todos los casos.

### Limitaciones de VCG

- Es un **mecanismo directo**: exige revelar toda la información privada (la función de valor completa).
- En subastas combinatorias, el **Winner Determination Problem (WDP)** es NP-duro y hay que resolverlo N veces.
- Es vulnerable a la **colusión**: si dos agentes coordinan sus declaraciones inflándolas, pueden reducirse mutuamente los pagos sin alterar el resultado.
- Presenta **no-monotonicidad de ingresos**: añadir más agentes puede reducir los pagos totales, lo que es problemático en mercados electrónicos donde un agente puede crear fácilmente identidades ficticias.