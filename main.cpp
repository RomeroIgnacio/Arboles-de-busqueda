#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Arbol;

template<class T>
class Nodo
{
    private:
        T elem;
        Nodo<T>* izq;
        Nodo<T>* der;

        Nodo(const T& elem)
        {
            this -> elem = elem;
            this -> izq = nullptr;
            this -> der = nullptr;
        }

    public:
        Nodo() : elem(T()), izq(nullptr), der(nullptr) {}
        friend class Arbol<T>;
};

template<class T>
class Arbol
{
    private:
        void rot_sim_der(Nodo<T>*& arbol);
        void rot_sim_izq(Nodo<T>*& arbol);
        void rot_dbl_der(Nodo<T>*& arbol);
        void rot_dbl_izq(Nodo<T>*& arbol);

    public:
        Nodo<T>* raiz;

        Arbol() : raiz(nullptr) {}

        void inicializa();
        bool vacio() const;
        T recupera(const Nodo<T>* pos) const;
        void inserta(const T& elem, Nodo<T>*& arbol);
        Nodo<T>* localiza(const T& elem, Nodo<T>* arbol) const;
        Nodo<T>* menor(Nodo<T>* arbol) const;
        Nodo<T>* mayor(Nodo<T>* arbol) const;
        bool es_hoja(const Nodo<T>* arbol) const;
        void recorrido_preorder(Nodo<T>* arbol) const;
        void recorrido_inorder(Nodo<T>* arbol) const;
        void recorrido_postorder(Nodo<T>* arbol) const;
        void elimina(Nodo<T>*& pos);
        int altura(Nodo<T>* arbol) const;
        int fact_eq(Nodo<T>* arbol) const;
        void balanceo();

        void eliminar_valor(const T& valor)
        {
            if (vacio())
            {
                cout << "Error: El árbol está vacío." << endl;
                return;
            }

            Nodo<T>* nodo_a_eliminar = localiza(valor, raiz);
            if (nodo_a_eliminar != nullptr)
            {
                elimina(nodo_a_eliminar);
            }
            else
            {
                cout << "Error: El valor no existe en el árbol." << endl;
            }
        }
};

template<typename T>
void Arbol<T>::inicializa()
{
    raiz = nullptr;
}

template<typename T>
bool Arbol<T>::vacio() const
{
    return raiz == nullptr;
}

template<typename T>
T Arbol<T>::recupera(const Nodo<T>* pos) const
{
    if (pos == nullptr)
    {
        throw runtime_error("¡Error de excepción! Posición nula.");
    }

    return pos -> elem;
}

template<typename T>
void Arbol<T>::inserta(const T& elem, Nodo<T>*& arbol)
{
    if (arbol == nullptr)
    {
        arbol = new Nodo<T>(elem);
    }
    else
    {
        if (elem < arbol -> elem)
        {
            inserta(elem, arbol -> izq);
        }
        else
        {
            inserta(elem, arbol -> der);
        }
    }
}

template<typename T>
Nodo<T>* Arbol<T>::localiza(const T& elem, Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return nullptr;
    }
    else if (elem == arbol -> elem)
    {
        return arbol;
    }
    else if (elem < arbol -> elem)
    {
        return localiza(elem, arbol -> izq);
    }
    else
    {
        return localiza(elem, arbol -> der);
    }
}

template<typename T>
Nodo<T>* Arbol<T>::menor(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return nullptr;
    }
    else if (arbol -> izq == nullptr)
    {
        return arbol;
    }
    else
    {
        return menor(arbol -> izq);
    }
}

template<typename T>
Nodo<T>* Arbol<T>::mayor(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return nullptr;
    }
    else if (arbol -> der == nullptr)
    {
        return arbol;
    }
    else
    {
        return mayor(arbol -> der);
    }
}

template<typename T>
bool Arbol<T>::es_hoja(const Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return false;
    }
    else if (arbol -> izq == nullptr && arbol -> der == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
void Arbol<T>::recorrido_preorder(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return;
    }

    cout << arbol -> elem << " ";

    recorrido_preorder(arbol -> izq);

    recorrido_preorder(arbol -> der);
}

template<typename T>
void Arbol<T>::recorrido_inorder(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return;
    }

    recorrido_inorder(arbol -> izq);

    cout << arbol -> elem << " ";

    recorrido_inorder(arbol -> der);
}

template<typename T>
void Arbol<T>::recorrido_postorder(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return;
    }

    recorrido_postorder(arbol -> izq);

    recorrido_postorder(arbol -> der);

    cout << arbol -> elem << " ";
}

