
def esFactible(sala, eje_x, eje_y, alcance):
    # Verificamos si la posición está dentro de los límites de la sala y no es una pared
    """ ¿Cómo estoy verificando si no me salgo?
      0 <= eje_x < len(sala) -> Que nuestra fila no se salga de los límites
      0 <= eje_y < len(sala[0]) -> Lo mismo con nuestra columna
      sala[eje_x][eje_y] != -1 -> Que en esa posición a la que vayamos a ir no haya una pared
      alcance > 0 -> Que todavía podamos movernos
    """
    if 0 <= eje_x < len(sala) and 0 <= eje_y < len(sala[0]) and sala[eje_x][eje_y] != -1 and alcance >= 0:
        return True
    return False

def seguir(alcance):
    # Si hemos llegado a 0, no podemos seguir avanzando, así que salimos
    return alcance > 0

def esSolucion(enemigos):
    return enemigos == 0

def moonKnightBT(sala, eje_x, eje_y, alcance, enemigos):

    if esSolucion(enemigos):
        return True

    # Posición como visitada habiendo creado la posición previa
    estadoOrigen = sala[eje_x][eje_y]
    sala[eje_x][eje_y] = -1



    # Las posibles direcciones son:
    ''' Siendo este el formato de movimiento (dx, dy)
    (0, 1) = moverse a la derecha (dejamos x igual y nos movemos de columna a la siguiente)
    (1, 0) = moverse hacia abajo (dejamos la columna igual y cambiamos de fila)
    (0, -1) = moverse hacia la izquierda (dejamos la fila igual y nos movemos de columna a la anterior)
    (-1, 0) = moverse hacia arriba (retrocedemos una fila y nos quedamos en la misma columna) '''
    direcciones = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    esSol = False

    for x, y in direcciones:
        nuevo_x, nuevo_y = eje_x + x, eje_y + y
        if esFactible(sala, nuevo_x, nuevo_y, alcance - 1):
            # Prioridad: primero intentamos si hay un enemigo
            if sala[nuevo_x][nuevo_y] == 1:
                esSol = moonKnightBT(sala, nuevo_x, nuevo_y, alcance - 1, enemigos - 1)
            else:
                esSol = moonKnightBT(sala, nuevo_x, nuevo_y, alcance - 1, enemigos)
            if esSol:
                break

    sala[eje_x][eje_y] = estadoOrigen
    return esSol


if __name__ == "__main__":
    # Lectura de la entrada
    N, M, E = map(int, input().strip().split())

    # Inicializar la sala
    sala = []
    for _ in range(N):
        fila = list(map(int, input().split()))
        sala.append(fila)

    # Leer la posición inicial del Caballero Luna y el alcance de su arma
    X, Y, D = map(int, input().strip().split())

    if moonKnightBT(sala, X, Y, D, E):
        print("ATACA")
    else:
        print("CORRE")

'''
4 5 3
0 0 0 0 0
-1 1 0 1 0
-1 1 -1 0 0
0 0 0 -1 -1
3 1 3
'''

'''
4 5 3
0 0 0 0 0
-1 1 0 1 0
-1 1 -1 0 0
0 0 0 -1 -1
3 1 4
'''
