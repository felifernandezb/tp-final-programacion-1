#include <stdio.h>
#include <string.h>
#include "formula.h"

// =================
// FUNCIONES CARRERAS
// =================

int buscarCarreraPorId (stCarrera carrera[], int cant, int id)
{
    for (int i = 0; i < cant; i++)
    {
        if (id == carrera[i].id)
        {
            return i;
        }
    }

    return -1;
}

int generarIdCarrera(stCarrera carrera[], int cant)
{
    int maxId = 0;
    for (int i = 0; i < cant; i++)
    {
        if (carrera[i].id > maxId)
        {
            maxId = carrera[i].id;
        }
    }
    return maxId + 1;
}

int registrarCarrera(stCarrera carrera[], int *cant, stCarrera nuevo)
{

    if (*cant >= MAX_CARRERAS)
    {
        return 0;
    }

    carrera[*cant] = nuevo;
    (*cant)++;

    guardarCarrera(carrera, *cant);

    return 1;
}

void guardarCarreras(stCarrera carrera[], int cant)
{
    FILE *archivo = fopen("carreras.dat", "wb");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de carreras.\n");
        return;
    }

    fwrite(&cant, sizeof(int), 1, archivo);

    for (int i = 0; i < cant; i++)
    {
        fwrite(&carrera[i], sizeof(stCarrera), 1, archivo);
    }

    fclose(archivo);
}

void cargarCarreras(stCarrera carrera[], int *cant)
{
    FILE *archivo = fopen("carreras.dat", "rb");

    if (archivo == NULL)
    {
        *cant = 0;
        return;
    }

    fread(cant, sizeof(int), 1, archivo);

    for (int i = 0; i < *cant; i++)
    {
        fread(&carrera[i], sizeof(stCarrera), 1, archivo);
    }

    fclose(archivo);
}

void listarCarreras(stCarrera carrera[], int cant, stPista pista[], int cantPistas)
{
    if (cant == 0)
    {
        printf("No hay carreras registradas.\n");
        return;
    }

    printf("%-6s %-30s %-20s %-10s %-10s %-10s\n", "ID", "Fecha", "Pista", "1ro", "2ro", "3ro");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < cant; i++)
    {
        int posPista = buscarPistaPorId(pista, cantPistas, carrera[i].idPista);

        char fecha[15];
        sprintf(fecha, "%02d/%02d/%04d", carrera[i].fecha.dia, carrera[i].fecha.mes, carrera[i].fecha.anio);

        printf("%-6d %-15s %-20s %-10d %-10d %-10d\n",
        carrera[i].id,
        fecha,
        pista[posPista].nombre,
        carrera[i].podio[0],
        carrera[i].podio[1],
        carrera[i].podio[2]);
    }
}
