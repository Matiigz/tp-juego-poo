#include "GestorDanio.h"

GestorDanio::GestorDanio() {
    registrarRegla(TipoElemento::AGUA, TipoElemento::FUEGO, 50.0);
    registrarRegla(TipoElemento::FUEGO, TipoElemento::AGUA, 20.0);
    registrarRegla(TipoElemento::TIERRA, TipoElemento::FUEGO, 20.0);
    registrarRegla(TipoElemento::FUEGO, TipoElemento::TIERRA, 40.0);
    registrarRegla(TipoElemento::AGUA, TipoElemento::TIERRA, 30.0);
    registrarRegla(TipoElemento::TIERRA, TipoElemento::AGUA, 50.0);
}

void GestorDanio::registrarRegla(TipoElemento atacante, TipoElemento defensor, double danio) {
    matrizDanio[{atacante, defensor}] = danio;
}

double GestorDanio::calcularDanio(TipoElemento atacante, TipoElemento defensor) const {
    auto it = matrizDanio.find({atacante, defensor});
    if (it != matrizDanio.end()) {
        return it->second;
    }
    return 20.0;
}

void GestorDanio::limpiarReglas() {
    matrizDanio.clear();
}