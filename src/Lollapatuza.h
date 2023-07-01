#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H

//#include "tipos.h"
#include "PuestosDeComida.cpp"
#include <map>

using namespace std;

class lollapatuza {

public:
    lollapatuza();
    lollapatuza(Puestos p , Personas a);
    ~lollapatuza();
    void registrarCompra(Persona a, Producto p, IdPuesto id, Nat cant);
    void hackear(Persona a, Producto p);
    void actualizarHackeabilidad(Persona a, Producto p, IdPuesto id);
    void actualizarRanking(Persona a);
    Nat gastoTotalPersona(Persona a) const;
    Nat stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const;
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const;
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona) const;
    Persona personaQueMasGasto() const;
    IdPuesto puestoMenorStock(Producto i) const;
    const set<Persona> & personas() const;
    set<IdPuesto> puestos() const;

private:
    map<int , puestosDeComida> _puestos;  //map<int, puesto>
    set<IdPuesto> _conjPuestos;
    Personas _personas; //conj(int)
    map<Persona, Nat> _historialCompras;
    map<Persona, map<Producto, priority_queue<IdPuesto>>> _puestosHackeables; //veamos como hacer el minHeap => -1 vs comparator

    /* para comparar dos personas
    template<typename T>
    class ranking {
        public:
            bool operator() (const Persona& a1, const Persona& a2){
                if (l.gastoTotalPersona(a1) > l.gastoTotalPersona(a2)) {
                    return true;
                } else if (l.gastoTotalPersona(a1) == l.gastoTotalPersona(a2)) {
                    return a1 > a2;
                } else {
                    return false;
                }
            };
        private:
            lollapatuza l; // Según busqué, este error es por la "declaración anticipada" de lollapatuza.
                           // Como solución habría que mover toda esta clase fuera de la clase lollapatuza
    };*/
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
