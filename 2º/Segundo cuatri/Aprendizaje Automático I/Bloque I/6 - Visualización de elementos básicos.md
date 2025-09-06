## Recta
Damos un problema y vemos las formas de implementarlo en código:
![[Problema dibujar rectas.png]]
Veamos cómo definir la recta:
```python
def recta(x1, x2):
	return 0.5*x1 - x2 - 2

recta(4,0),recta(3,0.5),recta(2,-1),recta(-2, 3)
```
Esto devuelve:
```
(0.0, -1.0, 0.0, -6.0)
```
## Plano
![[Problema dibujar planos.png]]
```python
def plano(x1, x2, x3):
	return 1 + x2 + 2*x1 - x3

plano(4, -3, 6), plano(3, -2.5, 4), plano(-2, 1, -2), plano(-1, -1, 2)
```
Esto nos devuelve:
```
(0, 0.5, 0, -4)
```
## Hiperplano
![[Problema dibujar hiperplano.png]]
```python
def hiperplano(x1, x2, x3, x4, x5):
	return 1 - x5 - 3*x4 + 5*x3 - 2*x2 + x1

hiperplano(-2, -3, 3, 6, 2), hiperplano(1, -1, 1, 2, 3), hiperplano(1, -2, -3, 5, -4), hiperplano(1, 0, 0, 2, -1)
```
Esto nos devuelve:
```
(0, 0, -20, -3)
```
