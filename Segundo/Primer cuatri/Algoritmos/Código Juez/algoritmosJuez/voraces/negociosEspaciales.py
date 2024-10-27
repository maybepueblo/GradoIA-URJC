
def NegociosEspaciales(num, n):
    profit = 0
    sol = [0] * len(num)
    i = 0
    while n > 0 and i < len(num): # Mientras haya dinero que cambiar y hallan formas disponibles de cambio, seguimos
        if num[i] > n:
            i += 1 # Si la moneda en la que estamos, es mayor que n (monedas a cambiar), la descartamos
        else:
            profit += 1
            n -= num[i]
            sol[i] += 1
    return profit, sol

if __name__ == "__main__":
    N = int(input())
    Num = list(map(int, input().split()))
    Num.sort(reverse=True)
    mon = [0] * len(Num)
    output, mon = NegociosEspaciales(Num, N)
    print(output)
    for i in range(len(mon)):
        if mon[i] > 0:
            print(str(Num[i])+":", mon[i])


''' Primer caso
70
1 2 5 10 20 50 100 500 1000
'''
''' Segundo caso
93
1 2 5 10 20 50 100 500 1000
'''
''' Tercer caso
41010
61976 64104 92274 96761 46973 88714 36145 54608 99911 65325 66758 9757 10172 29027 95511 92770 26897 91850
'''