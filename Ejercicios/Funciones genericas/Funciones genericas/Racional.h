
#ifndef _RACIONAL_H
#define _RACIONAL_H

#include <iostream>

using namespace std;


template <class T>
class Racional {
public:
	//Excepcion que se lanza cuando se trata de crear
	//una fraccion con denominador 0
	class EDenominadorCero {};
	//Excepcion que se lanza cuando se produce una division
	//por 0
	class EDivisionPorCero {};

	// Funcion amiga que permite escribir una fraccion en un 'stream'
	friend ostream& operator<< (ostream& out, const Racional<T>& f) {
		// Poner aquí el código para escribir la fracción 'f' por el
		// stream 'out'.
		out << f._numer << "/" << f._denom;
		return out;
	}


	// IMPLEMENTAR AQUI LAS OPERACIONES DEL TAD, generalizando
	// la implementación de las operaciones del TAD Racional 
	// concreto.

	Racional() {
		_numer = 0;
		_denom = 1;
	}

	Racional(const T& n, const T& d) {
		if (d != 0) {
			_numer = n;
			_denom = d;
			reduce();
		}
		else {
			throw EDenominadorCero();
		}
	}

	Racional suma(const Racional& r) {
		Racional r2 = Racional();
		r2._denom = mcm(this->_denom, r._denom);
		r2._numer = (this->_numer * r2._denom / this->_denom) + (r._numer * r2._denom / r._denom);
		r2.reduce();
		return r2;
	}

	Racional operator - (const Racional& r) {
		Racional r2 = Racional();
		r2._denom = mcm(this->_denom, r._denom);
		r2._numer = ((this->_numer * r2._denom / this->_denom) - (r._numer * r2._denom / r._denom));
		r2.reduce();
		return r2;
	}

	void operator *= (const Racional& r) {
		this->_numer = _numer * r._numer;
		this->_denom = _denom * r._denom;
		reduce();
	}

	void divideYActualiza(const Racional& r) {
		if (r._numer == 0) {
			throw EDivisionPorCero();
		}
		else {
			this->_numer = this->_numer * r._denom;
			this->_denom = this->_denom * r._numer;
			reduce();
		}
	}

	bool operator == (const Racional& r) {
		return (this->_numer == r._numer) && (this->_denom == r._denom);
	}


private:
	// Incluir aquí los detalles de representación, junto con 
	// las operaciones privadas que se considere oportuno
	T _numer;
	T _denom;
	void reduce() {
		// Se asegura que el denominador siempre sea positivo   
		if (_denom < 0) {
			_numer = -_numer;
			_denom = -_denom;
		}
		// Se divide numerador y denominador por el maximo comun divisor de ambos
		T fsimp = mcd(_numer, _denom);
		_numer /= fsimp;
		_denom /= fsimp;
	}

	T mcd(T v1, T v2) {
		// El calculo del maximo comun divisor se hace por el algoritmo de Euclides
		v1 = abs(v1);
		v2 = abs(v2);
		if (v1 < v2) {
			T tmp = v1;
			v1 = v2;
			v2 = tmp;
		}
		while (v2 != 0) {
			T nv2 = v1 % v2;
			v1 = v2;
			v2 = nv2;
		}
		return v1;
	}

	T mcm(T v1, T v2) {
		return v1 * v2 / mcd(v1, v2);
	}
};


#endif