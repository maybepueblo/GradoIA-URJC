def knapsack_greedy(candidates, W):
    profit = 0
    cost = 0
    actual_object = 0
    while actual_object < len(candidates) and cost <= W:
        object = candidates[actual_object]
        peso_act = object[3]
        benef_act = object[2]
        if cost + peso_act <= W:
            cost += peso_act
            profit += benef_act
        else:
            profit_prop = (W - cost) / peso_act
            profit += profit_prop * benef_act
            cost = W
        actual_object += 1
    return profit, cost



if __name__ == '__main__':
    W = 100
    w = [10, 20, 30, 40, 50]
    v = [20, 30, 66, 40, 60]
    v_div_w = [2.0, 1.5, 2.2, 1.0, 1.2]
    candidates_by_weight = []
    candidates_by_value = []
    candidates_by_ratio = []
    for e in range(len(w)):
        candidates_by_weight.append((w[e], e, v[e], w[e], v_div_w[e]))
        candidates_by_value.append((v[e], e, v[e], w[e], v_div_w[e]))
        candidates_by_ratio.append((v_div_w[e], e, v[e], w[e], v_div_w[e]))
    candidates_by_weight.sort()
    candidates_by_value.sort(reverse=True)
    candidates_by_ratio.sort(reverse=True)

    #print(knapsack_greedy(candidates_by_value, W)[0])
    #print(knapsack_greedy(candidates_by_weight, W)[0])
    print(knapsack_greedy(candidates_by_ratio, W)[0])