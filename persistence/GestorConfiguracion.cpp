#include "GestorConfiguracion.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

bool GestorConfiguracion::cargarConfiguracion(const QString& rutaArchivo, Partida& partida) {
    QFile file(rutaArchivo);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) return false;
    QJsonObject obj = doc.object();

    if (obj.contains("elementosPorJugador")) {
        partida.setElementosPorJugador(obj["elementosPorJugador"].toInt(5));
    }

    if (obj.contains("tipoIA")) {
        QString strIA = obj["tipoIA"].toString();
        if (strIA == "ALEATORIA") partida.setTipoIA(TipoIA::ALEATORIA);
        else if (strIA == "SUPER_IA") partida.setTipoIA(TipoIA::SUPER_IA);
        else partida.setTipoIA(TipoIA::ESTRATEGICA);
    }

    if (obj.contains("reglasDanio") && obj["reglasDanio"].isArray()) {
        partida.getGestorDanioRef().limpiarReglas();
        QJsonArray arr = obj["reglasDanio"].toArray();
        for (auto val : arr) {
            QJsonObject o = val.toObject();
            TipoElemento atacante = Elemento::stringToTipo(o["atacante"].toString());
            TipoElemento defensor = Elemento::stringToTipo(o["defensor"].toString());
            double danio = o["danio"].toDouble();
            partida.getGestorDanioRef().registrarRegla(atacante, defensor, danio);
        }
    }
    return true;
}
void GestorConfiguracion::guardarParametrosPorDefecto(const QString& rutaArchivo, const QString& nombreJugador, int modoIA, int modoJuego, int cantidadCartas) {
    QJsonObject json;

    // Guardamos las "Variables del juego" que pidió el profesor
    json["nombre_jugador_defecto"] = nombreJugador;
    json["modo_ia_defecto"] = modoIA;
    json["modo_juego_defecto"] = modoJuego;
    json["cantidad_cartas"] = cantidadCartas;
    json["vida_inicial_cartas"] = 100;

    // Escribimos el archivo config.json
    QJsonDocument doc(json);
    QFile file(rutaArchivo);
    if (file.open(QIODevice::WriteOnly)) {
        // Usamos Indented para que el JSON quede ordenado y el profe lo pueda leer si abre el archivo
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
}