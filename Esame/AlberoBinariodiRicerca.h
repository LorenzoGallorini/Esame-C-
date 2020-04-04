//
//  AlberoBinariodiRicerca.h
//  Progetto Esame di Programmazione c++
//
//  Created by Lorenzo Gallorini on 23/03/2020.
//  Copyright © 2020 Lorenzo Gallorini. All rights reserved.
//  tar -cvzf Prova.tar.gz Prova
//

#ifndef AlberoBinariodiRicerca_h
#define AlberoBinariodiRicerca_h
#include <ostream>
#include <cstddef>
#include <iterator> 
/**
	@brief Eccezione custom di un elemento già inserito Error cod = -1;
*/
class Elemento_gia_inserito_exception {
public:
	int error_cod;
	Elemento_gia_inserito_exception():error_cod(-1){}
};
/**
	@brief Eccezione custom se non trovo l'elemento Error cod = -2;
*/
class Elemento_non_trovato_exception {
public:
	int error_cod;
	Elemento_non_trovato_exception():error_cod(-2){}
};
/**
	@brief Eccezione custom se non trovo l'elemento Error cod = -2;
*/
class Albero_non_inizializzato_Exception {
public:
	int error_cod;
	Albero_non_inizializzato_Exception():error_cod(-3){}
};
/**
    Questa Classe implementa un albero binario di ricerca di dati generici T.
    @brief Albero Binario di ricerca
*/
template <typename T,typename C,typename D>
class ABR{
/**
    Vado a dichiarare una struttura di supporto che rappresenterà tutti i nodi del nostro albero.
    @brief Nodo dell'albero
 */
    struct Nodo{
        T Val;   ///< Il valore del nodo
        Nodo *L; ///< Il figlio sinistro del nodo
        Nodo *R; ///< Il figlio destro del nodo
		Nodo *P; ///<Il padre del nodo
        /**
            Costruttore primario che inizializza il nodo.
            Ho deciso di utilizzare questo come costruttore primario perchè all'interno dell'albero
            non credo abbia senso ci siano dei Nodi senza valore.
            @param v  costante valore del dato
        */
        Nodo(const T &v)
            : Val(v) , L(nullptr),R(nullptr),P(nullptr) {}
		/**
			Costruttore primario che inizializza il nodo.
			Ho deciso di utilizzare questo come costruttore primario perchè all'interno dell'albero
			non credo abbia senso ci siano dei Nodi senza valore.
			@param v  costante valore del dato
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
    	Algoritmo ricorsivo di appoggio da richiamare nel distruttore per eliminare l'albero.
		L'algoritmo prende in input un nodo e ricorsivamente elimina tutti quelli sottostanti.
    	@param SubRoot di tipo puntatore a Nodo;
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
	Nodo* GetNodo(const T Value)
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
	T ValoreMinimo(Nodo *Partenza)
	{
		while (Partenza->L != nullptr)
			Partenza = Partenza->L;
		return Partenza->Val;
	}
	/**
	 *Metodo GeneraAlbero  per popolare un albero partendo da un nodo di un altro albero
	 *@param SubRoot di Tipo puntatore a Nodo
	 *@param Albero di tipo ABR
    */
	void GeneraAlbero(ABR &Albero, const Nodo *SubRoot)
	{
		Albero.Add(SubRoot->Val);
        if (SubRoot->L != nullptr)
            GeneraAlbero(Albero,SubRoot->L);
        if(SubRoot->R != nullptr)
            GeneraAlbero(Albero,SubRoot->R);
	}
	void PopolaAlbero(const Nodo *SubRoot)
	{
		Add(SubRoot->Val);
        if (SubRoot->L != nullptr)
            PopolaAlbero(SubRoot->L);
        if(SubRoot->R != nullptr)
            PopolaAlbero(SubRoot->R);
	}
public:
	
