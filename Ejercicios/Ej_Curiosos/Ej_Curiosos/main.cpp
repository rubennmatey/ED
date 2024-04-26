#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

/**
  FUNCION A IMPLEMENTAR.
  Aparte de esta funci?n, puedes implementar todas las funciones auxiliares que
  consideres oportuno.
  Debes describir y justificar aqu? la complejidad de la implementaci?n realizada:



*/
int tamano(const Arbin<int>& a) {
	if (a.esVacio()) return 0;
	return 1 + tamano(a.hijoIz()) + tamano(a.hijoDer());
}

int alturaArbol(const Arbin<int>& a) {
	if (a.esVacio()) return 0;
	return 1 + max(alturaArbol(a.hijoIz()), alturaArbol(a.hijoDer()));
}

// Función auxiliar para realizar el recorrido en profundidad (DFS) y contar los nodos curiosos
int aux_num_curiosos(const Arbin<int>& a, int nivel) {
	if (a.esVacio()) return 0;

	int curiososIzq = aux_num_curiosos(a.hijoIz(), nivel + 1);
	int curiososDer = aux_num_curiosos(a.hijoDer(), nivel + 1);

	int nodosIzq = tamano(a.hijoIz());
	int valorNodoActual = a.raiz();
	int nodosCuriososEnEsteSubarbol = (nivel + nodosIzq == valorNodoActual);

	return nodosCuriososEnEsteSubarbol + curiososIzq + curiososDer;
}

int num_curiosos(const Arbin<int>& a) {
	if (a.esVacio()) return 0;
	return aux_num_curiosos(a, 1);

}


Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

void escribe_arbol(Arbin<int> a) {
	if (a.esVacio()) cout << "#";
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) cout << "[" << a.raiz() << "]";
	else {
		cout << "(";
		escribe_arbol(a.hijoIz());
		cout << a.raiz();
		escribe_arbol(a.hijoDer());
		cout << ")";
	}
}


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		arbol = lee_arbol(cin);
		escribe_arbol(arbol);
		cout << " => " << num_curiosos(arbol);
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}