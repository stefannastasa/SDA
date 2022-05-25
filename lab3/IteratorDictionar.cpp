#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <iostream>
using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	/* Complexitate Theta(1) */
	current = dict.prim;
}


void IteratorDictionar::prim() {
	/* Complexitate Theta(1) */
	current = dict.prim;
}


void IteratorDictionar::urmator() {
	/* Complexitate Theta(1) */
	if(valid())
		current = current->next;
}


TElem IteratorDictionar::element() const{
	/* Complexitate Theta(1) */
	if(valid())
		return current->content;

	return pair <TCheie, TValoare>  (-1, -1);
}


bool IteratorDictionar::valid() const {
	/* Complexitate Theta(1) */
	if(current!=NULL)
		return true;
	return false;
}