	/**
     *Costruttore di Default classe ABR (Albero Binario di Ricerca)
     *Ho deciso di scrivere il costrutture per la funzione SubTree
    */
    ABR() : _Root(nullptr) {}
    /**
     *Costruttore della classe ABR (Albero Binario di Ricerca)
     *Ho deciso di scrivere il costrutture in questa maniera obbligando il passaggio di un valore
     *Perchè l'albero deve avere almeno la radice
     *@param value di Tipo T
    */
    ABR(const T value) : _Root(new Nodo(value)) {}
	/**
		Costruttore di copia

		@param other Albero da copiare
	*/
	ABR(const ABR &other) : _Root(nullptr) { PopolaAlbero(other._Root); }
	/**
		Operatore di assegnamento
		
		@param other lista da copiare
		@return reference a this

		@throw eccezione di allocazione di memoria
	*/
	ABR &operator=(const ABR &other) {
		if(this != &other) {
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
	 **@throw Elemento_gia_inserito_exception In caso si passa un valore già presente nell'albero
     *@param Value di Tipo T
    */
    void Add(const T Value)
    {
        if(Find(Value))
			throw Elemento_gia_inserito_exception();
        Nodo *AddN = _Root;
        Nodo *Padre = _Root;
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
			if (isLeft)
				Padre->L = new Nodo(Value,Padre);
			else
				Padre->R = new Nodo(Value,Padre);
		}
		else
			_Root = new Nodo(Value);
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
	void Remove(const T Value)
	{
		if (_Root == nullptr)
			throw Albero_non_inizializzato_Exception();
		Nodo *root=_Root;
		Nodo *curr = GetNodo(Value);
		if (curr == nullptr)
			throw Elemento_non_trovato_exception();
		Nodo *parent = curr->P;
		//Caso 1: Nodo Foglia
		if (curr->L == nullptr && curr->R == nullptr)
		{
			if (curr != root)//  Se il nodo da cancellare non è la Radice allora setto parent L/R to nullptr
			{
				if (parent->L == curr)
					parent->L = nullptr;
				else
					parent->R = nullptr;
			}
			else // se l'albero ha solo la radice la cancella e la setta a null
				_Root = nullptr;
			// dealloco la memoria
			delete curr;
			curr=nullptr;
		}
		//Case 2: Il Nodo ha entrambi i figli
		else if (curr->L && curr->R)
		{
			
			Nodo *successor  = GetNodo(ValoreMinimo(curr->R));// Trova il suo nodo succesore in-order
			
			int val = successor->Val;//Salva il valore del successore
			// Ricorsivamente elimino il succesore
			// Il successore avrà al massimo un figlio (Quello destro)
			Remove(successor->Val);
			curr->Val = val;// Copia il valore del successore nel nodo corrente
		}
		//Case 3: Il Nodo ha un solo figlio
		else
		{
			Nodo* child = (curr->L)? curr->L: curr->R;//Trova il nodo figlio
			if (curr != root)// Se il nodo da cancellare non è la radice setto i figli del parent
			{
				
				if (curr == parent->L)
					parent->L = child;
				else
					parent->R = child;
				child->P=parent;
			}
			else
			{
				_Root = child;// Se il nodo da cancellare è la radice alla setto la radice con child
				_Root->P = nullptr;
			}
			delete curr; //Dealloco la memoria
		}
	}
    /**
     *Metodo Count che restituisce il numero di elementi dell'albero
     *@return di tipo int
    */
	unsigned int Count() const { return CountR(_Root); }
    /**
      *Metodo Find che ricerca se un elemento è all'interno dell'albero
      *@param Value di tipo T
	  *@return const bool
     */
    bool Find(const T Value) const
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
    */
    ABR SubTree(T Value)
	{
		if(!Find(Value))
			throw Elemento_non_trovato_exception();
		Nodo *Ricerca = _Root;
		bool found = false;
		while (Ricerca != nullptr && !found)
			if(_Minore(Value,Ricerca->Val))
				Ricerca = Ricerca->L;
			else if(!_Uguali(Value,Ricerca->Val))
				Ricerca = Ricerca->R;
			else
				found = true;
		ABR<T,C,D> newTree;
		GeneraAlbero(newTree, Ricerca); //Funzione che popola l'albero.
		return newTree;
	}
	/**
     *Metodo MinimumValue che restituisce il valore minimo dell'albero
     *@return di tipo T
	 *@throw Albero_non_inizializzato_Exception In caso viene chiamato un albero non inizializzato
    */
	T MinimumValue()
	{
		if (_Root == nullptr)
			throw Albero_non_inizializzato_Exception();
		return ValoreMinimo(_Root);
	}
	/**
		Iteratore costante dell'Albero Binario di Ricerca
		@brief Iteratore costante della lista
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
		 *Metodo costruttore
		 *@param other di tipo const const_iterator
		 */
		const_iterator(const const_iterator &other) : _n(other._n) {
		}
		/**
		*Metodo costruttore
		*@param t di tipo const ABR<T>
		*/
		const_iterator(const ABR<T,C,D>* t){
			_n= inorderFirst(t->_Root);
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
		Nodo* inorderFirst( Nodo *p ) {
			if (p!=nullptr)
				while ( p->L != nullptr )
					p = p->L;
			return p;
		}
	}; //Classe const_iterator
	/**
		Ritorna l'iteratore all'inizio della sequenza dati
		@return iteratore all'inizio della sequenza
	*/
	const_iterator begin() const {
		const_iterator app =const_iterator(this);
		return app;
	}
	/**
		Ritorna l'iteratore alla fine della sequenza dati
		@return iteratore alla fine della sequenza
	*/
	const_iterator end() const {
		return const_iterator();
	}
};
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
