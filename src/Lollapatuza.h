#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H


#include "PuestosDeComida.h"
#include "heap.h"
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
    map<Persona, map<Producto, PriorityQueue<IdPuesto>>> _puestosHackeables; //veamos como hacer el minHeap => -1 vs comparator

    //me da una cola de prioridad con la operacion borrar cualquier elemento de la cola
    class colaRankingPersonas : public PriorityQueue<std::pair<Nat, Persona>, std::vector<std::pair<Nat, Persona>>, TupleComparator> {
    public:
        bool remove(const std::pair<Nat, Persona>& value) {
            auto it = std::find(begin(), end(), value);

            if (it == end()) {
                return false;
            }
            if (it == begin()) {
                // Sacamos el último
                pop();
            } else {
                // Removemos el elemento y reconstruimos el heap
                erase(it);
            }
            return true;
        }
    };
    colaRankingPersonas _rankingGastosPersonas;

};

//#include "Lollapatuza.cpp"

#endif //TP_LOLLA_LOLLAPATUZA_H
