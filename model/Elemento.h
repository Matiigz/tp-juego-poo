#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <QString>
#include <algorithm>

enum class TipoElemento { AGUA, TIERRA, FUEGO, DESCONOCIDO };

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
            default: return "DESCONOCIDO";
        }
    }

    static TipoElemento stringToTipo(const QString& str) {
        if (str.toUpper() == "AGUA") return TipoElemento::AGUA;
        if (str.toUpper() == "TIERRA") return TipoElemento::TIERRA;
        if (str.toUpper() == "FUEGO") return TipoElemento::FUEGO;
        return TipoElemento::DESCONOCIDO;
    }
};

#endif // ELEMENTO_H