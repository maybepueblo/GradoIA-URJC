

# Función para encontrar el "padre" en el conjunto disjunto
def find(parent, i):
    if parent[i] == i:
        return i
    return find(parent, parent[i])


# Función para hacer la unión de dos subconjuntos
def union(parent, rank, x, y):
    root_x = find(parent, x)
    root_y = find(parent, y)

    if rank[root_x] < rank[root_y]:
        parent[root_x] = root_y
    elif rank[root_x] > rank[root_y]:
        parent[root_y] = root_x
    else:
        parent[root_y] = root_x
        rank[root_x] += 1


def kruskal(n, edges):
    # Ordenar las aristas por el peso (distancia D)
    edges.sort(key=lambda x: x[2])

    parent = []
    rank = []

    # Inicializar los conjuntos disjuntos
    for node in range(n):
        parent.append(node)
        rank.append(0)

    mst_cost = 0
    mst_edges = 0

    # Iterar sobre las aristas ordenadas
    for edge in edges:
        h1, h2, dist = edge
        root1 = find(parent, h1)
        root2 = find(parent, h2)

        # Si no forman un ciclo, añadimos la arista al MST
        if root1 != root2:
            mst_cost += dist
            mst_edges += 1
            union(parent, rank, root1, root2)

            # Si ya hemos añadido N-1 aristas, terminamos
            if mst_edges == n - 1:
                break

    return mst_cost

if __name__ == '__main__':
    n, m = map(int, input().strip().split())
    edges = []

    for _ in range(m):
        h1, h2, d = map(int, input().strip().split())
        edges.append((h1, h2, d))

    resultado = kruskal(n, edges)
    print(resultado)

'''
10 15
0 1 592
0 4 637
1 5 895
1 6 116
2 5 127
3 7 575
3 9 1000
4 5 989
4 6 750
4 7 230
4 8 848
4 9 611
5 7 58
6 8 90
6 9 579
'''

'''
5 7
0 1 10
0 2 20
0 3 30
0 4 40
1 2 5
2 3 9
3 4 10
'''