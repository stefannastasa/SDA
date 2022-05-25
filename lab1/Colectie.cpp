#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>
#include <utility>
#include <assert.h>
using namespace std;

Colectie::Colectie()
{
	/*Complexitate Theta(1)*/
	mini = NULL_TELEM;
	maxi = NULL_TELEM;
	nrElem = 0;
	e = NULL;
}

void Colectie::adauga(TElem elem)
{
	/* Complexitate Theta(abs(elem - max(mini,maxi) ) + abs(elem - min(mini,maxi) + 2 ) ) */
	if (vida() == true)
	{
		mini = elem;
		maxi = elem;
		e = (TElem *)calloc(1, sizeof(TElem));
		
	}
	else
	{
		if (elem < mini)
		{
			resize(elem, maxi);
		}
		else if (elem > maxi)
		{
			resize(mini, elem);
		}
		
	}
	++e[getPos(elem)];
	++nrElem;
	
	
}
void Colectie::resize(TElem minim, TElem maxim)
{
	/* Complexitate Theta( abs(maxim-minim) + 1)*/
	TElem old_mini = mini;
	TElem old_maxi = maxi;
	mini = minim;
	maxi = maxim;

	int n_new = nrElemente();
	
	TElem *e_old = e;
	TElem *e_new = (TElem *)calloc(n_new, sizeof(TElem));
	int i = old_mini;
	
	while (i <= old_maxi)
	{
		e_new[getPos(i)] = e_old[i - old_mini];
		++i;
	}
	
	free(e_old);
	e = e_new;
}
unsigned int Colectie::getPos(TElem elem) const
{
	/*Complexitate Theta(1)*/
	return abs(elem - mini);
}

bool Colectie::sterge(TElem elem)
{
	/* Complexitate Theta(1) */
	if(vida())return false;
	if(!(mini <= elem && elem<=maxi))return false;
	bool ok = false;
	if(e[getPos(elem)]>=1){
		--e[getPos(elem)];
		--nrElem;
		ok = true;
	}
	return ok;
}

bool Colectie::cauta(TElem elem) const
{
	/* Complexitate Theta(1) */
	if(vida())return false;
	if (mini <= elem && elem <= maxi)
	{
		return e[getPos(elem)]!=0;
	}

	return false;
}

int Colectie::nrAparitii(TElem elem) const
{
	/* Complexitate Theta(1) */
	if(vida())return false;
	if (mini <= elem && elem <= maxi)
	{	
		return e[getPos(elem)];
	}
	else
	{
		return 0;
	}
}

int Colectie::nrElemente() const
{
	/* Complexitate Theta(1) */
	if (vida() == true)
		return 0;

	return abs(maxi - mini) + 1;
}

int Colectie::dim() const{
	/* Complexitate Theta(1) */
	return nrElem;
}

bool Colectie::vida() const
{
	/* Complexitate Theta(1) */
	if (mini == NULL_TELEM && maxi == NULL_TELEM)
		return true;
	return false;
}

IteratorColectie Colectie::iterator() const
{
	return IteratorColectie(*this);
}

Colectie::~Colectie()
{
	/* Complexitate Theta(1) */
	if(e!=NULL)
		free(e);
}
