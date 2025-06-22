
def esFactible(peso_actual, peso_max):
    return peso_actual <= peso_max

def esSolucion(beneficio_actual, beneficio_min):
    return beneficio_actual >= beneficio_min

def ABack(objetos, idx, peso_actual, beneficio_actual, peso_max, beneficio_min, seleccionados, mejor_sol):
    if beneficio_actual > mejor_sol[1] or (beneficio_actual == mejor_sol[1] and peso_actual < mejor_sol[2]):
        mejor_sol[0] = seleccionados[:]
        mejor_sol[1] = beneficio_actual
        mejor_sol[2] = peso_actual
    if idx == len(objetos):
        return
    ABack(objetos, idx + 1, peso_actual, beneficio_actual, peso_max, beneficio_min, seleccionados, mejor_sol)
    nombre, peso, beneficio = objetos[idx]
    if esFactible(peso_actual + peso, peso_max):
        seleccionados.append(nombre)
        ABack(objetos, idx + 1, peso_actual + peso, beneficio_actual + beneficio, peso_max, beneficio_min, seleccionados, mejor_sol)
        seleccionados.pop()



N, M, E = map(int, input().split())
objetos = []
for _ in range(N):
    entrada = input().split()
    nombre = entrada[0]
    peso = int(entrada[1])
    beneficio = int(entrada[2])
    objetos.append((nombre, peso, beneficio))
mejor_sol = [[], 0, 0]
ABack(objetos, 0, 0, 0, M, E, [], mejor_sol)
if mejor_sol[1] > E:
    print(" ".join(sorted(mejor_sol[0])))
    print(mejor_sol[2], mejor_sol[1])
    print("SE VA")
else:
    print(" ".join(sorted(mejor_sol[0])))
    print(mejor_sol[2], mejor_sol[1])
    print("VUELVE")
