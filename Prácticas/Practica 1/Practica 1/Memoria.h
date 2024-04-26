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
		// A implementar
		_capacidad = capacidad;
		_valor = new T * [capacidad];
		for (unsigned int i = 0; i < capacidad ; i++) {
			_valor[i] = nullptr;
		}
	}

	Memoria(const Memoria& mem) {
		_capacidad = mem._capacidad;
		_valor = new T * [_capacidad];
		for (unsigned int i = 0; i < mem._capacidad; i++) {
			if (mem._valor[i] == nullptr) {
				_valor[i] = nullptr;
			}
			else {
				_valor[i] = new T(*mem._valor[i]);
			}
		}
	}

	/**
	 * Devuelve el valor almacenado en la celda 'd'.
	 * Si 'd' est� fuera de rango, levanta EDireccionInvalida.
	 * Si la celda 'd' no est� inicializada, levanta ECeldaSinInicializar.
	 */
	const T& valor(unsigned int d) const {
		// A implementar
		if (d >= _capacidad) {
			throw EDireccionInvalida();
		}
		else {
			if (!inicializada(d)) {
				throw ECeldaSinInicializar();
			}
			else {
				return *_valor[d];
			}
		}
	}

	/**
	 * Almacena 'v' en la celda 'd'.
	 * Si 'd' est� fuera de rango, levanta EDireccionInvalida.
	 */
	void almacena(unsigned int d, const T& v) {
		// A implementar
		if (d >= _capacidad) {
			throw EDireccionInvalida();
		}
		else {
			if (_valor[d] != nullptr) {
				delete _valor[d];
			}
			_valor[d] = new T(v);
		}
	}

	/**
	 * Devuelve 'true' si la celda 'd' est� inicializada.
	 * En otro caso devuelve 'false'.
	 * Si 'd' est� fuera de rango, levanta EDireccionInvalida.
	 */
	bool inicializada(unsigned int d) const {
		// A implementar 
		if (d >= _capacidad) {
			throw EDireccionInvalida();
		}
		else {
			return _valor[d] != nullptr;
		}
	}

	/* Implementar el resto de operaciones y m�todos necesarios
	   para que la implementaci�n funcione */

	Memoria& operator = (const Memoria& m) {
		if (&m != this) {
			if (m._valor != nullptr) {
				for (unsigned int i = 0; i < _capacidad; i++) {
					delete _valor[i];
					_valor[i] = nullptr;
				}
				if (_valor == nullptr) {
					_capacidad = m._capacidad;
					_valor = new T * [m._capacidad];
					for (unsigned int i = 0; i < _capacidad; i++) {
						_valor[i] = nullptr;
					}
				}
				copiar(m);
			}
			else {
				for (unsigned int i = 0; i < m._capacidad; i++) {
					delete _valor[i];
				}
				_capacidad = m._capacidad;
			}
		}
		return *this;
	}

	// HAY QUE HACER DESTRUCTOR
	~Memoria() {		
		for (unsigned int i = 0; i < _capacidad; i++) {
			delete _valor[i];			
		}
		_capacidad = 0;
		delete[] _valor; 
		
	}

private:
	/* Declarar los campos necesarios para representar los
	   valores de este TAD, as� como las operaciones auxiliares
	   que se consideren oportunas */

	unsigned int _capacidad;
	T** _valor;

	void redimensionar(unsigned int n_cap) {
		
	}

	void copiar(const Memoria<T>& m) {
		if (_capacidad < m._capacidad) {
			T** viejos = _valor;
			_valor = new T * [m._capacidad];
			for (unsigned int i = 0; i < m._capacidad; i++) {
				_valor[i] = nullptr;
			}

			for (unsigned int i = 0; i < m._capacidad; i++) {
				if (viejos[i] != nullptr) {
					*_valor[i] = *viejos[i];
				}
				else {
					_valor[i] = nullptr;
				}
				delete viejos[i];
			}
			delete[] viejos;
		}

		_capacidad = m._capacidad;

		for (unsigned int i = 0; i < _capacidad; i++) {
			if (m._valor[i] != nullptr) {
				if (_valor[i] == nullptr) {
					_valor[i] = new T(*m._valor[i]);

				}
				else {
					*_valor[i] = *m._valor[i];
				}
			}
			else {
				if (_valor[i] != nullptr) delete _valor[i];
				_valor[i] = nullptr;
			}
		}
			
	}
};
#endif


