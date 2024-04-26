/**
  @file diccionario.h

  Implementaci�n din�mica del TAD Diccionario utilizando
  �rboles de b�squeda.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012;  Mercedes G�mez y Jos� Luis Sierra, 2017
	 Modificado en 2022 por Jos� Luis Sierra para permitir declarar iteradores no inicializados.
*/

#ifndef __DICCIO_H
#define __DICCIO_H

#include <fstream>
#include <cstddef>
#include "pila.h" // Usado internamente por los iteradores
using namespace std;


/**
 Implementaci�n din�mica del TAD Diccionario utilizando
 �rboles de b�squeda (no auto-balanceados).

 Las operaciones son:

 - diccionarioVacio: operaci�n generadora que construye
 un diccionario vac�o.

 - inserta(clave, valor): modificadora que a�ade una
 nueva pareja (clave, valor) al diccionario. Si la
 clave ya estaba se sustituye el valor.

 - borra(clave): operaci�n modificadora. Elimina la
 clave del diccionario.  Si la clave no est�,
 la operaci�n no tiene efecto.

 - valorDe(clave): operaci�n observadora que devuelve
 el valor asociado a una clave. Es un error preguntar
 por una clave que no existe.

 - contiene(clave): operaci�n observadora. Sirve para
 averiguar si se ha introducido una clave en el diccionario.

 - esVacio(): operacion observadora que indica si
 el diccionario tiene alguna clave introducida.

 @author Marco Antonio G�mez Mart�n ( con ligeras adaptaciones de Mercedes G�mez y Jos� Luis Sierra)
 */



 /// Excepciones generadas por algunos m�todos
class EClaveErronea {};

class EAccesoNoValido {};


