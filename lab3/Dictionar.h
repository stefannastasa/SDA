#pragma once

#define NULL_TVALOARE -1
#include <bits/stdc++.h>
#include <utility>

typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

typedef std::pair<TCheie,TValoare> TElem;
typedef struct elem{
			TElem content;
			elem* next;
			elem* last; 
}node;


class Dictionar {
	friend class IteratorDictionar;

	private:
	/* aici e reprezentarea */

		node* prim;
		node* last;
		int nrElems;
		

		//Cauta nodul care contine cheia transmisa
		//Daca nu exista, returneaza NULL
		node* searchNode(TCheie c) const;

	public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	// daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	int dim() const;

	//verifica daca dictionarul e vid 
	bool vid() const;

	std::vector<TValoare> colectiaValorilor() const;

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const;


	// destructorul dictionarului	
	~Dictionar();

};


