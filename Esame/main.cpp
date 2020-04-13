//
//  main.cpp
//  Esame
//
//  Created by Lorenzo Gallorini on 23/03/2020.
//  Copyright © 2020 Lorenzo Gallorini. All rights reserved.
//
#include <iostream>
#include <cassert>
#include "AlberoBinariodiRicerca.h"

using namespace std;

bool foo(int a) {
    if(a>20)return true;else return false;
}
bool foochar(char a) {
    if(a>=90)return true;else return false;
}
struct compara_int {
	bool operator()(int a, int b) const {
		return a<b;
	}
};
		
struct uguale_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

struct compara_char {
	bool operator()(char a, char b) const {
		return a<b;
	}
};
		
struct uguale_char {
	bool operator()(char a, char b) const {
		return a==b;
	}
};

struct square {
   double _l;

   square(): _l(0) {}

   square(double l): _l(l) {}
};
struct equals_square {

   bool operator()(const square &p1, const square &p2) const{
      return (p1._l == p2._l);
   }
};
struct compare_square {

   bool operator()(const square &p1, const square &p2) const {
	   return (p1._l < p2._l);
   }
};

//stampa square
std::ostream &operator<<(std::ostream &os, const square &p) {
    os << "Quadrato di lunghezza " << p._l;
    return os;
}
bool foosquare(square a) {
    return (a._l>=5);
}
void StampaErrore(int ErrorCode)
{
	string Errore;
	switch (ErrorCode) {
		case -1:
			Errore="Elemento già inserito";
			break;
		case -2:
			Errore="Elemento non trovato";
			break;
		case -3:
			Errore="Albero non inizializzato";
			break;
		case -4:
			Errore="New Nodo Bad Alloc";
			break;
		default:
			Errore="Errore Sconosciuto";
			break;
	}
	cerr << Errore << endl;
}

typedef ABR<square,compare_square,equals_square> AlberoQuadrato;
void SquareTest()
{
	AlberoQuadrato Albero;
	square D(6);
	Albero.Add(D);
	square G(9);
	Albero.Add(G);
	square A(3);
	Albero.Add(A);
	square C(5);
	Albero.Add(C);
	square B(4);
	Albero.Add(B);
	square E(7);
	Albero.Add(E);
	square F(8);
	Albero.Add(F);
	square H(-1);
	cout << endl;
	//Di conoscere il numero totale di dati inseriti nell’albero;
	assert(Albero.Count()==7);
	cout<< Albero.Count() << endl;
	cout << endl;
	//Il controllo di esistenza un elemento T;
	assert(Albero.Find(G));
	cout << Albero.Find(G) << endl;
	assert(!Albero.Find(H));
	cout << Albero.Find(H) << endl;
	/*Di accedere ai dati presenti nell’albero tramite un iteratore a sola lettura
	e di tipo forward. L’ordine con il quale sono ritornati i dati non è
	rilevante.*/
	cout << endl;
	typename AlberoQuadrato::const_iterator i,ie;
	for(i=Albero.begin(),ie=Albero.end(); !(i==ie); ++i)
		cout<<*i<<endl;
	cout << endl;
	//Di stampare il contenuto dell'albero (anche usando operator<<)
	cout << Albero << endl;
	/*Implementare inoltre un metodo subtree che, passato un dato d dello
	stesso tipo del dato contenuto nell’albero, ritorna un nuovo albero. Il nuovo albero deve corrispondere al sottoalbero avente come radice il nodo con il valore d. Ad esempio l'esecuzione di B=A.subtree(8) potrebbe corrispondere alla situazione in figura:*/
	AlberoQuadrato SubAlbero = Albero.SubTree(C);
	cout << SubAlbero << endl;
	/*Implementare una funzione globale printIF che dato un albero binario di tipo T, e un predicato P, stampa a schermo tutti i valori contenuti nell’albero che soddisfano il predicato.*/
	PrintIF(Albero,foosquare);
}

