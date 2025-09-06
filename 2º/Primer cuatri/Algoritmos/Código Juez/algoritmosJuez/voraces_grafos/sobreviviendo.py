
def update_components(old_id, new_id, comp_mst):
    for i in range(len(comp_mst)):
        if comp_mst[i] == old_id:
            comp_mst[i] = new_id

def kruskal(aristas, n):
    cost = 0 # Coste que llevamos, como acabamos de empezar, estamos a cero
    comp_mst = list(range(n))
    n_components = n
    i = 0
    esfuerzo_individual = [0] * n

    while n_components > 1 and i < len(aristas):
        cost_edge, origin, dest = aristas[i]
        if comp_mst[origin] != comp_mst[dest]:
            cost += cost_edge
            esfuerzo_individual[origin] += cost_edge
            esfuerzo_individual[dest] += cost_edge
            n_components -= 1
            update_components(comp_mst[origin], comp_mst[dest], comp_mst)
        i += 1
    return cost, esfuerzo_individual

if __name__ == "__main__":
    # N = concursantes edición / M = número de relaciones existentes
    N, M = map(int, input().strip().split())
    aristas = []
    esfuerzo = []
    for _ in range(M):
        # Ci y Cj = relación entre concursantes / E = esfuerzo para mantener esa relación
        Ci, Cj, E = map(int, input().strip().split())
        aristas.append((E, Ci, Cj))
        aristas.append((E, Cj, Ci))
    aristas.sort()

    sol, esfuerzo = kruskal(aristas, N)

    for i in range(N):
        print(f"C{i} -> {esfuerzo[i]}")
    print(f"Esfuerzo realizado -> {sol}")


'''    
10 13
0 2 68
0 8 63
1 4 53
1 7 110
2 7 11
3 5 107
3 9 30
4 7 97
5 7 38
5 9 31
6 8 67
7 8 24
7 9 41
'''

'''
10 19
0 1 140
0 6 133
0 8 34
0 9 163
1 3 74
1 6 98
1 7 186
2 4 145
2 6 113
2 7 88
2 8 22
3 6 138
3 9 52
4 5 64
4 9 189
5 7 166
5 9 101
6 7 91
6 9 184
'''