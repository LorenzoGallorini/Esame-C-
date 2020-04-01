//
//  main.cpp
//  Esame
//
//  Created by Lorenzo Gallorini on 23/03/2020.
//  Copyright © 2020 Lorenzo Gallorini. All rights reserved.
//

#include <iostream>
#include "AlberoBinariodiRicerca.h"

using namespace std;

bool foo(int a) {
    if(a>20)return true;else return false;
}

struct compare_int {
	bool operator()(int a, int b) const {
		return a<b;
	}
};
		
struct equal_int {
			bool operator()(int a, int b) const {
				return a==b;
			}
		};
		

void TestAddRemovePrint()
{
	ABR<int,compare_int,equal_int> Albero;
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
	std::cout << Albero<<std::endl;
	Albero.Remove(20);
    std::cout << Albero<<std::endl;
	PrintIF(Albero, foo);
    Albero.Remove(15);
    Albero.Remove(25);
    Albero.Remove(10);
    Albero.Remove(18);
	Albero.Remove(17);
	Albero.Remove(19);
	Albero.Remove(24);
	Albero.Remove(26);
	std::cout << Albero<<std::endl;
	PrintIF(Albero, foo);
}
void TestSubTreeCount()
{
	ABR<int,compare_int,equal_int> Albero;
	Albero.Add(20);
    Albero.Add(15);
    Albero.Add(25);
    Albero.Add(10);
    Albero.Add(18);
	Albero.Add(17);
	Albero.Add(19);
	Albero.Add(24);
	Albero.Add(26);
	ABR<int,compare_int,equal_int> SottoAlbero = Albero.SubTree(15);
	ABR<int,compare_int,equal_int> SottoAlbero2 = Albero.SubTree(24);
	std::cout<<Albero.Count()<<std::endl;
	std::cout<<SottoAlbero<<std::endl;
	
}

void TestCasiLimite()
{
	ABR<int,compare_int,equal_int> Albero;
	try{
		Albero.MinimumValue();
	}
	catch(Albero_non_inizializzato_Exception e)
	{
		std::cout << e.error_cod <<std::endl;
	}
	try{
		Albero.Remove(20);
	}
	catch(Albero_non_inizializzato_Exception e)
	{
		std::cout << e.error_cod <<std::endl;
	}
	Albero.Add(20);
	try{
		Albero.Add(20);
	}
	catch(Elemento_gia_inserito_exception e)
	{
		std::cout << e.error_cod <<std::endl;
	}
    Albero.Add(15);
    Albero.Add(25);
    Albero.Add(10);
    Albero.Add(18);
	Albero.Add(17);
	Albero.Add(19);
	Albero.Add(24);
	Albero.Add(26);
	Albero.MinimumValue();
	
	try{
		Albero.Remove(100);
	}
	catch(Elemento_non_trovato_exception e)
	{
		std::cout << e.error_cod <<std::endl;
	}
	try{
		ABR<int,compare_int,equal_int> Test = Albero.SubTree(100);
	}
	catch(Elemento_non_trovato_exception e)
	{
		std::cout << e.error_cod <<std::endl;
	}
}
int main(int argc, const char * argv[]) {

	#pragma region CodeBaseTesting
	
	ABR<int,compare_int,equal_int> T;
	T.Add(20);
	T.Add(15);
	T.Add(25);
	T.Add(10);
	T.Add(17);
	T.Add(30);
	ABR<int,compare_int,equal_int> TC;
	TC=T;
	ABR<int,compare_int,equal_int> TCo(T);
	T.Remove(25);
	
	std::cout << T <<std::endl;
	std::cout << TC <<std::endl;
	std::cout << TCo <<std::endl;

	TestAddRemovePrint();
	
	TestSubTreeCount();
	
	TestCasiLimite();
	
	#pragma endregion CodeBaseTesting
	#pragma region SpecBaseTesting
	
	#pragma endregion SpecBaseTesting
    
	return 0;
}
