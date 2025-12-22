def busqueda_binaria_fila(matriz, ini, fin, elem):
    if fin < ini:
        return fin
    if fin == ini:
        if matriz[fin][0] == elem:
            return fin
        if elem < matriz[fin][0]:
            if fin == 0:
                return fin
            else:
                return fin - 1
        else:
            return busqueda_binaria_fila(matriz, fin + 1, fin, elem)
    else:
        mid = (fin + ini) // 2
        if matriz[mid][0] == elem:
            return mid
        else:
            if elem > matriz[mid][0]:
                return busqueda_binaria_fila(matriz, mid + 1, fin, elem)
            else:
                return busqueda_binaria_fila(matriz, ini, mid - 1, elem)


def busqueda_binaria_columna(fila, ini, fin, elem):
    if fin < ini:
        return ini
    else:
        mid = (fin + ini) // 2
        if fila[mid] == elem:
            return mid
        else:
            if elem > fila[mid]:
                return busqueda_binaria_columna(fila, mid + 1, fin, elem)
            else:
                return busqueda_binaria_columna(fila, ini, mid - 1, elem)


def poner_X(matriz, f, col, N):
    if f > N - 1 or col > N - 1:
        return
    if col < 0:
        return poner_X(matriz, f, col + 1, N)
    if matriz[f][col] != "X":
        matriz[f][col] = "X"
        return
    else:
        if f == N - 1 and col == N - 1:
            return
        if col == N - 1:
            f += 1
            col = 0
            return poner_X(matriz, f, col, N)
        if col < N - 1:
            col += 1
            return poner_X(matriz, f, col, N)


if __name__ == "__main__":
    N = int(input())
    matriz = [[] for i in range(N)]

    # Lectura de la matriz
    for i in range(N):
        elementos = list(map(int, input().strip().split()))
        matriz[i] = elementos

    # Lectura de eliminados
    eliminados = list(map(int, input().strip().split()))

    # Arrays para almacenar posiciones a eliminar
    fila_eliminar = []
    columna_eliminar = []

    # Encontrar posiciones a eliminar
    for i in range(len(eliminados)):
        fila = busqueda_binaria_fila(matriz, 0, N - 1, eliminados[i])
        columna = busqueda_binaria_columna(matriz[fila], 0, N - 1, eliminados[i])
        if columna == N:
            fila += 1
            columna = 0
        fila_eliminar.append(fila)
        columna_eliminar.append(columna)

    # Eliminar (poner X)
    for i in range(len(eliminados)):
        poner_X(matriz, fila_eliminar[i], columna_eliminar[i], N)

    # Imprimir resultado
    for i in range(N):
        for j in range(N):
            print(matriz[i][j], end=" ")
        print()