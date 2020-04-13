//
//  AlberoBinariodiRicerca.h
//  Progetto Esame di Programmazione c++
//
//  Created by Lorenzo Gallorini on 23/03/2020.
//  Copyright © 2020 Lorenzo Gallorini. All rights reserved.
//

#ifndef AlberoBinariodiRicerca_h
#define AlberoBinariodiRicerca_h
#include <ostream>
#include <cstddef>
#include <iterator>


/**
	*@brief Eccezione custom di un elemento già inserito Error cod = -1;
*/
class Elemento_gia_inserito_exception {
public:
	int error_cod;
	Elemento_gia_inserito_exception():error_cod(-1){}
};
/**
	*@brief Eccezione custom se non trovo l'elemento Error cod = -2;
*/
class Elemento_non_trovato_exception {
public:
	int error_cod;
	Elemento_non_trovato_exception():error_cod(-2){}
};
/**
	*@brief Eccezione custom se non trovo l'elemento Error cod = -2;
*/
class Albero_non_inizializzato_Exception {
public:
	int error_cod;
	Albero_non_inizializzato_Exception():error_cod(-3){}
};
/**
	*@brief Eccezione custom di un elemento non inserito adeguatamente
*/
class New_Nodo_Bad_Alloc_Exception {
public:
	int error_cod;
	New_Nodo_Bad_Alloc_Exception():error_cod(-4){}
};
/**
    *Questa Classe implementa un albero binario di ricerca di dati generici T.
    *@brief Albero Binario di ricerca
	*@param T tipo del dato
	*@param C funtore di comparazione (<) di due dati
	*@param D funtore di comparazione (==) di due dati
*/
template <typename T,typename C,typename D>
class ABR{
	/**
    	*Vado a dichiarare una struttura di supporto che rappresenterà tutti i nodi del nostro albero.
   		*@brief Nodo dell'albero
 	*/
    struct Nodo{
        T Val;   ///< Il valore del nodo
        Nodo *L; ///< Il figlio sinistro del nodo
        Nodo *R; ///< Il figlio destro del nodo
		Nodo *P; ///<Il padre del nodo
		/**
            *Costruttore di default      
         */ 
        Nodo(): R(nullptr),L(nullptr),P(nullptr){}
        /**
            *Costruttore primario che inizializza il nodo.
            *Ho deciso di utilizzare questo come costruttore primario perchè all'interno dell'albero
            *non credo abbia senso ci siano dei Nodi senza valore.
            *@param v  costante valore del dato
        */
        Nodo(const T &v)
            : Val(v) , L(nullptr),R(nullptr),P(nullptr) {}
		/**
			*Costruttore primario che inizializza il nodo.
			*Ho deciso di utilizzare questo come costruttore primario perchè all'interno dell'albero
			*non credo abbia senso ci siano dei Nodi senza valore.
			*@param v  costante valore del dato
		*/
		Nodo(const T &v,Nodo *Pa)
			: Val(v) , L(nullptr),R(nullptr),P(Pa) {}
        /**
			Distruttore
        */
        ~Nodo() {
            L = nullptr;
            R = nullptr;
			P = nullptr;
        }
    }; // struct Nodo
    Nodo *_Root;
	C _Minore;
	D _Uguali;
    /**
    	*Algoritmo ricorsivo di appoggio da richiamare nel distruttore per eliminare l'albero.
		*L'algoritmo prende in input un nodo e ricorsivamente elimina tutti quelli sottostanti.
    	*@param SubRoot di tipo puntatore a Nodo;
    */
    void DeleteAlberoR(Nodo *SubRoot)
    {
        if (SubRoot!=nullptr)
		{
			if (SubRoot->L != nullptr)
				DeleteAlberoR(SubRoot->L);
			if (SubRoot->R != nullptr)
				DeleteAlberoR(SubRoot->R);
			delete SubRoot;
			SubRoot=nullptr;
		}
    }
	/**
		Algoritmo ricorsivo di appoggio da richiamare nel metodo Count per contare gli elementi dell'albero.
		Ho deciso di implentarlo così per poter avere sempre il numero di elementi senza tenere una variabile di appoggio.
		@param SubRoot di tipo puntatore a Nodo;
		@return un intero positivo
    */
    unsigned int CountR(const Nodo *SubRoot) const
    {
		int ris=0;
        if (SubRoot->L != nullptr)
            ris+=CountR(SubRoot->L);
        if(SubRoot->R != nullptr)
            ris+=CountR(SubRoot->R);
		return ++ris; 
    }
	/**
		Metodo GetNodo  per trovare un elemento dell'albero
		@param Value di Tipo T
		@return il nodo corrispondente al valore
    */
	Nodo* GetNodo(const T &Value)
	{
		Nodo *Ricerca = _Root;
		while (Ricerca != nullptr)
			if(_Minore(Value,Ricerca->Val))
				Ricerca = Ricerca->L;
			else if(!_Uguali(Value,Ricerca->Val))
				Ricerca = Ricerca->R;
			else
				return Ricerca;
		return Ricerca;
	}
	/**
	 *Metodo ValoreMinimo  per trovare l'elemento dell'albero più a sinistra
	 *@param Partenza di Tipo puntatore a Nodo
	 *@return T ritorna il valore minimo dell'albero sottostante a partenza
    */
	T ValoreMinimo(Nodo *Partenza) const
	{
		while (Partenza->L != nullptr)
			Partenza = Partenza->L;
		return Partenza->Val;
	}
	/**
	 * metodo che popola l'albero ricorsivamente
	 * @param SubRoot di tipo puntatore a nodo
	 */
	void PopolaAlberoR(const Nodo *SubRoot)
	{
		if (SubRoot != nullptr) {
			Add(SubRoot->Val);
			if (SubRoot->L != nullptr)
				PopolaAlberoR(SubRoot->L);
			if(SubRoot->R != nullptr)
				PopolaAlberoR(SubRoot->R);
		}
	}
public:
	
