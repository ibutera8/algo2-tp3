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
    map<Persona, map<Producto, minHeap(IdPuesto)>> _puestosHackeables;
    priority_queue<Persona> _rankingGastosPersonas;
    map<Persona, Nat> _posicionEnCola;
};

#include "Lollapatuza.cpp"

#endif //TP_LOLLA_LOLLAPATUZA_H
