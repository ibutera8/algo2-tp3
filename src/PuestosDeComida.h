#ifndef TP_LOLLA_PuestosDeComida_H
#define TP_LOLLA_PuestosDeComida_H

#include "tipos.h"
#include <map>

using namespace std;

class puestosDeComida {

public:
    puestosDeComida(aed2_Puesto& puesto);
    ~puestosDeComida();
    Nat obtenerStock(Producto p);
    Nat obtenerDescuentoItem(Producto p, Nat cant);
    Nat gastoPersonaPuesto(Persona a);
    Nat valorItemEnMenu(Producto p);
    Nat cantVentasSinPromo(Producto p, Persona a);
    void modificarStock(bool reponer, Producto p, Nat cant);
    void modificarVentas(bool reponer, Producto p, Nat cant, Persona a);
    void actualizarHackeabilidadPuesto(Persona a);
    //set<Nat> claves(map<Nat, Nat> dicc);
    //set<Nat> significados(map<Nat, Nat> dicc);
private:
    Menu _menu;
    Stock _stock;
    Promociones _promociones;
    Ventas _ventas;
    VentasSinPromo _ventasSinPromo;

};

//#include "PuestosDeComida.cpp"

#endif //TP_LOLLA_PuestosDeComida_H
