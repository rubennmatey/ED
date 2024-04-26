#include "Racional.h"
#include <cmath>

//Metodos publicos

  //**** COMPLETAR
  //  Deben implementarse los metodos publicos de la clase
  //****

Racional::Racional() {
	_numer = 0;
	_denom = 1;
}

Racional::Racional(long n, long d) {
	if (d != 0) {
		_numer = n;
		_denom = d;
		reduce();
	}
	else {
		throw EDenominadorCero();
	}
}

Racional Racional:: suma(const Racional& r) {
	Racional r2;
	r2._denom = mcm(this->_denom, r._denom);
	r2._numer = (this->_numer * r2._denom / this->_denom) + (r._numer * r2._denom / r._denom);
	r2.reduce();
	return r2;
}

Racional Racional:: operator - (const Racional r) {
	Racional r2 = Racional();
	r2._denom = mcm(this->_denom, r._denom);
	r2._numer = ((this->_numer * r2._denom / this->_denom) - (r._numer * r2._denom / r._denom));
	r2.reduce();
	return r2;
}

void Racional :: operator *= (const Racional r) {
	this->_numer = _numer * r._numer;
	this->_denom = _denom * r._denom;
	reduce();
}


void Racional :: divideYActualiza(const Racional r) {
	if (r._numer == 0) {
		throw EDivisionPorCero();
	}
	else {
		this->_numer = this->_numer * r._denom;
		this->_denom = this->_denom * r._numer;
		reduce();
	}
}

bool Racional:: operator == (const Racional r) {
	return (this->_numer == r._numer) && (this->_denom == r._denom);
}


// Funciones amigas
ostream& operator<<(ostream& out, const Racional& f) {
	out << f._numer << "/" << f._denom;
	return out;
}

// Metodos privados
void Racional::reduce() {
	// Se asegura que el denominador siempre sea positivo   
	if (_denom < 0) {
		_numer = -_numer;
		_denom = -_denom;
	}
	// Se divide numerador y denominador por el maximo comun divisor de ambos
	long fsimp = mcd(_numer, _denom);
	_numer /= fsimp;
	_denom /= fsimp;
}

long Racional::mcd(long v1, long v2) {
	// El calculo del maximo comun divisor se hace por el algoritmo de Euclides
	v1 = abs(v1);
	v2 = abs(v2);
	if (v1 < v2) {
		long tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	while (v2 != 0) {
		long nv2 = v1 % v2;
		v1 = v2;
		v2 = nv2;
	}
	return v1;
}

long Racional::mcm(long v1, long v2) {
	return v1 * v2 / mcd(v1, v2);
}

