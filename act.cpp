#include <iostream>
#include "arbol.h"

using namespace std;

int main()
{
    Arbol<int> arbol;
    arbol.inicializa(arbol.raiz);

    arbol.inserta(10, arbol.raiz);
    arbol.inserta(5, arbol.raiz);
    arbol.inserta(15, arbol.raiz);
    arbol.inserta(3, arbol.raiz);
    arbol.inserta(7, arbol.raiz);
    arbol.inserta(12, arbol.raiz);
    arbol.inserta(20, arbol.raiz);

    cout << "Recorrido preorder: ";
    arbol.recorrido_preorder(arbol.raiz);
    cout << endl;

    cout << "Recorrido inorder: ";
    arbol.recorrido_inorder(arbol.raiz);
    cout << endl;

    cout << "Recorrido postorder: ";
    arbol.recorrido_postorder(arbol.raiz);
    cout << endl;

    cout << "Altura del árbol: " << arbol.altura(arbol.raiz) << endl;

    cout << "Factor de equilibrio: " << arbol.fact_eq(arbol.raiz) << endl;

    return 0;
}
