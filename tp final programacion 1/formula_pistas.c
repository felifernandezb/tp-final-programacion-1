#include "formula_pistas.h"
#include <stdio.h>
#include <string.h>

int buscarPistaPorId (stPista pistas[], int cantidad, int id)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (id == pistas[i].id)
        {
            return i;
        }
    }

    return -1;
}

int generarIDPista (stPista pistas[], int cantidad)
{
    int maxId = 0;

    for (int i = 0; i < cantidad; i++)
    {
        if (pistas[i].id > maxId)
        {
            maxId = pistas[i].id;
        }
    }

    return maxId + 1;
}

int registrarPista (stPista pistas[], int *cantidad, stPista nuevo)
{
    if (*cantidad >= MAX_PISTAS)
    {
        return 0;
    }

    pistas[*cantidad] = nuevo;
    (*cantidad)++;

    guardarPista(pistas, *cantidad);

    return 1;
}
