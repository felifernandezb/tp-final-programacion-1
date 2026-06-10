#ifndef FORMULA_H_INCLUDED
#define FORMULA_H_INCLUDED

// =====================
//   TIPOS Y ESTRUCTURAS
// =====================

typedef struct {
    int dia;
    int mes;
    int anio;
} stFecha;

typedef struct {
    char marca[50];
    char sponsor[50];
    int idPiloto1;
    int idPiloto2;
} stEscuderia;

typedef struct {
    int id;
    char nombre[50];
    stEscuderia escuderia;
    int puntaje;
    int categoria;  // 1 = F1, 2 = F2
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

#endif // FORMULA_H_INCLUDED
