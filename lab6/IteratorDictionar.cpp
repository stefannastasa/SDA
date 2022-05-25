#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	/* O(dict.size) */
	current = 0;
	while(d.V[current]->size() == 0 ){
		++current;
		if(current >= d.size)
			break;
	}
	if(current < 1000)
		currentInLst = new list<TElem>::iterator_lista(d.V[current]->iterator());
	else 
		currentInLst = new list<TElem>::iterator_lista(d.V[999]->iterator());
}


void IteratorDictionar::prim() {
	/* O(dict.size) */
	current = 0;
	while(dict.V[current]->size() == 0 ){
			++current;
			if(current >= dict.size )
				break;
	}
	currentInLst = new list<TElem>::iterator_lista(dict.V[current]->iterator());
}


void IteratorDictionar::urmator() {
	/* O(dict.size) */
	
	currentInLst->next();
	if(!currentInLst->valid())
	{
		while(++current < dict.size ){
			if(dict.V[current]->size() > 0)
				break;
		}
		if(current < dict.size)
			currentInLst = new list<TElem>::iterator_lista(dict.V[current]->iterator());
		else
			currentInLst = NULL;
	}
}


TElem IteratorDictionar::element() const{
	/* Theta(1) */
	if(valid())
		return *(*currentInLst);
	else
		return pair <TCheie, TValoare>  (-1, -1);
}


bool IteratorDictionar::valid() const {
	/* Theta(1) */
	if(current < dict.size)
		if(currentInLst != NULL)
			return currentInLst->valid();
		else return false;
	else 
		return false;
}

