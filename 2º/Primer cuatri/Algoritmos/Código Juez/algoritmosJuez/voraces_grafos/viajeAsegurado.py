
from math import inf

def minDist(distances, visited):
    minDist = float('inf')
    bestItem = None
    for i in range(len(distances)):
        if not visited[i] and distances[i] < minDist:
            minDist = distances[i]
            bestItem = i
    return bestItem

def dijkstraViaje(g, node):
    distances = [inf]*len(g)
    distances[node] = 0

    visited = [False]*len(g)

    for _ in range(len(g)):
        nextNode = minDist(distances, visited)
        visited[nextNode] = True

        for (start, end, weight) in g[nextNode]:
            distances[end] = min(distances[end], distances[start]+weight)

    return distances

if __name__ == '__main__':
    n, m = map(int, input().strip().split())
    g = [[] for _ in range(n) ]
    for _ in range(m):
        h1, h2, d = map(int, input().strip().split())
        g[h1].append((h1, h2, d))
        g[h2].append((h2, h1, d))

    max_distances = 0
    for i in range(n):
        distances = dijkstraViaje(g,i)
        alcanzables = [dist for dist in distances if dist<inf]
        max_distances = max(max_distances, max(alcanzables))
    print(max_distances)

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