/*
NUMERO DE GRUPO: G26

NOMBRE Y APELLIDOS DE LOS PARTICIPANTES:
Iago Barroso Ortega
Rubén Matey Martín

SI ALGUN MIEMBRO DEL GRUPO NO HA PARTICIPADO EN LA PRACTICA,
EXPLICAR EL MOTIVO:

*/


#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void tiempo(const Arbin<char>& a, const int& nivel_actual, int& t) {
	
	if (a.raiz() == 'X') {
		t += nivel_actual * 2;
	}
	if (!a.hijoDer().esVacio()) {
		tiempo(a.hijoDer(), nivel_actual + 1, t);

	}
	if (!a.hijoIz().esVacio()) {
		tiempo(a.hijoIz(), nivel_actual + 1, t);
	}
	
}


int tiempoAyuda(const Arbin<char>& falda) {
	// A IMPLEMENTAR
	if (falda.esVacio()) {
		return 0;
	}
	int nivel_actual = 1;
	int t = 0;
	if (!falda.hijoDer().esVacio()) {
		tiempo(falda.hijoDer(), nivel_actual, t);

	}
	if (!falda.hijoIz().esVacio()) {
		tiempo(falda.hijoIz(), nivel_actual, t);
	}

	return t;




}

Arbin<char> leeArbol(istream& in) {
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
		Arbin<char> iz = leeArbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = leeArbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}

int main() {
	Arbin<char> falda;
	while (cin.peek() != EOF) {
		cout << tiempoAyuda(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}