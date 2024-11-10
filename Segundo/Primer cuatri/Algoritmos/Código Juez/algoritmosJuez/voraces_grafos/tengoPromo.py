import heapq

def greedyDijkstra(node, grafo, target_type, actividad):
    distances = [float('inf')] * len(grafo)
    distances[node] = 0
    pq = [(0, node)]
    min_dist = float('inf')

    while pq:
        current_distance, u = heapq.heappop(pq)
        if current_distance > distances[u]:
            continue

        for v, weight in grafo[u]:
            if actividad[v] == target_type:
                distance = current_distance + weight
                if distance < distances[v]:
                    distances[v] = distance
                    heapq.heappush(pq, (distance, v))
                    if v != node:
                        min_dist = min(min_dist, distance)

    return min_dist if min_dist != float('inf') else None

if __name__ == "__main__":
    # Leer entrada
    N, M = map(int, input().strip().split())
    actividad = list(map(int, input().strip().split()))
    grafo = {i: [] for i in range(N)}
    for _ in range(M):
        C, D, L = map(int, input().strip().split())
        grafo[C].append((D, L))
        grafo[D].append((C, L))

    # Identificar todos los tipos de actividad únicos
    tipos_actividad = set(actividad)
    resultado = {}

    # Ejecutar Dijkstra para cada tipo de actividad
    for tipo in tipos_actividad:
        min_dist = float('inf')
        for i in range(N):
            if actividad[i] == tipo:
                # Ejecutar Dijkstra modificado desde cada nodo del mismo tipo
                distancia = greedyDijkstra(i, grafo, tipo, actividad)
                if distancia is not None:
                    min_dist = min(min_dist, distancia)

        # Asignar la distancia mínima encontrada para este tipo
        resultado[tipo] = min_dist if min_dist != float('inf') else 0

    # Imprimir resultados en orden de los tipos de actividad
    print(" ".join(str(resultado[tipo]) for tipo in sorted(tipos_actividad)))

'''
6 10
0 0 0 1 1 1
0 1 2
0 3 1
0 2 5
1 2 3
1 3 2
2 3 3
2 4 1
2 5 5
3 4 1
4 5 1
'''

'''
20 41
2 1 1 1 1 1 1 0 1 2 0 3 1 0 2 1 0 2 3 3 
0 1 18
0 17 33
0 18 46
1 6 30
1 7 63
1 9 97
2 8 71
2 9 73
2 12 55
2 16 86
2 17 47
3 4 56
3 6 82
3 9 41
3 10 84
3 11 16
3 16 45
4 7 77
4 11 82
4 12 34
4 14 89
4 18 58
5 14 71
5 16 79
5 17 96
6 10 18
6 13 57
6 14 87
7 11 94
7 17 57
8 16 69
8 17 23
9 15 38
9 18 26
10 14 23
10 18 67
12 15 46
12 16 33
14 15 48
14 16 59
14 19 34
'''
