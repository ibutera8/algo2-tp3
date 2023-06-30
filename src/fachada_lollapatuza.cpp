#include "fachada_lollapatuza.h"
#include "Lollapatuza.h"
#include "PuestosDeComida.h"


FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos) {
    _lolla = lollapatuza(infoPuestos, personas);
}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    _lolla.registrarCompra(persona, producto, idPuesto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    _lolla.hackear(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return _lolla.gastoTotalPersona(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla.personaQueMasGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
    return _lolla.puestoMenorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return _lolla.personas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    return _lolla.stockEnPuesto(idPuesto, producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    return _lolla.descuentoEnPuesto(idPuesto, producto, cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    return _lolla.gastoEnPuesto(idPuesto, persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    Puestos puestos = _lolla.puestos();
    set<IdPuesto> ids;
    for (const auto& par : puestos) {
        ids.insert(par.first);
    }
    return ids;
}