#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/**
  FUNCION A IMPLEMENTAR.
  Aparte de esta función, puedes implementar todas las funciones auxiliares que
  consideres oportuno.
  Debes describir y justificar aquí LA COMPLEJIDAD de la implementación realizada:



*/
int tamano(const Arbin<char>& a) {
	if (a.esVacio()) return 0;
	return 1 + tamano(a.hijoIz()) + tamano(a.hijoDer());
}

int contarCaballeros(const Arbin<char>& mapa) {
	if (mapa.esVacio()) return 0;

	char contenido = mapa.raiz();
	int caballerosEnSubarbolIzq = contarCaballeros(mapa.hijoIz());
	int caballerosEnSubarbolDer = contarCaballeros(mapa.hijoDer());

	if (contenido == 'C') return 1 + caballerosEnSubarbolIzq + caballerosEnSubarbolDer;
	else return caballerosEnSubarbolIzq + caballerosEnSubarbolDer;
}

// Función auxiliar para determinar si un nodo está a salvo o no
bool estaASalvo(const Arbin<char>& mapa) {
	if (mapa.esVacio()) return false;

	char contenido = mapa.raiz();
	bool esPrincesa = (contenido == 'P');
	int caballerosEnCamino = contarCaballeros(mapa);
	int monstruosEnCamino = tamano(mapa) - caballerosEnCamino;

	return esPrincesa && (caballerosEnCamino >= monstruosEnCamino);
}

int aux(const Arbin<char>& m, int cuenta) {
	if (!m.esVacio()) {
		if (m.raiz() == 'P') {
			if (cuenta >= 0) return 1 + aux(m.hijoDer(), cuenta) + aux(m.hijoIz(), cuenta);
			else return aux(m.hijoIz(), cuenta) + aux(m.hijoDer(), cuenta);
		}
		else if (m.raiz() == 'C') {
			
			return aux(m.hijoIz(), cuenta) + aux(m.hijoDer(), cuenta + 1);
		}
		else if (m.raiz() == 'M') {
			
			return aux(m.hijoIz(), cuenta) + aux(m.hijoDer(), cuenta - 1);
		}
	}
	return 0;
}


// Función principal para contar el número de nodos a salvo en el mapa
int num_a_salvo(const Arbin<char>& mapa) {
	int cuenta = 0;
	if (mapa.esVacio()) return 0;
	return aux(mapa, cuenta);
}


Arbin<char> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = lee_arbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = lee_arbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}


void escribe_arbol(Arbin<char> a) {
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
	Arbin<char> arbol;
	while (cin.peek() != EOF) {
		cout << num_a_salvo(lee_arbol(cin));
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}