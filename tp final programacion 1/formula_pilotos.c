#include "formula_pilotos.h"
#include <stdio.h>
#include <string.h>

// =================
// FUNCIONES PILOTOS
// =================

int buscarPilotoPorId(stPiloto pilotos[], int cant, int id)
{
    for (int i = 0; i < cant; i++)
    {
        if (pilotos[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

int generarIdPiloto(stPiloto pilotos[], int cant)
{
    int maxId = 0;
    for (int i = 0; i < cant; i++)
    {
        if (pilotos[i].id > maxId)
        {
            maxId = pilotos[i].id;
        }
    }
    return maxId + 1;
}

int registrarPiloto(stPiloto pilotos[], int *cant, stPiloto nuevo)
{
    // Verificar que el ID no exista ya
    if (buscarPilotoPorId(pilotos, *cant, nuevo.id) != -1)
        return 0;

    // Agregar al final del array e incrementar cantidad
    pilotos[*cant] = nuevo;
    (*cant)++;

    // Persistir cambios en el archivo
    guardarPilotos(pilotos, *cant);

    return 1;
}

int eliminarPiloto(stPiloto pilotos[], int *cant, int id)
{
    // Buscar la posición del piloto
    int pos = buscarPilotoPorId(pilotos, *cant, id);

    // Si no existe, devolver 0
    if (pos == -1)
        return 0;

    // Pisar la posición con todos los elementos siguientes
    for (int i = pos; i < *cant - 1; i++)
    {
        pilotos[i] = pilotos[i + 1];
    }

    // Decrementar cantidad
    (*cant)--;

    // Persistir cambios en el archivo
    guardarPilotos(pilotos, *cant);

    return 1;
}

void ordenarPilotosAlfabeticamente(stPiloto pilotos[], int cant, stPiloto resultado[])
{
    // Copiar el array original al resultado
    for (int i = 0; i < cant; i++)
    {
        resultado[i] = pilotos[i];
    }

    // Bubble sort por nombre
    for (int i = 0; i < cant - 1; i++)
    {
        for (int j = 0; j < cant - i - 1; j++)
        {
            if (strcmp(resultado[j].nombre, resultado[j + 1].nombre) > 0)
            {
                stPiloto temp = resultado[j];
                resultado[j] = resultado[j + 1];
                resultado[j + 1] = temp;
            }
        }
    }
}

void listarPilotos(stPiloto pilotos[], int cant, stEscuderia escuderias[], int cantEscuderias)
{
    if (cant == 0)
    {
        printf("No hay pilotos registrados.\n");
        return;
    }

    printf("%-5s %-30s %-20s %-10s %-10s\n", "ID", "Nombre", "Escuderia", "Puntaje", "Categoria");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < cant; i++)
    {
        int posEsc = buscarEscuderiaPorId(escuderias, cantEscuderias, pilotos[i].idEscuderia);

        printf("%-5d %-30s %-20s %-10d %-10s\n",
               pilotos[i].id,
               pilotos[i].nombre,
               posEsc != -1 ? escuderias[posEsc].marca : "N/A",
               pilotos[i].puntaje,
               pilotos[i].categoria == 1 ? "F1" : "F2");
    }
}

void guardarPilotos(stPiloto pilotos[], int cant)
{
    FILE *archivo = fopen("pilotos.dat", "wb");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de pilotos.\n");
        return;
    }

    // Primero guardamos la cantidad, después los pilotos
    fwrite(&cant, sizeof(int), 1, archivo);

    for (int i = 0; i < cant; i++)
    {
        fwrite(&pilotos[i], sizeof(stPiloto), 1, archivo);
    }

    fclose(archivo);
}

void cargarPilotos(stPiloto pilotos[], int *cant)
{
    FILE *archivo = fopen("pilotos.dat", "rb");

    // Si no existe el archivo, arrancamos con array vacío
    if (archivo == NULL)
    {
        *cant = 0;
        return;
    }

    // Primero leemos la cantidad, después los pilotos
    fread(cant, sizeof(int), 1, archivo);

    for (int i = 0; i < *cant; i++)
    {
        fread(&pilotos[i], sizeof(stPiloto), 1, archivo);
    }

    fclose(archivo);
}

int modificarPiloto(stPiloto pilotos[], int cant, int id, stPiloto actualizado)
{
    // Buscar la posición del piloto
    int pos = buscarPilotoPorId(pilotos, cant, id);
    // Si no existe, devolver 0
    if (pos == -1)
        return 0;

    // Conservar tanto el ID original como el ID de la escudería original y reemplazar el resto
    actualizado.id = id;
    actualizado.idEscuderia = pilotos[pos].idEscuderia;

    pilotos[pos] = actualizado;

    // Persistir cambios en el archivo
    guardarPilotos(pilotos, cant);

    return 1;
}

int modificarPilotoCompleto(stPiloto pilotos[], int cantPilotos, stEscuderia escuderias[], int cantEscuderias, int id, stPiloto actualizado)
{
    int pos = buscarPilotoPorId(pilotos, cantPilotos, id);
    if (pos == -1)
        return 0;

    int mismaEscuderia = (pilotos[pos].idEscuderia == actualizado.idEscuderia);

    int posEscNueva = buscarEscuderiaPorId(escuderias, cantEscuderias, actualizado.idEscuderia);
    if (posEscNueva == -1)
        return -1;
    if (escuderias[posEscNueva].categoria != actualizado.categoria)
        return -2;

    // Solo validar cupo si es una escudería distinta
    if (!mismaEscuderia)
    {
        if (escuderias[posEscNueva].idPiloto1 != -1 && escuderias[posEscNueva].idPiloto2 != -1)
            return -3;

        // Liberar lugar en escudería anterior
        int posEscVieja = buscarEscuderiaPorId(escuderias, cantEscuderias, pilotos[pos].idEscuderia);
        if (posEscVieja != -1)
        {
            if (escuderias[posEscVieja].idPiloto1 == id)
                escuderias[posEscVieja].idPiloto1 = -1;
            else if (escuderias[posEscVieja].idPiloto2 == id)
                escuderias[posEscVieja].idPiloto2 = -1;
        }

        // Asignar a nueva escudería
        if (escuderias[posEscNueva].idPiloto1 == -1)
            escuderias[posEscNueva].idPiloto1 = id;
        else
            escuderias[posEscNueva].idPiloto2 = id;

        guardarEscuderias(escuderias, cantEscuderias);
    }

    modificarPiloto(pilotos, cantPilotos, id, actualizado);
    return 1;
}

// ====================
// FUNCIONES ESCUDERIAS
// ====================

int listarEscuderiasDisponibles(stEscuderia escuderias[], int cant, int categoria, int idEscudActual)
{
    int contador = 0;
    printf("%-5s %-30s %-20s %-10s\n", "ID", "Marca", "Sponsor", "Lugares");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < cant; i++)
    {
        if (escuderias[i].categoria != categoria)
            continue;


        int lugares = 0;
        int esSuEscuderia = (escuderias[i].id == idEscudActual);
        if (escuderias[i].idPiloto1 == -1) lugares++;
        if (escuderias[i].idPiloto2 == -1) lugares++;

        if (lugares > 0)
            printf("%-5d %-30s %-20s %-10d\n",
                   escuderias[i].id,
                   escuderias[i].marca,
                   escuderias[i].sponsor,
                   lugares);
        else if (esSuEscuderia)
            printf("%-5d %-30s %-20s %-10s\n",
                   escuderias[i].id,
                   escuderias[i].marca,
                   escuderias[i].sponsor,
                   "actual");
                   contador++;
    }
    return contador;
}

int generarIdEscuderia(stEscuderia escuderias[], int cant)
{
    int maxId = 0;
    for (int i = 0; i < cant; i++)
    {
        if (escuderias[i].id > maxId)
            maxId = escuderias[i].id;
    }
    return maxId + 1;
}

int hayEscuderiaDisponible(stEscuderia escuderias[], int cant, int categoria)
{
    for (int i = 0; i < cant; i++)
    {
        if (escuderias[i].categoria != categoria)
            continue;
        if (escuderias[i].idPiloto1 == -1 || escuderias[i].idPiloto2 == -1)
            return 1;
    }
    return 0;
}

void listarEscuderias(stEscuderia escuderias[], int cant, stPiloto pilotos[], int cantPilotos)
{
    if (cant == 0)
    {
        printf("No hay escuderias registradas.\n");
        return;
    }

    printf("%-5s %-20s %-20s %-10s %-10s\n", "ID", "Marca", "Sponsor", "Categoria", "Lugares");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < cant; i++)
    {
        int lugares = 0;
        if (escuderias[i].idPiloto1 == -1) lugares++;
        if (escuderias[i].idPiloto2 == -1) lugares++;

        printf("%-5d %-20s %-20s %-10s %-10d\n",
               escuderias[i].id,
               escuderias[i].marca,
               escuderias[i].sponsor,
               escuderias[i].categoria == 1 ? "F1" : "F2",
               lugares);
    }
}

