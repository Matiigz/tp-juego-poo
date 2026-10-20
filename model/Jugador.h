#ifndef JUGADOR_H
#define JUGADOR_H

#include "Elemento.h"
#include <vector>
#include <memory>
#include <QString>

class Jugador {
private:
    QString nombre;
    std::vector<std::shared_ptr<Elemento>> elementos;

public:
    Jugador(const QString& n) : nombre(n) {}

    QString getNombre() const { return nombre; }
    void agregarElemento(std::shared_ptr<Elemento> e) { elementos.push_back(e); }
    const std::vector<std::shared_ptr<Elemento>>& getElementos() const { return elementos; }
    
    bool tieneElementosVivos() const;
    int cantidadElementosVivos() const;
    void limpiarElementos() { elementos.clear(); }
};

#endif // JUGADOR_H