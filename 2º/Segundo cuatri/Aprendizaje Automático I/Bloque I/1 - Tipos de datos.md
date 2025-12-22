Con datos tabulados diremos que los ejemplos a partir de los cuales aprenderemos nuestro modelo están en una tabla tal que:
- cada fila = ejemplo
- columna = atributo de dicho ejemplo
Podemos distinguir varios tipos de atributos:
## Continuos
Cualquier valor en un intervalo de los reales. Como por ejemplo de menos infinito a más infinito o números concretos.

```python
# Este código genera un pandas dataframe con 10 ejemplos de 2 atributos continuos
# en el intervalo (0,1) generados de manera aleatoria

N = 10
df_continuo = pd.DataFrame({
    'Atributo 1': [random.uniform(0, 1) for _ in range(N)],
    'Atributo 2': [random.uniform(0, 1) for _ in range(N)]
})

print(df_continuo)
df_continuo.info()
```

Veamos el resultado de ejecutar el código de arriba: 
```   
Atributo 1  Atributo 2
0    0.239590    0.460580
1    0.651428    0.844460
2    0.404908    0.218350
3    0.429152    0.399100
4    0.294895    0.350442
5    0.420354    0.020448
6    0.951516    0.245469
7    0.666009    0.727250
8    0.528354    0.491630
9    0.346567    0.966367
<class 'pandas.core.frame.DataFrame'>
RangeIndex: 10 entries, 0 to 9
Data columns (total 2 columns):
 #   Column      Non-Null Count  Dtype  
---  ------      --------------  -----  
 0   Atributo 1  10 non-null     float64
 1   Atributo 2  10 non-null     float64
dtypes: float64(2)
memory usage: 292.0 bytes`
```
Observamos la simplicidad del output pero que se nota claramente que nos encontramos en intervalos específicos, en este caso siendo entre el 0 y el 1.
## Discretos
Pueden tomar un número finito de valores dentro de un intervalo. Los booleanos son un caso particular (0|1)

```python
# Este código genera un pandas dataframe con 10 ejemplos de 2 atributos discretos
# en el intervalo (-5,5) generados de manera aleatoria

N = 10
df_discreto = pd.DataFrame({
    'Atributo 1': [random.randint(-5, 5) for _ in range(N)],
    'Atributo 2': [random.randint(-5, 5) for _ in range(N)]
})

print(df_discreto)
```
## Categóricos
Pueden tomar un número finito de valores dentro de un conjunto sin relación de orden entre sus miembros. Por ejemplo en un atributo color, eligiendo entre rojo, verde o azul, siendo categórico porque no hay relación de orden entre estos.

Sin embargo con el día de la semana es categórico pero mantiene el orden de los días.
```python
# Este código genera un pandas dataframe con 10 ejemplos de 2 atributos categóricos

N = 10
df_categorico = pd.DataFrame({
    'Atributo 1': [random.choice(['hombre', 'mujer']) for _ in range(N)],
    'Atributo 2': [random.choice(['rojo', 'verde', 'azul']) for _ in range(N)],
}, dtype="category")

print(df_categorico)
df_categorico.info()
```
### Codificación
Hay una relación biyectiva entre un conjunto de categorías y el conjunto de los números naturales. Siendo que a cada elemento del conjunto de categorías se le asigna un número natural. Si lo hacemos estaremos codificando el atributo categórico. Hay dos maneras de hacer esto en Pandas:
- Con un entero a cada elemento del conjunto
- Codificación *One-Hot*
#### Codificación con enteros
Pandas distingue entre "Series" y "DataFrames". 
- Una serie es el equivalente a un array o a un vector. 
- DF es una tabla. 
Una única columna de un DF es una serie automáticamente.

Pandas nos permite codificar con enteros una serie. Si queremos codificar todos los atributos de un DF debemos recorrer sus columnas con `cat.codes`. Está bien ir creando un diccionario sobre la marcha. Para ello usaremos primero `cat.categories` y luego juntaremos códigos y categorías en la estructura de datos `dict` de Python.
```python
# En este ejemplo vamos a ver como funciona `cat.codes` y `cat.categories`
# y creamos el diccionario de códigos a categorías.

codes1 = df_categorico['Atributo 1'].cat.codes
categ1 = df_categorico['Atributo 1'].cat.categories
code_to_categ1 = dict(zip(codes1,df_categorico['Atributo 1']))

