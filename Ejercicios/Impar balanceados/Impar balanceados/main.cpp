/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN
REALIZADO LA PRÁCTICA:


(si algún componente no ha realizado la práctica,
no debe aparecer)

*/

#include <iostream>
#include <string>
using namespace std;
#include "Arbin.h"


/*
   DETERMINACION JUSTIFICADA DE LA COMPLEJIDAD:



*/

int cuentaImpares(const Arbin<int>& a) {
	if (a.esVacio()) return 0;

	int count = (a.raiz() % 2 != 0) ? 1 : 0;
	count += cuentaImpares(a.hijoDer());
	count += cuentaImpares(a.hijoIz());
	return count;
}

int num_imparBalanceados(const Arbin<int>& a) {
	if (a.esVacio()) {
		return 0;
	}
	int cuenta = 0;
	if (cuentaImpares(a.hijoDer()) == cuentaImpares(a.hijoIz())) {
		cuenta = 1;
	}

	cuenta += num_imparBalanceados(a.hijoDer());
	cuenta += num_imparBalanceados(a.hijoIz());
	return cuenta;

	//if (!a.esVacio()) {
	//	if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {
	//		numImpares++;
	//	}
	//	else {
	//		numD = num_imparBalanceados(a.hijoDer());
	//		numI = num_imparBalanceados(a.hijoIz());
	//		numImpares += numD + numI;
	//		if (numI == numD) numImpares++;
	//		/*if (num_imparBalanceados(a.hijoDer()) == num_imparBalanceados(a.hijoIz())) {
	//			numImpares += 1 + num_imparBalanceados(a.hijoDer()) + num_imparBalanceados(a.hijoIz());
	//		}
	//		else {
	//			numImpares = num_imparBalanceados(a.hijoDer()) + num_imparBalanceados(a.hijoIz());
	//		}*/


	//	}
	//}
		// return numImpares;
	
}


// NO MODIFICAR NADA A PARTIR DE AQUI

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		cout << num_imparBalanceados(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}