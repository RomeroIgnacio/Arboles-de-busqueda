#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>

template<class T>
class Nodo
{
    public:
        T dato;
        Nodo<T>* izquierdo;
        Nodo<T>* derecho;

        Nodo(const T& dato)
        {
            this->dato = dato;
            this->izquierdo = nullptr;
            this->derecho = nullptr;
        }
};

template<typename T>
class Arbol
{
    private:
        void rot_sim_der(Arbol<T>*& arbol);
        void rot_sim_izq(Arbol<T>*& arbol);
        void rot_dbl_der(Arbol<T>*& arbol);
        void rot_dbl_izq(Arbol<T>*& arbol);

    public:
        Nodo<T>* raiz;

        Arbol() : raiz(nullptr) {}
        //Arbol() : raiz(nulptr) {}

        void inicializa(Arbol<T>*& arbol);
        bool vacio(const Arbol<T>* arbol) const;
        T recupera(const Nodo<T>* pos, const Arbol<T>* arbol) const;
        void inserta(const T& elem, Arbol<T>*& arbol);
        Nodo<T>* localiza(const T& elem, const Arbol<T>* arbol) const;
        Nodo<T>* menor(const Arbol<T>* arbol) const;
        Nodo<T>* mayor(const Arbol<T>* arbol) const;
        bool es_hoja(const Nodo<T>* arbol) const;
        void recorrido_preorder(const Arbol<T>* arbol) const;
        void recorrido_inorder(const Arbol<T>* arbol) const;
        void recorrido_postorder(const Arbol<T>* arbol) const;
        void elimina(Nodo<T>* pos, Arbol<T>*& arbol);
        int altura(const Arbol<T>* arbol) const;
        int fact_eq(const Arbol<T>* arbol) const;
        void balanceo(Arbol<T>*& arbol);
};

#endif
