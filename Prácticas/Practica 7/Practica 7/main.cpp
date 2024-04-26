/*
NOMBRE Y APELLIDOS DE LOS COMPONENTES DEL GRUPO QUE HAN
REALIZADO LA PRÁCTICA:
Rubén Matey Martín
Iago Barroso Ortega

(si algún componente no ha realizado la práctica,
no debe aparecer)

*/

#include <iostream>
#include <string>
#include <sstream>
#include "diccionario.h"
#include "lista.h"
// Puedes realizar las inclusiones adicionales que precises

using namespace std;

typedef Lista<string> tLinea;  // Representa una linea de texto
typedef Lista<tLinea> tTexto;  // Representa un texto

// Representa una entrada en un listado de referencias cruzadas
typedef struct {
	string palabra;          // la palabra
	Lista<int> lineas;	     // la lista de lineas en las que aparece 
	// la palabra
} tEntradaRefCruzadas;

// Representa un listado de referencias cruzadas
typedef Lista<tEntradaRefCruzadas> tRefCruzadas;

tRefCruzadas genera_referencias_cruzadas(const tTexto& texto) {
	Lista<tLinea>::ConstIterator i1 = texto.cbegin();
	Diccionario<string, Lista<int>> d;
	int cont = 1;
	while (i1 != texto.cend()) {
		Lista<string> l = i1.elem();
		Lista<string>::ConstIterator i2 = l.cbegin();
		while (i2 != l.cend()) {
			if (d.contiene(i2.elem())) {
				Lista<int> l1 = d.valorPara(i2.elem());
				l1.pon_final(cont);
				d.inserta(i2.elem(), l1);
			}
			else {
				Lista<int> l1;
				l1.pon_final(cont);
				d.inserta(i2.elem(), l1);

			}
			i2.next();
		}
		cont++;
		i1.next();
	}

	Diccionario<string, Lista<int>>::ConstIterator i3 = d.cbegin();
	tRefCruzadas listaFinal;
	while (i3 != d.cend()) {
		tEntradaRefCruzadas entrada;
		entrada.lineas = d.valorPara(i3.clave());
		entrada.palabra = i3.clave();
		listaFinal.pon_final(entrada);
		i3.next();
	}
	
	return listaFinal;

}


// PROGRAMA DE PRUEBA: No modificar nada a partir de aqui

tLinea divide_palabras(const string& linea_txt) {
	tLinea linea;
	istringstream iss(linea_txt);
	string palabra;
	while (iss >> palabra) {
		linea.pon_final(palabra);
	}
	return linea;
}

// ¡¡¡ Muy mal codigo: no os fijeis en el!!!!
void muestra_ref_cruzadas(const tRefCruzadas& ref_cruzadas) {
	for (int i = 0; i < ref_cruzadas.longitud(); i++) {
		tEntradaRefCruzadas entrada_ref_cruzada = ref_cruzadas.elem(i);
		cout << entrada_ref_cruzada.palabra;
		for (int j = 0; j < entrada_ref_cruzada.lineas.longitud(); j++) {
			cout << " " << entrada_ref_cruzada.lineas.elem(j);
		}
		cout << endl;
	}
}

int main() {
	tTexto texto;

	string linea_txt;

	while (getline(cin, linea_txt)) {
		tLinea linea = divide_palabras(linea_txt);
		texto.pon_final(linea);
	}
	tRefCruzadas ref_cruzadas = genera_referencias_cruzadas(texto);
	muestra_ref_cruzadas(ref_cruzadas);
	return 0;
}
