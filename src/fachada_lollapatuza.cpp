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
    //
}

Persona FachadaLollapatuza::mayorGastador() const {
    return _lolla.personaQueMasGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
   // TODO: Completar
}

const set<Persona> &FachadaLollapatuza::personas() const {
    // TODO: Completar
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    // TODO: Completar
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    // TODO: Completar
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    // TODO: Completar
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    // TODO: Completar
}