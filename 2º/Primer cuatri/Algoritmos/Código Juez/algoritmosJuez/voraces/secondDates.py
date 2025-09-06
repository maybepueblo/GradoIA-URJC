
def secondDates(participantes, n, k):
    grupo1 = []
    grupo2 = []
    Sum1 = 0
    Sum2 = 0
    lenRestante = len(participantes)-k
    for elem in range(len(participantes)):
        jovenes = 0
        mayores = 0
        objeto = participantes[elem]
        if elem < k:
            jovenes = objeto[1]
            Sum1 -= jovenes
        else:
            mayores = objeto[1]
            Sum1 += mayores
    for elem in range(len(participantes)):
        jovenes = 0
        mayores = 0
        objeto = participantes[elem]
        if elem < n-k:
            jovenes = objeto[1]
            Sum2 -= jovenes
        else:
            mayores = objeto[1]
            Sum2 += mayores
    if Sum1 >= Sum2:
        for elem in range(len(participantes)):
            objeto = participantes[elem]
            if elem < k:
                grupo1.append(objeto[0])
            else:
                grupo2.append(objeto[0])
    else:
        for elem in range(len(participantes)):
            objeto = participantes[elem]
            if elem < n-k:
                grupo1.append(objeto[0])
            else:
                grupo2.append(objeto[0])
    return grupo1, grupo2



if __name__ == '__main__':
    # Siendo n el número de participantes y k el tamaño de uno de los grupos
    n, k = map(int, input().strip().split())
    participantes = []

    for _ in range(n):
        nombre, edad = input().strip().split()
        participantes.append((nombre, int(edad)))
    participantes.sort(key=lambda x: x[1])

    G1, G2 = secondDates(participantes, n, k)
    for elem in range(len(G1)):
        print(G1[elem], end=' ')
    print()
    for elem in range(len(G2)):
        print(G2[elem], end=' ')

# Datos para tenerlos a mano
'''
5 2
JamesLineberger 55
JeanetteMaurey 73
ChristieDangelo 29
HeatherTrew 78
LeolaSwift 30
''''''
5 3
TammyEvans 67
TimothyLeflore 96
LaurenHumphrey 37
DonnyLopez 93
LorettaFox 36
'''