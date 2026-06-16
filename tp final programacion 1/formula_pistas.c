#include "formula_pistas.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

// =====================
//   FUNCIONES PISTAS
// =====================

int expandirColeccion(stColeccionPistas *col)
{
    int nuevaDimension = col->dimension * 2;
    stPista *nuevo = (stPista *) realloc(col->pistas, nuevaDimension * sizeof(stPista));
    if (nuevo == NULL)
        return 0;
    col->pistas = nuevo;
    col->dimension = nuevaDimension;
    return 1;
}

int inicializarColeccion(stColeccionPistas *col)
{
    col->pistas = (stPista *)malloc(DIMENSION_INICIAL_PISTAS * sizeof(stPista));
    if (col->pistas == NULL)
        return 0;
    col->dimension = DIMENSION_INICIAL_PISTAS;
    col->validos = 0;
    return 1;
}

int buscarPistaPorId(stColeccionPistas *col, int id)
{
    for (int i = 0; i < col->validos; i++)
        if (col->pistas[i].id == id)
            return i;
    return -1;
}

int generarIDPista(stColeccionPistas *col)
{
    int maxId = 0;
    for (int i = 0; i < col->validos; i++)
        if (col->pistas[i].id > maxId)
            maxId = col->pistas[i].id;
    return maxId + 1;
}

int registrarPista(stColeccionPistas *col, stPista nuevo)
{
    if (col->validos >= col->dimension)
        if (!expandirColeccion(col))
            return 0;

    col->pistas[col->validos] = nuevo;
    col->validos++;
    guardarPista(col);
    return 1;
}

int modificarPista(stColeccionPistas *col, int id, stPista nuevaPista)
{
    int pos = buscarPistaPorId(col, id);
    if (pos == -1)
        return 0;
    nuevaPista.id = id;
    col->pistas[pos] = nuevaPista;
    guardarPista(col);
    return 1;
}

int eliminarPista(stColeccionPistas *col, int idPistaABorrar)
{
    int pos = buscarPistaPorId(col, idPistaABorrar);
    if (pos == -1)
        return 0;
    for (int i = pos; i < col->validos - 1; i++)
        col->pistas[i] = col->pistas[i + 1];
    col->validos--;
    guardarPista(col);
    return 1;
}

void guardarPista(stColeccionPistas *col)
{
    FILE *archi = fopen("pistas.dat", "wb");
    if (archi == NULL)
    {
        printf("El archivo no se pudo abrir.\n");
        return;
    }
    fwrite(&col->validos, sizeof(int), 1, archi);
    for (int i = 0; i < col->validos; i++)
        fwrite(&col->pistas[i], sizeof(stPista), 1, archi);
    fclose(archi);
}

void cargarPista(stColeccionPistas *col)
{
    FILE *archi = fopen("pistas.dat", "rb");
    if (archi == NULL)
    {
        col->validos = 0;
        return;
    }
    fread(&col->validos, sizeof(int), 1, archi);
    if (col->validos > col->dimension)
        expandirColeccion(col);
    for (int i = 0; i < col->validos; i++)
        fread(&col->pistas[i], sizeof(stPista), 1, archi);
    fclose(archi);
}

void ordenarPistasAlfabeticamente(stColeccionPistas *col, stColeccionPistas copia)
{
    for (int i = 0; i < col->validos; i++)
        pistasOrdenadas[i] = col->pistas[i];
    for (int i = 0; i < col->validos - 1; i++)
        for (int j = 0; j < col->validos - i - 1; j++)
            if (strcmp(pistasOrdenadas[j].nombre, pistasOrdenadas[j+1].nombre) > 0)
            {
                stPista aux = pistasOrdenadas[j];
                pistasOrdenadas[j] = pistasOrdenadas[j+1];
                pistasOrdenadas[j+1] = aux;
            }
}

void listarPistas(stColeccionPistas *col)
{
    if (col->validos == 0)
    {
        printf("No hay datos guardados.\n");
        return;
    }
    printf("%-5s %-30s %-30s %-10s\n", "ID", "Nombre", "Ubicacion", "Distancia (km)");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < col->validos; i++)
        printf("%-5d %-30s %-30s %-10.3f\n",
               col->pistas[i].id,
               col->pistas[i].nombre,
               col->pistas[i].ubicacion,
               col->pistas[i].distancia);
}

