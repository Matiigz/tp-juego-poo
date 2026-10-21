#ifndef PARTIDA_H
#define PARTIDA_H

#include "Jugador.h"
#include "GestorDanio.h"
#include "EstrategiaIA.h"
#include <memory>

enum class ModoJuego { COMUN, MIXTO };

class Partida {
private:
    Jugador humano;
    Jugador ia;
    GestorDanio gestorDanio;
    TipoIA tipoIA;
    ModoJuego modoJuego;
    int rondaActual;
    int elementosPorJugador;

public:
    Partida(const QString& nombreHumano = "Humano", TipoIA iaTipo = TipoIA::ESTRATEGICA, int cantElementos = 5);

    void inicializarNuevaPartida();
    QString ejecutarRonda(int indiceElementoHumano);

    Jugador& getHumano() { return humano; }
    Jugador& getIA() { return ia; }
    const GestorDanio& getGestorDanio() const { return gestorDanio; }
    GestorDanio& getGestorDanioRef() { return gestorDanio; }

    TipoIA getTipoIA() const { return tipoIA; }
    void setTipoIA(TipoIA t) { tipoIA = t; }

    ModoJuego getModoJuego() const { return modoJuego; }
    void setModoJuego(ModoJuego m) { modoJuego = m; }

    int getRonda() const { return rondaActual; }
    void setRonda(int r) { rondaActual = r; }

    int getElementosPorJugador() const { return elementosPorJugador; }
    void setElementosPorJugador(int e) { elementosPorJugador = e; }

    bool estaTerminada() const;
    QString getGanador() const;
};

#endif // PARTIDA_H