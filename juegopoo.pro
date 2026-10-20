QT       += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    model/GestorDanio.cpp \
    model/Jugador.cpp \
    model/EstrategiaIA.cpp \
    model/Partida.cpp \
    persistence/GestorConfiguracion.cpp \
    persistence/GestorPersistencia.cpp \
    ui/MainWindow.cpp

HEADERS += \
    model/Elemento.h \
    model/Agua.h \
    model/Tierra.h \
    model/Fuego.h \
    model/GestorDanio.h \
    model/Jugador.h \
    model/EstrategiaIA.h \
    model/Partida.h \
    persistence/GestorConfiguracion.h \
    persistence/GestorPersistencia.h \
    ui/MainWindow.h
 FORMS += ui/MainWindow.ui

RESOURCES += \
    recursos.qrc