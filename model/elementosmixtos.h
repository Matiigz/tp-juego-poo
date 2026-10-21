#ifndef ELEMENTOSMIXTOS_H
#define ELEMENTOSMIXTOS_H

#include "Elemento.h"

// BARRO: Ataca como AGUA, Defiende como TIERRA
class Barro : public Elemento {
public:
    Barro() : Elemento(TipoElemento::BARRO) {}
    QString getNombreTipo() const override { return "Barro"; }
    TipoElemento getTipoAtaque() const override { return TipoElemento::AGUA; }
    TipoElemento getTipoDefensa() const override { return TipoElemento::TIERRA; }
};

// LAVA: Ataca como FUEGO, Defiende como TIERRA
class Lava : public Elemento {
public:
    Lava() : Elemento(TipoElemento::LAVA) {}
    QString getNombreTipo() const override { return "Lava"; }
    TipoElemento getTipoAtaque() const override { return TipoElemento::FUEGO; }
    TipoElemento getTipoDefensa() const override { return TipoElemento::TIERRA; }
};

// VAPOR: Ataca como FUEGO, Defiende como AGUA
class Vapor : public Elemento {
public:
    Vapor() : Elemento(TipoElemento::VAPOR) {}
    QString getNombreTipo() const override { return "Vapor"; }
    TipoElemento getTipoAtaque() const override { return TipoElemento::FUEGO; }
    TipoElemento getTipoDefensa() const override { return TipoElemento::AGUA; }
};

#endif // ELEMENTOSMIXTOS_H