#ifndef FORMULA_SERVICIO_H_INCLUDED
#define FORMULA_SERVICIO_H_INCLUDED

#include "formula.h"

// ========================
//   PILOTOS
// ========================

int registrarPiloto(stPiloto pilotos[], int *cant, stPiloto nuevo);
int modificarPiloto(stPiloto pilotos[], int cant, int id, stPiloto actualizado);
int eliminarPiloto(stPiloto pilotos[], int *cant, int id);
void listarPilotos(stPiloto pilotos[], int cant);
int buscarPilotoPorId(stPiloto pilotos[], int cant, int id);

void ordenarPilotosAlfabeticamente(stPiloto pilotos[], int cant, stPiloto resultado[]);

void guardarPilotos(stPiloto pilotos[], int cant);
void cargarPilotos(stPiloto pilotos[], int *cant);

// ========================
//   ESCUDERIAS
// ========================

int registrarEscuderia(stEscuderia escuderias[], int *cant, stEscuderia nueva, stPiloto pilotos[], int cantPilotos);
int modificarEscuderia(stEscuderia escuderias[], int cant, int id, stEscuderia actualizada, stPiloto pilotos[], int cantPilotos);
int eliminarEscuderia(stEscuderia escuderias[], int *cant, int id);
void listarEscuderias(stEscuderia escuderias[], int cant);
int buscarEscuderiaPorId(stEscuderia escuderias[], int cant, int id);

void guardarEscuderias(stEscuderia escuderias[], int cant);
void cargarEscuderias(stEscuderia escuderias[], int *cant);



#endif // FORMULA_SERVICIO_H_INCLUDED
