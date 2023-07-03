#include "fachada_lollapatuza.h"

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos) : _lolla(lollapatuza(infoPuestos, personas)) {}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    _lolla.registrarCompraLolla(persona, producto, idPuesto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    _lolla.hackearLolla(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return _lolla.gastoTotalPersonaLolla(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla.personaQueMasGastoLolla();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
    return _lolla.puestoMenorStockLolla(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return _lolla.personasLolla();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    return _lolla.stockEnPuestoLolla(idPuesto, producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    return _lolla.descuentoEnPuestoLolla(idPuesto, producto, cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    return _lolla.gastoEnPuestoLolla(idPuesto, persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    set<IdPuesto> puestos = _lolla.puestosLolla();
    set<IdPuesto> ids;
    for (const auto& id : puestos) {
        ids.insert(id);
    }
    return ids;
}