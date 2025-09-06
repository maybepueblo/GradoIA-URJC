
def velada(actividades):
    profit = 0
    cost = 0
    for _ in range(len(actividades)):
        objeto_actual = actividades[_]
        if objeto_actual[1] >= cost:
            cost = objeto_actual[0]
            profit += 1
    return profit

if __name__ == "__main__":
    # Número de actividades a realizar
    N = int(input())
    actividades = []

    for i in range(N):
        datos = input().strip().split()
        nombre_actividad = datos[0]
        # I = Tiempo Inicio, F = Instante finalización
        I, F = map(int, datos[1:])
        actividades.append((F, I, nombre_actividad))
    actividades.sort()

    output = velada(actividades)
    print(output)

'''
5
Vacunarse 20 30
BaniarAlPez 35 40
Entrenar 31 85
PonerTweets 10 15
LlamadaConIbai 80 100
'''
