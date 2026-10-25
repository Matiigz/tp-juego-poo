#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <map>
#include "../model/Partida.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onIniciarJuegoClicked();
    void onCargarJuegoInicioClicked();

    void onReglasClicked();
    void onReglasJuegoClicked();
    void onVolverReglasClicked();

    void onDificultadAleatoriaClicked();
    void onDificultadEstrategicaClicked();
    void onDificultadSuperIAClicked();

    void onModoComunClicked();
    void onModoMixtoClicked();

    void onContinuarJuegoClicked();
    void onVolverDificultadClicked();

    void onAtacarClicked();
    void onOpcionesClicked();
    void onGuardarFinClicked();
    void onVolverMenuClicked();
    void onContinuarPartidaClicked();
    void onNuevaPartidaFinClicked();
    void onAyudaIAClicked();

private:
    Ui::MainWindow *ui;
    Partida partida;
    int cartaSeleccionadaIndex = -1;
    TipoIA dificultadSeleccionada;
    ModoJuego modoSeleccionado = ModoJuego::COMUN;

    bool seleccionoDificultad = false;
    bool seleccionoModo = false;

    int pistasRestantes = 0;
    QWidget* paginaAnteriorReglas = nullptr;
    QString nombreJugadorActual = "Jugador 1"; // <- NUEVO

    std::map<int, int> saludAnteriorHumano;
    std::map<int, int> saludAnteriorIA;

    void actualizarInterfaz();
    void limpiarLayout(QLayout* layout);
    void iniciarPartidaConDificultad(TipoIA tipo);
    void resaltarBotonDificultad(QPushButton* botonActivo);
    void verificarInicioPermitido();
};

#endif // MAINWINDOW_H