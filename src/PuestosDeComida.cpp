#include <list>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include <algorithm> // Todavía no sabemos si se puede usar
#include "tipos.h"
#include "PuestosDeComida.h"

template<typename T>
puestosDeComida<T>::puestosDeComida(Stock s ,Menu m , Promociones p) {
    _stock = s;
    _menu = m;
    _promociones = p;
    map<int, vector<Nat>> promosDiccConArreglo;
    for (int i = 0; i < p.size(); i++) {
        Nat ultimoDescuentoDefinido = 0;
        vector<Nat> cantidadesPromoItem;
        for (int j = 0; j < p[i].size(); j++) {
            cantidadesPromoItem.push_back(p[i][j]);
        }
        Nat maxCant = cantidadesPromoItem[0];
        for (int j = 1; j < cantidadesPromoItem.size(); j++){
            if (cantidadesPromoItem[j] > maxCant){
                maxCant = cantidadesPromoItem[j];
            }
        }
        vector<Nat> arrDescuentos(maxCant, 0);
        for (int k = 0; k < maxCant; k++){
            for (int l = 0; l < cantidadesPromoItem.size(); l++) {
                if (cantidadesPromoItem[l] = k){
                    ultimoDescuentoDefinido = p[i][k];
                }
                arrDescuentos[k] = ultimoDescuentoDefinido;
            }
        }
        promosDiccConArreglo[i] = arrDescuentos;
    }
    //_ventas =
    //_ventasSinPromo =
}

template<typename T>
puestosDeComida<T>::~puestosDeComida(){}

template<typename T>
Nat puestosDeComida<T>::obtenerStock(Producto p){
    return this-> _stock(p);
}

template<typename T>
Nat puestosDeComida<T>::obtenerDescuentoItem(Producto p, Nat cant){
    return this-> _promociones(p)(cant);
}

template<typename T>
Nat puestosDeComida<T>::gastoPersonaPuesto(Persona a){
    return this -> _ventas(a);
}

template<typename T>
void puestosDeComida<T>::modificarStock(bool reponer, Producto p, Nat cant){

    if (reponer) {
        _stock[p] = obtenerStock(p) + cant;
    } else {
        _stock[p] = obtenerStock(p) - cant;
    }
}





template<typename T>
void puestosDeComida<T>::modificarVentas(bool reponer, Producto p, Nat cant, Persona a){

    Nat  ventaVieja = gastoPersonaPuesto(a);
    Nat descuento = obtenerDescuentoItem(p,cant);
    //Nat gastado = _menu[p]*cant*(div(100-descuento,100));

    if (reponer) {
        Nat ventaNueva = ventaVieja + gastado;
        gastoPersonaPuesto(a) = gastoPersonaPuesto(a) + ventaNueva;

        if (obtenerDescuentoItem(p,cant) == 0) {
            if ( this-> _ventasSinPromo(p)[a].count == 0 ) {
                this -> _ventasSinPromo(p)[a,cant];
            }
        }
    }



    if (reponer) {
        _ventas[p] = obtenerStock(p) + cant;
    } else {

    }
}