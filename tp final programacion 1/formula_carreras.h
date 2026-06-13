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
void listarCarrerasDePista(stCarrera carrera[], int cant, stPista pista[], int idPista, int cantPistas);
void listarCarrerasDePiloto(stCarrera carrera[], int cant, stPista pista[], int idPiloto, int cantPistas);
int hayChoqueFechas(stCarrera carrera[], int cant, int idPista, stFecha fecha);
int eliminarCarrera(stCarrera carrera[], int *cant, int id);
int modificarCarrera(stCarrera carrera[], int *cant, int id, stCarrera nueva);

#endif // FORMULA_CARRERAS_H_INCLUDED
