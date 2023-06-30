#include <list>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include <algorithm> // Todavía no sabemos si se puede usar
#include "tipos.h"
#include "PuestosDeComida.h"

puestosDeComida::puestosDeComida(aed2_Puesto& puesto) {
    _stock = puesto.stock;
    _menu = puesto.menu;
    _promociones = puesto.promociones;

    //tenemos que recorrer todo el dicc _promociones
    //primero lo recorremos por producto, y luego vamos llenando los huecos:
    for (pair<Producto, map<Cant, Descuento>> par : _promociones){
        int prod = par.first;
        Nat ultimaCantDefinida = 0;
        //busco el maximo de las claves del dicc de promos para el producto actual
        for (pair<Cant, Descuento> promo : _promociones[prod]) {
            if (promo.first > ultimaCantDefinida) {
                ultimaCantDefinida = promo.first;
            }
        }
        //defino los huecos
        Nat ultimoDescDefinido = 0;
        for(int i = 0; i <= ultimaCantDefinida; i++) {
            if (_promociones[prod].count(i) == 1) {
                //en la pos i no tenog hueco, me agarro el descuento
                ultimoDescDefinido = _promociones[prod][i];
            } else {
                //en la pos i tengo hueco, lo lleno con el ultimo descuento definido
                _promociones[prod][i] = ultimoDescDefinido;
            }
        }
    }
    
    // map<int, vector<Nat>> promosDiccConArreglo;
    // for (int i = 0; i < p.size(); i++) {
    //     Nat ultimoDescuentoDefinido = 0;
    //     vector<Nat> cantidadesPromoItem;
    //     for (int j = 0; j < p[i].size(); j++) {
    //         cantidadesPromoItem.push_back(p[i][j]);
    //     }
    //     Nat maxCant = cantidadesPromoItem[0];
    //     for (int j = 1; j < cantidadesPromoItem.size(); j++){
    //         if (cantidadesPromoItem[j] > maxCant){
    //             maxCant = cantidadesPromoItem[j];
    //         }
    //     }
    //     vector<Nat> arrDescuentos(maxCant, 0);
    //     for (int k = 0; k < maxCant; k++){
    //         for (int l = 0; l < cantidadesPromoItem.size(); l++) {
    //             if (cantidadesPromoItem[l] = k){
    //                 ultimoDescuentoDefinido = p[i][k];
    //             }
    //             arrDescuentos[k] = ultimoDescuentoDefinido;
    //         }
    //     }
    //     promosDiccConArreglo[i] = arrDescuentos;
    // }
}

puestosDeComida::~puestosDeComida(){}

Nat puestosDeComida::obtenerStock(Producto p){
    return this-> _stock[p];
}

Nat puestosDeComida::obtenerDescuentoItem(Producto p, Nat cant){
    return this-> _promociones[p][cant];
}

Nat puestosDeComida::gastoPersonaPuesto(Persona a){
    Nat res;
    _ventas.count(a) == 1 ? res = _ventas[a] : res = 0;
    return res;
}

Nat puestosDeComida::valorItemEnMenu(Producto p){
    return this->_menu[p];
}

Nat puestosDeComida::cantVentasSinPromo(Producto p, Persona a){
    return this->_ventasSinPromo[p][a];
}


void puestosDeComida::modificarStock(bool reponer, Producto p, Nat cant){

    if (reponer) {
        _stock[p] += cant;
    } else {
        _stock[p] -= cant;
    }
}


void puestosDeComida::modificarVentas(bool reponer, Producto p, Nat cant, Persona a){

    Nat  ventaVieja = gastoPersonaPuesto(a);
    Nat descuento = obtenerDescuentoItem(p,cant);
    Nat gastado = (_menu[p] * cant) * ((100 - descuento)/100); //esto me da la division entera

    if (reponer) {
        Nat ventaNueva = ventaVieja + gastado;
        _ventas[a] = ventaNueva;

        if (descuento == 0) {
            if ( this-> _ventasSinPromo[p].count(a) == 0 ) {
                //lo defino 
                this -> _ventasSinPromo[p][a] = cant;
            } else {
                //ya etsa definido, le sumo
                _ventasSinPromo[p][a] += cant;
            }
        }
    } else {
        Nat ventaNueva = ventaVieja - gastado;
        _ventas[a] = ventaNueva;
        
        if(descuento == 0) {
            _ventasSinPromo[p][a] -= cant;
        }

        if(_ventasSinPromo[p][a] == 0){
            _ventasSinPromo[p].erase(a);
        }

        if(_ventasSinPromo[p].size() == 0) {
            _ventasSinPromo.erase(p);
        }
    }

    // if (reponer) {
    //     _ventas[p] = obtenerStock(p) + cant;
    // } else {

    // }
}

void puestosDeComida::actualizarHackeabilidadPuesto(Persona a) {
    if (_ventas[a] == 0){
         _ventas.erase(a);
    }

}