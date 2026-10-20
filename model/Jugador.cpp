#include "Jugador.h"

bool Jugador::tieneElementosVivos() const {
    for (const auto& elem : elementos) {
        if (elem && elem->estaVivo()) return true;
    }
    return false;
}

int Jugador::cantidadElementosVivos() const {
    int contador = 0;
    for (const auto& elem : elementos) {
        if (elem && elem->estaVivo()) contador++;
    }
    return contador;
}