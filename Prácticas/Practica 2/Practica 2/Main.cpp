/*
Número de grupo: G26

Nombre y apellidos de los autores de la práctica (si alguno de los miembros del grupo
no hay realizado la práctica, no debe incluirse su nombre):
Rubén Matey Martín
Iago Barroso Ortega
2ºG

*/

#include <iostream>
#include <string>
#include "pila.h"
using namespace std;

bool esSimboloAbierto(const char& cadena) {
    return cadena == '[' || cadena == '(' || cadena == '{';
}
bool esSimboloCerrado(const char& cadena) {
    return cadena == ']' || cadena == ')' || cadena == '}';
}

bool esContrario(const char& c1, const char& c2) {
    if (c1 == '(') {
        return c2 == ')';
    }
    else if (c1 == '[') {
        return c2 == ']';
    }
    else if (c1 == '{') {
        return c2 == '}';
    }
    else return false;
}

bool esEquilibrada(const string& cadena) {
    Pila <char> pila1;
    long unsigned int i = 0;
    while (i < cadena.size()) {
       
        if (esSimboloAbierto(cadena[i])) {
            pila1.apila(cadena[i]);
        }
        else if (esSimboloCerrado(cadena[i])) {
            if (!pila1.esVacia() && esContrario(pila1.cima(), cadena[i])) {
                pila1.desapila();
            }
            else {
                return false;
            }
        }
        i++;
    }

    return pila1.esVacia();

}


int main() {
    string cadena;
    while (getline(cin, cadena)) {
        if (esEquilibrada(cadena))
            cout << "EQUILIBRADA" << endl;
        else
            cout << "NO_EQUILIBRADA" << endl;
    }
    return 0;
}