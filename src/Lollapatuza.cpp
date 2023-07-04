#include "Lollapatuza.h"


lollapatuza::lollapatuza() {}

lollapatuza::lollapatuza(Puestos p , Personas a) {
    //defino las variables privadas pasadas por parametro
    _personas = a;
    //transformo aed2_puesto struct de la catedra a puestosDeComida modulo nuestro
    for (pair<Nat, aed2_Puesto> par : p) {
        Nat pid = par.first;
        puestosDeComida puesto = puestosDeComida(par.second);
        _puestos.insert({pid, puesto});
    }
    //inicializo los gastos por persona en 0
    for (Persona persona : a) {
        _historialCompras[persona] = 0;
        _rankingGastosPersonas.push(make_pair(0,persona*-1));

    }

}

lollapatuza::~lollapatuza(){}

void lollapatuza::registrarCompraLolla(Persona a, Producto p, IdPuesto id, Nat cant){
    puestosDeComida &puesto = _puestos[id];
    puesto.modificarStock(false, p, cant);
    puesto.modificarVentas(true, p, cant, a);
    Nat descuento = puesto.obtenerDescuentoItem(p, cant);
    float descPorcent = static_cast<float>(descuento) / 100.0f;
    Nat gastado = 0;
    if (descuento == 0 ) {
         gastado = puesto.valorItemEnMenu(p) * cant;
    } else {
        gastado = (puesto.valorItemEnMenu(p) * cant)*(1-descPorcent);
    }
    _historialCompras[a] += gastado;
    if (descuento == 0){
        this->_puestosHackeables[a][p].push(-1* id); //multiplicaba por -1 porque asi armamos el minHeap
    }
    this->actualizarRankingLolla(a);
}

void lollapatuza::hackearLolla(Persona a, Producto p){
    int puid = -1 * _puestosHackeables[a][p].top(); //multiplicaba por -1 para obtener el id original
    puestosDeComida &puesto = _puestos[puid];
    puesto.modificarStock(true, p, 1);
    puesto.modificarVentas(false, p, 1, a);

    int gastado = puesto.valorItemEnMenu(p);
    _historialCompras[a] -= gastado;
    this->actualizarHackeabilidadLolla(a, p, puid);
    this->actualizarRankingLolla(a);
}

void lollapatuza::actualizarHackeabilidadLolla(Persona a, Producto p, IdPuesto pid){
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

void lollapatuza::actualizarRankingLolla(Persona a){
    pair<Nat, Persona> valor = make_pair(gastoTotalPersonaLolla(a), -1 * a);
    this->_rankingGastosPersonas.remove(valor);
    this->_rankingGastosPersonas.push(valor);
}


Nat lollapatuza::gastoTotalPersonaLolla(Persona a) const{
    return _historialCompras.find(a)->second;
}


Persona lollapatuza::personaQueMasGastoLolla() const{
    return (this->_rankingGastosPersonas.top()).second * -1;
}


//revisar esta para que devuelva el id de puesto
//ahora esta devolviendo la posicion en el dicc

IdPuesto lollapatuza::puestoMenorStockLolla(Producto i) const{
    IdPuesto res = 0;
    Nat menorStock = 10000; // Corregir este numero
    bool primeraIt = true;
    for (pair<IdPuesto, puestosDeComida> par : _puestos) { // Acá se rompe con el tipo de dato de par y el de _puestos
        if (primeraIt){
            res = par.first;
            menorStock = stockEnPuestoLolla(par.first, i);
            primeraIt = false;
        }
        if (stockEnPuestoLolla(par.first, i) < menorStock) {
            res = par.first;
            menorStock = stockEnPuestoLolla(par.first, i);
        }
    }

    return res;
}


const set<Persona> & lollapatuza::personasLolla() const {
    return _personas;
}


//tiene que devolver las claves del diccionario _puestos

set<IdPuesto> lollapatuza::puestosLolla() const{
    set<IdPuesto> claves = set<int>();
    for (pair<IdPuesto, puestosDeComida> par : this->_puestos) { // Acá se rompe con el tipo de dato de par y el de _puestos
        claves.insert(par.first);
    }
    return claves;
}


Nat lollapatuza::stockEnPuestoLolla(IdPuesto idPuesto, const Producto &producto) const{
    puestosDeComida puesto = _puestos.find(idPuesto)->second;
    return puesto.obtenerStock(producto);
}


Nat lollapatuza::descuentoEnPuestoLolla(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const{
    puestosDeComida puesto = _puestos.find(idPuesto)->second;
    return puesto.obtenerDescuentoItem(producto, cantidad);
}



Nat lollapatuza::gastoEnPuestoLolla(IdPuesto idPuesto, Persona persona) const{
    puestosDeComida puesto = _puestos.find(idPuesto)->second;
    return puesto.gastoPersonaPuesto(persona);
}
