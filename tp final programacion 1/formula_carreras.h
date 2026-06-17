#ifndef FORMULA_CARRERAS_H_INCLUDED
#define FORMULA_CARRERAS_H_INCLUDED

#include "formula.h"
#include "formula_pistas.h"


// ========================
//   CARRERA
// ========================

int buscarCarreraPorId (stCarrera carrera[], int cant, int id);
int generarIdCarrera(stCarrera carrera[], int cant);
int registrarCarrera(stCarrera carrera[], int *cant, stCarrera nuevo);
void guardarCarreras(stCarrera carrera[], int cant);
void cargarCarreras(stCarrera carrera[], int *cant);
void listarCarreras(stCarrera carrera[], int cant, stColeccionPistas *col, stPiloto pilotos[], int cantPilotos);
void listarCarrerasDePista(stCarrera carrera[], int cant, stColeccionPistas *col , int idPista, stPiloto pilotos[], int cantPilotos);
void listarCarrerasDePiloto(stCarrera carrera[], int cant, stColeccionPistas *col, int idPiloto, stPiloto pilotos[], int cantPilotos);
int hayChoqueFechas(stCarrera carrera[], int cant, int idPista, stFecha fecha);
int hayChoqueFechasPiloto(stCarrera carrera[], int cant, int idPiloto, stFecha fecha);
int eliminarCarrera(stCarrera carrera[], int *cant, int id);
int modificarCarrera(stCarrera carrera[], int *cant, int id, stCarrera nueva);
int mismaCategoria(stPiloto pilotos[], int cantPilotos, int idPiloto1, int idPiloto2, int idPiloto3, int idPilotoVR);

#endif // FORMULA_CARRERAS_H_INCLUDED
