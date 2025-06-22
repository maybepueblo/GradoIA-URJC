def esFactible(room, fila, columna):
    return 0 <= fila < len(room) and 0 <= columna < len(room[0]) and room[fila][columna] != -1


def esSolucion(tiendas):
    return tiendas == 0


def esMejorSol(pasos, actSol):
    return pasos < actSol[0]


def pedroBT(room, fila, columna, tiendas, personas, pasos, actSol):
    esSol = esSolucion(tiendas)
    if esSol:
        if esMejorSol(pasos, actSol):
            actSol[0] = pasos
            actSol[1] = personas
        return actSol

    else:
        estadoAct = room[fila][columna]
        room[fila][columna] = -1
        despl = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        for x, y in despl:
            nuevaFila, nuevaColumna = fila + x, columna + y
            if esFactible(room, nuevaFila, nuevaColumna):
                if room[nuevaFila][nuevaColumna] == 1:  # Tienda
                    actSol = pedroBT(room, nuevaFila, nuevaColumna, tiendas - 1, personas, pasos + 1, actSol)
                elif room[nuevaFila][nuevaColumna] == 2:  # Persona
                    actSol = pedroBT(room, nuevaFila, nuevaColumna, tiendas, personas + 1, pasos + 1, actSol)
                else:  # Celda vacía
                    actSol = pedroBT(room, nuevaFila, nuevaColumna, tiendas, personas, pasos + 1, actSol)
        room[fila][columna] = estadoAct
    return actSol


N, M, P = map(int, input().strip().split())

sala = []

for _ in range(N):
    fila = list(map(int, input().strip().split()))
    sala.append(fila)

Sol = pedroBT(sala, 0, 0, P, 0, 1, [float('inf'), 0])

print(Sol[0])
for i in range(Sol[1]):
    print("PEDRO")
