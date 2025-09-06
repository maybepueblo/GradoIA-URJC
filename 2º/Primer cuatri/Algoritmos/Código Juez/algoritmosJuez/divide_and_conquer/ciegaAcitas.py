from pydoc import resolve


def busquedaBin(lista, objetivo):

    inicio = 0
    fin = len(lista)-1

    while inicio <= fin:
        medio = (inicio+fin)//2
        if lista[medio] == objetivo:
            return medio
        elif lista[medio] < objetivo:
            inicio = medio+1
        else:
            fin = medio-1

    return -1

def resolver_citas(reservas, acompanantes, parejas):
    # Esta lista nos va a devolver nuestros resultados
    resultados = []
    for persona1, persona2 in parejas:

        # Tenemos que buscar a cada persona en cada grupo
        posicion1 = busquedaBin(reservas, persona1)

        # Repetimos con la siguiente
        posicion2 = busquedaBin(acompanantes, persona2)

        # Verificamos si están las dos personas, si falta una o las dos es un PLANTON
        if posicion1 == -1 or posicion2 == -1:
            resultados.append("PLANTON")
        else:
            resultados.append(f"{posicion1} {posicion2}")
    return resultados

if __name__ == "__main__":
    # Entrada
    N = int(input())
    reservas = list(map(int, input().strip().split()))
    M = int(input())
    acompanantes = list(map(int, input().strip().split()))
    P = int(input())
    parejas = []
    for i in range(P):
        P1, P2 = map(int, input().strip().split())
        parejas.append((P1, P2))

    solucion = resolver_citas(reservas, acompanantes, parejas)
    for i in range(len(solucion)):
        print(solucion[i])

'''
6
5 21 32 42 87 92
4
10 50 78 97
3
87 97
21 10
32 40
'''
'''
10
37036 119991 227138 327291 332258 381774 479553 480061 637012 852699 
10
38560 136237 173057 197161 359481 516138 565549 700896 743348 857364 
59
119991 857364
227138 700896
37036 173057
119991 516138
852699 565549
332258 38560
332258 38560
1597507 1900986
332258 565549
327291 1837826
480061 38560
37036 857364
480061 173057
1579808 516138
227138 857364
227138 1867911
1254568 1419599
332258 359481
852699 857364
332258 38560
479553 197161
119991 565549
1250215 197161
381774 743348
1572265 136237
37036 857364
1970094 1139482
852699 1850541
479553 743348
637012 565549
1075644 38560
1619644 38560
1577770 857364
37036 173057
381774 1036294
332258 700896
327291 38560
1217878 700896
327291 857364
1439887 136237
381774 743348
332258 38560
227138 565549
327291 516138
1538952 516138
332258 359481
37036 136237
327291 565549
637012 197161
1199467 38560
480061 565549
479553 857364
479553 197161
1109265 359481
479553 359481
479553 38560
480061 516138
637012 197161
227138 700896
'''