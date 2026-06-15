#include <stdio.h>
#include <stdlib.h>
#include "formula_pilotos.h"
#include "formula_pistas.h"
#include "formula_carreras.h"
#include "formula_inicial.h"

int main()
{
    // Arrays y contadores
    stPiloto    pilotos[MAX_PILOTOS];
    stEscuderia escuderias[MAX_ESCUDERIAS];
    stPista     pistas[MAX_PISTAS];
    stCarrera   carreras[MAX_CARRERAS];
    int cantPilotos = 0, cantEscuderias = 0, cantPistas = 0, cantCarreras = 0;

    // Cargar datos al arrancar
    cargarPilotos(pilotos, &cantPilotos);
    cargarEscuderias(escuderias, &cantEscuderias);
    cargarPista(pistas, &cantPistas);
    cargarCarreras(carreras, &cantCarreras);

    if (cantPilotos == 0 && cantEscuderias == 0)
        cargarDatosIniciales(pilotos, &cantPilotos, escuderias, &cantEscuderias, pistas, &cantPistas, carreras, &cantCarreras);

    int opcion;
    do
    {
        printf("\n=== FORMULA 1 & 2 ===\n");
        printf("1. Pilotos\n");
        printf("2. Escuderias\n");
        printf("3. Pistas\n");
        printf("4. Carreras\n");
        printf("5. Restablecer datos iniciales\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

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
                scanf("%d", &opPiloto);

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

                    printf("Categoria (1=F1, 2=F2): ");
                    scanf("%d", &nuevo.categoria);

                    if (!hayEscuderiaDisponible(escuderias, cantEscuderias, nuevo.categoria))
                    {
                        printf("No hay escuderias con lugar disponible para esa categoria.\n");
                        break;
                    }

                    listarEscuderiasDisponibles(escuderias, cantEscuderias, nuevo.categoria);

                    printf("Nombre: ");
                    scanf(" %49[^\n]", nuevo.nombre);

                    printf("ID Escuderia: ");
                    scanf("%d", &nuevo.idEscuderia);

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
                    scanf("%d", &id);

                    stPiloto actualizado;
                    printf("Nuevo nombre: ");
                    scanf(" %49[^\n]", actualizado.nombre);
                    printf("Nueva categoria (1=F1, 2=F2): ");
                    scanf("%d", &actualizado.categoria);
                    printf("Nuevo puntaje: ");
                    scanf("%d", &actualizado.puntaje);

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
                    scanf("%d", &id);

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
                scanf("%d", &opEscuderia);

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
                    scanf(" %49[^\n]", nueva.marca); // lee hasta 49 caracteres ([^\n] significa "todo hasta que encuentre un enter")
                    printf("Sponsor: ");
                    scanf(" %49[^\n]", nueva.sponsor);
                    printf("Categoria: ");
                    scanf("%d\n", nueva.categoria);

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
                    scanf("%d", &id);

                    stEscuderia actualizada;
                    printf("Nueva marca: ");
                    scanf(" %49[^\n]", actualizada.marca);
                    printf("Nuevo sponsor: ");
                    scanf(" %49[^\n]", actualizada.sponsor);

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
                    scanf("%d", &id);

                    printf("Esto eliminara tambien sus pilotos. Confirma? (1=Si, 0=No): ");
                    int confirma;
                    scanf("%d", &confirma);

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
        break;
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
                scanf("%d", &opPista);

                switch (opPista)
                {
                case 1:
                {
                    stPista copia[MAX_PISTAS];
                    ordenarPistasAlfabeticamente(pistas, cantPistas, copia);
                    listarPistas(copia, cantPistas);
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
                    scanf(" %49[^\n]", nueva.nombre);
                    printf("Ubicacion: ");
                    scanf(" %99[^\n]", nueva.ubicacion);
                    printf("Distancia (km): ");
                    scanf("%f", &nueva.distancia);

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
                    scanf("%d", &id);

                    stPista actualizada;
                    printf("Nuevo nombre: ");
                    scanf(" %49[^\n]", actualizada.nombre);
                    printf("Nueva ubicacion: ");
                    scanf(" %99[^\n]", actualizada.ubicacion);
                    printf("Nueva distancia (km): ");
                    scanf("%f", &actualizada.distancia);

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
                    scanf("%d", &id);

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
                scanf("%d", &opCarrera);

                switch (opCarrera)
                {
                case 1:
                {
                    listarCarreras(carreras, cantCarreras, pistas, cantPistas, pilotos);
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
                    printf("ID de la pista: ");
                    scanf("%d", &nueva.idPista);

                    if (buscarPistaPorId(pistas, cantPistas, nueva.idPista) == -1)
                    {
                        printf("Pista no encontrada.\n");
                        break;
                    }

                    printf("Fecha (dia mes anio): ");
                    scanf("%d %d %d", &nueva.fecha.dia, &nueva.fecha.mes, &nueva.fecha.anio);

                    if (hayChoqueFechas(carreras, cantCarreras, nueva.idPista, nueva.fecha))
                    {
                        printf("Ya hay una carrera en esa pista en esa fecha.\n");
                        break;
                    }

                    printf("Vueltas: ");
                    scanf("%d", &nueva.vueltas);

                    listarPilotos(pilotos, cantPilotos, escuderias, cantEscuderias);
                    printf("ID piloto 1er lugar: ");
                    scanf("%d", &nueva.podio[0]);
                    printf("ID piloto 2do lugar: ");
                    scanf("%d", &nueva.podio[1]);
                    printf("ID piloto 3er lugar: ");
                    scanf("%d", &nueva.podio[2]);

                    printf("ID piloto vuelta rapida: ");
                    scanf("%d", &nueva.vueltaRapida.idPiloto);
                    printf("Tiempo vuelta rapida (min seg ms): ");
                    scanf("%d %d %d", &nueva.vueltaRapida.minutos,
                          &nueva.vueltaRapida.segundos,
                          &nueva.vueltaRapida.milisegundos);

                    if (registrarCarrera(carreras, &cantCarreras, nueva))
                        printf("Carrera registrada correctamente.\n");
                    else
                        printf("Error al registrar carrera.\n");
                    break;
                }
                case 3:
                {
                    listarCarreras(carreras, cantCarreras, pistas, cantPistas, pilotos);

                    int id;
                    printf("ID de la carrera a modificar: ");
                    scanf("%d", &id);

                    stCarrera nueva;
                    listarPistas(pistas, cantPistas);
                    printf("ID de la pista: ");
                    scanf("%d", &nueva.idPista);
                    printf("Fecha (dia mes anio): ");
                    scanf("%d %d %d", &nueva.fecha.dia, &nueva.fecha.mes, &nueva.fecha.anio);
                    printf("Vueltas: ");
                    scanf("%d", &nueva.vueltas);

                    listarPilotos(pilotos, cantPilotos, escuderias, cantEscuderias);
                    printf("ID piloto 1er lugar: ");
                    scanf("%d", &nueva.podio[0]);
                    printf("ID piloto 2do lugar: ");
                    scanf("%d", &nueva.podio[1]);
                    printf("ID piloto 3er lugar: ");
                    scanf("%d", &nueva.podio[2]);

                    printf("ID piloto vuelta rapida: ");
                    scanf("%d", &nueva.vueltaRapida.idPiloto);
                    printf("Tiempo vuelta rapida (min seg ms): ");
                    scanf("%d %d %d", &nueva.vueltaRapida.minutos,
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
                    listarCarreras(carreras, cantCarreras, pistas, cantPistas, pilotos);

                    int id;
                    printf("ID de la carrera a eliminar: ");
                    scanf("%d", &id);

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
                    scanf("%d", &id);

                    if (buscarPilotoPorId(pilotos, cantPilotos, id) == -1)
                    {
                        printf("Piloto no encontrado.\n");
                        break;
                    }

                    listarCarrerasDePiloto(carreras, cantCarreras, pistas, id, cantPistas);
                    break;
                }
                case 6:
                {
                    stPista copia[MAX_PISTAS];
                    ordenarPistasAlfabeticamente(pistas, cantPistas, copia);
                    listarPistas(copia, cantPistas);

                    int id;
                    printf("ID de la pista: ");
                    scanf("%d", &id);

                    if (buscarPistaPorId(pistas, cantPistas, id) == -1)
                    {
                        printf("Pista no encontrada.\n");
                        break;
                    }

                    listarCarrerasDePista(carreras, cantCarreras, pistas, id, cantPistas);
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
            cargarDatosIniciales(pilotos, &cantPilotos, escuderias, &cantEscuderias, pistas, &cantPistas, carreras, &cantCarreras);
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }
    }
    while (opcion != 0);
    return 0;
}
