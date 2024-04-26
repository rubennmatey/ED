/*
NOMBRE Y APELLIDOS DE LOS/AS AUTORES/AS:
	Iago Barroso Ortega
	Rubén Matey Martín

*/


#include "ParqueDeAtracciones.h"

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	La complejidad de esta constructora es constante y es O(1) ya que solamente crea el objeto y no realiza ninguna operación más
*/

ParqueDeAtracciones::ParqueDeAtracciones() {	
	
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	Como la complejidad de las funciones contiene e inserta en el peor de los casos es O(n) la complejidad 
	de la función es O(n)
*/
void ParqueDeAtracciones::an_atraccion(const string& nombre_atraccion) {
	if (lista_atracciones.contiene(nombre_atraccion)) {
		throw EAtraccionYaExiste();
	}
	else {
		InfoAtraccion a = InfoAtraccion(nombre_atraccion);
		lista_atracciones.inserta(nombre_atraccion, a);
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	Como la complejidad de las funciones contiene e inserta en el peor de los casos es O(n) la complejidad 
	de la función es O(n)
*/
void ParqueDeAtracciones::an_ninio(const string& nombre_ninio) {
	if (lista_ninos.contiene(nombre_ninio)) {
		throw ENinioYaRegistrado();
	}
	else {
		InfoNino n = InfoNino(nombre_ninio);
		lista_ninos.inserta(nombre_ninio, n);
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	Como las complejidades de las funciones busca, valor y pon_final es O(n) la complejidad de la función 
	es O(n)
*/
void ParqueDeAtracciones::poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion) {
	DiccionarioHash<string, InfoNino>::Iterator in = lista_ninos.busca(nombre_ninio);
	DiccionarioHash<string, InfoAtraccion>::Iterator ia = lista_atracciones.busca(nombre_atraccion);


	if (in != lista_ninos.end() && ia != lista_atracciones.end() && !in.valor().esta_en_cola) {
		in.valor().esta_en_cola = true;
		ia.valor().cola.pon_final(in.valor());
	}
	else {
		throw EAccesoAtraccion();
	}

}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	Las dos búsquedas en los diccionarios tienen complejidad O(n), la funcion esVacia también tiene complejidad
	O(n) y las actualizaciones de los valores en los diccionarios son O(n) por lo que la complejidad de la 
	función es O(n)
*/
void ParqueDeAtracciones::avanzar(const string& nombre_atraccion) {
	DiccionarioHash<string, InfoAtraccion>::Iterator ia = lista_atracciones.busca(nombre_atraccion);
	if (ia != lista_atracciones.end()) {
		if (ia.valor().cola.esVacia()) return;
		DiccionarioHash<string, InfoNino>::Iterator in = lista_ninos.busca(ia.valor().cola.primero().nombre);
		ia.valor().cola.quita_ppio();
		in.valor().esta_en_cola = false;
		if (in.valor().visitas.contiene(nombre_atraccion)) {
			int n = in.valor().visitas.valorPara(nombre_atraccion);
			in.valor().visitas.inserta(nombre_atraccion, n + 1);
		}
		else {
			in.valor().visitas.inserta(nombre_atraccion, 1);
		}
	}
	else {
		throw EAtraccionNoExiste();
	}
	
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	La complejidad dependerá del número de atracciones que haya visitado el níño ya que el acceso a estas 
	visitas es lo que tendrá más coste -> O(1 + k), siendo k el numero de atracciones visitadas
*/
Lista<string> ParqueDeAtracciones::atracciones_visitadas(const string& nombre_ninio) const {
	DiccionarioHash<string, InfoNino>::ConstIterator in = lista_ninos.cbusca(nombre_ninio);

	if (in != lista_ninos.cend()) {
		Diccionario<string, int>::ConstIterator id = in.valor().visitas.cbegin();
		Lista<string> lista_atracciones;
		while (id != in.valor().visitas.cend()) {
			lista_atracciones.pon_final(id.clave());
			id.next();
		}
		return lista_atracciones;
	}
	else {
		throw ENinioNoRegistrado();
	}
}

/*
COMPLEJIDAD: Determina justificadamente la complejidad de la operaci?n.
	La complejidad de esta función será O(n) ya que la búsqueda en los diccionarios ambas en el peor caso tendrán complejidad O(n)
	donde n es el número de elementos en el diccionario, la complejidad de la comprobación de la lista con la funcion contiene es O(1) 
	y el acceso al diccionario de visitas para devolver el valor entero es, al igual, O(1)
*/
int ParqueDeAtracciones::numero_visitas(const string& nombre_ninio, const string& nombre_atraccion) const {
	DiccionarioHash<string, InfoNino>::ConstIterator in = lista_ninos.cbusca(nombre_ninio);
	DiccionarioHash<string, InfoAtraccion>::ConstIterator ia = lista_atracciones.cbusca(nombre_atraccion);

	if (in != lista_ninos.cend() && ia != lista_atracciones.cend()) {
		if (!in.valor().visitas.contiene(ia.clave())) return 0;
		return in.valor().visitas.valorPara(ia.clave());
	}
	else {
		throw EConsultaNumViajes();
	}

}

