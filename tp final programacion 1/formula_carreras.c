#include <stdio.h>
#include <string.h>
#include "formula.h"
#include "formula_carreras.h"
#include "formula_pistas.h"
#include "formula_pilotos.h"

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

    if (hayChoqueFechas(carrera, *cant, nuevo.idPista, nuevo.fecha))
    {
        return 0;
    }

    carrera[*cant] = nuevo;
    (*cant)++;

    guardarCarreras(carrera, *cant);

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

void listarCarreras(stCarrera carrera[], int cant, stColeccionPistas *col, stPiloto pilotos[], int cantPilotos)
{
    if (cant == 0)
    {
        printf("No hay carreras registradas.\n");
        return;
    }

    printf("%-6s %-20s %-20s %-15s %-15s %-15s\n", "ID", "Fecha", "Pista", "1ro", "2ro", "3ro");
    printf("-------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cant; i++)
    {
        int posPista = buscarPistaPorId(col, carrera[i].idPista);

        char fecha[15];
        sprintf(fecha, "%02d/%02d/%04d", carrera[i].fecha.dia, carrera[i].fecha.mes, carrera[i].fecha.anio);
        int pos1 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[0]);
        int pos2 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[1]);
        int pos3 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[2]);

        printf("%-6d %-20s %-20s %-15s %-15s %-15s\n",
               carrera[i].id,
               fecha,
               posPista != -1 ? col->pistas[posPista].nombre : "Desconocida",
               pos1 != -1 ? pilotos[pos1].nombre : "N/A",
               pos2 != -1 ? pilotos[pos2].nombre : "N/A",
               pos3 != -1 ? pilotos[pos3].nombre : "N/A");

        int posVR = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].vueltaRapida.idPiloto);
        printf("  Vuelta rapida: %s - %d:%02d:%03d\n",
               posVR != -1 ? pilotos[posVR].nombre : "N/A",
               carrera[i].vueltaRapida.minutos,
               carrera[i].vueltaRapida.segundos,
               carrera[i].vueltaRapida.milisegundos);
    }
}

void listarCarrerasDePista(stCarrera carrera[], int cant, stColeccionPistas *col , int idPista, stPiloto pilotos[], int cantPilotos)
{
    if (cant == 0)
    {
        printf("No hay carreras registradas.\n");
        return;
    }
    printf("%-6s %-15s %-20s %-20s %-20s %-20s\n", "ID", "Fecha", "Pista", "1ro", "2ro", "3ro");
    printf("---------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < cant; i++)
    {
        if (carrera[i].idPista == idPista)
        {
            int posPista = buscarPistaPorId(col, carrera[i].idPista);
            char fecha[15];
            sprintf(fecha, "%02d/%02d/%04d", carrera[i].fecha.dia, carrera[i].fecha.mes, carrera[i].fecha.anio);
            int pos1 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[0]);
            int pos2 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[1]);
            int pos3 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[2]);
            printf("%-6d %-15s %-20s %-20s %-20s %-20s\n",
                   carrera[i].id,
                   fecha,
                   col->pistas[posPista].nombre,
                   pos1 != -1 ? pilotos[pos1].nombre : "N/A",
                   pos2 != -1 ? pilotos[pos2].nombre : "N/A",
                   pos3 != -1 ? pilotos[pos3].nombre : "N/A");
            int posVR = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].vueltaRapida.idPiloto);
            printf("  Vuelta rapida: %s - %d:%02d:%03d\n",
                   posVR != -1 ? pilotos[posVR].nombre : "N/A",
                   carrera[i].vueltaRapida.minutos,
                   carrera[i].vueltaRapida.segundos,
                   carrera[i].vueltaRapida.milisegundos);
        }
    }
}

void listarCarrerasDePiloto(stCarrera carrera[], int cant, stColeccionPistas *col, int idPiloto, stPiloto pilotos[], int cantPilotos)
{
    if (cant == 0)
    {
        printf("No hay carreras registradas.\n");
        return;
    }

    printf("%-6s %-15s %-20s %-20s %-20s %-20s\n", "ID", "Fecha", "Pista", "1ro", "2ro", "3ro");
    printf("-------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cant; i++)
    {
        if (carrera[i].podio[0] == idPiloto ||
                carrera[i].podio[1] == idPiloto ||
                carrera[i].podio[2] == idPiloto ||
                carrera[i].vueltaRapida.idPiloto == idPiloto)
        {
            // 1. Buscamos la pista y VALIDAMOS que exista (evita el crash si está en 0)
            int posPista = buscarPistaPorId(col, carrera[i].idPista);

            char fecha[15];
            sprintf(fecha, "%02d/%02d/%04d", carrera[i].fecha.dia, carrera[i].fecha.mes, carrera[i].fecha.anio);

            int pos1 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[0]);
            int pos2 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[1]);
            int pos3 = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].podio[2]);

            printf("%-6d %-15s %-20s %-20s %-20s %-20s\n",
                   carrera[i].id,
                   fecha,
                   posPista != -1 ? col->pistas[posPista].nombre : "Desconocida", // Agregada validación aquí
                   pos1 != -1 ? pilotos[pos1].nombre : "N/A",
                   pos2 != -1 ? pilotos[pos2].nombre : "N/A",
                   pos3 != -1 ? pilotos[pos3].nombre : "N/A");
            // 2. Mostrar la vuelta rápida con el nombre del piloto
            if (carrera[i].vueltaRapida.idPiloto == idPiloto)
            {
                // Buscamos la posición del piloto de la vuelta rápida
                int posVR = buscarPilotoPorId(pilotos, cantPilotos, carrera[i].vueltaRapida.idPiloto);

                printf("  Vuelta rapida de %s: %d:%02d:%03d\n",
                       posVR != -1 ? pilotos[posVR].nombre : "Piloto Desconocido", // Muestra el nombre
                       carrera[i].vueltaRapida.minutos,
                       carrera[i].vueltaRapida.segundos,
                       carrera[i].vueltaRapida.milisegundos);
            }
        }
    }
}

int hayChoqueFechas(stCarrera carrera[], int cant, int idPista, stFecha fecha)
{
    for (int i = 0; i < cant; i++)
    {
        if (carrera[i].idPista == idPista &&
                carrera[i].fecha.dia == fecha.dia &&
                carrera[i].fecha.mes == fecha.mes &&
                carrera[i].fecha.anio == fecha.anio)
        {
            return 1;
        }

    }

    return 0;

}

int eliminarCarrera(stCarrera carrera[], int *cant, int id)
{
    int pos = buscarCarreraPorId(carrera, *cant, id);
    if (pos == -1)
    {
        return 0;
    }
    carrera[pos] = carrera[*cant - 1];
    (*cant)--;
    guardarCarreras(carrera, *cant);

    return 1;

}

int modificarCarrera(stCarrera carrera[], int *cant, int id, stCarrera nueva)
{

    int pos = buscarCarreraPorId(carrera, *cant, id);
    if (pos == -1)
    {
        return 0;
    }
    carrera[pos] = nueva;
    guardarCarreras(carrera, *cant);

    return 1;
}
