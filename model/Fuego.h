#ifndef FUEGO_H
#define FUEGO_H

#include "Elemento.h"

class Fuego : public Elemento {
public:
    Fuego(double e = 100.0) : Elemento(TipoElemento::FUEGO, e) {}
    QString getNombreTipo() const override { return "Fuego"; }
};

#endif // FUEGO_H