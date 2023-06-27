#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <set>
#include <vector>


using namespace std;

using Persona = int;
using IdPuesto = int;
using Producto = int;
using Nat = unsigned int;
using Stock = map<Producto, Nat>;
using Promociones = map<Producto, map<Nat, Nat>>;
using Menu = map<Producto, Nat>;
using Personas = set<int>;
using Ventas = map<Persona,Nat>;
using VentasSinPromo = map<Producto, map<Persona,Nat>>;


//using PuestosHackeables = map<persona,map<item,minHeap<IdPuesto>>>;

//me da una cola de prioridad con la operacion borrar cualquier elemento de la cola
template<typename T>
class colaPrior : public priority_queue<T, vector<T>> {
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

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

using Puestos = map<int , aed2_Puesto >;

#endif //SOLUCION_TIPOS_H
