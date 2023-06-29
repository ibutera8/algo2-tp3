#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H

//#include "tipos.h"
#include "PuestosDeComida.cpp"
#include <map>

using namespace std;

template<typename T>
class lollapatuza {

public:
    lollapatuza(Puestos p , Personas a);
    ~lollapatuza();
    void registrarCompra(Persona a, Producto p, IdPuesto id, Nat cant);
    void hackear(Persona a, Producto p);
    void actualizarHackeabilidad(Persona a, Producto p, IdPuesto id);
    void actualizarRanking(Persona a);
    Nat gastoTotalPersona(Persona a);
    Nat stockEnPuesto(IdPuesto idPuesto, const Producto &producto);
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad);
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona);
    Persona personaQueMasGasto() const;
    IdPuesto puestoMenorStock(Producto i);
    set<Persona> personas();
    set<IdPuesto> puestos();

private:
    Puestos _puestos;  //map<int, puesto>
    set<IdPuesto> _conjPuestos;
    Personas _personas; //conj(int)
    map<Persona, Nat> _historialCompras;
    map<Persona, map<Producto, priority_queue<IdPuesto>>> _puestosHackeables; //veamos como hacer el minHeap => -1 vs comparator

    // para comparar dos personas
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
            lollapatuza<T> l;
    };
    //me da una cola de prioridad con la operacion borrar cualquier elemento de la cola
    class colaRankingPersonas : public priority_queue<Persona , vector<Persona>, ranking> {
    public:
        bool remove(const T& value) {
            auto it = find(this->c.begin(), this->c.end(), value);

            if (it == this->c.end()) {
                return false;
            }
            if (it == this->c.begin()) {
                // deque the top element
                this->pop();
            }
            else {
                // remove element and re-heap
                this->c.erase(it);
                make_heap(this->c.begin(), this->c.end(), this->comp);
            }
            return true;
        }
    };

    colaRankingPersonas _rankingGastosPersonas; //la creamos con ranking
    //map<Persona, Nat> _posicionEnCola;
};

//#include "Lollapatuza.cpp"

#endif //TP_LOLLA_LOLLAPATUZA_H
