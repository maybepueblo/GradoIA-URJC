
def alfombraRoja(participantes, participantesN):
    profit = 0
    i = 0
    while participantes[i][1] != participantesN[0][0]:
        profit += participantes[i][4]
        i += 1
    return profit

if __name__ == "__main__":
    # N = número de famosos esperando
    N = int(input())
    famosos = []
    famosos_nombre = []

    for i in range(N):
        datos = input().strip().split()
        # S = Nombre del famoso
        S = datos[0]
        # M = Amabilidad del famoso, L = Fama del famoso, T = Tiempo de entrevista al famoso
        M, L, T = map(int, datos[1:])
        # L/M debido a la relación más fama es más prioritario pero más amable puede esperar más tiempo
        famosos.append((L/M, S, M, L, T))
        famosos_nombre.append((S, M, L, T))
    famosos.sort(reverse=True)
    famosos_nombre.sort()

    output = alfombraRoja(famosos, famosos_nombre)
    for i in range(len(famosos)):
        print(famosos[i][1])
    print(output)

'''
5
Rivers 80 50 6
Ibai 65 60 7
KanyeWest 10 2 1
TaylorSwift 90 95 10
Chiara 85 20 4
'''
