#include "lista.h"
#include <iostream>
#include <string>
#include "DiccionarioHash.h"
using namespace std;


typedef struct {
	int x;
	double val;
} tEntrada;

typedef Lista<tEntrada> tVector;


double producto_escalar(const tVector& u, const tVector& v) {
	Lista<tEntrada>::ConstIterator i1 = u.cbegin();
	Lista<tEntrada>::ConstIterator i2 = v.cbegin();
	DiccionarioHash<int, double> d;
	double res = 0;

	while (i1 != u.cend()) {
		d.inserta(i1.elem().x, i1.elem().val);
		i1.next();
	}
	while (i2 != v.cend()) {
		if (d.contiene(i2.elem().x)) {
			res += i2.elem().val * d.valorPara(i2.elem().x);
		}
		i2.next();
	}


	return res;
}

bool leeVector(tVector& v) {
	if (cin.peek() == '(') {
		char sep;
		cin >> sep;
		while (cin.peek() != ')') {
			tEntrada e;
			unsigned int i;
			double val;
			cin >> e.x >> sep >> e.val;
			if (cin.peek() != ')') {
				cin >> sep;
			}
			v.pon_final(e);
		}
		cin >> sep;
		return true;
	}
	else return false;
}
void saltaLinea() {
	string s;
	getline(cin, s);
}

int main() {
	bool fin = false;
	while (!fin) {
		tVector u;
		tVector v;
		if (leeVector(u)) {
			leeVector(v);
			saltaLinea();
			cout << producto_escalar(u, v) << endl;
		}
		else {
			fin = true;
		}
	}
}