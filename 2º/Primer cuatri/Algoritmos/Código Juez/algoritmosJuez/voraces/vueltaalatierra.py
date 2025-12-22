def knapsack_greedy(candidates, N):
    profit = 0
    cost = 0
    actual_object = 0
    mochila = [0] * len(candidates)
    while actual_object < len(candidates) and cost <= N:
        obj = candidates[actual_object]
        if obj[2] + cost <= N:
            cost += obj[2]
            profit += obj[1]
            mochila[obj[3]] = 1
        else:
            proportion = (N - cost) / obj[2]
            profit += proportion * obj[1]
            cost = N
            mochila[obj[3]] = proportion
        actual_object += 1
    return profit, mochila

if __name__ == '__main__':
    N, M = map(int, input().strip().split())
    candidates = []
    for i in range(M):
        v1, p1 = map(int, input().strip().split())
        candidates.append((p1 / v1, v1, p1, i))
    candidates.sort()
    profit, mochila = knapsack_greedy(candidates, N)
    print("{:.2f}".format(profit))
    print(mochila)
'''
50 3
60 10
100 20
120 30


10 1
500 30
'''