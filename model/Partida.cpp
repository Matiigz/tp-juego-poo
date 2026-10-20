#include "Partida.h"
#include "Agua.h"
#include "Tierra.h"
#include "Fuego.h"
#include <random>

Partida::Partida(const QString& nombreHumano, TipoIA iaTipo, int cantElementos)
    : humano(nombreHumano), ia("IA Bot"), tipoIA(iaTipo), rondaActual(1), elementosPorJugador(cantElementos) {}

void Partida::inicializarNuevaPartida() {
    humano.limpiarElementos();
    ia.limpiarElementos();
    rondaActual = 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    auto generarElementoRandom = [&](int t) -> std::shared_ptr<Elemento> {
        if (t == 0) return std::make_shared<Agua>();
        if (t == 1) return std::make_shared<Tierra>();
        return std::make_shared<Fuego>();
    };

    for (int i = 0; i < elementosPorJugador; ++i) {
        humano.agregarElemento(generarElementoRandom(dist(gen)));
        ia.agregarElemento(generarElementoRandom(dist(gen)));
    }
}

QString Partida::ejecutarRonda(int indiceElementoHumano) {
    if (estaTerminada()) return "La partida ha finalizado.";

    auto elemHumano = humano.getElementos()[indiceElementoHumano];
    if (!elemHumano->estaVivo()) {
        return "El elemento seleccionado ya no tiene energía activa.";
    }

    auto elemIA = EstrategiaIA::elegirElemento(tipoIA, ia, elemHumano, gestorDanio);
    if (!elemIA) return "La IA no tiene elementos disponibles.";

    double danioA_IA = gestorDanio.calcularDanio(elemHumano->getTipo(), elemIA->getTipo());
    double danioAHumano = gestorDanio.calcularDanio(elemIA->getTipo(), elemHumano->getTipo());

    elemIA->reducirEnergia(danioA_IA);
    elemHumano->reducirEnergia(danioAHumano);

    QString resultado = QString("Ronda %1:\n- Tu %2 causó %3 de daño al %4 enemigo.\n- El %4 enemigo causó %5 de daño a tu %2.\n")
                        .arg(rondaActual)
                        .arg(elemHumano->getNombreTipo())
                        .arg(danioA_IA)
                        .arg(elemIA->getNombreTipo())
                        .arg(danioAHumano);

    if (!elemHumano->estaVivo()) resultado += "-> Tu elemento ha sido eliminado.\n";
    if (!elemIA->estaVivo()) resultado += "-> El elemento de la IA ha sido eliminado.\n";

    rondaActual++;
    return resultado;
}

bool Partida::estaTerminada() const {
    return !humano.tieneElementosVivos() || !ia.tieneElementosVivos();
}

QString Partida::getGanador() const {
    if (!humano.tieneElementosVivos() && !ia.tieneElementosVivos()) return "Empate";
    if (!ia.tieneElementosVivos()) return humano.getNombre();
    if (!humano.tieneElementosVivos()) return ia.getNombre();
    return "En juego";
}