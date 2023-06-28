#include <list>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include "tipos.h"
#include "Lollapatuza.h"
#include "PuestosDeComida.cpp"
#include "PuestosDeComida.h"

template<typename T>
lollapatuza<T>::lollapatuza(Puestos p , Personas a) {
    //defino las variables privadas pasadas por parametro
    _puestos = p;
    _personas = a;
    //inicializo los gastos por persona en 0
    for (Persona persona : a) {
        _historialCompras[persona] = 0;
    }

}

template<typename T>
lollapatuza<T>::~lollapatuza(){}

template<typename T>
void lollapatuza<T>::registrarCompra(Persona a, Producto p, IdPuesto id, Nat cant){
    puestosDeComida<T> puesto = _puestos[id];
    puesto.modificarStock(false, p, cant);
    puesto.modificarVentas(true, p, cant, a);
    Nat descuento = puesto.obtenerDescuentoItem(p, cant);
    Nat gastado = puesto.menu[p] * cant;
    this->_personas[a] = this->_personas[a] + gastado;
    if (descuento == 0){
        this->_puestosHackeables[a][p] = id;
    }
    this->actualizaRanking(_rankingGastosPersonas, a);
}

template<typename T>
void lollapatuza<T>::hackear(Persona a, Producto p){
    int pid = _puestosHackeables[a][p].top();
    puestosDeComida<T>* puesto = _puestos[pid];
    &puesto->modificarStock(true, p, 1);
    &puesto->modificarVentas(false, p, 1, a);

    int gastado = &puesto->_menu[p];
    _historialCompras[a] += gastado;
    this->actualizarHackeabilidad(a, p, pid);
    this->actualizarRanking(a);
}

template<typename T>
void lollapatuza<T>::actualizarHackeabilidad(Persona a, Producto p, IdPuesto pid){
    puestosDeComida<T> puesto = _puestos[pid];
    if (puesto._ventasSinPromo[p][a] == 0){
        this->_puestosHackeables[a][p].erase(pid);
    }
    if (this->_puestosHackeables[a][p].size() == 0){
        this->_puestosHackeables[a].erase(p);
    }
    if (this->_puestosHackeables[a].size() == 0){
        this->_puestosHackeables.erase(a);
    }
    if (puesto._ventas[a] == 0){
        puesto._ventas.erase(a);
    }
}

template<typename T>
void lollapatuza<T>::actualizarRanking(Persona a){
    this->_rankingGastosPersona.remove(a);
    this->_rankingGastosPersona.push(a);
}


template<typename T>
Nat lollapatuza<T>::gastoTotalPersona(Persona a){
    return this->_personas[a];
}

template<typename T>
Persona lollapatuza<T>::personaQueMasGasto() const{
    return this->_rankingGastosPersonas.top();
}

template<typename T>
IdPuesto lollapatuza<T>::puestoMenorStock(Producto i){
    Nat res = 0;
    for (i = 0; i < this->_puestos.length() - 1; i++){
        puestosDeComida<T> puesto     = _puestos[i];
        puestosDeComida<T> puesto_sig = _puestos[i + 1];
        if (puesto.stock[i] < puesto_sig.stock[i]){
            res = i;
        }
    }
    return res;
}

template<typename T>
set<Persona> lollapatuza<T>::personas(){
    return this->_personas;
}

template<typename T>
Puestos lollapatuza<T>::puestos(){
    return this->_puestos;
}












