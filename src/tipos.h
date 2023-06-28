#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <set>
#include <queue>
#include <vector>


using namespace std;

using Persona = int;
using IdPuesto = int;
using Producto = int;
using Nat = unsigned int;
using Stock = map<Producto, Nat>;
using Promociones = map<Producto, map<Nat, Nat>>;
using Menu = map<Producto, Nat>;
using Personas = set<Persona>;
using Ventas = map<Persona,Nat>;
using VentasSinPromo = map<Producto, map<Persona,Nat>>;


//using PuestosHackeables = map<persona,map<item,minHeap<IdPuesto>>>;


struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

using Puestos = map<int , aed2_Puesto>;

#endif //SOLUCION_TIPOS_H
