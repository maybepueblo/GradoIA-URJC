def esFactible(escenario, x, y):
    return 0 <= x < len(escenario) and 0 <= y < len(escenario[0]) and escenario[x][y] != 3


def esFactible(escenario, x, y):
    return 0 <= x < len(escenario) and 0 <= y < len(escenario[0]) and escenario[x][y] != 3 and escenario[x][y] != 'S'


def esSolucion(erizo_x, erizo_y, obj_x, obj_y, anillos):
    return (erizo_x, erizo_y) == (obj_x, obj_y) and anillos == 0


def imprimirEscenario(escenario):
    for fila in escenario:
        print(" ".join(str(c) for c in fila))
    print()


def mover(escenario, x, y, dx, dy):
    pasos = 0
    recogidos = 0
    while True:
        nx, ny = x + dx, y + dy
        if not esFactible(escenario, nx, ny):
            break
        x, y = nx, ny
        pasos += 1
        if escenario[x][y] == 1:
            escenario[x][y] = 'Sc'
            recogidos += 1
        else:
            escenario[x][y] = 'S'
    return x, y, pasos, recogidos


def SonicVueltaAtras(escenario, sonicX, sonicY, obj_x, obj_y, coins, segs, visitados):
    if esSolucion(sonicX, sonicY, obj_x, obj_y, coins):
        return segs
    estado = (sonicX, sonicY, coins)
    if estado in visitados and visitados[estado] <= segs:
        return float('inf')
    visitados[estado] = segs
    min_tiempo = float('inf')
    direcciones = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    for dx, dy in direcciones:
        estado_escenario = [fila[:] for fila in escenario]
        newX, newY, pasos, recogidos = mover(escenario, sonicX, sonicY, dx, dy)
        if pasos > 0:
            nuevos_anillos = coins - recogidos
            tiempo = SonicVueltaAtras(escenario, newX, newY, obj_x, obj_y, nuevos_anillos, segs + pasos, visitados)
            min_tiempo = min(min_tiempo, tiempo)
        escenario = [fila[:] for fila in estado_escenario]
    return min_tiempo






if __name__ == "__main__":
    N = int(input())
    coins = 0
    escenario = []
    for _ in range(N):
        f = list(map(int, input().strip().split()))
        coins += f.count(1)
        escenario.append(f)
    Sx, Sy, Ex, Ey = map(int, input().strip().split())
    visitados = {}
    escenario[Sx][Sy] = 'S'
    resultado = SonicVueltaAtras(escenario, Sx, Sy, Ex, Ey, coins, 1, visitados)
    print(resultado)
