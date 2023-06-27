#include <list>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include "tipos.h"
#include "PuestosDeComida.h"

template<typename T>
puestosDeComida<T>::puestosDeComida(Stock s ,Menu m , Promociones p) : _stock(s), _menu(m), _promociones(p) {}

template<typename T>
puestosDeComida<T>::~puestosDeComida(){}

template<typename T>
Nat puestosDeComida<T>::obtenerStock(Producto p){}

template<typename T>
Nat puestosDeComida<T>::obtenerDescuentoItem(Producto p, Nat cant){}

template<typename T>
Nat puestosDeComida<T>::gastoPersonaPuesto(Persona a){}

template<typename T>
void puestosDeComida<T>::modificarStock(bool reponer, Producto p, Nat cant){}
