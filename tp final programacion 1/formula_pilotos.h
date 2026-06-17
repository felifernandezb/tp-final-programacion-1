#ifndef FORMULA_SERVICIO_H_INCLUDED
#define FORMULA_SERVICIO_H_INCLUDED

#include "formula.h"

// ========================
//   PILOTOS
// ========================

int registrarPiloto(stPiloto pilotos[], int *cant, stPiloto nuevo);
int modificarPiloto(stPiloto pilotos[], int cant, int id, stPiloto actualizado);
int modificarPilotoCompleto(stPiloto pilotos[], int cantPilotos, stEscuderia escuderias[], int cantEscuderias, int id, stPiloto actualizado);
int eliminarPiloto(stPiloto pilotos[], int *cant, int id);
void listarPilotos(stPiloto pilotos[], int cant, stEscuderia escuderias[], int cantEscuderias);
int buscarPilotoPorId(stPiloto pilotos[], int cant, int id);
int generarIdPiloto(stPiloto pilotos[], int cant);

void ordenarPilotosAlfabeticamente(stPiloto pilotos[], int cant, stPiloto resultado[]);

void guardarPilotos(stPiloto pilotos[], int cant);
void cargarPilotos(stPiloto pilotos[], int *cant);

// ========================
//   ESCUDERIAS
// ========================

int registrarEscuderia(stEscuderia escuderias[], int *cant, stEscuderia nueva);
int modificarEscuderia(stEscuderia escuderias[], int cant, int id, stEscuderia actualizada, stPiloto pilotos[], int cantPilotos);
int eliminarEscuderia(stEscuderia escuderias[], int *cant, int id, stPiloto pilotos[], int *cantPilotos);
void listarEscuderias(stEscuderia escuderias[], int cant, stPiloto pilotos[], int cantPilotos);
int buscarEscuderiaPorId(stEscuderia escuderias[], int cant, int id);
int generarIdEscuderia(stEscuderia escuderias[], int cant);

void guardarEscuderias(stEscuderia escuderias[], int cant);
void cargarEscuderias(stEscuderia escuderias[], int *cant);

int hayEscuderiaDisponible(stEscuderia escuderias[], int cant, int categoria);
void listarEscuderiasDisponibles(stEscuderia escuderias[], int cant, int categoria, int idEscudActual);
void ordenarEscuderiasAlfabeticamente(stEscuderia escuderias[], int cant, stEscuderia resultado[]);



#endif // FORMULA_SERVICIO_H_INCLUDED
