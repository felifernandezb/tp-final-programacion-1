#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "formula_pilotos.h"
#include "formula_pistas.h"

/**
 * @brief funcion auxiliar que limpia el buffer de entrada
 * todas las funciones de esta librería dejan el buffer de entrada limpio
 * es decir que ninguna función provocará que la siguiente entrada por teclado
 * sea omitida.
 */
void limpiarBuferDeEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief funcion utilitaria para verificar si una precondicion
 * es igual a una postcondicion.
 * Es util para sentencias como while (confirmar('s'))
 * o if (confirmar('n')), etc
 * @return 1 o 0 dependiendo si la condicion es igual al dato escaneado por teclado
 */
int confirmar(char condicion)
{
    char aux = '\0';
    scanf("%c", &aux);
    limpiarBuferDeEntrada();
    return tolower(aux) == tolower(condicion);
}

/**
 * @brief abstracción de scanf para datos de tipo int
 * @return el dato escaneado por teclado
 */
int scanInt(void)
{
    int aux = 0;
    scanf("%d", &aux);
    limpiarBuferDeEntrada();
    return aux;
}

/**
 * @brief abstracción de scanf para datos de tipo char
 * @return el dato escaneado por teclado
 */
char scanChar(void)
{
    char aux = 0;
    scanf(" %c", &aux);
    limpiarBuferDeEntrada();
    return aux;
}

/**
 * @brief abstracción de scanf para datos de tipo float
 * @return el dato escaneado por teclado
 */
float scanFloat(void)
{
    float aux = 0;
    while (scanf("%f", &aux) != 1)
    {
        limpiarBuferDeEntrada();
        printf("Ingrese un numero valido: ");
    }
    limpiarBuferDeEntrada();
    return aux;
}

/**
 * @brief abstraccion de la funcion fgets que permite controlar la dimension
 * de la cadena que ingresa por teclado.
 * Garantiza que el string no termine con un salto de linea,
 * efecto conocido e indeseable de fgets.
 * Permite que ingrese una cadena vacía
 * @param string cadena sobre la cual guardar lo escaneado por teclado
 * @param maxLength dimension máxima de la cadena
 * @return la longitud de la cadena escaneada, puede ser mayor o igual a cero
 */
int scanString(char* string, int maxLength)
{
    if (fgets(string, maxLength, stdin) == NULL)
    {
        return -1;
    }
    int ult = strlen(string) - 1;
    if (string[ult] == '\n')
    {
        string[ult] = '\0';
    }
    else
    {
        limpiarBuferDeEntrada();
    }
    return strlen(string);
}

void scanFecha(stFecha *fecha)
{
    printf("Fecha (dia mes anio): ");
    char buffer[30];
    fgets(buffer, 30, stdin);

    if (sscanf(buffer, "%d %d %d", &fecha->dia, &fecha->mes, &fecha->anio) != 3)
    {
        printf("Formato invalido. Ingrese dia, mes y anio separados por espacios.\n");
        scanFecha(fecha);
        return;
    }

    if (fecha->dia  < 1  || fecha->dia  > 31  ||
            fecha->mes  < 1  || fecha->mes  > 12  ||
            fecha->anio < 1894 || fecha->anio > 9999)
    {
        printf("Fecha invalida. El dia debe ser 1-31, el mes 1-12 y el anio debe tener exactamente 4 digitos.\n");
        scanFecha(fecha);
        return;
    }
}

int scanIdPiloto(stPiloto pilotos[], int cantPilotos, char* mensaje)
{
    int id;
    do
    {
        printf("%s", mensaje);
        id = scanInt();
        if (buscarPilotoPorId(pilotos, cantPilotos, id) == -1)
            printf("Piloto no encontrado. Ingrese un ID valido.\n");
    }
    while (buscarPilotoPorId(pilotos, cantPilotos, id) == -1);
    return id;
}

int scanIdPista(stColeccionPistas *col)
{
    int id;
    do
    {
        printf("ID de la pista: ");
        id = scanInt();

        if (buscarPistaPorId(col, id) == -1)
            printf("Pista no encontrada. Ingrese un ID valido.\n");
    }
    while (buscarPistaPorId(col, id) == -1);

    return id;
}

void scanVueltaRapida(stVueltaRapida *vueltaRapida)
{
    char buffer[30];
    fgets(buffer, 30, stdin);
    if (sscanf(buffer, "%d %d %d", &vueltaRapida->minutos, &vueltaRapida->segundos, &vueltaRapida->milisegundos) != 3)
    {
        printf("Formato invalido. Ingrese minutos, segundos y milisegundos separados por espacios.\n");
        scanVueltaRapida(vueltaRapida);
        return;
    }

    if (vueltaRapida->minutos < 0 || vueltaRapida->minutos > 60 ||
        vueltaRapida->segundos < 0 || vueltaRapida->segundos > 60 ||
        vueltaRapida->milisegundos < 0 || vueltaRapida->milisegundos > 999)
    {
        printf("Tiempo invalido. Los minutos y segundos deben estar entre 0-60, milisegundos 0-999.\n");
        scanVueltaRapida(vueltaRapida);
        return;
    }
}
