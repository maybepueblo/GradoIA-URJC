
'''
Sabiendo la distancia entre los distintos enemigos en el mapa y que cada 5 metros de recorrido, gastamos
1 en energía de las alas, hemos de calcular la red de caminos generada que minimiza el coste de energía
del jugador de forma que pueda llegar a cualquier enemigo en el mapa
'''

import math

def update_components(old_id, new_id, comp_mst):
    for i in range(len(comp_mst)):
        if comp_mst[i] == old_id:
            comp_mst[i] = new_id

def kruskal(aristas, n):
    cost = 0 # Coste que llevamos, como acabamos de empezar, estamos a cero
    comp_mst = list(range(n))
    n_components = n
    i = 0
    while n_components > 1 and i < len(aristas):
        origin = aristas[i][1]
        dest = aristas[i][2]
        cost_edge = aristas[i][0]
        if comp_mst[origin] != comp_mst[dest]:
            cost += cost_edge
            n_components -= 1
            update_components(comp_mst[origin], comp_mst[dest], comp_mst)
        i += 1
    return cost

if __name__ == '__main__':
    # n = número de enemigos, m = número total de conexiones
    n, m = map(int, input().strip().split())
    aristas = []

    for _ in range(m):
        # Identificadores de enemigos con vida y distancia en metros
        n1, n2, d = map(int, input().strip().split())
        aristas.append((d, n1, n2))
        aristas.append((d, n2, n1))
    aristas.sort()

    sol = kruskal(aristas, n)
    gas = math.ceil(sol/5)
    print(gas)

'''
10 13
0 2 125
0 8 59
1 4 89
1 7 24
2 7 90
3 5 86
3 9 15
4 7 47
5 7 43
5 9 36
6 8 57
7 8 80
7 9 103
'''


