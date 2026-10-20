#ifndef ESTRATEGIAIA_H
#define ESTRATEGIAIA_H

#include "Jugador.h"
#include "GestorDanio.h"
#include <memory>

enum class TipoIA { ALEATORIA, ESTRATEGICA, SUPER_IA };

class EstrategiaIA {
public:
    static std::shared_ptr<Elemento> elegirElemento(
        TipoIA tipo, 
        const Jugador& ia, 
        std::shared_ptr<Elemento> elemHumano, 
        const GestorDanio& gestor
    );
};

#endif // ESTRATEGIAIA_H