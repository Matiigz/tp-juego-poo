#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <QString>
#include <algorithm>

enum class TipoElemento { AGUA, TIERRA, FUEGO, BARRO, LAVA, VAPOR, DESCONOCIDO };

class Elemento {
protected:
    double energia;
    TipoElemento tipo;

public:
    Elemento(TipoElemento t, double e = 100.0) : energia(e), tipo(t) {}
    virtual ~Elemento() = default;

    double getEnergia() const { return energia; }
    TipoElemento getTipo() const { return tipo; }
    bool estaVivo() const { return energia > 0.0; }

    virtual TipoElemento getTipoAtaque() const { return tipo; }
    virtual TipoElemento getTipoDefensa() const { return tipo; }

    void reducirEnergia(double cantidad) {
        energia = std::max(0.0, energia - cantidad);
    }

    void setEnergia(double e) {
        energia = std::max(0.0, std::min(100.0, e));
    }

    virtual QString getNombreTipo() const = 0;

    static QString tipoToString(TipoElemento t) {
        switch (t) {
        case TipoElemento::AGUA: return "AGUA";
        case TipoElemento::TIERRA: return "TIERRA";
        case TipoElemento::FUEGO: return "FUEGO";
        case TipoElemento::BARRO: return "BARRO";
        case TipoElemento::LAVA: return "LAVA";
        case TipoElemento::VAPOR: return "VAPOR";
        default: return "DESCONOCIDO";
        }
    }

    static TipoElemento stringToTipo(const QString& str) {
        if (str.toUpper() == "AGUA") return TipoElemento::AGUA;
        if (str.toUpper() == "TIERRA") return TipoElemento::TIERRA;
        if (str.toUpper() == "FUEGO") return TipoElemento::FUEGO;
        if (str.toUpper() == "BARRO") return TipoElemento::BARRO;
        if (str.toUpper() == "LAVA") return TipoElemento::LAVA;
        if (str.toUpper() == "VAPOR") return TipoElemento::VAPOR;
        return TipoElemento::DESCONOCIDO;
    }
};

#endif // ELEMENTO_H