	/**
     *Costruttore di Default classe ABR (Albero Binario di Ricerca)
    */
    ABR() : _Root(nullptr) {}
    /**
     *Costruttore della classe ABR (Albero Binario di Ricerca)
     *@param value di Tipo T
	 *@throw New_Nodo_Bad_Alloc_Exception In caso si verifichi un errore in fase di creazione di un nodo
    */
	ABR(const T &value){
		try
		{
			_Root = new Nodo(value);
		}
		catch(...)
		{
			_Root = nullptr;
			throw New_Nodo_Bad_Alloc_Exception();
		}
	}
	/**
		*Costruttore di copia
		*@param other Albero da copiare
	 	*@throw New_Nodo_Bad_Alloc_Exception
	*/
	ABR(const ABR& other) : _Root(nullptr) {
		try
		{
			PopolaAlberoR(other._Root);
		}
		catch(...)
		{
			DeleteAlberoR(_Root);
			throw New_Nodo_Bad_Alloc_Exception(); //lancio ancora throw
		}
	}
	/**
		Operatore di assegnamento
		@param other lista da copiare
		@return puntatore a this
		@throw eccezione di allocazione di memoria
	*/
	ABR &operator=(const ABR &other) {
		if( this != &other) {
			ABR tmp(other);
				std::swap(_Root,tmp._Root);
		}
		return *this;
	}
    /**
	*Distruttore della classe ABR
    */
    ~ABR() {
		DeleteAlberoR(_Root);
		_Root = nullptr;
	}
    /**
     *Metodo Add per aggiungere un elemento all'albero
	 *Nel caso l'albero sia vuoto imposta la radica con quel nodo
	 *@throw Elemento_gia_inserito_exception In caso si passa un valore già presente nell'albero
	 *@throw New_Nodo_Bad_Alloc_Exception In caso si verifichi un errore in fase di creazione di un nodo
     *@param Value di Tipo T
    */
    void Add(const T &Value)
    {
        if(Find(Value))
			throw Elemento_gia_inserito_exception();
        Nodo *AddN = _Root;
        Nodo *Padre = _Root;
		Nodo *Nuovo ;
		try{
			 Nuovo = new Nodo(Value);
		}
		catch(...)
		{
			Nuovo = nullptr;
			throw New_Nodo_Bad_Alloc_Exception();
		}
		bool isLeft=true;
		if (Padre != nullptr)
		{
			while (AddN != nullptr)
			{
				if(_Minore(Value,AddN->Val))
				{
					Padre=AddN;
					isLeft=true;
					AddN = AddN->L;
				}
				else
				{
					Padre=AddN;
					isLeft=false;
					AddN = AddN->R;
				}
			}
			Nuovo->P = Padre;
			if (isLeft)
				Padre->L = Nuovo;
			else
				Padre->R = Nuovo;
		}
		else
			_Root = Nuovo;
    }
    /**
     *Metodo Remove per rimuovere un elemento all'albero.
	 *Ho suddiviso l'algoritmo in tre casi diffenti:
	 *Caso 1: Nodo Foglia.
	 *Caso 2: Il Nodo ha entrambi i figli.
	 *Caso 3: Il Nodo ha un solo figlio.
     *@param Value di Tipo T
	 *@throw Albero_non_inizializzato_Exception In caso viene chiamato un albero non inizializzato
	 *@throw Elemento_non_trovato_exception In caso si passa un valore non presente nell'albero
    */
	void Remove(const T &Value)
	{
		if (_Root == nullptr)
			throw Albero_non_inizializzato_Exception();
		Nodo *Root=_Root;
		Nodo *Current = GetNodo(Value);
		if (Current == nullptr)
			throw Elemento_non_trovato_exception();
		Nodo *Padre = Current->P;
		//Caso 1: Nodo Foglia
		if (Current->L == nullptr && Current->R == nullptr)
		{
			if (Current != Root)//  Se il nodo da cancellare non è la Radice allora setto parent L/R to nullptr
			{
				if (Padre->L == Current)
					Padre->L = nullptr;
				else
					Padre->R = nullptr;
			}
			else // se l'albero ha solo la radice la cancella e la setta a null
				_Root = nullptr;
			// dealloco la memoria
			delete Current;
			Current=nullptr;
		}
		//Case 2: Il Nodo ha entrambi i figli
		else if (Current->L && Current->R)
		{
			Nodo *Successore  = GetNodo(ValoreMinimo(Current->R));// Trova il suo nodo succesore in-order
			int val = Successore->Val;//Salva il valore del successore
			// Ricorsivamente elimino il succesore
			// Il successore avrà al massimo un figlio (Quello destro)
			Remove(Successore->Val);
			Current->Val = val;// Copia il valore del successore nel nodo corrente
		}
		//Case 3: Il Nodo ha un solo figlio
		else
		{
			Nodo* Figlio = (Current->L)? Current->L: Current->R;//Trova il nodo figlio
			if (Current != Root)// Se il nodo da cancellare non è la radice setto i figli del parent
			{
				if (Current == Padre->L)
					Padre->L = Figlio;
				else
					Padre->R = Figlio;
				Figlio->P=Padre;
			}
			else
			{
				_Root = Figlio;// Se il nodo da cancellare è la radice alla setto la radice con child
				_Root->P = nullptr;
			}
			delete Current; //Dealloco la memoria
		}
	}
    /**
     *Metodo Count che restituisce il numero di elementi dell'albero
     *@return intero positivo
    */
	unsigned int Count() const { return CountR(_Root); }
    /**
      *Metodo Find che ricerca se un elemento è all'interno dell'albero
      *@param Value di tipo T
	  *@return const bool
     */
    bool Find(const T &Value) const
    {
		Nodo *Ricerca = _Root;
		while (Ricerca != nullptr)
			if(_Minore(Value,Ricerca->Val))
				Ricerca = Ricerca->L;
			else if(!_Uguali(Value,Ricerca->Val))
				Ricerca = Ricerca->R;
			else
				return true;
		return false;
    }
    /**
     *Metodo SubTree che restituisce il sottoalbero con Root il nodo corrispondente al valore dato in input
     *@param Value di tipo T
     *@return di tipo puntatore ABR
	 *@throw Elemento_non_trovato_exception In caso si passa un valore non presente nell'albero
	 *@throw New_Nodo_Bad_Alloc_Exception in caso non si riesca ad allocare un nodo
    */
    ABR SubTree(const T &Value)
	{
		if(!Find(Value))
			throw Elemento_non_trovato_exception();
		Nodo *Ricerca = GetNodo(Value);
		ABR<T,C,D> newTree;
		try{
		newTree.PopolaAlberoR(Ricerca); //Funzione che popola l'albero.
		}
		catch(...)
		{
			newTree.DeleteAlberoR(newTree._Root);
			throw New_Nodo_Bad_Alloc_Exception();
		}
		return newTree;
	}
	/**
     *Metodo MinimumValue che restituisce il valore minimo dell'albero
     *@return di tipo T
	 *@throw Albero_non_inizializzato_Exception In caso viene chiamato un albero non inizializzato
    */
	T MinimumValue() const
	{
		if (_Root == nullptr)
			throw Albero_non_inizializzato_Exception();
		return ValoreMinimo(_Root);
	}
	/**
		Iteratore costante dell'Albero Binario di Ricerca
		@brief Iteratore costante dell'albero
	*/
	class const_iterator {
		const Nodo *_n;
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;
		/**
		 *Metodo costrutture di default
		 */
		const_iterator() : _n(nullptr) {}
		/**
		 *Metodo costruttore di copia
		 *@param other di tipo const const_iterator
		 */
		const_iterator(const const_iterator &other) : _n(other._n) {
		}
		/**
		*Metodo costruttore
		*@param t di tipo const ABR<T>
		*/
		const_iterator(const ABR<T,C,D>* t){
			_n= AllLeft(t->_Root);
		}
		/**
		 **Ridefinizione dell'operatore =
		 *@param other tipo const const_iterator
		*/
		const_iterator& operator=(const const_iterator &other) {
			_n = other._n;
			return *this;
		}
		/**
		 *Metodo distruttore
		 */
		~const_iterator() {
		}
		/**
		 **Ridefinizione dell'operatore * per deferenziare il puntatore
		*/
		reference operator*() const {
			return _n->Val; //Dereferenziamento
		}
		/**
		 *Ridefinizione dell'operatore -> per deferenziare il puntatore
		*/
		pointer operator->() const {
			return &(_n->Val); 		//Ritorna il puntatore al dato riferito dall'iteratore
		}
		/**
		 *Ridefinizione dell'operatore di iterazione post-incremento
		 */
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			
			if(_n->R != nullptr) {
				_n = _n->R;
				while (_n->L != nullptr)
					_n = _n->L;
				return tmp;
			}
			while(true) {
				if(_n->P == nullptr) {
					_n = nullptr;
					return tmp;
				}
				if(_n->P->L == _n) {
					_n = _n->P;
				   return tmp;
				}
				_n = _n->P;
			}
			