template<typename T>
void Arbol<T>::elimina(Nodo<T>*& pos)
{
    if (pos == nullptr)
    {
        cout << "Error: Nodo nulo." << endl;
        return;
    }

    if (es_hoja(pos))
    {
        delete pos;
        pos = nullptr;
        return;
    }

    Nodo<T>* pos_reemplazo;
    if (pos -> izq != nullptr)
    {
        pos_reemplazo = mayor(pos -> izq);
    }
    else
    {
        pos_reemplazo = menor(pos -> der);
    }

    pos -> elem = pos_reemplazo -> elem;
    elimina(pos_reemplazo);
}

template<typename T>
int Arbol<T>::altura(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return 0;
    }

    int alt_izq = altura(arbol -> izq);
    int alt_der = altura(arbol -> der);

    return (alt_izq > alt_der) ? (alt_izq + 1) : (alt_der + 1);
}

template<typename T>
int Arbol<T>::fact_eq(Nodo<T>* arbol) const
{
    if (arbol == nullptr)
    {
        return 0;
    }

    return altura(arbol -> der) - altura(arbol -> izq);
}

template<typename T>
void Arbol<T>::balanceo()
{
    if (vacio())
    {
        return;
    }

    int factor_eq = fact_eq(raiz);

    if (factor_eq < -1)
    {
        if (fact_eq(raiz -> izq) == -1)
        {
            rot_sim_der(raiz);
        }
        else
        {
            rot_dbl_der(raiz);
        }
    }
    else if (factor_eq > 1)
    {
        if (fact_eq(raiz -> der) == 1)
        {
            rot_sim_izq(raiz);
        }
        else
        {
            rot_dbl_izq(raiz);
        }
    }
}

template<typename T>
void Arbol<T>::rot_sim_der(Nodo<T>*& arbol)
{
    if (arbol == nullptr || arbol -> izq == nullptr)
    {
        return;
    }

    Nodo<T>* aux1 = arbol -> izq;
    Nodo<T>* aux2 = aux1 -> der;

    arbol -> izq = aux2;
    aux1 -> der = arbol;

    arbol = aux1;
}

template<typename T>
void Arbol<T>::rot_sim_izq(Nodo<T>*& arbol)
{
    if (arbol == nullptr || arbol -> der == nullptr)
    {
        return;
    }

    Nodo<T>* aux1 = arbol -> der;
    Nodo<T>* aux2 = aux1 -> izq;

    arbol -> der = aux2;
    aux1 -> izq = arbol;

    arbol = aux1;
}

template<typename T>
void Arbol<T>::rot_dbl_der(Nodo<T>*& arbol)
{
    if (arbol == nullptr || arbol -> izq == nullptr || arbol -> izq -> der == nullptr)
    {
        return;
    }

    Nodo<T>* aux1 = arbol -> izq;
    Nodo<T>* aux2 = aux1 -> der;
    Nodo<T>* aux3 = aux2 -> izq;
    Nodo<T>* aux4 = aux2 -> der;

    arbol -> izq = aux4;
    aux1 -> der = aux3;
    aux2 -> izq = aux1;

    arbol = aux2;
}

template<typename T>
void Arbol<T>::rot_dbl_izq(Nodo<T>*& arbol)
{
    if (arbol == nullptr || arbol -> der == nullptr || arbol -> der -> izq == nullptr)
    {
        return;
    }

    Nodo<T>* aux1 = arbol -> der;
    Nodo<T>* aux2 = aux1 -> izq;
    Nodo<T>* aux3 = aux2 -> der;
    Nodo<T>* aux4 = aux2 -> izq;

    arbol -> der = aux4;
    aux1 -> izq = aux3;
    aux2 -> der = aux1;

    arbol = aux2;
}

int main()
{
    Arbol<int>* arbol = new Arbol<int>();

    arbol -> inserta(50, arbol -> raiz);
    arbol -> inserta(30, arbol -> raiz);
    arbol -> inserta(70, arbol -> raiz);

	cout << "Recorrido inorder del árbol:" << endl;
    arbol -> recorrido_inorder(arbol -> raiz);
    cout << endl;

    int elemento = 35;
    Nodo<int>* encontrado = arbol -> localiza(elemento, arbol -> raiz);
    if (encontrado != nullptr)
    {
        cout << "El elemento " << elemento << " ha sido encontrado en el árbol." << endl;
    }
    else
    {
        cout << "El elemento " << elemento << " no ha sido encontrado en el árbol." << endl;
    }

    int elemento_eliminar = 30;
    arbol->eliminar_valor(elemento_eliminar);

    cout << "Recorrido inorder del árbol después de eliminar " << elemento_eliminar << ":" << endl;
    arbol -> recorrido_inorder(arbol -> raiz) ;
    cout << endl;

    return 0;
}
