
#include "Lollapatuza.h"
//#include "PuestosDeComida.cpp"
//#include "PuestosDeComida.h"

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
    Nat gastado = puesto.valorItemEnMenu(p) * cant;
    _historialCompras[a] += gastado;
    if (descuento == 0){
        this->_puestosHackeables[a][p].push(-1* id); //multiplicaba por -1 porque asi armamos el minHeap
    }
    this->actualizarRanking(a);
}

template<typename T>
void lollapatuza<T>::hackear(Persona a, Producto p){
    int puid = -1 * _puestosHackeables[a][p].top(); //multiplicaba por -1 para obtener el id original
    puestosDeComida<T> puesto = _puestos[puid];
    puesto.modificarStock(true, p, 1);
    puesto.modificarVentas(false, p, 1, a);

    int gastado = puesto.valorItemEnMenu(p);
    _historialCompras[a] -= gastado;
    this->actualizarHackeabilidad(a, p, puid);
    this->actualizarRanking(a);
}

template<typename T>
void lollapatuza<T>::actualizarHackeabilidad(Persona a, Producto p, IdPuesto pid){
    puestosDeComida<T> puesto = _puestos[pid];
    if (puesto.cantVentasSinPromo(p, a) == 0){
        this->_puestosHackeables[a][p].pop();
    }
    if (this->_puestosHackeables[a][p].size() == 0){
        this->_puestosHackeables[a].erase(p);
    }
    if (this->_puestosHackeables[a].size() == 0){
        this->_puestosHackeables.erase(a);
    }
    //esto creo que deberia ir en modificar ventas en puestos, 
    //esta modificando una variable privada del tipo puestoDeComida
    // if (puesto._ventas[a] == 0){
    //     puesto._ventas.erase(a);
    // }

    puesto.actualizarHackeabilidadPuesto(a);
}

template<typename T>
void lollapatuza<T>::actualizarRanking(Persona a){
    this->_rankingGastosPersonas.remove(a);
    this->_rankingGastosPersonas.push(a);
}


template<typename T>
Nat lollapatuza<T>::gastoTotalPersona(Persona a){
    return this->_historialCompras[a];
}

template<typename T>
Persona lollapatuza<T>::personaQueMasGasto() const{
    return this->_rankingGastosPersonas.top();
}


//revisar esta para que devuelva el id de puesto
//ahora esta devolviendo la posicion en el dicc
template<typename T>
IdPuesto lollapatuza<T>::puestoMenorStock(Producto i){
    IdPuesto res = 0;
    Nat menorStock = 0;
    for (pair<IdPuesto, puestosDeComida<T>> par : _puestos) {
        if (stockEnPuesto(par.first, i) < menorStock) {
            res = par.first;
            menorStock = stockEnPuesto(par.first, i);
        }
    }

    return res;
   /* Nat res = 0;
    for (i = 0; i < this->_puestos.length() - 1; i++){
        puestosDeComida<T> puesto     = _puestos[i];
        puestosDeComida<T> puesto_sig = _puestos[i + 1];
        if (puesto.stock[i] < puesto_sig.stock[i]){
            res = i;
        }
    }
    return res;*/
}

template<typename T>
set<Persona> lollapatuza<T>::personas(){
    return this->_personas;
}


//tiene que devolver las claves del diccionario _puestos
template<typename T>
set<IdPuesto> lollapatuza<T>::puestos(){
    set<IdPuesto> claves = set<int>();
    for (pair<IdPuesto, puestosDeComida<T>> par : this->_puestos) {
        claves.insert(par.first);
    }
    return claves;
}

template<typename T>
Nat lollapatuza<T>::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) {
    puestosDeComida<T> puesto = _puestos[idPuesto];
    return puesto.obtenerStock(producto);
}


template<typename T>
Nat lollapatuza<T>::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) {
    puestosDeComida<T> puesto = _puestos[idPuesto];
    return puesto.obtenerDescuentoItem(producto, cantidad);
}


template<typename T>
Nat lollapatuza<T>::gastoEnPuesto(IdPuesto idPuesto, Persona persona) {
    puestosDeComida<T> puesto = _puestos[idPuesto];
    return puesto.gastoPersonaPuesto(persona);
}