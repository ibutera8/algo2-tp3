
#include "Lollapatuza.h"
//#include "PuestosDeComida.cpp"
//#include "PuestosDeComida.h"

lollapatuza::lollapatuza() {}

lollapatuza::lollapatuza(Puestos p , Personas a) {
    //defino las variables privadas pasadas por parametro
    _puestos = p;
    _personas = a;
    //inicializo los gastos por persona en 0
    for (Persona persona : a) {
        _historialCompras[persona] = 0;
    }

}

lollapatuza::~lollapatuza(){}

void lollapatuza::registrarCompra(Persona a, Producto p, IdPuesto id, Nat cant){
    puestosDeComida puesto = _puestos[id];
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

void lollapatuza::hackear(Persona a, Producto p){
    int puid = -1 * _puestosHackeables[a][p].top(); //multiplicaba por -1 para obtener el id original
    puestosDeComida puesto = _puestos[puid];
    puesto.modificarStock(true, p, 1);
    puesto.modificarVentas(false, p, 1, a);

    int gastado = puesto.valorItemEnMenu(p);
    _historialCompras[a] -= gastado;
    this->actualizarHackeabilidad(a, p, puid);
    this->actualizarRanking(a);
}

void lollapatuza::actualizarHackeabilidad(Persona a, Producto p, IdPuesto pid){
    puestosDeComida puesto = _puestos[pid];
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

void lollapatuza::actualizarRanking(Persona a){
    this->_rankingGastosPersonas.remove(a);
    this->_rankingGastosPersonas.push(a);
}


Nat lollapatuza::gastoTotalPersona(Persona a){
    return this->_historialCompras[a];
}


Persona lollapatuza::personaQueMasGasto() const{
    return this->_rankingGastosPersonas.top();
}


//revisar esta para que devuelva el id de puesto
//ahora esta devolviendo la posicion en el dicc

IdPuesto lollapatuza::puestoMenorStock(Producto i){
    IdPuesto res = 0;
    Nat menorStock = 0;
    for (pair<IdPuesto, puestosDeComida> par : _puestos) { // Acá se rompe con el tipo de dato de par y el de _puestos
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


set<Persona> lollapatuza::personas(){
    return _personas;
}


//tiene que devolver las claves del diccionario _puestos

set<IdPuesto> lollapatuza::puestos(){
    set<IdPuesto> claves = set<int>();
    for (pair<IdPuesto, puestosDeComida> par : this->_puestos) { // Acá se rompe con el tipo de dato de par y el de _puestos
        claves.insert(par.first);
    }
    return claves;
}


Nat lollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) {
    puestosDeComida puesto = _puestos[idPuesto];
    return puesto.obtenerStock(producto);
}


Nat lollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) {
    puestosDeComida puesto = _puestos[idPuesto];
    return puesto.obtenerDescuentoItem(producto, cantidad);
}



Nat lollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) {
    puestosDeComida puesto = _puestos[idPuesto];
    return puesto.gastoPersonaPuesto(persona);
}