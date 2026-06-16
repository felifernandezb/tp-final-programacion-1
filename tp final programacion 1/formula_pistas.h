#ifndef FORMULA_PISTAS_H_INCLUDED
#define FORMULA_PISTAS_H_INCLUDED

#include "formula.h"

/// FUNCIONES DINAMICAS+
int inicializarColeccion(stColeccionPistas *col);
int expandirColeccion(stColeccionPistas *col);

/// FUNCIONES DE REGISTRO, EDICIÓN Y ELIMINACIÓN DE PISTAS
int buscarPistaPorId(stColeccionPistas *col, int id);
int generarIDPista(stColeccionPistas *col);
int registrarPista(stColeccionPistas *col, stPista nuevo);
int modificarPista(stColeccionPistas *col, int id, stPista nuevaPista);
int eliminarPista(stColeccionPistas *col, int idPistaABorrar);

/// FUNCION DE CARGA Y GUARDADO
void guardarPista(stColeccionPistas *col);
void cargarPista(stColeccionPistas *col);

/// FUNCIONES DE ORDEN Y MUESTRA
void ordenarPistasAlfabeticamente(stColeccionPistas *col, stPista pistasOrdenadas[]);
void listarPistas(stPista pistasOrdenadas[], int cant);

#endif // FORMULA_PISTAS_H_INCLUDED
