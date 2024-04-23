#include <iostream>
#include "arbol.h"

using namespace std;

template<typename T>
void inicializa(Arbol<T>*& arbol)
{
    arbol = nullptr;
}

template<typename T>
bool vacio(const Arbol<T>* arbol)
{
    return arbol == nullptr;
}

template<typename T>
T recupera(const Nodo<T>* pos, const Arbol<T>* arbol)
{
    if (arbol == nullptr || pos == nullptr)
    {
        throw std::runtime_error("¡Error de excepción! Insuficiencia de datos");
    }

    return pos->dato;
}

template<typename T>
void inserta(const T& elem, Arbol<T>*& arbol)
{
    if (arbol == nullptr)
    {
        Nodo<T>* aux = new Nodo<T>(elem);
        arbol = aux;
    }
    else
    {
        if (elem < arbol->dato)
        {
            inserta(elem, arbol->izquierdo);
        }
        else
        {
            inserta(elem, arbol->derecho);
        }
    }
}

template<typename T>
Nodo<T>* localiza(const T& elem, const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return nullptr;
    }
    else if (elem == arbol->dato)
    {
        return arbol;
    }
    else if (elem < arbol->dato)
    {
        return localiza(elem, arbol->izquierdo);
    }
    else
    {
        return localiza(elem, arbol->derecho);
    }
}

template<typename T>
Nodo<T>* menor(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return nullptr;
    }
    else if (arbol->izquierdo == nullptr)
    {
        return arbol;
    }
    else
    {
        return menor(arbol->izquierdo);
    }
}

template<typename T>
Nodo<T>* mayor(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return nullptr;
    }
    else if (arbol->derecho == nullptr)
    {
        return arbol;
    }
    else
    {
        return mayor(arbol->derecho);
    }
}

template<typename T>
bool es_hoja(const Nodo<T>* arbol)
{
    if (arbol == nullptr)
    {
        return false;
    }
    else if (arbol->izquierdo == nullptr && arbol->derecho == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
void recorrido_preorder(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return;
    }

    std::cout << arbol->dato << " ";

    recorrido_preorder(arbol->izquierdo);

    recorrido_preorder(arbol->derecho);
}

template<typename T>
void recorrido_inorder(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return;
    }

    recorrido_inorder(arbol->izquierdo);

    std::cout << arbol->dato << " ";

    recorrido_inorder(arbol->derecho);
}

template<typename T>
void recorrido_postorder(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return;
    }

    recorrido_postorder(arbol->izquierdo);

    recorrido_postorder(arbol->derecho);

    std::cout << arbol->dato << " ";
}

template<typename T>
void elimina(Nodo<T>* pos, Arbol<T>*& arbol)
{
    if (arbol == nullptr || pos == nullptr)
    {
        std::cout << "Error: Árbol o posición nulos." << std::endl;
        return;
    }

    if (es_hoja(arbol))
    {
        liberar_nodo(arbol);
        arbol = nullptr;
        return;
    }

    Nodo<T>* pos_reemplazo;
    if (arbol->izquierdo != nullptr)
    {
        pos_reemplazo = mayor(arbol->izquierdo);
    }
    else
    {
        pos_reemplazo = menor(arbol->derecho);
    }

    pos->dato = pos_reemplazo->dato;
    elimina(pos_reemplazo, arbol);
}

template<typename T>
int altura(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return 0;
    }

    int alt_izq = altura(arbol->izquierdo);
    int alt_der = altura(arbol->derecho);

    return (alt_izq > alt_der) ? (alt_izq + 1) : (alt_der + 1);
}

template<typename T>
int fact_eq(const Arbol<T>* arbol)
{
    if (arbol == nullptr)
    {
        return 0;
    }

    return altura(arbol->derecho) - altura(arbol->izquierdo);
}

template<typename T>
void balanceo(Arbol<T>*& arbol)
{
    if (arbol != nullptr)
    {
        int factor_eq = fact_eq(arbol);

        if (factor_eq < -1)
        {
            if (fact_eq(arbol->izquierdo) == -1)
            {
                rot_sim_der(arbol);
            }
            else
            {
                rot_dob_der(arbol);
            }
        }
        else if (factor_eq > 1)
        {
            if (fact_eq(arbol->derecho) == 1)
            {
                rot_sim_izq(arbol);
            }
            else
            {
                rot_dob_izq(arbol);
            }
        }
    }
}

template<typename T>
void rot_sim_der(Arbol<T>*& arbol)
{
    if (arbol != nullptr && arbol->izquierdo != nullptr)
    {
        Arbol<T>* aux1 = arbol->izquierdo;
        Arbol<T>* aux2 = aux1->derecho;

        arbol->izquierdo = aux2;
        aux1->derecho = arbol;

        arbol = aux1;
    }
}

template<typename T>
void rot_sim_izq(Arbol<T>*& arbol)
{
    if (arbol != nullptr && arbol->derecho != nullptr)
    {
        Arbol<T>* aux1 = arbol->derecho;
        Arbol<T>* aux2 = aux1->izquierdo;

        arbol->derecho = aux2;
        aux1->izquierdo = arbol;

        arbol = aux1;
    }
}

template<typename T>
void rot_dbl_der(Arbol<T>*& arbol)
{
    if (arbol != nullptr && arbol->izquierdo != nullptr && arbol->izquierdo->derecho != nullptr)
    {
        Arbol<T>* aux1 = arbol->izquierdo;
        Arbol<T>* aux2 = aux1->derecho;
        Arbol<T>* aux3 = aux2->izquierdo;
        Arbol<T>* aux4 = aux2->derecho;

        arbol->izquierdo = aux4;
        aux1->derecho = aux3;
        aux2->izquierdo = aux1;

        arbol = aux2;
    }
}

template<typename T>
void rot_dbl_izq(Arbol<T>*& arbol)
{
    if (arbol != nullptr && arbol->derecho != nullptr && arbol->derecho->izquierdo != nullptr)
    {
        Arbol<T>* aux1 = arbol->derecho;
        Arbol<T>* aux2 = aux1->izquierdo;
        Arbol<T>* aux3 = aux2->derecho;
        Arbol<T>* aux4 = aux2->izquierdo;

        arbol->derecho = aux4;
        aux1->izquierdo = aux3;
        aux2->derecho = aux1;

        arbol = aux2;
    }
}
