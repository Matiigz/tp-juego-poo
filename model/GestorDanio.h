#ifndef GESTORDANIO_H
#define GESTORDANIO_H

#include "Elemento.h"
#include <map>
#include <utility>

class GestorDanio {
private:
    std::map<std::pair<TipoElemento, TipoElemento>, double> matrizDanio;

public:
    GestorDanio();
    void registrarRegla(TipoElemento atacante, TipoElemento defensor, double danio);
    double calcularDanio(TipoElemento atacante, TipoElemento defensor) const;
    void limpiarReglas();
};

#endif // GESTORDANIO_H