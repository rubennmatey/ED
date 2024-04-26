/*
Número de grupo : G26

Nombre y apellidos de los autores de la práctica(si alguno de los miembros del grupo
	no hay realizado la práctica, no debe incluirse su nombre) :
	Iago Barroso Ortega
	Rubé
	n Matey Martín


	*/

#include <iostream>
#include "cola.h"
	using namespace std;

unsigned int afortunado(unsigned int n, unsigned int m) { //n>=1  m>=2 
	
	Cola<int> q;
	for (int i = 1; i <= n; i++) {
		q.pon(i);
	}
	int nElem = n;
	int cont = 1;

	while (nElem > 1) {
		if (cont != m) {
			q.pon(q.primero());
			cont++;
		}
		else {
			cont = 1;
			nElem--;
		}
		q.quita();
	}
	return q.primero();
	

}


int main() {
	int n, m;
	while ((cin >> n)) {
		cin >> m;
		cout << afortunado(n, m) << endl;
	}
	return 0;
}