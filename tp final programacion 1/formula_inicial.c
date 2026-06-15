#include "formula_inicial.h"
#include "formula_pilotos.h"
#include "formula_pistas.h"
#include "formula_carreras.h"
#include <string.h>

void cargarDatosIniciales(stPiloto pilotos[], int *cantPilotos,
                          stEscuderia escuderias[], int *cantEscuderias,
                          stPista pistas[], int *cantPistas,
                          stCarrera carreras[], int *cantCarreras)
{
    // ========================
    // ESCUDERIAS F1
    // ========================
    stEscuderia esc;

    // ESCUDERIAS F1
    esc.categoria = 1;
    esc.id = 1; strcpy(esc.marca, "McLaren");      strcpy(esc.sponsor, "OKX");         esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 2; strcpy(esc.marca, "Ferrari");      strcpy(esc.sponsor, "Shell");        esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 3; strcpy(esc.marca, "Red Bull");     strcpy(esc.sponsor, "Oracle");       esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 4; strcpy(esc.marca, "Mercedes");     strcpy(esc.sponsor, "Petronas");     esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 5; strcpy(esc.marca, "Aston Martin"); strcpy(esc.sponsor, "Aramco");       esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 6; strcpy(esc.marca, "Alpine");       strcpy(esc.sponsor, "BWT");          esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 7; strcpy(esc.marca, "Haas");         strcpy(esc.sponsor, "MoneyGram");    esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 8; strcpy(esc.marca, "Racing Bulls"); strcpy(esc.sponsor, "Visa");         esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id = 9; strcpy(esc.marca, "Williams");     strcpy(esc.sponsor, "Duracell");     esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =10; strcpy(esc.marca, "Audi");         strcpy(esc.sponsor, "Audi");         esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =11; strcpy(esc.marca, "Cadillac");     strcpy(esc.sponsor, "GM");           esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;

    // ESCUDERIAS F2
    esc.categoria = 2;
    esc.id =12; strcpy(esc.marca, "Prema");          strcpy(esc.sponsor, "Prema");      esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =13; strcpy(esc.marca, "Rodin");          strcpy(esc.sponsor, "Rodin");      esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =14; strcpy(esc.marca, "ART Grand Prix"); strcpy(esc.sponsor, "ART");        esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =15; strcpy(esc.marca, "AIX Racing");     strcpy(esc.sponsor, "AIX");        esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =16; strcpy(esc.marca, "Van Amersfoort"); strcpy(esc.sponsor, "VAR");        esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =17; strcpy(esc.marca, "Invicta");        strcpy(esc.sponsor, "Invicta");    esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =18; strcpy(esc.marca, "Hitech");         strcpy(esc.sponsor, "Hitech");     esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =19; strcpy(esc.marca, "Trident");        strcpy(esc.sponsor, "Trident");    esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =20; strcpy(esc.marca, "MP Motorsport");  strcpy(esc.sponsor, "MP");         esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id =21; strcpy(esc.marca, "Campos");         strcpy(esc.sponsor, "Campos");     esc.idPiloto1 = -1; esc.idPiloto2 = -1; escuderias[(*cantEscuderias)++] = esc;
    esc.id=22; strcpy(esc.marca, "DAMS");            strcpy(esc.sponsor, "Lucas Oil");  esc.idPiloto1= -1;  esc.idPiloto2= -1;  escuderias[(*cantEscuderias)++] = esc;
    // ========================
    // PILOTOS F1
    // ========================
    stPiloto p;
    p.puntaje = 0;
    p.categoria = 1;

    p.id= 1; strcpy(p.nombre, "Lando Norris");       p.idEscuderia= 1; escuderias[0].idPiloto1= 1; pilotos[(*cantPilotos)++]=p;
    p.id= 2; strcpy(p.nombre, "Oscar Piastri");      p.idEscuderia= 1; escuderias[0].idPiloto2= 2; pilotos[(*cantPilotos)++]=p;
    p.id= 3; strcpy(p.nombre, "Charles Leclerc");    p.idEscuderia= 2; escuderias[1].idPiloto1= 3; pilotos[(*cantPilotos)++]=p;
    p.id= 4; strcpy(p.nombre, "Lewis Hamilton");     p.idEscuderia= 2; escuderias[1].idPiloto2= 4; pilotos[(*cantPilotos)++]=p;
    p.id= 5; strcpy(p.nombre, "Max Verstappen");     p.idEscuderia= 3; escuderias[2].idPiloto1= 5; pilotos[(*cantPilotos)++]=p;
    p.id= 6; strcpy(p.nombre, "Isack Hadjar");       p.idEscuderia= 3; escuderias[2].idPiloto2= 6; pilotos[(*cantPilotos)++]=p;
    p.id= 7; strcpy(p.nombre, "George Russell");     p.idEscuderia= 4; escuderias[3].idPiloto1= 7; pilotos[(*cantPilotos)++]=p;
    p.id= 8; strcpy(p.nombre, "Kimi Antonelli");     p.idEscuderia= 4; escuderias[3].idPiloto2= 8; pilotos[(*cantPilotos)++]=p;
    p.id= 9; strcpy(p.nombre, "Fernando Alonso");    p.idEscuderia= 5; escuderias[4].idPiloto1= 9; pilotos[(*cantPilotos)++]=p;
    p.id=10; strcpy(p.nombre, "Lance Stroll");       p.idEscuderia= 5; escuderias[4].idPiloto2=10; pilotos[(*cantPilotos)++]=p;
    p.id=11; strcpy(p.nombre, "Pierre Gasly");       p.idEscuderia= 6; escuderias[5].idPiloto1=11; pilotos[(*cantPilotos)++]=p;
    p.id=12; strcpy(p.nombre, "Franco Colapinto");   p.idEscuderia= 6; escuderias[5].idPiloto2=12; pilotos[(*cantPilotos)++]=p;
    p.id=13; strcpy(p.nombre, "Esteban Ocon");       p.idEscuderia= 7; escuderias[6].idPiloto1=13; pilotos[(*cantPilotos)++]=p;
    p.id=14; strcpy(p.nombre, "Ollie Bearman");      p.idEscuderia= 7; escuderias[6].idPiloto2=14; pilotos[(*cantPilotos)++]=p;
    p.id=15; strcpy(p.nombre, "Liam Lawson");        p.idEscuderia= 8; escuderias[7].idPiloto1=15; pilotos[(*cantPilotos)++]=p;
    p.id=16; strcpy(p.nombre, "Arvid Lindblad");     p.idEscuderia= 8; escuderias[7].idPiloto2=16; pilotos[(*cantPilotos)++]=p;
    p.id=17; strcpy(p.nombre, "Alex Albon");         p.idEscuderia= 9; escuderias[8].idPiloto1=17; pilotos[(*cantPilotos)++]=p;
    p.id=18; strcpy(p.nombre, "Carlos Sainz");       p.idEscuderia= 9; escuderias[8].idPiloto2=18; pilotos[(*cantPilotos)++]=p;
    p.id=19; strcpy(p.nombre, "Nico Hulkenberg");    p.idEscuderia=10; escuderias[9].idPiloto1=19; pilotos[(*cantPilotos)++]=p;
    p.id=20; strcpy(p.nombre, "Gabriel Bortoleto");  p.idEscuderia=10; escuderias[9].idPiloto2=20; pilotos[(*cantPilotos)++]=p;
    p.id=21; strcpy(p.nombre, "Sergio Perez");       p.idEscuderia=11; escuderias[10].idPiloto1=21; pilotos[(*cantPilotos)++]=p;
    p.id=22; strcpy(p.nombre, "Valtteri Bottas");    p.idEscuderia=11; escuderias[10].idPiloto2=22; pilotos[(*cantPilotos)++]=p;

    // ========================
    // PILOTOS F2
    // ========================
    p.categoria = 2;

    p.id=23; strcpy(p.nombre, "Sebastian Montoya");  p.idEscuderia=12; escuderias[11].idPiloto1=23; pilotos[(*cantPilotos)++]=p;
    p.id=24; strcpy(p.nombre, "Mari Boya");          p.idEscuderia=12; escuderias[11].idPiloto2=24; pilotos[(*cantPilotos)++]=p;
    p.id=25; strcpy(p.nombre, "Martinius Stenshorne");p.idEscuderia=13; escuderias[12].idPiloto1=25; pilotos[(*cantPilotos)++]=p;
    p.id=26; strcpy(p.nombre, "Alexander Dunne");    p.idEscuderia=13; escuderias[12].idPiloto2=26; pilotos[(*cantPilotos)++]=p;
    p.id=27; strcpy(p.nombre, "Kush Maini");         p.idEscuderia=14; escuderias[13].idPiloto1=27; pilotos[(*cantPilotos)++]=p;
    p.id=28; strcpy(p.nombre, "Tasanapol Inthraphuvasak"); p.idEscuderia=14; escuderias[13].idPiloto2=28; pilotos[(*cantPilotos)++]=p;
    p.id=29; strcpy(p.nombre, "Emerson Fittipaldi Jr."); p.idEscuderia=15; escuderias[14].idPiloto1=29; pilotos[(*cantPilotos)++]=p;
    p.id=30; strcpy(p.nombre, "Cian Shields");       p.idEscuderia=15; escuderias[14].idPiloto2=30; pilotos[(*cantPilotos)++]=p;
    p.id=31; strcpy(p.nombre, "Nicolas Varrone");    p.idEscuderia=16; escuderias[15].idPiloto1=31; pilotos[(*cantPilotos)++]=p;
    p.id=32; strcpy(p.nombre, "Rafael Villagomez");  p.idEscuderia=16; escuderias[15].idPiloto2=32; pilotos[(*cantPilotos)++]=p;
    p.id=33; strcpy(p.nombre, "Rafael Camara");      p.idEscuderia=17; escuderias[16].idPiloto1=33; pilotos[(*cantPilotos)++]=p;
    p.id=34; strcpy(p.nombre, "Joshua Durksen");     p.idEscuderia=17; escuderias[16].idPiloto2=34; pilotos[(*cantPilotos)++]=p;
    p.id=35; strcpy(p.nombre, "Colton Herta");       p.idEscuderia=18; escuderias[17].idPiloto1=35; pilotos[(*cantPilotos)++]=p;
    p.id=36; strcpy(p.nombre, "Laurens van Hoepen"); p.idEscuderia=19; escuderias[18].idPiloto1=36; pilotos[(*cantPilotos)++]=p;
    p.id=37; strcpy(p.nombre, "John Bennett");       p.idEscuderia=19; escuderias[18].idPiloto2=37; pilotos[(*cantPilotos)++]=p;
    p.id=38; strcpy(p.nombre, "Oliver Goether");     p.idEscuderia=20; escuderias[19].idPiloto1=38; pilotos[(*cantPilotos)++]=p;
    p.id=39; strcpy(p.nombre, "Gabriele Mini");      p.idEscuderia=20; escuderias[19].idPiloto2=39; pilotos[(*cantPilotos)++]=p;
    p.id=40; strcpy(p.nombre, "Nikola Tsolov");      p.idEscuderia=21; escuderias[20].idPiloto1=40; pilotos[(*cantPilotos)++]=p;
    p.id=41; strcpy(p.nombre, "Noel Leon");          p.idEscuderia=21; escuderias[20].idPiloto2=41; pilotos[(*cantPilotos)++]=p;
    p.id=42; strcpy(p.nombre, "Ritomo Miyata");      p.idEscuderia=18; escuderias[17].idPiloto2=42; pilotos[(*cantPilotos)++]=p;
    p.id=43; strcpy(p.nombre, "Dino Beganovic");     p.idEscuderia=22; escuderias[21].idPiloto1=43; pilotos[(*cantPilotos)++]=p;
    p.id=44; strcpy(p.nombre, "Roman Bilinski");     p.idEscuderia=22; escuderias[21].idPiloto2=44; pilotos[(*cantPilotos)++]=p;

    // ========================
    // PISTAS (F1 2026)
    // ========================
    stPista pi;

    pi.id= 1; strcpy(pi.nombre, "Albert Park");          strcpy(pi.ubicacion, "Melbourne, Australia");   pi.distancia = 5.278f; pistas[(*cantPistas)++] = pi;
    pi.id= 2; strcpy(pi.nombre, "Shanghai");             strcpy(pi.ubicacion, "Shanghai, China");        pi.distancia = 5.451f; pistas[(*cantPistas)++] = pi;
    pi.id= 3; strcpy(pi.nombre, "Suzuka");               strcpy(pi.ubicacion, "Suzuka, Japon");          pi.distancia = 5.807f; pistas[(*cantPistas)++] = pi;
    pi.id= 4; strcpy(pi.nombre, "Sakhir");               strcpy(pi.ubicacion, "Sakhir, Bahrain");        pi.distancia = 5.412f; pistas[(*cantPistas)++] = pi;
    pi.id= 5; strcpy(pi.nombre, "Jeddah");               strcpy(pi.ubicacion, "Jeddah, Arabia Saudita"); pi.distancia = 6.174f; pistas[(*cantPistas)++] = pi;
    pi.id= 6; strcpy(pi.nombre, "Miami");                strcpy(pi.ubicacion, "Miami, USA");             pi.distancia = 5.412f; pistas[(*cantPistas)++] = pi;
    pi.id= 7; strcpy(pi.nombre, "Circuit Gilles Villeneuve"); strcpy(pi.ubicacion, "Montreal, Canada"); pi.distancia = 4.361f; pistas[(*cantPistas)++] = pi;
    pi.id= 8; strcpy(pi.nombre, "Monaco");               strcpy(pi.ubicacion, "Monaco");                 pi.distancia = 3.337f; pistas[(*cantPistas)++] = pi;
    pi.id= 9; strcpy(pi.nombre, "Barcelona-Catalunya");  strcpy(pi.ubicacion, "Barcelona, Espana");      pi.distancia = 4.657f; pistas[(*cantPistas)++] = pi;
    pi.id=10; strcpy(pi.nombre, "Red Bull Ring");        strcpy(pi.ubicacion, "Spielberg, Austria");     pi.distancia = 4.318f; pistas[(*cantPistas)++] = pi;
    pi.id=11; strcpy(pi.nombre, "Silverstone");          strcpy(pi.ubicacion, "Silverstone, Gran Bretana"); pi.distancia = 5.891f; pistas[(*cantPistas)++] = pi;
    pi.id=12; strcpy(pi.nombre, "Hungaroring");          strcpy(pi.ubicacion, "Budapest, Hungria");      pi.distancia = 4.381f; pistas[(*cantPistas)++] = pi;
    pi.id=13; strcpy(pi.nombre, "Spa-Francorchamps");    strcpy(pi.ubicacion, "Spa, Belgica");           pi.distancia = 7.004f; pistas[(*cantPistas)++] = pi;
    pi.id=14; strcpy(pi.nombre, "Zandvoort");            strcpy(pi.ubicacion, "Zandvoort, Holanda");     pi.distancia = 4.259f; pistas[(*cantPistas)++] = pi;
    pi.id=15; strcpy(pi.nombre, "Monza");                strcpy(pi.ubicacion, "Monza, Italia");          pi.distancia = 5.793f; pistas[(*cantPistas)++] = pi;
    pi.id=16; strcpy(pi.nombre, "Baku");                 strcpy(pi.ubicacion, "Baku, Azerbaiyan");       pi.distancia = 6.003f; pistas[(*cantPistas)++] = pi;
    pi.id=17; strcpy(pi.nombre, "Marina Bay");           strcpy(pi.ubicacion, "Singapur");               pi.distancia = 4.940f; pistas[(*cantPistas)++] = pi;
    pi.id=18; strcpy(pi.nombre, "Circuit of the Americas"); strcpy(pi.ubicacion, "Austin, USA");         pi.distancia = 5.513f; pistas[(*cantPistas)++] = pi;
    pi.id=19; strcpy(pi.nombre, "Autodromo Hermanos Rodriguez"); strcpy(pi.ubicacion, "Mexico DF, Mexico"); pi.distancia = 4.304f; pistas[(*cantPistas)++] = pi;
    pi.id=20; strcpy(pi.nombre, "Interlagos");           strcpy(pi.ubicacion, "Sao Paulo, Brasil");      pi.distancia = 4.309f; pistas[(*cantPistas)++] = pi;
    pi.id=21; strcpy(pi.nombre, "Las Vegas");            strcpy(pi.ubicacion, "Las Vegas, USA");         pi.distancia = 6.201f; pistas[(*cantPistas)++] = pi;
    pi.id=22; strcpy(pi.nombre, "Losail");               strcpy(pi.ubicacion, "Lusail, Qatar");          pi.distancia = 5.380f; pistas[(*cantPistas)++] = pi;
    pi.id=23; strcpy(pi.nombre, "Yas Marina");           strcpy(pi.ubicacion, "Abu Dhabi, EAU");         pi.distancia = 5.281f; pistas[(*cantPistas)++] = pi;
    pi.id=24; strcpy(pi.nombre, "Madrid");               strcpy(pi.ubicacion, "Madrid, Espana");         pi.distancia = 5.500f; pistas[(*cantPistas)++] = pi;

    // ========================
    // GUARDAR TODO
    // ========================
    guardarPilotos(pilotos, *cantPilotos);
    guardarEscuderias(escuderias, *cantEscuderias);
    guardarPista(pistas, *cantPistas);

}
