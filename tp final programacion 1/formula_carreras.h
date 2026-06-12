#ifndef FORMULA_CARRERAS_H_INCLUDED
#define FORMULA_CARRERAS_H_INCLUDED

#include "formula.h"

// ========================
//   CARRERA
// ========================

int buscarCarreraPorId (stCarrera carrera[], int cant, int id);
int generarIdCarrera(stCarrera carrera[], int cant);
int registrarCarrera(stCarrera carrera[], int *cant, stCarrera nuevo);
void guardarCarreras(stCarrera carrera[], int cant);
void cargarCarreras(stCarrera carrera[], int *cant);
void listarCarreras(stCarrera carrera[], int cant, stPista pista[], int cantPistas);



#endif // FORMULA_CARRERAS_H_INCLUDED
