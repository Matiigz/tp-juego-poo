#ifndef GESTORPERSISTENCIA_H
#define GESTORPERSISTENCIA_H

#include "../model/Partida.h"
#include <QString>

class GestorPersistencia {
public:
    static bool guardarPartida(const QString& rutaArchivo, const Partida& partida);
    static bool cargarPartida(const QString& rutaArchivo, Partida& partida);
};

#endif // GESTORPERSISTENCIA_H