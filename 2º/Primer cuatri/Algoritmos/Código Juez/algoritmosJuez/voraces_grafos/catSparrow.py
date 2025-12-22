
import heapq

def dijkstraSparrow(S, E, graph):
    distancias = [float('inf')] * len(graph)
    # Distancia con el inicio
    distancias[S] = 0
    previo = [None] * len(graph) # Reconstruir el camino
    pq = [(0, S)] # (distancia acumulada, cama actual)

    while pq:
        distancia_actual, nodo_actual = heapq.heappop(pq)
        # Te saca el primer elemento de la lista

        if distancia_actual > distancias[nodo_actual]:
            continue

        for vecino, weight in graph[nodo_actual]:
            distancia = distancia_actual + weight
            if distancia < distancias[vecino]:
                distancias[vecino] = distancia
                previo[vecino] = nodo_actual
                heapq.heappush(pq, (distancia, vecino)) # Meter en cola de prioridad

    camino_recorrido = []
    actual = E
    while actual is not None:
        camino_recorrido.append(actual)
        actual = previo[actual]

    camino_recorrido.reverse() # Invertimos para tener desde S a E

    return distancias[E], camino_recorrido

if __name__ == "__main__":
    N, M = map(int, input().strip().split())
    graphBeds = {_: [] for _ in range(N)}


    for i in range(M):
        C1, C2, D = map(int, input().strip().split())
        graphBeds[C1].append((C2, D))
        graphBeds[C2].append((C1, D))

    # S = cama origen, E = cama destino
    S, E = map(int, input().strip().split())

    distancia_total, camino = dijkstraSparrow(S, E, graphBeds)

    print(distancia_total)
    print(" ".join(map(str, camino)))

'''    
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 5 4
2 8 2
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
0 4
'''
'''
20 33
0 11 34
0 18 38
1 3 88
1 5 88
1 17 24
1 19 84
2 12 30
2 16 86
2 17 19
3 9 29
3 14 83
3 16 94
3 17 24
4 6 17
4 8 10
6 10 69
6 13 28
7 10 96
7 12 38
7 13 4
7 14 56
8 14 17
10 13 88
10 14 78
10 15 2
11 16 36
11 19 19
12 13 11
12 14 34
12 16 58
13 17 96
13 19 56
15 17 18
8 11
'''

