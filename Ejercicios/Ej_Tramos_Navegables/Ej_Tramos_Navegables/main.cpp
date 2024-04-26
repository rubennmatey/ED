
#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool esHoja(const Arbin<int>& a) {
	return (!a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio());
}

int aux(const Arbin<int>& a, int& n) {
	if (a.esVacio()) {
		return 0;
	}
	else {
		if (esHoja(a)) {
			n = 1;
			return 0;
		}
		else {
			int ret = 0;
			int ni = 0;
			int nd = 0;
			ret = aux(a.hijoDer(), nd) + aux(a.hijoIz(), ni);
			n = nd + ni + a.raiz();
			if (n < 0) n = 0;
			if (n >= 3) ret++;
			return ret;
		}
	}
	
}

int numeroTramosNavegables(const Arbin<int>& cuenca) {
	// A IMPLEMENTAR
	if (cuenca.esVacio()) return 0;
	int n = 0;
	return aux(cuenca.hijoDer(), n) + aux(cuenca.hijoIz(),n);

}

Arbin<int> leeArbol(istream& in) {
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
		Arbin<int> iz = leeArbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = leeArbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

int main() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF) {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}