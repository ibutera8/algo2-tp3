#include <list>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include "tipos.h"
#include "Lollapatuza.h"

template<typename T>
lollapatuza<T>::lollapatuza(Puestos p , Personas a) : _puestos(p), _personas(a) {}

template<typename T>
lollapatuza<T>::~lollapatuza(){}

template<typename T>
void lollapatuza<T>::registrarCompra(Persona a, Producto p, IdPuesto id, Nat cant){}

template<typename T>
void lollapatuza<T>::hackear(Persona a, Producto p){}

template<typename T>
Nat lollapatuza<T>::gastoTotalPersona(Persona a){}

template<typename T>
Persona lollapatuza<T>::personaQueMasGasto(){
    return this->_rankingGastosPersonas.top();
}

template<typename T>
IdPuesto lollapatuza<T>::puestoMenorStock(Producto i){}

template<typename T>
set<Persona> lollapatuza<T>::personas(){
    return this->_personas;
}

template<typename T>
Puestos lollapatuza<T>::puestos(){
    return this->_puestos;
}












