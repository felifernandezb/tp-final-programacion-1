#ifndef FORMULA_PISTAS_H_INCLUDED
#define FORMULA_PISTAS_H_INCLUDED

/// FUNCIONES DE CARGA, EDICIÓN Y ELIMINACIÓN DE PISTAS
int buscarPistaPorId (stPista pistas[], int cant, int id);
int generarIDPista (stPista pistas[], int cant);
int registrarPista (stPista pistas[], int *cant, stPista nuevo);
int modificarPista ();
int eliminarPista ();

/// FUNCIONES DE ORDEN Y MUESTRA
void ordenarPistasAlfabeticamente ();
void listarPistas ();

void guardarPista ();
void cargarPista ();

#endif // FORMULA_PISTAS_H_INCLUDED
