#include "lista.h"
#include <iostream>
#include <string>
#include "diccionario.h"

using namespace std;

// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
public:
	string alumno;
	int nota;
	Puntuacion(const string& nombre, int puntuacion) : alumno(nombre), nota(puntuacion) {}
};

// Construye una lista con las puntuaciones de aquellos alumnos cuya
// calificación final es distinta de 0. Dicha lista está ordenada
// alfabéticamente por nombre de alumno
// Parámetros:
//    bien: Lista de alumnos que han resuelto correctamente un ejercicio (si
//          un alumno ha resuelto correctamente varios ejercicios, aparecerá
//          varias veces en la lista)
//    mal: Lista de alumnos que han resuelto incorrectamente un ejercicio (si
//          un alumno ha resuelto correctamente varios ejercicios, aparecerá
//          varias veces en la lista)
//    listado: Listado de calificaciones, ordenado alfabéticamente por nombre
//          de alumno. Solo aparecen aquellos alumnos cuya calificación final 
//          es distinta de 0.

void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	Lista<string>::ConstIterator i1 = bien.cbegin();
	Lista<string>::ConstIterator i2 = mal.cbegin();
	Diccionario<string, int> d;
	while (i1 != bien.cend()) {
		int valor = 0;
		if (d.contiene(i1.elem())) {
			valor = d.valorPara(i1.elem());
			d.inserta(i1.elem(), valor + 1);
		}
		else {
			d.inserta(i1.elem(), 1);
		}
		i1.next();
	}
	while (i2 != mal.cend()) {
		int valor = 0;
		if (d.contiene(i2.elem())) {
			valor = d.valorPara(i2.elem());
			d.inserta(i2.elem(), valor - 1);
		}
		else {
			d.inserta(i2.elem(), -1);
		}
		i2.next();
	}
	Diccionario<string, int>::ConstIterator i3 = d.cbegin();
	while (i3 != d.cend()) {
		if (d.valorPara(i3.clave()) != 0) {
			listado.pon_final(Puntuacion(i3.clave(), d.valorPara(i3.clave())));
		}
		
		i3.next();
	}

}

void imprimePuntuaciones(Lista<Puntuacion>& listado) {
	Lista<Puntuacion>::ConstIterator i = listado.cbegin();
	Lista<Puntuacion>::ConstIterator e = listado.cend();
	while (i != e) {
		cout << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
		i.next();
	}
	cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			string resultado;
			cin >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

int main() {
	string comienzo;
	while (cin >> comienzo) {
		Lista<string> bien;
		Lista<string> mal;
		Lista<Puntuacion> listado;
		leeResultados(bien, mal);
		califica(bien, mal, listado);
		imprimePuntuaciones(listado);
	}
	return 0;
}