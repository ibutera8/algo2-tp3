#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H


#include "PuestosDeComida.h"
#include <set>

using namespace std;

class lollapatuza {

public:
    lollapatuza();
    lollapatuza(Puestos p , Personas a);
    ~lollapatuza();
    void registrarCompraLolla(Persona a, Producto p, IdPuesto id, Nat cant);
    void hackearLolla(Persona a, Producto p);
    void actualizarHackeabilidadLolla(Persona a, Producto p, IdPuesto id);
    void actualizarRankingLolla(Persona a, int gastoViejo);
    Nat gastoTotalPersonaLolla(Persona a) const;
    Nat stockEnPuestoLolla(IdPuesto idPuesto, const Producto &producto) const;
    Nat descuentoEnPuestoLolla(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const;
    Nat gastoEnPuestoLolla(IdPuesto idPuesto, Persona persona) const;
    Persona personaQueMasGastoLolla() const;
    IdPuesto puestoMenorStockLolla(Producto i) const;
    const set<Persona> & personasLolla() const;
    set<IdPuesto> puestosLolla() const;

private:
    map<int , puestosDeComida> _puestos;  //map<int, puesto>
    set<IdPuesto> _conjPuestos;
    Personas _personas; //conj(int)
    map<Persona, Nat> _historialCompras;
    map<Persona, map<Producto, priority_queue<IdPuesto>>> _puestosHackeables; //veamos como hacer el minHeap => -1 vs comparator

    //me da una cola de prioridad con la operacion borrar cualquier elemento de la cola
    class colaRankingPersonas : public priority_queue<pair<Nat, Persona>> {
    public:
        bool remove(const pair<Nat, Persona>& value) {
            auto it = find(this->c.begin(), this->c.end(), value);

            if (it == this->c.end()) {
                return false;
            }
            if (it == this->c.begin()) {
                // sacamos el ultimo
                this->pop();
            }
            else {
                // removemos y volvemos a armar el heap
                this->c.erase(it);
                make_heap(this->c.begin(), this->c.end(), this->comp);
            }
            return true;
        }
    };

    colaRankingPersonas _rankingGastosPersonas;
};

//#include "Lollapatuza.cpp"

#endif //TP_LOLLA_LOLLAPATUZA_H
