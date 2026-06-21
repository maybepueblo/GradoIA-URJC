## Índice

1. [Motivación](#1-motivación)
2. [Introducción a PyTorch](#2-introducción-a-pytorch)
3. [Google Colab](#3-google-colab)
4. [Tensores en PyTorch](#4-tensores-en-pytorch)
5. [Autograd](#5-autograd)
6. [Datasets y Dataloaders](#6-datasets-y-dataloaders)
7. [Arquitecturas](#7-arquitecturas)
8. [Optimizadores en PyTorch](#8-optimizadores-en-pytorch)
9. [Flujo completo de entrenamiento](#9-flujo-completo-de-entrenamiento)

---

## 1. Motivación

Claves del auge del Deep Learning:

1. **Datos**: disponibilidad masiva de datos etiquetados (y no etiquetados).
2. **Hardware paralelizable**:
   - GPUs y TPUs altamente optimizadas para cálculos intensivos.
   - Uso eficiente de recursos gracias a librerías como CUDA.
3. **Algoritmos**: métodos que permiten optimizar funciones altamente complejas, como las redes neuronales profundas.

---

## 2. Introducción a PyTorch

### ¿Qué es PyTorch?

- Biblioteca de **código abierto para aprendizaje profundo**, desarrollada por Facebook AI Research (FAIR).
- Lanzada en **enero de 2017**; destaca por su facilidad de uso y flexibilidad.
- Muy popular en la investigación académica gracias a sus **grafos dinámicos**, que permiten construir modelos adaptativos y comprensibles.

### Comparación con otros frameworks

- **TensorFlow** (2015): inicialmente conocido por sus **grafos estáticos**, lo que complicaba la depuración. En **2019**, la versión 2.0 mejoró la usabilidad, acercándose al enfoque de PyTorch.
- **Keras** (2015): biblioteca de alto nivel que usaba TensorFlow como backend. Simplificó la creación de modelos, pero PyTorch ofrecía **más control** desde el inicio.
- **PyTorch** (2017): popularidad creciente desde 2018 en la comunidad académica. La **versión 1.0 (2018)** integró capacidades para producción.

### Ventajas de PyTorch

- **Simplicidad y legibilidad**: sintaxis intuitiva y fácil para programadores familiarizados con Python.
- **Soporte para grafos dinámicos**: presente desde 2017, ideal para investigación y prototipado rápido.
- **Comunidad y ecosistema**: en 2020 PyTorch superó a TensorFlow en citas académicas; fuerte soporte de Meta (Facebook) y una comunidad activa.

---

## 3. Google Colab

Entorno en la nube habitual para ejecutar PyTorch.

**Ventajas:**
- **Acceso a GPU y TPU gratuitas**: acelera el entrenamiento de modelos.
- **Entorno preconfigurado**: incluye PyTorch y otras bibliotecas por defecto.
- **Basado en la nube**: accesible desde cualquier lugar sin hardware potente.

**Desventaja principal:**
- **Limitaciones en la depuración**: menos eficiente por la ejecución en la nube y la falta de integración directa con entornos locales.

---

## 4. Tensores en PyTorch

### Concepto

- Un **tensor** se entiende matemáticamente como una **matriz multidimensional**.
- Es la **unidad fundamental** para almacenar datos en PyTorch.
- Son similares a los arrays de **NumPy**, con la ventaja de poder **procesarse en GPU**.
- Se crean y manipulan con `torch.tensor`.

```python
import torch
import numpy as np
```

### Inicialización de tensores

**A partir de datos (listas):**

```python
data = [[1, 2], [3, 4]]
x_data = torch.tensor(data)

print(x_data.dtype)   # tipo de dato (p. ej. torch.int64)
print(x_data.shape)   # dimensiones
print(x_data.device)  # dispositivo (cpu / cuda)
```

**A partir de NumPy:**

```python
np_array = np.array(data)
x_np = torch.from_numpy(np_array)   # comparte memoria con el array
```

También es habitual encontrar el constructor `torch.Tensor` (con mayúscula):

```python
np_tensor = torch.Tensor(np_array)
```

> **Diferencia clave**: `torch.tensor(...)` infiere el `dtype` a partir de los datos, mientras que `torch.Tensor(...)` fuerza por defecto el tipo `float32`. Conviene usar `torch.tensor` para conservar el tipo original.

**A partir de otro tensor** (hereda propiedades salvo que se sobrescriban):

```python
x_ones = torch.ones_like(x_data)                  # conserva propiedades de x_data
x_rand = torch.rand_like(x_data, dtype=torch.float)  # sobrescribe el dtype
```

**A partir de unas dimensiones (`shape`)** con valores constantes o aleatorios:

```python
shape = (2, 3,)
rand_tensor  = torch.rand(shape)   # aleatorios uniformes en [0,1)
ones_tensor  = torch.ones(shape)   # unos
zeros_tensor = torch.zeros(shape)  # ceros
```

### Operaciones con tensores

PyTorch ofrece una amplia variedad de operaciones, altamente optimizadas para GPU:

- **Aritméticas básicas.**
- **Álgebra lineal**: producto punto a punto, transposición, inversión de matrices, SVD, etc.
- **Redimensionado**: funciones como `reshape` y `view`.
- **Agregación**: `mean`, `sum`, `max`, etc.

**Indexación estilo NumPy:**

```python
rand_tensor = torch.rand((3, 4, 5))

scalar = rand_tensor[1, 2, 2]   # un elemento concreto
rand_1 = rand_tensor[:, 1, :]   # todos los elementos para un índice fijo de una dimensión
rand_1.shape                    # la dimensión indexada "desaparece"
```

Uso de `...` (Ellipsis) y conservación de dimensiones con *slicing*:

```python
rnd = torch.randn(4, 4, 8, 2, 3)

# Último índice de la 3ª dimensión (la dimensión se elimina):
rnd[:, :, -1, :, :].shape
rnd[:, :, -1, ...].shape
rnd[..., -1, :, :].shape

# Igual, pero MANTENIENDO la dimensión (con slice -1:):
rnd[:, :, -1:, :, :].shape
rnd[:, :, -1:, ...].shape
rnd[..., -1:, :, :].shape
```

**Producto de matrices, producto punto a punto y concatenación:**

```python
tensor = torch.randn(3, 4)

# Producto de matrices (3 formas equivalentes)
y1 = tensor @ tensor.T
y2 = tensor.matmul(tensor.T)
y3 = torch.rand_like(y1)
torch.matmul(tensor, tensor.T, out=y3)   # escribe el resultado en y3

# Producto punto a punto (element-wise)
z1 = tensor * tensor
z2 = tensor.mul(tensor)
z3 = torch.rand_like(tensor)
torch.mul(tensor, tensor, out=z3)

# Concatenación a lo largo de distintas dimensiones
concat = torch.concat([z1, z2, z3], dim=1)   # concatena por columnas
concat = torch.concat([z1, z2, z3], dim=0)   # concatena por filas

# Concatenar en una nueva (tercera) dimensión: se añade un eje con [..., None]
concat = torch.concat([z1[..., None], z2[..., None], z3[..., None]], dim=2)
```

`torch.allclose(a, b)` permite comprobar que dos tensores son numéricamente iguales.

### Interoperabilidad tensor ↔ NumPy

> **Importante**: en CPU, un tensor y su array de NumPy **pueden compartir la misma memoria**. Cambiar uno cambia el otro si se usan operaciones **in-place**.
>
> Las operaciones **in-place** (in situ) llevan un sufijo `_` y modifican el tensor directamente, sin variables auxiliares.

```python
t = torch.ones(5)
n = t.numpy()    # n comparte memoria con t

t.add_(1)        # in-place: modifica t Y n
t += 1           # también modifica ambos
```

En cambio, una operación **no in-place** crea un nuevo tensor y **desvincula** tensor y array (aumentando la memoria usada):

```python
t = torch.ones(5)
n = t.numpy()
t = t + 1        # crea un nuevo t; n NO cambia
```

### Tensores en GPU (devices)

Los tensores pueden vivir en distintos *devices* (CPU, GPU/TPU). Según el cómputo, conviene usar uno u otro para acelerar.

Comprobar disponibilidad de GPU:

```python
import torch
torch.cuda.is_available()   # True / False
```

Por línea de comandos:

```bash
!nvidia-smi
```

Definir una variable `device` para trasladar modelos y tensores de forma uniforme:

```python
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
```

Así, si no hay GPU disponible, por defecto se usa la CPU.

**Mover tensores entre dispositivos:**

```python
tensor_cpu  = torch.from_numpy(np.random.randn(100))
print(tensor_cpu.device)          # cpu

tensor_cuda = tensor_cpu.to(device)   # mover a GPU (si existe)
print(tensor_cuda.device)

# Volver a CPU: .to('cpu') o directamente .cpu()
print(tensor_cuda.cpu().device)
```

---

## 5. Autograd

### Concepto

- **Autograd** es el motor de **diferenciación automática** de PyTorch, usado para calcular los gradientes de las funciones en redes neuronales.
- Permite optimizar modelos calculando automáticamente las derivadas de la función de pérdida, **siempre que todas las operaciones se definan con funciones de PyTorch sobre tensores**.
- Internamente utiliza **backpropagation**.

### Uso de `.backward()`

Para registrar un tensor en el grafo de cómputo se activa `requires_grad=True`. Tras construir el grafo (forward) hasta el nodo final, se invoca `.backward()` y los gradientes quedan acumulados en el atributo `.grad` de cada hoja.

```python
import torch

# requires_grad=True activa el seguimiento de gradientes
a = torch.tensor([3.0], requires_grad=True)
b = torch.tensor([1.0], requires_grad=True)
c = torch.tensor([-2.0])   # sin requires_grad: NO se guardan sus gradientes en .grad

# Operaciones intermedias que construyen el grafo
h = ...   # función de a, b, c
g = ...
f = ...   # nodo final (escalar)

f.backward()           # calcula d f / d (tensores con requires_grad=True)
print(f.item())

print(a.grad)          # gradiente de f respecto a a
print(b.grad)          # gradiente de f respecto a b
print(c.grad)          # None (no tenía requires_grad)
```

**Nodos intermedios:** por defecto, los gradientes de los nodos intermedios (`h`, `g`) y del nodo final (`f`) **no se almacenan** (PyTorch los descarta para ahorrar memoria, de ahí el *warning*). Para conservarlos se usa `.retain_grad()`:

```python
h = ...
h.retain_grad()   # fuerza a almacenar el gradiente de un nodo intermedio
g = ...
g.retain_grad()
f = ...
f.retain_grad()

f.backward()
print(h.grad, g.grad, f.grad)   # ahora sí están disponibles
```

### Uso de `torch.autograd.grad`

Alternativa a `.backward()` como herramienta **genérica** para calcular gradientes puntuales:

```python
a = torch.tensor([3.0], requires_grad=True)
b = torch.tensor([1.0], requires_grad=True)
c = torch.tensor([-2.0], requires_grad=True)

h = ...
g = ...
f = ...

grad_a = torch.autograd.grad(f, a)   # gradiente de f respecto a a
print(grad_a[0].item())
```

### Diferencias entre `.backward()` y `torch.autograd.grad`

|                       | `backward()`                                | `torch.autograd.grad`                       |
|-----------------------|---------------------------------------------|---------------------------------------------|
| **Modifica `.grad`**  | Sí, almacena los gradientes en `.grad`.     | No, los devuelve explícitamente.            |
| **Uso**               | Entrenamiento con optimizadores.            | Cómputo de gradientes puntuales.            |
| **Argumentos**        | No requiere argumentos adicionales.         | Necesita especificar las variables.         |

### Caso de uso: optimización con restricciones (multiplicadores de Lagrange)

Minimizar `f(x, y) = x² + y²` sujeto a `x + y = 1`, es decir `(x + y − 1)² = 0`. Se define la Lagrangiana:

```
L(x, y, λ) = x² + y² + λ (x + y − 1)²
```

donde `λ` penaliza la violación de la restricción. La optimización se hace por **gradiente descendente**, ajustando `x` e `y` mientras se mantiene `x + y ≈ 1`.

```python
import torch

def lagrangian(x, y, lambda_1):
    f = x**2 + y**2        # función objetivo
    g1 = x + y - 1         # restricción
    return f + lambda_1 * g1**2   # Lagrangiana

learning_rate = 0.01
num_iterations = 1000

def optimize(lambda_1):
    x = torch.tensor(2.0, requires_grad=True)
    y = torch.tensor(1.0, requires_grad=True)
    for _ in range(num_iterations):
        L = lagrangian(x, y, lambda_1)
        grad_x, grad_y = torch.autograd.grad(L, [x, y])
        # Actualización manual sobre .data (no rastreada por autograd)
        x.data -= learning_rate * grad_x
        y.data -= learning_rate * grad_y
    return x.item(), y.item()
```

Para `λ` grande (p. ej. 10) la solución converge a la recta `x + y = 1`; para `λ = 0` la restricción no penaliza y se minimiza solo `x² + y²` (hacia el origen).

---

## 6. Datasets y Dataloaders

### Datasets

- Un **`Dataset`** es una colección de datos para entrenamiento y test.
- Es una **clase abstracta** que representa los datos en un formato adecuado para entrenar.
- Almacena los **datos** (p. ej. imágenes o texto) y sus **etiquetas** (p. ej. las clases en clasificación).
- Un `Dataset` personalizado debe sobrescribir **dos métodos clave**:
  - `__len__()`: devuelve el número total de ejemplos.
  - `__getitem__(idx)`: devuelve un ejemplo concreto dado un índice.
- Estos métodos permiten a PyTorch acceder a datos y etiquetas de forma eficiente durante el entrenamiento.

```python
import torch
from torch.utils.data import Dataset, DataLoader

class MyDataset(Dataset):
    def __init__(self, data, labels):
        self.data = data
        self.labels = labels

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return self.data[idx], self.labels[idx]

data   = [[1.0, 2.0], [3.0, 4.0], [5.0, 6.0], [7.0, 8.0]]
labels = [0, 1, 0, 1]

dataset = MyDataset(data, labels)
print(len(dataset))    # 4
print(dataset[0])      # ([1.0, 2.0], 0)
```

### Dataloaders

- El **`DataLoader`** carga los datos de un `Dataset` de forma eficiente y en **mini-lotes (batches)** durante el entrenamiento.
- Funcionalidades clave:
  - **Batching**: divide los datos en mini-lotes, mejorando la eficiencia.
  - **Shuffling**: mezcla aleatoria de los datos antes de cada época; permite además definir métodos de muestreo (*samplers*).
  - **Paralelización**: usa múltiples procesos para cargar datos concurrentemente, acelerando la carga (especialmente con grandes volúmenes).
- Toma un `Dataset` y devuelve **iteradores** que proporcionan lotes durante el entrenamiento.
- Muy útil cuando los datos no caben completamente en memoria.

```python
dataloader = DataLoader(dataset, batch_size=2, shuffle=True)

for batch_idx, (batch_data, batch_labels) in enumerate(dataloader):
    print(f"Lote {batch_idx + 1}")
    print("Datos:", batch_data)
    print("Etiquetas:", batch_labels)
```

> Tras pasar por el `DataLoader`, los datos se entregan agrupados como **tensores por lotes** (cada lote apila `batch_size` ejemplos), a diferencia de los elementos sueltos que devuelve el `Dataset`.

### Relación entre Datasets y Dataloaders

- El `Dataset` **contiene** los datos y etiquetas; el `DataLoader` se encarga de **cargarlos en lotes** eficientemente.
- El `Dataset` es la **"fuente de datos"**; el `DataLoader` es el **"gestor de acceso"** que organiza cómo se alimentan al modelo.
- Usar `DataLoader` mejora el rendimiento, da más control sobre la carga y facilita el manejo de grandes volúmenes de datos.

---

## 7. Arquitecturas

- **`torch.nn`** es el módulo de PyTorch para construir redes neuronales.
- Facilita su creación mediante clases de alto nivel que representan las capas de la red.
- Principales clases:
  - `nn.Linear`: capa completamente conectada (*fully connected*).
  - `nn.Conv2d`: capa convolucional 2D.
  - `nn.ReLU`: función de activación ReLU.
  - `nn.Softmax`: función de activación Softmax.
- **`nn.Module`** es la clase base para todos los modelos; contiene las funciones para definir las capas y la propagación hacia adelante (`forward()`).

### Layers (capas)

Las capas son objetos invocables que se aplican directamente sobre los tensores:

```python
import torch
from torch.nn import Linear, Sigmoid

f1 = Linear(2, 1)   # capa lineal con pesos W y sesgos b: entrada de dim 2, salida de dim 1
sigma = Sigmoid()   # activación sigmoide

x = torch.ones([2])

print(f1(x))         # salida lineal
print(sigma(f1(x)))  # salida tras la activación
```

Para reproducir el cálculo en GPU basta mover tensores (y modelo) al `device`:

```python
x = torch.ones([2]).to(device)
f1 = f1.to(device)
print(sigma(f1(x)))
```

### Models (modelos con `nn.Module`)

Para definir un modelo (o un bloque, que puede ser tan simple como una función) se hereda de `nn.Module`: se declaran los componentes en `__init__` y se define el paso hacia adelante en `forward`:

```python
from torch import nn

class Bloque(nn.Module):
    def __init__(self):
        super().__init__()
        self.f1 = torch.log
        self.f2 = torch.math.cos

    def forward(self, x):
        x = self.f1(1 + x)
        x = self.f2(x)
        return x

b1 = Bloque()
x = torch.ones([1])
print(b1(x))   # invocar el módulo ejecuta forward()
```

### Funciones de pérdida

PyTorch proporciona un amplio conjunto de funciones de pérdida en el módulo `nn`:

```python
from torch import nn

loss_fn = nn.MSELoss()   # error cuadrático medio

y_true = torch.tensor([1.0])
y_pred = torch.tensor([0.5])
loss_fn(y_pred, y_true)   # valor de la pérdida
```

---

## 8. Optimizadores en PyTorch

- Los optimizadores están en el módulo **`torch.optim`**.
- Reciben como entrada:
  - **Parámetros del modelo** (los pesos y sesgos de la red o modelo a entrenar).
  - **Tasa de aprendizaje (`lr`)**, que controla el tamaño del paso en cada actualización.
  - Opcionalmente, otros **hiperparámetros** como `momentum`, `beta1`, `beta2`, etc.
- Se instancian con el módulo `torch.optim`:

```python
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
```

---

## 9. Flujo completo de entrenamiento

A la hora de entrenar, PyTorch hace uso de Autograd. El ciclo es:

1. Se evalúan las funciones (**forward**) hasta obtener la función de pérdida (último nodo del grafo).
2. Se invoca **`backward()`** para calcular los gradientes.
3. Se **actualizan los parámetros** con ayuda del optimizador.

Esquema típico del bucle de entrenamiento (p. ej. regresión logística con `SGD` sobre `breast_cancer_dataset` de sklearn):

```python
# 1. Cargar datos, dividir en train/test y convertir a tensores
# 2. Definir el modelo (hereda de nn.Module, implementa forward)
# 3. Instanciar modelo, función de pérdida y optimizador
# 4. Entrenar; 5. Evaluar; (usar normalización para mejorar resultados)

model = LogisticRegressionModel(...)
loss_fn = nn.BCELoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

for epoch in range(num_epochs):
    optimizer.zero_grad()       # reinicia los gradientes acumulados
    y_pred = model(X_train)     # forward
    loss = loss_fn(y_pred, y_train)
    loss.backward()             # backward (calcula gradientes)
    optimizer.step()            # actualiza los parámetros
```

> **Detalle importante**: `optimizer.zero_grad()` es necesario porque los gradientes se **acumulan** en `.grad` entre iteraciones; sin reiniciarlos, se sumarían los de pasos anteriores.

### Resumen del ecosistema

| Componente        | Módulo / clase            | Función                                                |
|-------------------|---------------------------|--------------------------------------------------------|
| Datos             | `torch.tensor`            | Unidad fundamental (matriz multidimensional, GPU).     |
| Diferenciación    | `autograd` (`.backward()`)| Cálculo automático de gradientes vía backpropagation.  |
| Carga de datos    | `Dataset` / `DataLoader`  | Estructurar y servir datos en mini-lotes.              |
| Arquitectura      | `torch.nn` / `nn.Module`  | Capas y definición del `forward`.                      |
| Pérdida           | `torch.nn` (p. ej. `MSELoss`) | Mide el error entre predicción y objetivo.         |
| Optimización      | `torch.optim` (p. ej. `Adam`, `SGD`) | Actualiza los parámetros del modelo.        |
