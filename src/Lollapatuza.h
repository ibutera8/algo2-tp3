#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H

#include "tipos.h"
#include <map>

using namespace std;

template<typename T>
class lollapatuza {

public:
    lollapatuza(Puestos p , Personas a);
    ~lollapatuza();
    void registrarCompra(Persona a, Producto p, IdPuesto id, Nat cant);
    void hackear(Persona a, Producto p);
    Nat gastoTotalPersona(Persona a);
    Persona personaQueMasGasto();
    IdPuesto puestoMenorStock(Producto i);
    set<Persona> personas();
    Puestos puestos();

private:

    Puestos _puestos;  //map<int, puesto>
    set<IdPuesto> _conjPuestos;
    Personas _personas; //conj(int)
    map<Persona, Nat> _historialCompras;
    map<Persona, map<Producto, colaPrior<IdPuesto>>> _puestosHackeables; //veamos como hacer el minHeap => -1 vs comparator
    colaPrior<Persona> _rankingGastosPersonas; //la creamos con ranking
    //map<Persona, Nat> _posicionEnCola;

    // para comparar dos personas
    class ranking {
        public:
            int operator() (const Persona& a1, const Persona& a2)
            {
                return this->gastoTotalPersona(a1) > this->gastoTotalPersona(a2);
            }
    };
};

#include "Lollapatuza.cpp"

#endif //TP_LOLLA_LOLLAPATUZA_H
