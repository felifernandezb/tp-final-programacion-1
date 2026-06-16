#ifndef FORMULA_INICIAL_H_INCLUDED
#define FORMULA_INICIAL_H_INCLUDED

#include "formula.h"

void cargarDatosIniciales(stPiloto pilotos[], int *cantPilotos,
                          stEscuderia escuderias[], int *cantEscuderias,
                          stColeccionPistas *colPistas,
                          stCarrera carreras[], int *cantCarreras);

void exportarTablaAPuntajes(stPiloto pilotos[], int cantPilotos, stEscuderia escuderias[], int cantEscuderias);
void ordenarPilotosPorPuntaje(stPiloto pilotos[], int cantPilotos, stPiloto resultado[]);
void mostrarTablaDePuntajes(stPiloto pilotos[], int cantPilotos, stEscuderia escuderias[], int cantEscuderias);
void exportarTablaDePuntajes(stPiloto pilotos[], int cantPilotos, stEscuderia escuderias[], int cantEscuderias);

#endif // FORMULA_INICIAL_H_INCLUDED
