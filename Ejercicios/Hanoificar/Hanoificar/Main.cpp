#include <iostream>
#include <string>
#include "pila.h"

using namespace std;

Pila<int> hanoificar(Pila<int>& p) {
    Pila<int> vieja;
    Pila<int> resto_viejo;
    Pila<int> resto;
    if (p.esVacia()) {
        return resto;
    }
    else {
        int mayor = p.cima();
        vieja.apila(p.cima());
        p.desapila();
        while (!p.esVacia()) {
            if (p.cima() > mayor) {
                mayor = p.cima();
                vieja.apila(p.cima());
                p.desapila();
            }
            else {
                resto_viejo.apila(p.cima());
                p.desapila();
            }
        }
        while (!vieja.esVacia()) {
            p.apila(vieja.cima());
            vieja.desapila();
        }
        while (!resto_viejo.esVacia()) {
            resto.apila(resto_viejo.cima());
            resto_viejo.desapila();
        }
        return resto;
    }
    
}

// NO MODIFICAR A PARTIR DE AQUI


void imprime(const Pila<int>& p) {
    Pila<int> p_aux = p;
    while (!p_aux.esVacia()) {
        cout << p_aux.cima() << ' ';
        p_aux.desapila();
    }
}

bool ejecuta_caso() {
    int n;
    cin >> n;
    if (n == -1) return false;
    else {
        Pila<int> p;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            p.apila(v);
        }
        Pila<int> resto = hanoificar(p);
        imprime(p);
        cout << "#";
        imprime(resto);
        cout << endl;
    }
    return true;
}


int main() {
    while (ejecuta_caso());
    return 0;
}