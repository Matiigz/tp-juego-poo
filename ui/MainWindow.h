#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
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
    
    // --- Slots para la Dificultad ---
    void onDificultadAleatoriaClicked();
    void onDificultadEstrategicaClicked();
    void onDificultadSuperIAClicked();
    void onContinuarJuegoClicked(); // NUEVO BOTON
    void onVolverDificultadClicked();

    void onAtacarClicked();
    void onOpcionesClicked();
    void onGuardarFinClicked();
    void onVolverMenuClicked();

private:
    Ui::MainWindow *ui;
    Partida partida;
    int cartaSeleccionadaIndex = -1;
    TipoIA dificultadSeleccionada; // Guarda lo que elijamos

    void actualizarInterfaz();
    void limpiarLayout(QLayout* layout);
    void iniciarPartidaConDificultad(TipoIA tipo);
    void resaltarBotonDificultad(QPushButton* botonActivo); // Pinta el botón elegido
};

#endif // MAINWINDOW_H