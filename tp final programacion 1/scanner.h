#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include "formula.h"

void limpiarBuferDeEntrada(void);
int confirmar(char condicion);
int scanInt(void);
char scanChar(void);
float scanFloat(void);
int scanString(char* string, int maxLength);
void scanFecha(stFecha *fecha);
int scanIdPiloto(stPiloto pilotos[], int cantPilotos, char* mensaje);
int scanIdPista(stColeccionPistas *col);

#endif // SCANNER_H_INCLUDED
