#ifndef ELEMENTOSMIXTOS_H
#define ELEMENTOSMIXTOS_H

#include "Elemento.h"


class Barro : public Elemento {
public:
    Barro() : Elemento(TipoElemento::BARRO) {}
    QString getNombreTipo() const override { return "Barro"; }
    TipoElemento getTipoAtaque() const override { return TipoElemento::AGUA; }
    TipoElemento getTipoDefensa() const override { return TipoElemento::TIERRA; }
};


class Lava : public Elemento {
public:
    Lava() : Elemento(TipoElemento::LAVA) {}
    QString getNombreTipo() const override { return "Lava"; }
    TipoElemento getTipoAtaque() const override { return TipoElemento::FUEGO; }
    TipoElemento getTipoDefensa() const override { return TipoElemento::TIERRA; }
};


class Vapor : public Elemento {
public:
    Vapor() : Elemento(TipoElemento::VAPOR) {}
    QString getNombreTipo() const override { return "Vapor"; }
    TipoElemento getTipoAtaque() const override { return TipoElemento::FUEGO; }
    TipoElemento getTipoDefensa() const override { return TipoElemento::AGUA; }
};

#endif // ELEMENTOSMIXTOS_H
