def elParcero(elementos, benef, posy, posx, mov, count2):
    pos = [[0, 1], [0, -1], [1, 0], [-1, 0]]

    posfalso = [mov,count2,benef]
    if benef == 0:
        return posfalso
    estadoacc = elementos[posy][posx]
    elementos[posy][posx] = -1
    if estadoacc == 2:
        count2 += 1


    for x,y in pos:
        auxx=posx + x
        auxy=posy + y
        if auxx < len(elementos[0]) and auxy < len(elementos) and auxx >= 0 and auxy >= 0 and elementos[auxy][auxx] != -1:
            creacion = posfalso
            if elementos[auxy][auxx] == 0 or elementos[auxy][auxx] == 2:
                creacion = elParcero(elementos, benef, auxy, auxx, mov + 1, count2)

            if elementos[auxy][auxx] == 1:
                creacion = elParcero(elementos, benef - 1, auxy, auxx, mov + 1, count2)


            if creacion[2] == posfalso[2] == 0:
                if creacion[0] < posfalso[0]:
                    posfalso = creacion
                if creacion[0] == posfalso[0]:
                    if creacion[1] < posfalso[1]:
                        posfalso = creacion
            elif creacion[2] == 0:
                posfalso = creacion

    elementos[posy][posx] = estadoacc
    return posfalso
if __name__ == '__main__':
    N,M,B = input().split()
    elementos = []
    for _ in range(int(N)):
        elementos.append(list(map(int, input().rstrip().split())))
    zzz = elParcero(elementos, int(B), posy=0, posx=0, mov = 1,count2 = 0)
    print(zzz[0])
    for _ in range(zzz[1]):
        print('PEDRO')
