/*
NOMBRE Y APELLIDOS DE LOS/AS AUTORES/AS:
	Iago Barroso Ortega
	Rub�n Matey Mart�n

*/

#ifndef _PARQUE_ATRACCIONES_H
#define _PARQUE_ATRACCIONES_H
#include <string>
#include "lista.h"
#include "diccionario.h"
#include "DiccionarioHash.h"


// Realizar los 'include' adicionales
// que se estimen oportunos.

using namespace std;

class EAtraccionYaExiste {};

class ENinioYaRegistrado {};

class EAtraccionNoExiste {};

class ENinioNoRegistrado {};

class EAccesoAtraccion {};

class EConsultaNumViajes {};


class ParqueDeAtracciones {
public:
	ParqueDeAtracciones();
	void an_atraccion(const string& nombre_atraccion);
	void an_ninio(const string& nombre_ninio);
	void poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion);
	void avanzar(const string& nombre_atraccion);
	Lista<string> atracciones_visitadas(const string& nombre_ninio) const;
	int numero_visitas(const string& nombre_ninio, const string& nombre_atraccion) const;
private:
	// Definir la representaci�n que se estime oportuna, as� como declarar los m�todos
	// auxiliares que se consideren oportunos (si se estima necesario). 
	
	
	
	class InfoNino {
	public:
		InfoNino(string n) {
			nombre = n;
			esta_en_cola = false;
		}

		string nombre;
		bool esta_en_cola;
		Diccionario<string, int> visitas;
	};

	class InfoAtraccion {
	public:
		InfoAtraccion(string n) {
			nombre = n;
		}

		string nombre;
		Lista<InfoNino> cola;
	};

	DiccionarioHash<string, InfoAtraccion> lista_atracciones;
	DiccionarioHash<string, InfoNino> lista_ninos;

};

#endif