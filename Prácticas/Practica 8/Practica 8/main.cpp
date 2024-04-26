/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN
REALIZADO LA PRÁCTICA:
Rubén Matey Martín
Iago Barroso Ortega


(si algún componente no ha realizado la práctica,
no debe aparecer)

*/

#include "lista.h"
#include <iostream>
#include <string>
#include "diccionario.h"
#include "diccionarioHash.h"
using namespace std;


typedef Lista<string> tTexto; // Representación del texto

typedef Lista<int> tFirma;    // Representación de la firma



void construye_firma(const tTexto& texto, tFirma& firma) {
	DiccionarioHash<string, int> d1;
	Lista<string>::ConstIterator i1 = texto.cbegin();
	while (i1 != texto.cend()) {
		int valor = 0;
		if (d1.contiene(i1.elem())) {
			valor = d1.valorPara(i1.elem());
			d1.inserta(i1.elem(), valor + 1);
		}
		else {
			d1.inserta(i1.elem(), 1);
		}
		i1.next();
	}

	Diccionario<int, int> d2;
	DiccionarioHash<string, int>::ConstIterator i2 = d1.cbegin();
	while (i2 != d1.cend()) {
		d2.inserta(d1.valorPara(i2.clave()), 1);
		i2.next();
	}
	Diccionario<int, int>::ConstIterator i3 = d2.cbegin();

	while (i3 != d2.cend()) {
		firma.pon_final(i3.clave());
		i3.next();
	}
	

}

// NO MODIFICAR
bool lee_texto(tTexto& texto) {
	int n;
	cin >> n;
	if (n == -1) return false;
	else {
		for (int i = 0; i < n; i++) {
			string palabra;
			cin >> palabra;
			texto.pon_final(palabra);
		}
		return true;
	}
}

bool ejecuta_caso() {
	tTexto texto;
	if (lee_texto(texto)) {
		tFirma firma;
		construye_firma(texto, firma);
		for (int i = 0; i < firma.longitud(); i++) {
			cout << firma.elem(i) << " ";
		}
		cout << endl;
		return true;
	}
	else {
		return false;
	}
}


int main() {
	while (ejecuta_caso());
}