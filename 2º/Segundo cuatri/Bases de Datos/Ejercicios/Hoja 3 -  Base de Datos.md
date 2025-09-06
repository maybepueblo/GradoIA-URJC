## 1º Ejercicio
De acuerdo con el esquema, indicar falsas y verdaderas
1. Verdadero
2. Verdadero
3. Falso
4. Verdadero
5. Falso
6. Verdadero
7. Verdadero
8. Falso
9. Verdadero
10. Falso
11. Verdadero
12. Verdadero
13. Falso
14. Falso
15. Verdadero
16. Falso
17. Verdadero
18. Verdadero
19. Falso
20. Falso
## 2º Ejercicio
## 3º Ejercicio

a. **Nombre y NIF de todo el personal**
```mysql
π nombre-p, NIF (PERSONAL)
```
b. **Nombre y NIF del personal del alojamiento "El pájaro loco"**
```
π nombre-p, NIF (σ nombre-aloja = "El pájaro loco" (PERSONAL))
```
c. **Nombre de las actividades de nivel "Avanzado"**
```
π nombre-activ (σ nivel = "Avanzado" (ACTIVIDADES))
```
d. **Código de las actividades que se realizan en el alojamiento "El pájaro loco" los viernes**
```
π codigo-activ (σ nombre-aloja = "El pájaro loco" ∧ dia-semana = "viernes" (REALIZA_ACITVIDAD))
```
e. **Precio de las habitaciones tipo "doble" del alojamiento "El pájaro loco"**
```
π precio (σ nombre-aloja = "El pájaro loco" ∧ tipo = "doble" (HABITACIONES))
```