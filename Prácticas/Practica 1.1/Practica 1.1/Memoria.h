/*
N�mero de grupo: G26

Nombre y apellidos de los autores de la pr�ctica (si alguno de los miembros del grupo
no hay realizado la pr�ctica, no debe incluirse su nombre): Iago Barroso Ortega y Rub�n Matey Mart�n


*/

using namespace std;

#ifndef _MEMORIA_H_
#define _MEMORIA_H_

/// Excepci�n de direccion invalida
class EDireccionInvalida {};

/// Excepci�n de celda sin inicializar
class ECeldaSinInicializar {};

template<class T>
class Memoria {

public:
	/**
	 * crea una memoria con 'capacidad' celdas.
	 */
	Memoria(unsigned int capacidad) {
		celdas = new T * [capacidad];
		for (int i = 0; i < capacidad; ++i) {
			celdas[i] = nullptr; // Todas las celdas apuntan a nullptr (no inicializadas)
		}
	}
	~Memoria() {
		for (int i = 0; i < capacidad; ++i) {
			delete celdas[i]; // Liberar la memoria de cada celda
		}
		delete[] celdas; // Liberar la memoria del array de punteros
	}


	/**
	 * Devuelve el valor almacenado en la celda 'd'.
	 * Si 'd' est� fuera de rango, levanta EDireccionInvalida.
	 * Si la celda 'd' no est� inicializada, levanta ECeldaSinInicializar.
	 */
	const T& valor(unsigned int d) const {
		// A implementar
		if(d >= capacidad) {
			throw EDireccionInvalida(); // La direcci�n est� fuera del rango v�lido
		}
		if (celdas[d] == nullptr) {
			throw ECeldaSinInicializar(); // La celda no est� inicializada
		}
		return *celdas[d]; // Devolver el valor almacenado en la celda
	}
	

	/**
	 * Almacena 'v' en la celda 'd'.
	 * Si 'd' est� fuera de rango, levanta EDireccionInvalida.
	 */
	void almacena(int d, T v) {
		if ( d >= capacidad) {
			throw EDireccionInvalida(); // La direcci�n est� fuera del rango v�lido
		}
		if (celdas[d] != nullptr) {
			delete celdas[d]; // Liberar memoria previa si ya estaba inicializada
		}
		celdas[d] = new T(v); // Asignar memoria para el nuevo valor
	}

	/**
	 * Devuelve 'true' si la celda 'd' est� inicializada.
	 * En otro caso devuelve 'false'.
	 * Si 'd' est� fuera de rango, levanta EDireccionInvalida.
	 */
	bool inicializada(unsigned int d) const {
		// A implementar 
		if ( d >= capacidad) {
			throw EDireccionInvalida(); // La direcci�n est� fuera del rango v�lido
		}
		return celdas[d] != nullptr;
	}

	/* Implementar el resto de operaciones y m�todos necesarios
	   para que la implementaci�n funcione */

	Memoria& operator = (const Memoria& m) {
		if (&m != this) {
			copiar(m);
		}
		return *this;
	}



private:
	/* Declarar los campos necesarios para representar los
	   valores de este TAD, as� como las operaciones auxiliares
	   que se consideren oportunas */

	T** celdas; // Array din�mico de punteros a tipo T
	int capacidad;

	void redimensionar(int n_cap) {

		T** viejos = celdas;
		capacidad = n_cap;
		celdas = new T * [capacidad];
		for (unsigned int i = 0; i < capacidad; i++) {
			celdas[i] = viejos[i];
		}

		//T** viejos = new T* [capacidad];
		/*
		Memoria viejos(capacidad);
		viejos.celdas = celdas;
		capacidad = n_cap;
		celdas = new T * [capacidad];
		for (unsigned int i = 0; i < capacidad; i++) {
			celdas[i] = viejos.celdas[i];
		}
		*/
		//delete[] viejos.celdas;
		/*for (unsigned int i = 0; i < viejos.capacidad; i++) {
			viejos.celdas[i] = nullptr;
			delete viejos.celdas[i];
		}*/



	}

	void copiar(const Memoria& m) {
		if (capacidad < m.capacidad) {
			redimensionar(m.capacidad);
		}
		for (unsigned int i = 0; i < m.capacidad; i++) {
			celdas[i] = m.celdas[i];
		}
		capacidad = m.capacidad;
	}

};
#endif


