#include <stdio.h>
#include <stdlib.h>
#include "formula_pilotos.h"
#include "formula_pistas.h"
#include "formula_carreras.h"
#include "formula_inicial.h"
#include "scanner.h"

int main()
{
    // Arrays y contadores
    stPiloto    pilotos[MAX_PILOTOS];
    stEscuderia escuderias[MAX_ESCUDERIAS];
    //stPista     pistas[MAX_PISTAS];
    stCarrera   carreras[MAX_CARRERAS];
    int cantPilotos = 0, cantEscuderias = 0, cantPistas = 0, cantCarreras = 0;

    stColeccionPistas colPistas;
    if (!inicializarColeccion(&colPistas))
    {
        printf("Error al inicializar la coleccion de pistas.\n");
        return 1;
    }

    // Cargar datos al arrancar
    cargarPilotos(pilotos, &cantPilotos);
    cargarEscuderias(escuderias, &cantEscuderias);
    cargarPista(&colPistas);
    cargarCarreras(carreras, &cantCarreras);

    if (cantPilotos == 0 && cantEscuderias == 0)
        cargarDatosIniciales(pilotos, &cantPilotos, escuderias, &cantEscuderias, &colPistas, carreras, &cantCarreras);

    int opcion;
    do
    {
        printf("\n=== FORMULA 1 & 2 ===\n");
        printf("1. Pilotos\n");
        printf("2. Escuderias\n");
        printf("3. Pistas\n");
        printf("4. Carreras\n");
        printf("5. Tabla de piloto\n");
        printf("6. Restablecer datos iniciales\n");

        printf("0. Salir\n");
        printf("Opcion: ");
        opcion = scanInt();

        switch (opcion)
        {
        case 1: // submenú pilotos
            int opPiloto;
            do
            {
                printf("\n=== PILOTOS ===\n");
                printf("1. Listar pilotos\n");
                printf("2. Registrar piloto\n");
                printf("3. Modificar piloto\n");
                printf("4. Eliminar piloto\n");
                printf("0. Volver\n");
                printf("Opcion: ");
                opPiloto = scanInt();

                switch (opPiloto)
                {
                case 1:
                {
                    stPiloto copia[MAX_PILOTOS];
                    ordenarPilotosAlfabeticamente(pilotos, cantPilotos, copia);
                    listarPilotos(copia, cantPilotos, escuderias, cantEscuderias);
                    break;
                }
                case 2:
                {
                    if (cantPilotos >= MAX_PILOTOS)
                    {
                        printf("No hay lugar para mas pilotos.\n");
                        break;
                    }

                    stPiloto nuevo;
                    nuevo.id = generarIdPiloto(pilotos, cantPilotos);

                    do
                    {
                        printf("Categoria: (1=F1, 2=F2): ");
                        nuevo.categoria = scanInt();
                        if (nuevo.categoria != 1 && nuevo.categoria != 2)
                            printf("Categoria invalida. Ingrese 1 para F1 o 2 para F2. \n");
                    }
                    while (nuevo.categoria != 1 && nuevo.categoria != 2);

                    if (!hayEscuderiaDisponible(escuderias, cantEscuderias, nuevo.categoria))
                    {
                        printf("No hay escuderias con lugar disponible para esa categoria.\n");
                        break;
                    }

                    listarEscuderiasDisponibles(escuderias, cantEscuderias, nuevo.categoria);

                    printf("Nombre: ");
                    scanString(nuevo.nombre, 50);

                    printf("ID Escuderia: ");
                    nuevo.idEscuderia = scanInt();

                    nuevo.puntaje = 0;

                    int posEsc = buscarEscuderiaPorId(escuderias, cantEscuderias, nuevo.idEscuderia);
                    if (posEsc == -1)
                    {
                        printf("Escuderia no encontrada.\n");
                        break;
                    }
                    if (escuderias[posEsc].categoria != nuevo.categoria)
                    {
                        printf("La escuderia no corresponde a esa categoria.\n");
                        break;
                    }
                    if (escuderias[posEsc].idPiloto1 != -1 && escuderias[posEsc].idPiloto2 != -1)
                    {
                        printf("La escuderia ya tiene dos pilotos.\n");
                        break;
                    }

                    if (escuderias[posEsc].idPiloto1 == -1)
                        escuderias[posEsc].idPiloto1 = nuevo.id;
                    else
                        escuderias[posEsc].idPiloto2 = nuevo.id;

                    if (registrarPiloto(pilotos, &cantPilotos, nuevo))
                        printf("Piloto registrado correctamente.\n");
                    else
                        printf("Error al registrar piloto.\n");
                    break;
                }
                case 3:
                {
                    stPiloto copia[MAX_PILOTOS];
                    ordenarPilotosAlfabeticamente(pilotos, cantPilotos, copia);
                    listarPilotos(copia, cantPilotos, escuderias, cantEscuderias);

                    int id;
                    printf("ID del piloto a modificar: ");
                    id = scanInt();

                    stPiloto actualizado;
                    printf("Nuevo nombre: ");
                    scanString(actualizado.nombre, 50);
                    do
                    {
                        printf("Nueva categoria (1=F1, 2=F2): ");
                        actualizado.categoria = scanInt();
                        if (actualizado.categoria != 1 && actualizado.categoria != 2)
                            printf("Categoria invalida. Ingrese 1 para F1 o 2 para F2. \n");
                    }
                    while (actualizado.categoria != 1 && actualizado.categoria != 2);
                    printf("Nuevo puntaje: ");
                    actualizado.puntaje = scanInt();

                    if (modificarPiloto(pilotos, cantPilotos, id, actualizado))
                        printf("Piloto modificado correctamente.\n");
                    else
                        printf("Piloto no encontrado.\n");
                    break;
                }
                case 4:
                {
                    stPiloto copia[MAX_PILOTOS];
                    ordenarPilotosAlfabeticamente(pilotos, cantPilotos, copia);
                    listarPilotos(copia, cantPilotos, escuderias, cantEscuderias);

                    int id;
                    printf("ID del piloto a eliminar: ");
                    id = scanInt();

                    int pos = buscarPilotoPorId(pilotos, cantPilotos, id);
                    if (pos != -1)
                    {
                        int posEsc = buscarEscuderiaPorId(escuderias, cantEscuderias, pilotos[pos].idEscuderia);
                        if (posEsc != -1)
                        {
                            if (escuderias[posEsc].idPiloto1 == id)
                                escuderias[posEsc].idPiloto1 = -1;
                            else if (escuderias[posEsc].idPiloto2 == id)
                                escuderias[posEsc].idPiloto2 = -1;
                            guardarEscuderias(escuderias, cantEscuderias);
                        }
                    }

                    if (eliminarPiloto(pilotos, &cantPilotos, id))
                        printf("Piloto eliminado correctamente.\n");
                    else
                        printf("Piloto no encontrado.\n");
                    break;
                }
                case 0:
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while (opPiloto != 0);

            break;
        case 2:
        {
            int opEscuderia;
            do
            {
                printf("\n=== ESCUDERIAS ===\n");
                printf("1. Listar escuderias\n");
                printf("2. Registrar escuderia\n");
                printf("3. Modificar escuderia\n");
                printf("4. Eliminar escuderia\n");
                printf("0. Volver\n");
                printf("Opcion: ");
                opEscuderia = scanInt();

                switch (opEscuderia)
                {
                case 1:
                {
                    stEscuderia copia[MAX_ESCUDERIAS];
                    ordenarEscuderiasAlfabeticamente(escuderias, cantEscuderias, copia);
                    listarEscuderias(copia, cantEscuderias, pilotos, cantPilotos);
                    break;
                }
                case 2:
                {
                    if (cantEscuderias >= MAX_ESCUDERIAS)
                    {
                        printf("No hay lugar para mas escuderias.\n");
                        break;
                    }
                    stEscuderia nueva;
                    nueva.id = generarIdEscuderia(escuderias, cantEscuderias);
                    nueva.idPiloto1 = -1;
                    nueva.idPiloto2 = -1;

                    printf("Marca: ");
                    scanString(nueva.marca, 50);
                    printf("Sponsor: ");
                    scanString(nueva.sponsor, 50);
                    do
                    {
                        printf("Categoria: (1=F1, 2=F2): ");
                        nueva.categoria = scanInt();
                        if (nueva.categoria != 1 && nueva.categoria != 2)
                            printf("Categoria invalida. Ingrese 1 para F1 o 2 para F2. \n");
                    }
                    while (nueva.categoria != 1 && nueva.categoria != 2);


                    if (registrarEscuderia(escuderias, &cantEscuderias, nueva))
                        printf("Escuderia registrada correctamente.\n");
                    else
                        printf("Error al registrar escuderia.\n");
                    break;
                }
                case 3:
                {
                    stEscuderia copia[MAX_ESCUDERIAS];
                    ordenarEscuderiasAlfabeticamente(escuderias, cantEscuderias, copia);
                    listarEscuderias(copia, cantEscuderias, pilotos, cantPilotos);

                    int id;
                    printf("ID de la escuderia a modificar: ");
                    id = scanInt();

                    stEscuderia actualizada;
                    printf("Nueva marca: ");
                    scanString(actualizada.marca, 50);
                    printf("Nuevo sponsor: ");
                    scanString(actualizada.sponsor, 50);

                    if (modificarEscuderia(escuderias, cantEscuderias, id, actualizada, pilotos, cantPilotos))
                        printf("Escuderia modificada correctamente.\n");
                    else
                        printf("Escuderia no encontrada.\n");
                    break;
                }
                case 4:
                {
                    stEscuderia copia[MAX_ESCUDERIAS];
                    ordenarEscuderiasAlfabeticamente(escuderias, cantEscuderias, copia);
                    listarEscuderias(copia, cantEscuderias, pilotos, cantPilotos);

                    int id;
                    printf("ID de la escuderia a eliminar: ");
                    id = scanInt();
                    int confirma = -1;
                    while (confirma != 1 && confirma != 0)
                    {
                        printf("Esto eliminara tambien sus pilotos. Confirma? (1=Si, 0=No): ");
                        confirma = scanInt();
                        if (confirma != 1 && confirma != 0)
                            printf("Error, numero no valido, intente nuevamente.\n");

                    }


                    if (confirma == 1)
                    {
                        if (eliminarEscuderia(escuderias, &cantEscuderias, id, pilotos, &cantPilotos))
                            printf("Escuderia eliminada correctamente.\n");
                        else
                            printf("Escuderia no encontrada.\n");
                    }
                    break;
                }
                case 0:
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while (opEscuderia != 0);
            break;
        }
        case 3:
        {
            int opPista;
            do
            {
                printf("\n=== PISTAS ===\n");
                printf("1. Listar pistas\n");
                printf("2. Registrar pista\n");
                printf("3. Modificar pista\n");
                printf("4. Eliminar pista\n");
                printf("0. Volver\n");
                printf("Opcion: ");
                opPista = scanInt();

                switch (opPista)
                {
                case 1:
                {
                    stColeccionPistas copia;
                    inicializarColeccion(&copia);

                    ordenarPistasAlfabeticamente(&colPistas, copia);
                    listarPistas(copia, col->cant);
                    free(&copia);
                    break;
                }
                case 2:
                {
                    if (cantPistas >= MAX_PISTAS)
                    {
                        printf("No hay lugar para mas pistas.\n");
                        break;
                    }
                    stPista nueva;
                    nueva.id = generarIDPista(pistas, cantPistas);

                    printf("Nombre: ");
                    scanString(nueva.nombre, 50);
                    printf("Ubicacion: ");
                    scanString(nueva.ubicacion, 100);

                    do
                    {
                        printf("Distancia (km): ");
                        nueva.distancia = scanFloat();

                        if (nueva.distancia < 0 || nueva.distancia >= 10)
                            printf("Error. La distancia debe ser mayor a 0 y menor que 11.\n");
                    }
                    while (nueva.distancia < 0 || nueva.distancia >= 10);

                    if (registrarPista(pistas, &cantPistas, nueva))
                        printf("Pista registrada correctamente.\n");
                    else
                        printf("Error al registrar pista.\n");
                    break;
                }
                case 3:
                {
                    stPista copia[MAX_PISTAS];
                    ordenarPistasAlfabeticamente(pistas, cantPistas, copia);
                    listarPistas(copia, cantPistas);

                    int id;
                    printf("ID de la pista a modificar: ");
                    id = scanInt();

                    stPista actualizada;
                    printf("Nuevo nombre: ");
                    scanString(actualizada.nombre, 50);
                    printf("Nueva ubicacion: ");
                    scanString(actualizada.ubicacion, 100);
                    do
                    {
                        printf("Nueva distancia (km): ");
                        actualizada.distancia = scanFloat();

                        if (actualizada.distancia < 0 || actualizada.distancia >= 10)
                            printf("Error. La distancia debe ser mayor a 0 y menor que 11.\n");
                    }
                    while (actualizada.distancia < 0 || actualizada.distancia >= 10);

                    if (modificarPista(pistas, cantPistas, id, actualizada))
                        printf("Pista modificada correctamente.\n");
                    else
                        printf("Pista no encontrada.\n");
                    break;
                }
                case 4:
                {
                    stPista copia[MAX_PISTAS];
                    ordenarPistasAlfabeticamente(pistas, cantPistas, copia);
                    listarPistas(copia, cantPistas);

                    int id;
                    printf("ID de la pista a eliminar: ");
                    id = scanInt();

                    if (eliminarPista(pistas, &cantPistas, id))
                        printf("Pista eliminada correctamente.\n");
                    else
                        printf("Pista no encontrada.\n");
                    break;
                }
                case 0:
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while (opPista != 0);
            break;
        }
        case 4:
        {
            int opCarrera;
            do
            {
                printf("\n=== CARRERAS ===\n");
                printf("1. Listar carreras\n");
                printf("2. Registrar carrera\n");
                printf("3. Modificar carrera\n");
                printf("4. Eliminar carrera\n");
                printf("5. Carreras de un piloto\n");
                printf("6. Carreras en una pista\n");
                printf("0. Volver\n");
                printf("Opcion: ");
                opCarrera = scanInt();

                switch (opCarrera)
                {
                case 1:
                {
                    listarCarreras(carreras, cantCarreras, pistas, cantPistas, pilotos, cantPilotos);
                    break;
                }
                case 2:
                {
                    if (cantCarreras >= MAX_CARRERAS)
                    {
                        printf("No hay lugar para mas carreras.\n");
                        break;
                    }

                    stCarrera nueva;
                    nueva.id = generarIdCarrera(carreras, cantCarreras);

                    listarPistas(pistas, cantPistas);
                    nueva.idPista = scanIdPista(pistas, cantPistas);

                    scanFecha(&nueva.fecha);

                    if (hayChoqueFechas(carreras, cantCarreras, nueva.idPista, nueva.fecha))
                    {
                        printf("Ya hay una carrera en esa pista en esa fecha.\n");
                        break;
                    }

                    do
                    {
                        printf("Vueltas: ");
                        nueva.vueltas = scanInt();

                        if (nueva.vueltas < 44 || nueva.vueltas > 78) /// Tomamos de referencia a la carrera con menos vueltas (GP de Bélgica) y la que más tiene (GP de Mónaco).
                            printf("Error. Las vueltas no pueden ser menores que 44 ni mayores a 78.\n");
                    }
                    while (nueva.vueltas < 44 || nueva.vueltas > 78);

                    listarPilotos(pilotos, cantPilotos, escuderias, cantEscuderias);
                    nueva.podio[0] = scanIdPiloto(pilotos, cantPilotos, "ID piloto 1er lugar: ");
                    nueva.podio[1] = scanIdPiloto(pilotos, cantPilotos, "ID piloto 2do lugar: ");
                    nueva.podio[2] = scanIdPiloto(pilotos, cantPilotos, "ID piloto 3er lugar: ");

                    nueva.vueltaRapida.idPiloto = scanIdPiloto(pilotos, cantPilotos, "ID piloto vuelta rapida: ");
                    printf("Tiempo vuelta rapida (min seg ms): ");
                    scanf("%d %d %d", &nueva.vueltaRapida.minutos, /// Aplicamos scanf porque se nos hizo más práctico.
                          &nueva.vueltaRapida.segundos,
                          &nueva.vueltaRapida.milisegundos);

                    int pos1 = buscarPilotoPorId(pilotos, cantPilotos, nueva.podio[0]);
                    int pos2 = buscarPilotoPorId(pilotos, cantPilotos, nueva.podio[1]);
                    int pos3 = buscarPilotoPorId(pilotos, cantPilotos, nueva.podio[2]);
                    int posVR = buscarPilotoPorId(pilotos, cantPilotos, nueva.vueltaRapida.idPiloto);

                    if (pos1 != -1) pilotos[pos1].puntaje += 25;
                    if (pos2 != -1) pilotos[pos2].puntaje += 18;
                    if (pos3 != -1) pilotos[pos3].puntaje += 15;
                    if (posVR != -1) pilotos[posVR].puntaje += 1;

                    guardarPilotos(pilotos, cantPilotos);

                    if (registrarCarrera(carreras, &cantCarreras, nueva))
                        printf("Carrera registrada correctamente.\n");
                    else
                        printf("Error al registrar carrera.\n");
                    break;
                }
                case 3:
                {
                    listarCarreras(carreras, cantCarreras, pistas, cantPistas, pilotos, cantPilotos);

                    printf("ID de la carrera a modificar: ");
                    int id = scanInt();

                    if (buscarCarreraPorId(carreras, cantCarreras, id) == -1)
                    {
                        printf("Carrera no encontrada.\n");
                        break;
                    }

                    stCarrera nueva;
                    nueva.id = id;

                    listarPistas(pistas, cantPistas);
                    nueva.idPista = scanIdPista(pistas, cantPistas);

                    scanFecha(&nueva.fecha);

                    do
                    {
                        printf("Vueltas: ");
                        nueva.vueltas = scanInt();
                        if (nueva.vueltas < 44 || nueva.vueltas > 78)
                            printf("Error. Las vueltas no pueden ser menores que 44 ni mayores a 78.\n");
                    }
                    while (nueva.vueltas < 44 || nueva.vueltas > 78);

                    listarPilotos(pilotos, cantPilotos, escuderias, cantEscuderias);
                    nueva.podio[0] = scanIdPiloto(pilotos, cantPilotos, "ID piloto 1er lugar: ");
                    nueva.podio[1] = scanIdPiloto(pilotos, cantPilotos, "ID piloto 2do lugar: ");
                    nueva.podio[2] = scanIdPiloto(pilotos, cantPilotos, "ID piloto 3er lugar: ");

                    printf("ID piloto vuelta rapida: ");
                    nueva.vueltaRapida.idPiloto = scanInt();
                    printf("Tiempo vuelta rapida (min seg ms): ");
                    scanf("%d %d %d", &nueva.vueltaRapida.minutos, /// Aplicamos scanf porque se nos hizo más práctico.
                          &nueva.vueltaRapida.segundos,
                          &nueva.vueltaRapida.milisegundos);

                    if (modificarCarrera(carreras, &cantCarreras, id, nueva))
                        printf("Carrera modificada correctamente.\n");
                    else
                        printf("Carrera no encontrada.\n");
                    break;
                }
                case 4:
                {
                    listarCarreras(carreras, cantCarreras, pistas, cantPistas, pilotos, cantPilotos);

                    int id;
                    printf("ID de la carrera a eliminar: ");
                    id = scanInt();

                    if (eliminarCarrera(carreras, &cantCarreras, id))
                        printf("Carrera eliminada correctamente.\n");
                    else
                        printf("Carrera no encontrada.\n");
                    break;
                }
                case 5:
                {
                    stPiloto copia[MAX_PILOTOS];
                    ordenarPilotosAlfabeticamente(pilotos, cantPilotos, copia);
                    listarPilotos(copia, cantPilotos, escuderias, cantEscuderias);

                    int id;
                    printf("ID del piloto: ");
                    id = scanInt();

                    if (buscarPilotoPorId(pilotos, cantPilotos, id) == -1)
                    {
                        printf("Piloto no encontrado.\n");
                        break;
                    }

                    listarCarrerasDePiloto(carreras, cantCarreras, pistas, id, cantPistas, pilotos, cantPilotos);
                    break;
                }
                case 6:
                {
                    stPista copia[MAX_PISTAS];
                    ordenarPistasAlfabeticamente(pistas, cantPistas, copia);
                    listarPistas(copia, cantPistas);

                    int id;
                    printf("ID de la pista: ");
                    id = scanInt();

                    if (buscarPistaPorId(pistas, cantPistas, id) == -1)
                    {
                        printf("Pista no encontrada.\n");
                        break;
                    }

                    listarCarrerasDePista(carreras, cantCarreras, pistas, id, cantPistas, pilotos, cantPilotos);
                    break;
                }
                case 0:
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while (opCarrera != 0);
            break;
        }
        case 5:
        {
            int opPuntajes;
            do
            {
                printf("\n=== TABLA DE PUNTAJES ===\n");
                printf("1. Ver tabla en pantalla\n");
                printf("2. Exportar tabla a .txt\n");
                printf("0. Volver\n");
                printf("Opcion: ");
                opPuntajes = scanInt();

                switch (opPuntajes)
                {
                case 1:
                    mostrarTablaDePuntajes(pilotos, cantPilotos, escuderias, cantEscuderias);
                    break;
                case 2:
                    exportarTablaDePuntajes(pilotos, cantPilotos, escuderias, cantEscuderias);
                    break;
                case 0:
                    break;
                default:
                    printf("Opcion invalida.\n");
                }
            }
            while (opPuntajes != 0);
            break;
        }
        case 6:
        {
            cantPilotos = 0;
            cantEscuderias = 0;
            cantPistas = 0;
            cantCarreras = 0;
            cargarDatosIniciales(pilotos, &cantPilotos, escuderias, &cantEscuderias, pistas, &cantPistas, carreras, &cantCarreras);
            printf("Datos iniciales restablecidos.\n");
            break;

        }

        case 0:
            printf("Saliendo del gestor de Formula 1...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }
    }
    while (opcion != 0);

    free(colPistas.pistas);

    return 0;
}
