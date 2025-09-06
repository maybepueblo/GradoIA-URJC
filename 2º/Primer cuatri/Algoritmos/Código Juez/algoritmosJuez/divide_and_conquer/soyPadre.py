
# Función improvisada que furula para crear un árbol en un diccionario
def arbol(familias):
    tree = {}
    # Para cada padre que tiene cierta dirección a un nodo hijo en nuestras familias, lo asignamos en el conjunto
    for parent, *children in familias:
        tree[parent] = children
    return tree


def calcular_niveles(arbol, niveles, actual=0, nivel=1, visitado=None):

    # Iniciamos el conjunto de visitado
    if visitado is None:
        visitado = set()

    if actual in visitado:
        return

    visitado.add(actual)
    niveles[actual] = nivel

    if actual not in arbol or not arbol[actual]:
        return

    hijos = arbol[actual]
    medio = len(hijos)//2

    for hijo in hijos[:medio]:
        calcular_niveles(arbol, niveles, hijo, nivel+1, visitado)
    for hijo in hijos[medio:]:
        calcular_niveles(arbol, niveles, hijo, nivel+1, visitado)


if __name__ == "__main__":
    N = int(input())
    familias = []
    for i in range(N):
        enteros = list(map(int, input().split()))
        familias.append(enteros)
    M = int(input())
    miembros = []
    for i in range(M):
        miembro = int(input())
        miembros.append(miembro)

    tree = arbol(familias)
    niveles = {}
    calcular_niveles(tree, niveles, 0, 1)

    # Usar un metodo de python que dado un diccionario obtiene el valor de una clave, en caso contrario, imprime -1
    for miembro in miembros:
        print(niveles.get(miembro, -1))


'''
10
0 2
2 9
9 7
7 1 6 8
1 3 4
6
8
3
4 5
5
3
1
6
5
'''

