#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
#include <bits/stl_vector.h>
Dictionar::Dictionar() {
	/* Complexitate Theta(1) */
	prim = NULL;
	last = NULL;
	nrElems = 0;
}

Dictionar::~Dictionar() {
	/* Complexitate Theta(nrElems) */
	while(prim != NULL){
		node* aux = prim;
		prim = prim->next;

		free(aux);
	}
}

TValoare Dictionar::adauga(TCheie c, TValoare v){
	/* Complexitate O(n) */
	node* pos = (node*)searchNode(c);
	if(pos != NULL){
		TValoare changed = pos->content.second; 
		pos->content.second = v;

		return changed;
	}

	TElem cont(c,v);
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->content = cont;
	newNode->next = NULL;
	newNode->last = NULL;	

	if(nrElems == 0){
		prim = newNode;
		last = newNode;
	}else{
		last->next = newNode;
		newNode->last = last;

		last = newNode;
	}

	++nrElems;

	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{
	/* Complexitate O(n) */
	node* pos = this->searchNode(c);

	if(pos!=NULL)
		return pos->content.second;

	return NULL_TVALOARE;
}


TValoare Dictionar::sterge(TCheie c){
	/* Complexitate O(nrElems) */

	node* pos = searchNode(c);
	if(pos!=NULL){
		TValoare to_return = pos->content.second;
		
		if(pos==prim && pos == last){
			prim=NULL;
			last=NULL;
		}
		else if(pos == prim){
			prim = pos->next;
			prim->last = NULL;
		}else if(pos == last){
			last = pos->last;
			last->next = NULL;
		}else{
			pos->last->next = pos->next;
			pos->next->last = pos->last;
		}

		free(pos);

		nrElems--;
		return to_return;
	}

	return NULL_TVALOARE;
}


int Dictionar::dim() const {
	/* Complexitate Theta(1) */

	return nrElems;
}

bool Dictionar::vid() const{
	/* Complexitate Theta(1) */
	if(nrElems)return false;

	return true;
}

node* Dictionar::searchNode(TCheie c) const{
	/* Complexitate O(nrElems) */
	node* aux = prim;

	while(aux != NULL){
		if(aux->content.first == c)
			break;
		
		aux = aux->next;
	}
	return aux;
}

std::vector<TValoare> Dictionar::colectiaValorilor() const{
	/* Complexitate Theta(nrElems) */
	std::vector<TValoare> to_return(nrElems);

	node* aux = prim;
	while(aux != NULL){

		to_return.push_back(aux->content.second);
		aux = aux->next;
	}

	return to_return;
}

IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}