			return tmp;
		}
		/**
		*Ridefinizione dell'operatore di iterazione pre-incremento
		*/
		const_iterator& operator++() {
			
			if(_n->R != nullptr) {// se posso andare a destra vado a destra poi vado tutto a sinistra
				_n = _n->R;
				while (_n->L != nullptr)
					_n = _n->L;
				return *this;
			}
			while(true) {
				if(_n->P == nullptr) {// se sono arrivato alla radice restituisco nullptr
					_n = nullptr;
					return *this;
				}
				if(_n->P->L == _n) {// torno su finche non torno da dove sono arrivato
					_n = _n->P;
				   return *this;
				}
				_n = _n->P;//torno su fino a dove sono arrivato
			}
			return *this;
		}

		/**
		 *Ridefinizione dell'operatore di  uguaglianza ==
		*/
		bool operator==(const const_iterator &other) const {
			return (_n == other._n);
		}
		/**
		 *Ridefinizione dell'operatore di  disuguaglianza !=
		*/
		bool operator!=(const const_iterator &other) const {
			return (_n != other._n);
		}
	private:
		friend class ABR<T,C,D>;
		/**
		 *funzione di appoggio che trova il nodo più piccolo.
		 *@param p di tipo puntatore a nodo.
		 *@return puntatore a nodo.
		 */
		Nodo* AllLeft( Nodo *p ) {
			if (p!=nullptr)
				while ( p->L != nullptr )
					p = p->L;
			return p;
		}
	}; //Classe const_iterator
	/**
		Ritorna l'iteratore con nodo più a sinistra dell'albero
		@return iteratore
	*/
	const_iterator begin() const {
		return const_iterator(this);
	}
	/**
		Ritorna l'iteratore alla fine della sequenza dati
		@return iteratore alla fine della sequenza
	*/
	const_iterator end() const {
		return const_iterator();
	}
}; ///class ABR
/**
 *Funzione che stampa gli alberi che soddisfano un determinato predicato
 *@param Albero di tipo albero binario
 *@param P predicato
 */
template <typename T,typename C,typename D, typename Predicato>
void PrintIF(const ABR<T,C,D> &Albero,Predicato P)
{
    typename ABR<T,C,D>::const_iterator i,ie;
	for(i=Albero.begin(),ie=Albero.end(); (i!=ie); i++)
		if(P(*i))
			std::cout<<*i<<std::endl;
}
/**
 *Ridefinisco l'operatore cout per accetare in ingresso un albero ABR
 *e stampare il contenuto
 *@return lo stream
*/
template <typename T, typename C, typename D>
std::ostream& operator<<(
	std::ostream &os,
	const ABR<T,C,D> &r) {
	typename ABR<T,C,D>::const_iterator i,ie;
	for(i=r.begin(),ie=r.end(); !(i==ie); ++i)
		os<<*i<<std::endl;
	return os;
}
#endif /* AlberoBinariodiRicerca_h */
