#ifndef TP_LOLLA_PuestosDeComida_H
#define TP_LOLLA_PuestosDeComida_H

#include "tipos.h"
#include <map>

using namespace std;

template<typename T>
class puestosDeComida {

public:
    puestosDeComida(Stock s ,Menu m , Promociones p);
    ~puestosDeComida();
    Nat obtenerStock(Producto p);
    Nat obtenerDescuentoItem(Producto p, Nat cant);
    Nat gastoPersonaPuesto(Persona a);
    void modificarStock(bool reponer, Producto p, Nat cant);
    void modificarVentas(bool reponer, Nat a, Producto p, Nat cant);
    set<Nat> claves(map<Nat, Nat> dicc);
    set<Nat> significados(map<Nat, Nat> dicc);
private:
    Menu _menu;
    Stock _stock;
    Promociones _promociones;
    Ventas _ventas;
    VentasSinPromo _ventasSinPromo;

};

#include "PuestosDeComida.cpp"

#endif //TP_LOLLA_PuestosDeComida_H
