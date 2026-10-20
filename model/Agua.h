#ifndef AGUA_H
#define AGUA_H

#include "Elemento.h"

class Agua : public Elemento {
public:
    Agua(double e = 100.0) : Elemento(TipoElemento::AGUA, e) {}
    QString getNombreTipo() const override { return "Agua"; }
};

#endif // AGUA_H