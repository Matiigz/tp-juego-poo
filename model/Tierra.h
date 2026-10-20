#ifndef TIERRA_H
#define TIERRA_H

#include "Elemento.h"

class Tierra : public Elemento {
public:
    Tierra(double e = 100.0) : Elemento(TipoElemento::TIERRA, e) {}
    QString getNombreTipo() const override { return "Tierra"; }
};

#endif // TIERRA_H