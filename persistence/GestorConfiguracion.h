#ifndef GESTORCONFIGURACION_H
#define GESTORCONFIGURACION_H

#include "../model/Partida.h"
#include <QString>

class GestorConfiguracion {
public:
    static bool cargarConfiguracion(const QString& rutaArchivo, Partida& partida);
};

#endif // GESTORCONFIGURACION_H