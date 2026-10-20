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