/*
	Grupo: G26
	Nombres:
	Iago Barroso Ortega
	Rubén Matey Martín
*/


#include <iostream>
using namespace std;
#include <string>

#include "lista.h"
// INCLUIR EL RESTO DE TADS QUE SE CONSIDEREN OPORTUNOS
bool esVocal(char c) {
	return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U';
}

void invierteSecuenciasNoVocales(Lista<char>& mensaje) {
	// A IMPLEMENTAR
	if (!mensaje.esVacia()) {
		Lista<char> copia;
		Lista<char> cons;
		/*copia.pon_final(mensaje.primero());
		mensaje.quita_ppio();*/
		while (!mensaje.esVacia()) {
			if (esVocal(mensaje.primero())) {
				while (!cons.esVacia()) {
					copia.pon_final(cons.ultimo());
					cons.quita_final();
				}
				copia.pon_final(mensaje.primero());
			}
			else {
				cons.pon_final(mensaje.primero());
			}
			mensaje.quita_ppio();
		}
		while (!cons.esVacia()) {
			copia.pon_final(cons.ultimo());
			cons.quita_final();
		}
		mensaje = copia;
	}
}




// Imprime la lista por la salida estandar
void imprime(const Lista<char>& l) {
	l.print();
	cout << endl;
}


// Codifica el mensaje
void codifica(Lista<char>& mensaje) {
	invierteSecuenciasNoVocales(mensaje);
	mensaje.enredar();
}

// Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for (unsigned int i = 0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);
}

int main() {
	string linea;
	while (getline(cin, linea)) {
		Lista<char> mensaje;
		construyeMensaje(linea, mensaje);
		codifica(mensaje);
		imprime(mensaje);
	}
	return 0;
}