int buscarEscuderiaPorId(stEscuderia escuderias[], int cant, int id)
{
    for (int i = 0; i < cant; i++)
    {
        if (escuderias[i].id == id)
            return i;
    }
    return -1;
}

int registrarEscuderia(stEscuderia escuderias[], int *cant, stEscuderia nueva)
{
    // Verificar que no se supere el máximo
    if (*cant >= MAX_ESCUDERIAS)
        return 0;

    // Verificar que el ID no exista ya
    if (buscarEscuderiaPorId(escuderias, *cant, nueva.id) != -1)
        return 0;

    // Asegurarse que los lugares estén vacíos
    nueva.idPiloto1 = -1;
    nueva.idPiloto2 = -1;

    // Agregar al final del array e incrementar cantidad
    escuderias[*cant] = nueva;
    (*cant)++;

    // Persistir cambios en el archivo
    guardarEscuderias(escuderias, *cant);

    return 1;
}

// Esta función no permite cambiar la categoría porque rompería la consistencia con los pilotos asignados.
int modificarEscuderia(stEscuderia escuderias[], int cant, int id, stEscuderia actualizada, stPiloto pilotos[], int cantPilotos)
{
    // Buscar la posición de la escudería
    int pos = buscarEscuderiaPorId(escuderias, cant, id);

    // Si no existe, devolver 0
    if (pos == -1)
        return 0;

    // Conservar ID y pilotos, solo actualizar marca y sponsor
    escuderias[pos].marca[0] = '\0';
    escuderias[pos].sponsor[0] = '\0';
    strcpy(escuderias[pos].marca, actualizada.marca);
    strcpy(escuderias[pos].sponsor, actualizada.sponsor);

    // Persistir cambios en el archivo
    guardarEscuderias(escuderias, cant);

    return 1;
}

