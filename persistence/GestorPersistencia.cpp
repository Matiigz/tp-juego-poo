#include "GestorPersistencia.h"
#include "../model/Agua.h"
#include "../model/Tierra.h"
#include "../model/Fuego.h"
#include <QFile>
#include <QDataStream>

bool GestorPersistencia::guardarPartida(const QString& rutaArchivo, const Partida& partida) {
    QFile file(rutaArchivo);
    
    if (!file.open(QIODevice::WriteOnly)) return false;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0); 
    
    out << partida.getRonda();
    out << partida.getElementosPorJugador();
    out << static_cast<int>(partida.getTipoIA());

    auto serializarJugador = [&out](const Jugador& j) {
        out << j.getNombre();
        out << static_cast<int>(j.getElementos().size());
        for (const auto& elem : j.getElementos()) {
            out << static_cast<int>(elem->getTipo());
            out << elem->getEnergia();
        }
    };

   
    serializarJugador(const_cast<Partida&>(partida).getHumano());
    serializarJugador(const_cast<Partida&>(partida).getIA());

    file.close();
    return true;
}

bool GestorPersistencia::cargarPartida(const QString& rutaArchivo, Partida& partida) {
    QFile file(rutaArchivo);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    int ronda, elementosPorJugador, tipoIA;
    in >> ronda >> elementosPorJugador >> tipoIA;

    partida.setRonda(ronda);
    partida.setElementosPorJugador(elementosPorJugador);
    partida.setTipoIA(static_cast<TipoIA>(tipoIA));

    auto deserializarJugador = [&in](Jugador& j) {
        j.limpiarElementos();
        QString nombre;
        int cantElementos;
        in >> nombre >> cantElementos;

        for (int i = 0; i < cantElementos; ++i) {
            int tipoInt;
            double energia;
            in >> tipoInt >> energia;

            TipoElemento t = static_cast<TipoElemento>(tipoInt);
            std::shared_ptr<Elemento> elem;

            if (t == TipoElemento::AGUA) elem = std::make_shared<Agua>(energia);
            else if (t == TipoElemento::TIERRA) elem = std::make_shared<Tierra>(energia);
            else elem = std::make_shared<Fuego>(energia);

            j.agregarElemento(elem);
        }
    };

    deserializarJugador(partida.getHumano());
    deserializarJugador(partida.getIA());

    file.close();
    return true;
}
