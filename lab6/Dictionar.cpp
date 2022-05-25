#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

ull hashFunct(TCheie x, int range){
	if(x < 0)
		x += range;
	ull result = 0;
	const ull normalis = 23; //arbitrary prime number
	//for now

	while(x > 0){
		result += (x & 7);
		result *= normalis;
		x = (x >> 4);
	}

	return result % range;
}
// Mare parte din complexitatile acestei structuri de date este dependenta de numarul
// de coliziuni pe care functia de hashing le genereaza => cu cat am o functie de hashing 
// mai buna si o multime de indexi mai mare, eficienta in timp a structurii este de O(1) pentru
// un numar cat mai mare de elemente
Dictionar::Dictionar() {
	/* Theta(size) */
	size = 1000;
	nrElems = 0;
	V = new list<TElem>*[size];
	for(ull a = 0;a<size;++a)
		V[a] = new list<TElem>;
}

Dictionar::~Dictionar() {
	/* Theta(size) */
	for(ull a = 0;a<size;++a)
		delete V[a];
	delete[] V;
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
	/* O( V[index].size() ) - O(nr de coliziuni pe valoarea hash-ului) */
	TValoare to_return = NULL_TVALOARE;
	ull index = hashFunct(c, size);
	list<TElem>::iterator_lista pos = V[index]->iterator();
	if(V[index]->size() > 0){
		for(; pos.valid() ; pos.next() ){
			if( (*pos).first == c ){
				to_return = (*pos).second;
				pos.modif(TElem(c, v));
				return to_return;
			}
		}
	}

	// std::cout<<c<<' '<<hashFunct(c,size)<<'\n';
	V[index]->pushBack(TElem(c, v));
	++nrElems;
	
	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	/* O(nr de coliziuni pe valoarea hash-ului)*/
	TValoare to_return = NULL_TVALOARE;
	ull index = hashFunct(c, size);

	if(V[index]->size() == 0){
		return to_return;
	}else{
		list<TElem>::iterator_lista pos = V[index]->iterator();
		for(;pos.valid();pos.next()){
			if( (*pos).first == c){
				to_return = (*pos).second;
				break;
			}
		}
		return to_return;
	}
}


TValoare Dictionar::sterge(TCheie c){
	/* O(nr de coliziuni pe valoarea hash-ului) */
	TValoare to_return = NULL_TVALOARE;
	ull index = hashFunct(c, size);
	list<TElem>::iterator_lista pos = V[index]->iterator();

	for(;pos.valid();pos.next()){
		if( (*pos).first == c){
			to_return = (*pos).second;
			pos.deleteElem();
			--nrElems;

			break;
		}
	}
	return to_return;
}


int Dictionar::dim() const {
	/* Theta(1) */
	return nrElems;
}

bool Dictionar::vid() const{
	/* Theta(1) */
	
	return nrElems == 0;
}

void Dictionar::filtreaza(Conditie cond){
	
	for(ull i = 0;i<size;++i){
		if(V[i]->size() > 0){
			list<TElem>::iterator_lista pos = V[i]->iterator();
			while(pos.valid()){
				if( cond((*pos).first) ){
					pos.deleteElem();
					--nrElems;
				}else{
					pos.next();
				}
			}
		}
	}
}


IteratorDictionar Dictionar::iterator() const{
	return IteratorDictionar(*this);
}


