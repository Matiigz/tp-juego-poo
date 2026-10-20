#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../model/Partida.h"

// Esto le avisa a C++ que existe una interfaz creada en el .ui
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
    void onAtacarClicked();
    void onOpcionesClicked();
    void onGuardarFinClicked();
    void onVolverMenuClicked();

private:
    Ui::MainWindow *ui; // Puntero mágico que controla tu diseño
    Partida partida;
    int cartaSeleccionadaIndex = -1;

    void actualizarInterfaz();
    void limpiarLayout(QLayout* layout);
};

#endif // MAINWINDOW_H