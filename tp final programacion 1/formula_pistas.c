#include "formula_pistas.h"
#include <stdio.h>
#include <string.h>

// =====================
//   FUNCIONES PISTAS
// =====================

int buscarPistaPorId (stPista pistas[], int cant, int id)
{
    for (int i = 0; i < cant; i++)
    {
        if (id == pistas[i].id)
        {
            return i;
        }
    }

    return -1;
}

int generarIDPista (stPista pistas[], int cant)
{
    int maxId = 0;

    for (int i = 0; i < cant; i++)
    {
        if (pistas[i].id > maxId)
        {
            maxId = pistas[i].id;
        }
    }

    return maxId + 1;
}

int registrarPista (stPista pistas[], int *cant, stPista nuevo)
{
    if (*cant >= MAX_PISTAS)
    {
        return 0;
    }

    pistas[*cant] = nuevo;
    (*cant)++;

    guardarPista(pistas, *cant);

    return 1;
}

int modificarPista (stPista pistas[], int cant, int id, stPista nuevaPista)
{
    int pos = buscarPistaPorId(pistas, cant, id);

    if (pos == -1)
    {
        return 0;
    }

    nuevaPista.id = id;
    pistas[pos] = nuevaPista;

    guardarPista(pistas, cant);

    return 1;
}

int eliminarPista (stPista pistas[], int *cant, int idPistaABorrar)
{
    int pos = buscarPistaPorId(pistas, *cant, idPistaABorrar);

    if (pos == -1)
    {
        return 0;
    }

    for (int i = pos; i < *cant - 1; i++)
    {
        pistas[i] = pistas[i+1];
    }

    (*cant)--;

    guardarPista(pistas, *cant);

    return 1;
}

void guardarPista (stPista pistas[], int cant)
{
    FILE *archi = fopen("pistas.dat", "wb");

    if (archi == NULL)
    {
        printf("El archivo no se pudo abrir.\n");
        return;
    }

    fwrite(&cant, sizeof(int), 1, archi);

    for (int i = 0; i < cant; i++)
    {
        fwrite(&pistas[i], sizeof(stPista), 1, archi);
    }

    fclose(archi);
}

void cargarPista (stPista pistas[], int *cant)
{
    FILE *archi = fopen("pistas.dat", "rb");

    if (archi == NULL)
    {
        *cant = 0;
        return;
    }

    fread(cant, sizeof(int), 1, archi);

    for (int i = 0; i < *cant; i++)
    {
        fread(&pistas[i], sizeof(stPista), 1, archi);
    }

    fclose(archi);
}

void ordenarPistasAlfabeticamente (stPista pistas[], int cant, stPista pistasOrdenadas[])
{
    for (int i = 0; i < cant; i++)
    {
        pistasOrdenadas[i] = pistas[i];
    }

    for (int i = 0; i < cant - 1; i++)
    {
        for (int j = 0; j < cant - i - 1; j++)
        {
            if (strcmp(pistasOrdenadas[j].nombre, pistasOrdenadas[j+1].nombre) > 0)
            {
                stPista aux = pistasOrdenadas[j];
                pistasOrdenadas[j] = pistasOrdenadas[j+1];
                pistasOrdenadas[j+1] = aux;
            }
        }
    }
}

void listarPistas (stPista pistas[], int cant)
{
    if (cant == 0)
    {
        printf("No hay datos guardados.\n");
        return;
    }

    printf("%-5s %-30s %-30s %-10s\n", "ID", "Nombre", "Ubicacion", "Distancia (km)");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < cant; i++)
    {
        printf("%-5d %-30s %-30s %-10.3f\n", pistas[i].id, pistas[i].nombre, pistas[i].ubicacion, pistas[i].distancia);
    }
}
