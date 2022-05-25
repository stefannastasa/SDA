#pragma once


#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;
typedef unsigned long long ull;
class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie,TValoare> TElem;
#include "list.h"

typedef bool (*Conditie)(TCheie);



class Dictionar {
	friend class IteratorDictionar;

	private:
	/* aici e reprezentarea */
		
		list<TElem>** V;// list of all the pairs, with collisions
		
		ull size;
		ull nrElems;
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

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const ;
	
	//Filtreaza dictionarul dupa conditia transmisa
	//Preconditii: dict, Conditie cond
	/*
		Complexitate Theta(max(size, nrElems))
		SubAlgoritm filtrare(dictionar dict, Conditie cond)

			i <- 0
			pentru i = 0, i < dict.size, i <- i+1
			executa
				Daca dict.V[i].size() > 0 atunci
					pos <= dict.V[i].iterator() 
					cat timp pos.valid() == Adevarat executa
						Daca cond(pos.element().cheie) atunci
							pos.stergeElem()
							dict.nrElems <- dict.nrElems - 1
						Altfel
							pos.urmator()
						SfDaca
					SfCatTimp
				SfDaca
			SfPentru
		SfSubAlgoritm	
	*/
	//Postconditii: dict' <- dictionarul filtrat
	void filtreaza(Conditie cond);

	// destructorul dictionarului	
	~Dictionar();

};


