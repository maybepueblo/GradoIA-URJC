
def esSolucion(actCost, objetos, P):
    min_peso = float('inf')
    for o in objetos:
        if min_peso > o[1]:
            min_peso = o[1]
    return actCost + min_peso > P

def esFactible(o, actCost):
    return o[1] + actCost <= P

def bt(objetos, actCost, actProfit, bestProfit, P):
    if esSolucion(actCost, objetos, P):
        if actProfit > bestProfit:
            bestProfit = actProfit
    else:
        for k in range(len(objetos)):
            o = objetos[k]
            if esFactible(o, actCost):
                actCost +=  o[1]
                actProfit += o[2]
                bestProfit = bt(objetos, actCost, actProfit, bestProfit, P)
                actCost -= o[1]
                actProfit -= o[2]
    return bestProfit

if __name__ == "__main__":
    # N = número de objetos, P = peso máximo aerolínea, B = beneficio mínimo que debe alcanzar
    N, P, B = map(int, input().strip().split())
    objetos = []
    for i in range(N):
        datos = input().strip().split()
        O = datos[0] # nombre del objeto
        C = int(datos[1]) # peso
        G = int(datos[2]) # beneficio que aporta
        objetos.append((O, C, G))

    mejorProfit = bt(objetos, 0, 0, 0, P)
    print(mejorProfit)

'''
3 50 25
ColoniaDanaPaola 45 50
Toalla 25 30
Desodorante 25 30

60
'''

'''
3 45 60
LibrosDeAlgoritmos 45 50
Toalla 25 30
GafasDeSol 25 30

50
'''