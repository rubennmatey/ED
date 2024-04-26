#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

/**
  COMPLEJIDAD: Explica aqu� justificadamente cu�l es la complejidad de
			   esta funci�n
			   ***A COMPLETAR***
*/


bool esHoja(Arbin<int>& a) {
	return !a.esVacio() && a.hijoIz().esVacio() && a.hijoDer().esVacio();
}

unsigned int contarHojasMasProfundasQue(const Arbin<int>& a1, unsigned int k, unsigned int nivel_actual) {
	if (a1.esVacio()) return 0;

	if (a1.hijoIz().esVacio() && a1.hijoDer().esVacio() && nivel_actual >= k) return 1;

	unsigned int izq = contarHojasMasProfundasQue(a1.hijoIz(), k, nivel_actual + 1);
	unsigned int der = contarHojasMasProfundasQue(a1.hijoDer(), k, nivel_actual + 1);

	return izq + der;

}

unsigned int numero_hojas_mas_profundas_que(const Arbin<int>& a, unsigned int k) {
	if (a.esVacio()) return 0;

	unsigned nivel_actual = 0;
	return contarHojasMasProfundasQue(a, k, nivel_actual);
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



/**
La entrada al programa consiste de l�neas formadas por:
(1) Un �rbol de enteros
(2) El valor de k
Los �rboles se codifican de acuerdo con las siguientes reglas:
(1) El �rbol vac�o se codifica como #
(2) Los �rboles simples se codifican como [v], con
	v el valor del nodo
(3) Los �rboles complejos se codifican como (IvD),
	con I la codificaci�n del hijo izquierdo,
	v el valor de la ra�z, y D la codificaci�n
	del hijo derecho.
Para cada l�nea leida, escribe en la salida est�ndar
el n�mero de hojas que est�n a profundidad mayor que k


Ejemplo de entrada:

([2]1([4]3[5])) 0
([2]1([4]3[5])) 1
([2]1([4]3[5])) 2
([2]1([4]3[5])) 3
([2]1([4]3[5])) 4
([2]1([4]3[5])) 100

Salida asociada:

3
3
2
0
0
0

*/


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a, k) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}