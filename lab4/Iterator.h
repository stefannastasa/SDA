#pragma once


#include "LO.h"
class LO;


class Iterator{
	friend class LO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	LO& lista;
	
	int curent;
	/* aici e reprezentarea  specifica a iteratorului */


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		// muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		TElement elimina();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElement element() const;
};