void TestCostruttoriOperator()
{
	ABR<int,compara_int,uguale_int> T;
	ABR<int,compara_int,uguale_int> TS = T;
	T = TS;
	T.Add(20);
	T.Add(15);
	T.Add(10);
	T.Add(17);
	T.Add(30);
	T.Add(25);
	cout << T << endl;
	ABR<int,compara_int,uguale_int> TC;
	TC=T;
	ABR<int,compara_int,uguale_int> TCo(T);
	T.Remove(25);
	ABR<int,compara_int,uguale_int> TCT(4);
	
	cout << T <<endl;
	cout << TC <<endl;
	cout << TCo <<endl;
	cout << TCT <<endl;
}
void TestAddRemovePrint()
{
	ABR<int,compara_int,uguale_int> Albero;
	Albero.Add(20);
	Albero.Remove(20);
	Albero.Add(20);
    Albero.Add(15);
    Albero.Add(25);
	Albero.Remove(25);
	Albero.Add(25);
    Albero.Add(10);
    Albero.Add(18);
	Albero.Add(17);
	Albero.Add(19);
	Albero.Add(24);
	Albero.Add(26);
	cout << Albero<<endl;
	Albero.Remove(20);
    cout << Albero<<endl;
	PrintIF(Albero, foo);
    Albero.Remove(15);
    Albero.Remove(25);
    Albero.Remove(10);
    Albero.Remove(18);
	Albero.Remove(17);
	Albero.Remove(19);
	Albero.Remove(24);
	Albero.Remove(26);
	cout << Albero<<endl;
	PrintIF(Albero, foo);
}
void TestSubTreeCount()
{
	ABR<int,compara_int,uguale_int> Albero;
	Albero.Add(20);
    Albero.Add(15);
    Albero.Add(25);
    Albero.Add(10);
    Albero.Add(18);
	Albero.Add(17);
	Albero.Add(19);
	Albero.Add(24);
	Albero.Add(26);
	ABR<int,compara_int,uguale_int> SottoAlbero = Albero.SubTree(15);
	ABR<int,compara_int,uguale_int> SottoAlbero2 = Albero.SubTree(24);
	cout<<Albero.Count()<<endl;
	cout<<SottoAlbero<<endl;
	
}

void TestCasiLimite()
{
	ABR<int,compara_int,uguale_int> Albero;
	try
	{
		Albero.MinimumValue();
	}
	catch(Albero_non_inizializzato_Exception e)
	{
		StampaErrore(e.error_cod);
	}
	try
	{
		Albero.Remove(20);
	}
	catch(Albero_non_inizializzato_Exception e)
	{
		StampaErrore(e.error_cod);
	}
	Albero.Add(20);
	try
	{
		Albero.Add(20);
	}
	catch(Elemento_gia_inserito_exception e)
	{
		StampaErrore(e.error_cod);
	}
    Albero.Add(15);
    Albero.Add(25);
    Albero.Add(10);
    Albero.Add(18);
	Albero.Add(17);
	Albero.Add(19);
	Albero.Add(24);
	Albero.Add(26);
	cout << Albero.MinimumValue() << endl;
	
	try
	{
		Albero.Remove(100);
	}
	catch(Elemento_non_trovato_exception e)
	{
		StampaErrore(e.error_cod);
	}
	try
	{
		ABR<int,compara_int,uguale_int> Test = Albero.SubTree(100);
	}
	catch(Elemento_non_trovato_exception e)
	{
		StampaErrore(e.error_cod);
	}
}
// Deve essere possibile per l’utente scegliere la strategia usata per confrontare due dati T
typedef ABR<char,compara_char,uguale_char> ABRchar;

void SpecBaseTest()
{
	ABRchar Albero;
	Albero.Add('a');
	Albero.Add('b');
	Albero.Add('B');
	Albero.Add('A');
	Albero.Add('C');
	Albero.Add('p');
	Albero.Add('d');
	cout << endl;
	//Di conoscere il numero totale di dati inseriti nell’albero;
	assert(Albero.Count()==7);
	cout<< Albero.Count() << endl;
	cout << endl;
	//Il controllo di esistenza un elemento T;
	assert(Albero.Find('a'));
	cout << Albero.Find('a') << endl;
	assert(!Albero.Find('q'));
	cout << Albero.Find('q') << endl;
	/*Di accedere ai dati presenti nell’albero tramite un iteratore a sola lettura
	e di tipo forward. L’ordine con il quale sono ritornati i dati non è
	rilevante.*/
	cout << endl;
	typename ABRchar::const_iterator i,ie;
	for(i=Albero.begin(),ie=Albero.end(); !(i==ie); ++i)
		cout<<*i<<endl;
	cout << endl;
	//Di stampare il contenuto dell'albero (anche usando operator<<)
	cout << Albero << endl;
	/*Implementare inoltre un metodo subtree che, passato un dato d dello
	stesso tipo del dato contenuto nell’albero, ritorna un nuovo albero. Il nuovo albero deve corrispondere al sottoalbero avente come radice il nodo con il valore d. Ad esempio l'esecuzione di B=A.subtree(8) potrebbe corrispondere alla situazione in figura:*/
	ABRchar SubAlbero = Albero.SubTree('B');
	cout << SubAlbero << endl;
	/*Implementare una funzione globale printIF che dato un albero binario di tipo T, e un predicato P, stampa a schermo tutti i valori contenuti nell’albero che soddisfano il predicato.*/
	PrintIF(Albero,foochar);
}

int main(int argc, const char * argv[]) {

	#pragma region CodeBaseTesting
	
	TestCostruttoriOperator();
	
	TestAddRemovePrint();
	
	TestSubTreeCount();
	
	TestCasiLimite();
	//Questo insieme di casi di test raggiunge il 100% di  statement coverage
	#pragma endregion CodeBaseTesting
    
	#pragma region SpecBaseTesting
	
	SpecBaseTest();
	
	#pragma endregion SpecBaseTesting
	
	#pragma region ClasseCustomTest
	
	SquareTest();
	
	#pragma endregion ClasseCustomTest
	return 0;
}
