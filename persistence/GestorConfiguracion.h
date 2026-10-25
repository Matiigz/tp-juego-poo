#ifndef GESTORCONFIGURACION_H
#define GESTORCONFIGURACION_H

#include "../model/Partida.h"
#include <QString>

class GestorConfiguracion {
public:
    static bool cargarConfiguracion(const QString& rutaArchivo, Partida& partida);


    static void guardarParametrosPorDefecto(const QString& rutaArchivo, const QString& nombreJugador, int modoIA, int modoJuego, int cantidadCartas);
};

#endif // GESTORCONFIGURACION_H