int eliminarEscuderia(stEscuderia escuderias[], int *cant, int id, stPiloto pilotos[], int *cantPilotos)
{
    // Buscar la posición de la escudería
    int pos = buscarEscuderiaPorId(escuderias, *cant, id);

    // Si no existe, devolver 0
    if (pos == -1)
        return 0;

    // Eliminar los pilotos asignados
    if (escuderias[pos].idPiloto1 != -1)
        eliminarPiloto(pilotos, cantPilotos, escuderias[pos].idPiloto1);

    if (escuderias[pos].idPiloto2 != -1)
        eliminarPiloto(pilotos, cantPilotos, escuderias[pos].idPiloto2);

    // Correr los elementos siguientes una posición hacia atrás
    for (int i = pos; i < *cant - 1; i++)
    {
        escuderias[i] = escuderias[i + 1];
    }

    // Decrementar cantidad
    (*cant)--;

    // Persistir cambios en el archivo
    guardarEscuderias(escuderias, *cant);

    return 1;
}

void ordenarEscuderiasAlfabeticamente(stEscuderia escuderias[], int cant, stEscuderia resultado[])
{
    // Copiar el array original al resultado
    for (int i = 0; i < cant; i++)
    {
        resultado[i] = escuderias[i];
    }

    // Bubble sort por marca
    for (int i = 0; i < cant - 1; i++)
    {
        for (int j = 0; j < cant - i - 1; j++)
        {
            if (strcmp(resultado[j].marca, resultado[j + 1].marca) > 0)
            {
                stEscuderia temp = resultado[j];
                resultado[j] = resultado[j + 1];
                resultado[j + 1] = temp;
            }
        }
    }
}

void guardarEscuderias(stEscuderia escuderias[], int cant)
{
    FILE *archivo = fopen("escuderias.dat", "wb");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de escuderias.\n");
        return;
    }

    fwrite(&cant, sizeof(int), 1, archivo);

    for (int i = 0; i < cant; i++)
    {
        fwrite(&escuderias[i], sizeof(stEscuderia), 1, archivo);
    }

    fclose(archivo);
}

void cargarEscuderias(stEscuderia escuderias[], int *cant)
{
    FILE *archivo = fopen("escuderias.dat", "rb");

    if (archivo == NULL)
    {
        *cant = 0;
        return;
    }

    fread(cant, sizeof(int), 1, archivo);

    for (int i = 0; i < *cant; i++)
    {
        fread(&escuderias[i], sizeof(stEscuderia), 1, archivo);
    }

    fclose(archivo);
}
