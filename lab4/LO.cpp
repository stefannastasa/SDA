#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

//Complexitate Theta(1)
LO::LO(Relatie r){
	size = 20;
	nrElems = 0;
	rel = r;
	prim = -1;
	ultim = -1;

	// std::cout<<urm;
	size = 20;
	this->values = new TElement[20];
	this->urm = new int[20];
	this->pen = new int [20];
	urm[size-1] = -1;
	pen[0] = -1;
	primEmpty = 0;
	ultimEmpty = size-1;
	
	for(int i = 0;i < size-1;++i){
		urm[i] = i+1;
		pen[i+1] = i;
	}

}

// returnare dimensiune
int LO::dim() const {
	/* Complexitate Theta(1) */
	return nrElems;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* Complexitate Theta(1) */
	if(nrElems == 0)
		return true;
	else
		return false;
}

// returnare element
// arunca exceptie daca i nu e valid
TElement LO::element(int i) const{
	/* Complexitate O(index)*/
	exception exep;
	if(i>=nrElems || i < 0)
		throw exep;
	if(vida())
		return -1;

	int pos = prim;
	int it = 0;
	while(it<i){
		++it;
		pos = urm[pos];
	}

	return values[pos];
}

// sterge element de pe o pozitie i si returneaza elementul sters
// arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	/* Complexitate O(index) */
	exception exep;
	if(i>=nrElems || i<0)
		throw exep;
	if(vida())
		return NULL_TELEMENT;
	
	int pos = prim;
	int it = 0;
	while(it<i){
		++it;
		pos = urm[pos];
	}
	TElement to_return = values[pos];
	values[pos] = NULL_TELEMENT;

	if(it == 0){
		pen[urm[pos]] = -1;
		prim = urm[pos];

		urm[ultimEmpty] = pos;
		pen[pos] = ultimEmpty;
		urm[pos] = -1;
		
		ultimEmpty = pos;
	}else{
		urm[pen[pos]] = urm[pos];
		pen[urm[pos]] = pen[pos];

		urm[pos] = pen[pos] = -1;

		urm[ultimEmpty] = pos;
		pen[pos] = ultimEmpty;
		
		ultimEmpty = pos;
	}

	--nrElems;

	return to_return;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	/* Complexitate O(nrElems)*/
	if(vida())
		return -1;

	int pos = prim;
	int i = 0;
	
	while(rel(values[pos], e) && pos != ultim){
		if(e == values[pos])
			return i;
		
		++i;
		pos = urm[pos];
	}
	return -1;
	
}

// adaugare element in LO
void LO::adauga(TElement e) {
	/* Complexitate O(2*size + nrElems) */
	if(nrElems == size - 2)
		resize();
	
	if(vida()){
		prim = primEmpty;
		ultim = urm[primEmpty];
		primEmpty = urm[urm[primEmpty]];

		values[prim] = e;
		urm[prim] = ultim;
		pen[prim] = -1;

		pen[ultim] = prim;
		urm[ultim] = -1;
		values[ultim] = NULL_TELEMENT;

		++nrElems;

	}else{

		int pos = prim;
		while(rel(values[pos], e) && pos != ultim)
			pos = urm[pos];

		if(pos == prim){
			
			int newEmpty = urm[primEmpty];

			values[primEmpty] = e;
			urm[primEmpty] = prim;
			pen[prim] = primEmpty;
			pen[primEmpty] = -1;

			prim = primEmpty;

			primEmpty = newEmpty;
			pen[primEmpty] = -1;


		}else{
			int newEmpty = urm[primEmpty];
			values[primEmpty] = e;

			pen[primEmpty] = pen[pos];
			urm[primEmpty] = pos;
			urm[pen[pos]] = primEmpty;
			pen[pos] = primEmpty;

			primEmpty = newEmpty;
			pen[primEmpty] = -1;

		}
		++nrElems;
	}

}

// returnare iterator
Iterator LO::iterator(){
	return Iterator(*this);
}


//destructor
LO::~LO() {
	/* Complexitate Theta(1) */
	delete[] values;
	// std::cout<<urm;
	delete[] urm;
	delete[] pen;
}

void LO::resize() {
	/*Complexitate Theta(2*size)*/
	int old_size = size;
	size*=2;
	
	TElement *n_values = new TElement[size];
	int *n_urm = new int[size];
	int *n_pen = new int[size];

	for(int i=0;i<old_size;++i){
		n_values[i] = values[i];
		n_urm[i] = urm[i];
		n_pen[i] = pen[i];
	}
	n_urm[ultimEmpty] = old_size;
	for(int i=old_size;i<size;++i){
		n_values[i] = NULL_TELEMENT;
		n_urm[i] = i+1;

		n_pen[i] = ultimEmpty;
		ultimEmpty = i; 
	}
	delete[] values;
	delete[] urm;
	delete[] pen;
	values = n_values;
	urm = n_urm;
	pen = n_pen;

}


/*
	Complexitate Theta(nrElems)
	Subalgoritm ultimulIndex(LO, TElement e)


	Pre: LO, TElement e (cauta ultima pozitie a elementului e din LO)
	Post: rezultat <- indexul ultimului element cu aceasta valoare
					sau -1 daca acesta nu exista in lista 

	daca LO.vida() == Adevarat atunci
		return -1
	SfDaca

	pos <- LO.prim
	index <- 0
	rezultat <- -1
	CatTimp(pos != LO.ultim)
		Daca e == LO.values atunci
			rezultat = i
		SfDaca
	
		i <- i+1
		pos <- LO.urm[pos]
	SfCatTimp

	return rezultat

	SfSubalgoritm
*/
int LO::ultimulIndex(TElement e) const{
	
	if(vida())
		return -1;

	int pos = prim;
	int i = 0;
	int result = -1;
	while(pos != ultim){
		if(e == values[pos])
			result = i;
		++i;
		pos = urm[pos];
	}
	
	return result;

}