template <class tClave, class tValor>
class Diccionario {
private:
	/**
	Clase nodo que almacena internamente la pareja (clave, valor)
	y los punteros al hijo izquierdo y al hijo derecho.
	*/
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const tClave& clave, const tValor& valor)
			: _clave(clave), _valor(valor), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo* iz, const tClave& clave, const tValor& valor, Nodo* dr)
			: _clave(clave), _valor(valor), _iz(iz), _dr(dr) {}

		tClave _clave;
		tValor _valor;
		Nodo* _iz;
		Nodo* _dr;
	};



	/**
	Elimina todos los nodos de una estructura arb�rea
	que comienza con el puntero ra.
	Se admite que el nodo sea NULL (no habr� nada que
	liberar).
	*/
	static void libera(Nodo* ra) {
		if (ra != NULL) {
			libera(ra->_iz);
			libera(ra->_dr);
			delete ra;
		}
	}

	/**
	Copia la estructura jer�rquica de nodos pasada
	como par�metro (puntero a su raiz) y devuelve un
	puntero a una nueva estructura jer�rquica, copia
	de anterior.
	*/
	static Nodo* copia(Nodo* ra) {
		if (ra == NULL)
			return NULL;
		else
			return new Nodo(copia(ra->_iz),
				ra->_clave, ra->_valor,
				copia(ra->_dr));
	}

	/**
	Busca una clave en la estructura jer�rquica de
	nodos cuya ra�z se pasa como par�metro, y devuelve
	el nodo en la que se encuentra (o NULL si no est�).
	@param p Puntero a la ra�z de la estructura de nodos
	@param clave Clave a buscar
	*/
	static Nodo* buscaAux(Nodo* p, const tClave& clave) {

		if (p == NULL)
			return NULL;
		else if (p->_clave == clave)
			return p;
		else if (clave < p->_clave)
			return buscaAux(p->_iz, clave);
		else
			return buscaAux(p->_dr, clave);
	}

	/**
	Inserta una pareja (clave, valor) en la estructura
	jer�rquica que comienza en el puntero pasado como par�metro.
	Ese puntero se admite que sea NULL, por lo que se crear�
	un nuevo nodo que pasar� a ser la nueva ra�z de esa
	estructura jer�rquica. El m�todo devuelve un puntero a la
	ra�z de la estructura modificada. En condiciones normales
	coincidir� con el par�metro recibido; s�lo cambiar� si
	la estructura era vac�a.
	@param clave Clave a insertar. Si ya aparec�a en la
	estructura de nodos, se sobreescribe el valor.
	@param valor Valor a insertar.
	@param p Puntero al nodo ra�z donde insertar la pareja.
	@return Nueva ra�z (o p si no cambia).
	*/
	static Nodo* insertaAux(const tClave& clave, const tValor& valor, Nodo* p) {

		if (p == NULL) {
			return new Nodo(clave, valor);
		}
		else if (p->_clave == clave) {
			p->_valor = valor;
			return p;
		}
		else if (clave < p->_clave) {
			p->_iz = insertaAux(clave, valor, p->_iz);
			return p;
		}
		else { // (clave > p->_clave)
			p->_dr = insertaAux(clave, valor, p->_dr);
			return p;
		}
	}




	/**
	Elimina (si existe) la clave/valor de la estructura jer�rquica
	de nodos apuntada por p. Si la clave aparec�a en la propia ra�z,
	�sta cambiar�, por lo que se devuelve la nueva ra�z. Si no cambia
	se devuelve p.

	@param p Ra�z de la estructura jer�rquica donde borrar la clave.
	@param clave Clave a borrar.
	@return Nueva ra�z de la estructura, tras el borrado. Si la ra�z
	no cambia, se devuelve el propio p.
	*/
	static Nodo* borraAux(Nodo* p, const tClave& clave) {

		if (p == NULL)
			return NULL;
		else
			if (clave == p->_clave)
				return borraRaiz(p);
			else
				if (clave < p->_clave) {
					p->_iz = borraAux(p->_iz, clave);
					return p;
				}
				else { // clave > p->_clave
					p->_dr = borraAux(p->_dr, clave);
					return p;
				}
	}



	/**
	Borra la ra�z de la estructura jer�rquica de nodos
	y devuelve el puntero a la nueva ra�z que garantiza
	que la estructura sigue siendo v�lida para un �rbol de
	b�squeda (claves ordenadas).
	*/
	static Nodo* borraRaiz(Nodo* p) {

		Nodo* aux;

		if (p->_iz == NULL) { // Si no hay hijo izquierdo, la ra�z pasa a ser el hijo derecho
			aux = p->_dr;
			delete p;
			return aux;
		}
		else
			if (p->_dr == NULL) { // Si no hay hijo derecho, la ra�z pasa a ser el hijo izquierdo
				aux = p->_iz;
				delete p;
				return aux;
			}
			else { // La nueva ra�z es el elemento m�s peque�o del hijo derecho (sucesor de la actual ra�z)
				return mueveMinYBorra(p);
			}
	}



	/**
	M�todo auxiliar para el borrado; recibe un puntero a la
	ra�z a borrar. Busca el elemento m�s peque�o del hijo derecho
	que se convertir� en la ra�z (que devolver�), borra la antigua
	ra�z (p) y "cose" todos los punteros, de forma que ahora:

	- El m�nimo pasa a ser la ra�z, cuyo hijo izquierdo y
	derecho eran los hijos izquierdo y derecho de la ra�z
	antigua.
	- El hijo izquierdo del padre del elemento m�s peque�o
	pasa a ser el antiguo hijo derecho de ese m�nimo.
	*/
	static Nodo* mueveMinYBorra(Nodo* p) {

		// Vamos bajando hasta que encontramos el elemento
		// m�s peque�o (aquel que no tiene hijo izquierdo).
		// Vamos guardando tambi�n el padre (que ser� null
		// si el hijo derecho es directamente el elemento
		// m�s peque�o).
		Nodo* padre = NULL;
		Nodo* aux = p->_dr;
		while (aux->_iz != NULL) {
			padre = aux;
			aux = aux->_iz;
		}

		// aux apunta al elemento m�s peque�o.
		// padre apunta a su padre (si el nodo es hijo izquierdo)

		// Dos casos dependiendo de si el sucesor es la ra�z
		// del hijo derecho del nodo a borrar (=> padre == NULL) o no (=> padre != NULL)
		// 
		if (padre != NULL) {  // el sucesor no es la ra�z del subarbol derecho sino un nodo m�s profundo
			padre->_iz = aux->_dr; // el hijo derecho del sucesor pasa a ser el nuevo izquierdo de su padre
			// el sucesor ocupa el puesto del que hay que borrar...
			aux->_iz = p->_iz; //... su hijo izdo (que antes era null) pasa a ser el izquierdo del que borras
			aux->_dr = p->_dr; // ... su hijo dcho pasa a ser el derecho del que borras
		}
		else { // el sucesor es la ra�z del subarbol derecho de la clave a borrar
			aux->_iz = p->_iz;
		}

		delete p; // eliminamos el nodo con la clave a borrar
		return aux; // devolvemos la nueva ra�z
	}

	/**
	Puntero a la ra�z de la estructura jer�rquica
	de nodos.
	*/
	Nodo* _ra;

