#ifndef FORMULA_PISTAS_H_INCLUDED
#define FORMULA_PISTAS_H_INCLUDED

#include "formula.h"

/// FUNCIONES DE REGISTRO, EDICIÓN Y ELIMINACIÓN DE PISTAS
int buscarPistaPorId (stPista pistas[], int cant, int id);
int generarIDPista (stPista pistas[], int cant);
int registrarPista (stPista pistas[], int *cant, stPista nuevo);
int modificarPista (stPista pistas[], int cant, int id, stPista nuevaPista);
int eliminarPista (stPista pistas[], int *cant, int idPistaABorrar);

/// FUNCION DE CARGA Y GUARDADO
void guardarPista (stPista pistas[], int cant);
void cargarPista (stPista pistas[], int *cant);

/// FUNCIONES DE ORDEN Y MUESTRA
void ordenarPistasAlfabeticamente (stPista pistas[], int cant, stPista pistasOrdenadas[]);
void listarPistas (stPista pistas[], int cant);

#endif // FORMULA_PISTAS_H_INCLUDED