codes2 = df_categorico['Atributo 2'].cat.codes
categ2 = df_categorico['Atributo 2'].cat.categories
code_to_categ2 = dict(zip(codes2,df_categorico['Atributo 2']))

print('Diccionario código->categoría: ',code_to_categ1)
print('Diccionario código->categoría: ',code_to_categ2)
```
Si queremos asignar nosotros el código en vez de dejar a Python a elegirlo, hemos de hacer un diccionario con las categorías y su respectivo código para aplicarlo con un `map`.
```python
# En este ejemplo vamos a crear el diccionario de categorías a códigos

categorias1 = df_categorico['Atributo 1'].unique()
categ_to_code1= {string: i for i, string in enumerate(categorias1)}
categ1 = df_categorico['Atributo 1'].map(categ_to_code1)

categorias2 = ['blanco','amarillo','verde','cian','rosa','azul','morado',
               'rojo','marrón','gris','negro']
categ_to_code2= {string: i for i, string in enumerate(categorias2)}
categ2 = df_categorico['Atributo 2'].map(categ_to_code2)

print('Diccionario categoría->código: ',categ_to_code1)
print(categ1)

print('Diccionario categoría->código: ',categ_to_code2)
print(categ2)
```
Lo que hemos hecho arriba es obtener la lista de valores únicos para Atributo1 y luego asignar a cada uno el entero de su posición en lista. Mientras que para Atributo2 hemos creado una lista con todas las categorías posibles y luego hemos asignado a cada uno el entero correlativo empezando por cero.

Todo lo hecho está orientado a series de pandas (que son columnas). Si queremos cambiar todas las columnas categóricas por un código hemos de hacerlo en un bucle primero identificando las que necesitan actuación en ellas:
```python
# En este ejemplo vamos listar aquellas columnas que son categóricas
# y luego vamos a codificarlas

# 1) averiguamos las columnas categóricas
cat_cols = df_categorico.select_dtypes(include='category').columns.tolist()
# 2) creamos un dataframe con las columnas categóricas pero sin filas
df_cat_coded = pd.DataFrame(columns=cat_cols)
# 3) creamos un bucle que las recorra y las codifique, a la vez que..
#    creamos una diccionario de diccionarios para descodificar en el futuro
dict_decode={}
for col in cat_cols:
  codes = df_categorico[col].cat.codes
  code_to_categ = dict(zip(codes,df_categorico[col]))
  df_cat_coded[col] = codes
  dict_decode[col] = code_to_categ

print(df_cat_coded)
print(dict_decode)
```
#### *One-Hot*
Se crean tantas columnas como categorías diferentes hay por atributo categórico. Se realiza escribiendo un 1 en columna correspondiente a la categoría y un 0 en las demás.
## Utilidades extra
Las tablas pueden tener atributos de todos los tipos sin problema alguno. Pero a la hora de manejarlos en dfs de Pandas, es mejor que cada atributo esté bien diferenciado.

```python
df = pd.concat([df_continuo, df_discreto , df_categorico], axis=1)
df.columns = ['atbCon1', 'atbCon2', 'atbDis1', 'atbDis2', 'atbCat1', 'atbCat2']

print(df)
```

Usaremos varias librerías de Python, como las que se muestran en esta imagen:

![[Librerías ML I.png]]
En **SciKit-Learn** podemos encontrar algunos métodos de codificación similares a los vistos en Pandas. Está bien conocerlos pero no los usaremos hasta aprender modelos.
![[Codificación SciKit-Learn.png]]
## Ejercicio
Utilizar `factorize` de Pandas para crear una codificación de un atributo categórico. Di la diferencia entre este método y los usados. 
``` python
# Para la parte de factorizar podemos hacerlo de una forma simple:
import pandas as pd
etiquetas = pd.Series(['rojo', 'azul', 'rojo', 'verde'])
codigos, categorias = pd.factorize(etiquetas)
print(codigos) # [0, 1, 0, 2]
print(categorias) # Index(['rojo', 'azul', 'verde'], dtype='object')
```
Al usar `get_dummies` hemos añadido dos columnas a la tabla ("hombre" y "mujer") pero ¿cómo eliminaríamos Atributo 1?
```python
# Siempre que querramos eliminar la columna original "Atributo 1" podemos hacerlo así:
df = df.drop("Atributo 1", axis=1)

```
