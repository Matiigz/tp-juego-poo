#include "EstrategiaIA.h"
#include <random>

std::shared_ptr<Elemento> EstrategiaIA::elegirElemento(
    TipoIA tipo, 
    const Jugador& ia, 
    std::shared_ptr<Elemento> elemHumano, 
    const GestorDanio& gestor) 
{
    std::vector<std::shared_ptr<Elemento>> vivos;
    for (auto& e : ia.getElementos()) {
        if (e->estaVivo()) vivos.push_back(e);
    }

    if (vivos.empty()) return nullptr;

    if (tipo == TipoIA::ALEATORIA || !elemHumano) {
        static std::mt19937 rng(1337);
        std::uniform_int_distribution<size_t> dist(0, vivos.size() - 1);
        return vivos[dist(rng)];
    }

    if (tipo == TipoIA::ESTRATEGICA) {
        std::shared_ptr<Elemento> mejor = vivos[0];
        double mejorVentaja = -999.0;

        for (auto& e : vivos) {
            double danioCausado = gestor.calcularDanio(e->getTipo(), elemHumano->getTipo());
            double danioRecibido = gestor.calcularDanio(elemHumano->getTipo(), e->getTipo());
            double ventaja = danioCausado - danioRecibido;

            if (ventaja > mejorVentaja) {
                mejorVentaja = ventaja;
                mejor = e;
            }
        }
        return mejor;
    }

    if (tipo == TipoIA::SUPER_IA) {
        std::shared_ptr<Elemento> mejor = vivos[0];
        double mejorPuntaje = -999.0;

        for (auto& e : vivos) {
            double danioCausado = gestor.calcularDanio(e->getTipo(), elemHumano->getTipo());
            double danioRecibido = gestor.calcularDanio(elemHumano->getTipo(), e->getTipo());

            if (danioCausado >= elemHumano->getEnergia()) {
                danioCausado += 50.0;
            }

            double puntaje = danioCausado - (danioRecibido * 0.5);
            if (puntaje > mejorPuntaje) {
                mejorPuntaje = puntaje;
                mejor = e;
            }
        }
        return mejor;
    }

    return vivos[0];
}