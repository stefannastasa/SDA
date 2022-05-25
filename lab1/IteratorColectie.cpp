#include "IteratorColectie.h"
#include "Colectie.h"
#include <iostream>

IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* Complexitate Theta(1) */
	prim();
	frecv = 0;
}

void IteratorColectie::prim() {
	/* Complexitate Theta(1) */
	curent = col.mini;
	frecv = 0;
}


void IteratorColectie::urmator() {
	/* Complexitate Theta(1) */
	++frecv;
	if(col.nrAparitii(curent)<=frecv){
		frecv=0;
		++curent;
		while(col.nrAparitii(curent) == 0 && curent<=col.maxi)++curent;
	}
}


bool IteratorColectie::valid() const {
	/* Complexitate Theta(1) */
	if(col.vida())return false;
	if(curent <= col.maxi)
		return frecv < col.nrAparitii(curent);
	else return false;
}



TElem IteratorColectie::element() const {
	/* Complexitate Theta(1) */
	if(this->valid() && col.nrAparitii(curent))
		return curent;
	
	return NULL_TELEM;
}
