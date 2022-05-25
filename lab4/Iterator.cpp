#include "Iterator.h"
#include "LO.h"

Iterator::Iterator(LO& lo) : lista(lo){
	/* Complexitate Theta(1) */
	curent = lista.prim;
}

void Iterator::prim() {
	/* Complexitate Theta(1) */
	curent = lista.prim;
}

void Iterator::urmator(){
	/* Complexitate Theta(1) */
	std::exception exep;
	if(valid())
		curent = lista.urm[curent];
	else throw exep;
	// exceptie!!
}

bool Iterator::valid() const{
	/* Complexitate Theta(1) */
	if(curent == lista.ultim)
		return 0;
	
	return 1;
}

TElement Iterator::element() const{
	/* Complexitate Theta(1) */
	if( valid() )
		return lista.values[curent];

	std::exception e;
	throw e;
}




TElement Iterator::elimina(){
	/*Complexitate Theta(curent)*/
	std::exception e;
	if(!valid())
		throw e;
	
	TElement to_return = element();
	int to_delete = curent;
	urmator();
	lista.sterge(to_delete);

	return to_return;
}


