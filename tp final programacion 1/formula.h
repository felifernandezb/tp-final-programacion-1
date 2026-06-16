#ifndef FORMULA_H_INCLUDED
#define FORMULA_H_INCLUDED

#define DIMENSION_INICIAL_PISTAS 25
#define MAX_PILOTOS     48
#define MAX_ESCUDERIAS  24
#define MAX_CARRERAS    35
#define MAX_PODIO       3

// =====================
//   TIPOS Y ESTRUCTURAS
// =====================



typedef struct {
    int dia;
    int mes;
    int anio;
} stFecha;

typedef struct {
    int id;
    char marca[50];
    char sponsor[50];
    int idPiloto1;
    int idPiloto2;
    int categoria;      // 1 = F1, 2 = F2
} stEscuderia;

typedef struct {
    int id;
    char nombre[50];
    int idEscuderia;
    int puntaje;
    int categoria;
} stPiloto;

typedef struct {
    int id;
    char nombre[50];
    float distancia;
    char ubicacion[100];
} stPista;

typedef struct {
    int idPiloto;
    int minutos;
    int segundos;
    int milisegundos;
} stVueltaRapida;

typedef struct {
    int id;
    stFecha fecha;
    int podio[3];       // IDs de pilotos
    int vueltas;
    stVueltaRapida vueltaRapida;
    int idPista;
} stCarrera;

typedef struct {
    stPista *pistas;
    int dimension;
    int validos;
} stColeccionPistas;
#endif // FORMULA_H_INCLUDED