public:
	/** Constructor; operacion diccionarioVacio */
	Diccionario() : _ra(NULL) {
	}

	/** Destructor; elimina la estructura jer�rquica de nodos. */
	~Diccionario() {
		//libera();
		libera(_ra);
		_ra = NULL;
	}


	/** Constructor copia */
	Diccionario(const Diccionario<tClave, tValor>& other) : _ra(NULL) {
		_ra = copia(other._ra);
	}

	/** Operador de asignaci�n */
	Diccionario<tClave, tValor>& operator=(const Diccionario<tClave, tValor>& other) {
		if (this != &other) {
			libera(_ra);
			_ra = copia(other._ra);
		}
		return *this;
	}


	/**
	 Operaci�n observadora que devuelve si el diccionario es vac�o
	 (no contiene elementos) o no.
	 */
	bool esVacio() const {
		return _ra == NULL;
	}

	/**
	 Operaci�n observadora que permite averiguar si una clave
	 determinada est� o no en el diccionario.

	 @param clave Clave por la que se pregunta.
	 @return true si el diccionario contiene un valor asociado
	 a esa clave.
	 */
	bool contiene(const tClave& clave) const {
		return (buscaAux(_ra, clave) != NULL) ? true : false;
	}


	/**
	 Operaci�n observadora que devuelve el valor asociado
	 a una clave dada.

	 @param clave Clave por la que se pregunta.
	 */
	const tValor& valorPara(const tClave& clave) const {
		Nodo* p = buscaAux(_ra, clave);
		if (p == NULL)
			throw EClaveErronea();
		return p->_valor;
	}


	/**
	 Operaci�n mutadora que a�ade una nueva clave/valor
	 a un diccionario.
	 @param clave Clave nueva.
	 @param valor Valor asociado a esa clave. Si la clave
	 ya se hab�a insertado previamente, sustituimos el valor
	 viejo por el nuevo.
	 */
	void inserta(const tClave& clave, const tValor& valor) {
		_ra = insertaAux(clave, valor, _ra);
	}

	/**
	 Operaci�n modificadora que elimina una clave del diccionario.
	 Si la clave no exist�a la operaci�n no tiene efecto.
	 @param clave Clave a eliminar.
	 */
	void borra(const tClave& clave) {
		_ra = borraAux(_ra, clave);
	}

	// //
	// ITERADOR CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	Clase interna que implementa un iterador que permite recorrer el
	�rbol en inorden pero no permite modificarlo.
	*/
	class ConstIterator {
	public:
		ConstIterator() : _act(NULL) {}
		void next() {
			if (_act == NULL) throw EAccesoNoValido();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr != NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya est� vac�a, no quedan
				// ascendientes por visitar
				if (_ascendientes.esVacia())
					_act = NULL;
				else {
					_act = _ascendientes.cima();
					_ascendientes.desapila();
				}
			}
		}

		const tClave& clave() const {
			if (_act == NULL) throw EAccesoNoValido();
			return _act->_clave;
		}

		const tValor& valor() const {
			if (_act == NULL) throw EAccesoNoValido();
			return _act->_valor;
		}

		bool operator==(const ConstIterator& other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator& other) const {
			return !(this->operator==(other));
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class Diccionario;

		ConstIterator(Nodo* act) {
			_act = primeroInOrden(act);
		}

		/**
		Busca el primer elemento en inorden de
		la estructura jer�rquica de nodos pasada
		como par�metro; va apilando sus ascendientes
		para poder "ir hacia atr�s" cuando sea necesario.
		@param p Puntero a la ra�z de la subestructura.
		*/
		Nodo* primeroInOrden(Nodo* p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.apila(p);
				p = p->_iz;
			}
			return p;
		}

		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo* _act;

		// Ascendientes del nodo actual
		// a�n por visitar
		Pila<Nodo*> _ascendientes;
	};

	/**
	Devuelve el iterador constante al principio del
	diccionario (clave m�s peque�a).
	@return iterador al principio del recorrido;
	coincidir� con cend() si el diccionario est� vac�o.
	*/
	ConstIterator cbegin() const {
		return ConstIterator(_ra);
	}

	/**
	@return Devuelve un iterador al final del recorrido
	(fuera de �ste).
	*/
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	ConstIterator cbusca(const tClave& c)  const {
		Pila<Nodo*> ascendientes;
		Nodo* p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.apila(p);
				p = p->_iz;
			}
			else
				p = p->_dr;
		}
		ConstIterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}

	// //
	// ITERADOR NO CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	Clase interna que implementa un iterador sobre
	la �rbol de b�squeda que permite recorrer la lista e incluso
	alterar el valor de sus elementos.
	*/
	class Iterator {
	public:
		Iterator() : _act(NULL) {}
		void next() {
			if (_act == NULL) throw EAccesoNoValido();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr != NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya est� vac�a, no quedan
				// ascendientes por visitar
				if (_ascendientes.esVacia())
					_act = NULL;
				else {
					_act = _ascendientes.cima();
					_ascendientes.desapila();
				}
			}
		}

		const tClave& clave() const {
			if (_act == NULL) throw EAccesoNoValido();
			return _act->_clave;
		}

		tValor& valor() const {
			if (_act == NULL) throw EAccesoNoValido();
			return _act->_valor;
		}

		void setVal(const tValor& valor) {
			if (_act == NULL) throw EAccesoNoValido();
			_act->_valor = valor;
		}

		bool operator==(const Iterator& other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator& other) const {
			return !(this->operator==(other));
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class Diccionario;

		Iterator(Nodo* act) {
			_act = primeroInOrden(act);
		}

		/**
		Busca el primer elemento en inorden de
		la estructura jer�rquica de nodos pasada
		como par�metro; va apilando sus ascendientes
		para poder "ir hacia atr�s" cuando sea necesario.
		@param p Puntero a la ra�z de la subestructura.
		*/
		Nodo* primeroInOrden(Nodo* p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.apila(p);
				p = p->_iz;
			}
			return p;
		}

		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo* _act;

		// Ascendientes del nodo actual
		// a�n por visitar
		Pila<Nodo*> _ascendientes;
	};

	/**
	Devuelve el iterador al principio del recorrido.
	@return iterador al principio del recorrido;
	coincidir� con final() si el recorrido est� vac�o.
	*/
	Iterator begin() {
		return Iterator(_ra);
	}

	/**
	@return Devuelve un iterador al final del recorrido
	(fuera de �ste).
	*/
	Iterator end() {
		return Iterator();
	}

	Iterator busca(const tClave& c) {
		Pila<Nodo*> ascendientes;
		Nodo* p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.apila(p);
				p = p->_iz;
			}
			else
				p = p->_dr;
		}
		Iterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}
};

#endif // __DICCIO_H
