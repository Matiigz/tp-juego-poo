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
    if (estaTerminada()) return "<span style='color: gray;'>La partida ha finalizado.</span>";

    auto elemHumano = humano.getElementos()[indiceElementoHumano];
    if (!elemHumano->estaVivo()) {
        return "<span style='color: #e67e22;'>⚠️ El elemento seleccionado ya no tiene energía activa. Elige otro.</span>";
    }

    auto elemIA = EstrategiaIA::elegirElemento(tipoIA, ia, elemHumano, gestorDanio);
    if (!elemIA) return "<span style='color: gray;'>La IA no tiene elementos disponibles.</span>";

    // Calcular los daños
    double danioA_IA = gestorDanio.calcularDanio(elemHumano->getTipo(), elemIA->getTipo());
    double danioAHumano = gestorDanio.calcularDanio(elemIA->getTipo(), elemHumano->getTipo());

    // Aplicar daños
    elemIA->reducirEnergia(danioA_IA);
    elemHumano->reducirEnergia(danioAHumano);

    // Texto enriquecido (HTML) para darle color y emojis al log
    QString resultado = QString("<b>⚔️ Ronda %1:</b><br>"
                                "<span style='color: #27ae60;'>🟢 Tu %2 atacó causando <b>%3</b> de daño.</span><br>"
                                "<span style='color: #c0392b;'>🔴 El %4 de la IA respondió con <b>%5</b> de daño.</span><br>")
                            .arg(rondaActual)
                            .arg(elemHumano->getNombreTipo())
                            .arg(danioA_IA)
                            .arg(elemIA->getNombreTipo())
                            .arg(danioAHumano);

    // Avisos de eliminación
    if (!elemHumano->estaVivo()) {
        resultado += "<i><span style='color: #7f8c8d;'>☠️ Tu elemento ha sido eliminado.</span></i><br>";
    }
    if (!elemIA->estaVivo()) {
        resultado += "<i><span style='color: #7f8c8d;'>☠️ El elemento de la IA ha sido eliminado.</span></i><br>";
    }

    resultado += "<br>"; // Un pequeño salto de línea extra para separar visualmente las rondas

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