#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../persistence/GestorConfiguracion.h"
#include "../persistence/GestorPersistencia.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QToolButton>
#include <QIcon>
#include <QSize>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTextCursor>
#include <QLineEdit> 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), partida("Jugador 1")
{
    ui->setupUi(this);

    
    ui->pageJuego->setAttribute(Qt::WA_StyledBackground, true);
    ui->pageFin->setAttribute(Qt::WA_StyledBackground, true);
    ui->pageDificultad->setAttribute(Qt::WA_StyledBackground, true);
    ui->pageReglas->setAttribute(Qt::WA_StyledBackground, true);

    ui->pageDificultad->setStyleSheet("#pageDificultad { border-image: url(':/imagenes/fondo juego.jpg') 0 0 0 0 stretch stretch; }");
    ui->pageJuego->setStyleSheet("#pageJuego { border-image: url(':/imagenes/fondo juego.jpg') 0 0 0 0 stretch stretch; }");
    ui->pageFin->setStyleSheet("#pageFin { border-image: url(':/imagenes/fondo juego.jpg') 0 0 0 0 stretch stretch; }");
    ui->pageReglas->setStyleSheet("#pageReglas { border-image: url(':/imagenes/fondo juego.jpg') 0 0 0 0 stretch stretch; }");

    ui->logBatalla->setStyleSheet("background-color: rgba(255, 255, 255, 220); border-radius: 8px; color: black;");
 

   
    ui->btnDificultadAleatoria->setFixedSize(300, 95);
    ui->btnDificultadAleatoria->setText("");
    ui->btnDificultadAleatoria->setStyleSheet(
        "QPushButton {"
        "    border-image: url(':/imagenes/facil_1.png') 0 0 0 0 stretch stretch;"
        "    background-color: transparent;"
        "    border: none;"
        "    border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "    border: 3px solid #3498db;"
        "}"
        );

    ui->btnDificultadEstrategica->setFixedSize(300, 95);
    ui->btnDificultadEstrategica->setText("");
    ui->btnDificultadEstrategica->setStyleSheet(
        "QPushButton {"
        "    border-image: url(':/imagenes/normal_1.png') 0 0 0 0 stretch stretch;"
        "    background-color: transparent;"
        "    border: none;"
        "    border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "    border: 3px solid #2ecc71;"
        "}"
        );

    ui->btnDificultadSuperIA->setFixedSize(300, 95);
    ui->btnDificultadSuperIA->setText("");
    ui->btnDificultadSuperIA->setStyleSheet(
        "QPushButton {"
        "    border-image: url(':/imagenes/dificil_1.png') 0 0 0 0 stretch stretch;"
        "    background-color: transparent;"
        "    border: none;"
        "    border-radius: 20px;"
        "}"
        "QPushButton:hover {"
        "    border: 3px solid #e74c3c;"
        "}"
        );

    if (QLayout* layoutDificultad = ui->btnDificultadAleatoria->parentWidget()->layout()) {
        layoutDificultad->setAlignment(ui->btnDificultadAleatoria, Qt::AlignHCenter);
        layoutDificultad->setAlignment(ui->btnDificultadEstrategica, Qt::AlignHCenter);
        layoutDificultad->setAlignment(ui->btnDificultadSuperIA, Qt::AlignHCenter);
    }


    GestorConfiguracion::cargarConfiguracion("config.json", partida);
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);

    // Conexiones de botones principales y reglas
    connect(ui->btnIniciarJuego, &QPushButton::clicked, this, &MainWindow::onIniciarJuegoClicked);
    connect(ui->btnCargarJuegoInicio, &QPushButton::clicked, this, &MainWindow::onCargarJuegoInicioClicked);
    connect(ui->btnReglas, &QPushButton::clicked, this, &MainWindow::onReglasClicked);
    connect(ui->btnReglasJuego, &QPushButton::clicked, this, &MainWindow::onReglasJuegoClicked);
    connect(ui->btnVolverReglas, &QPushButton::clicked, this, &MainWindow::onVolverReglasClicked);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MainWindow::close);

    // Conexiones de dificultad, modos y nombre
    connect(ui->txtNombreJugador, &QLineEdit::textChanged, this, &MainWindow::verificarInicioPermitido);
    connect(ui->btnDificultadAleatoria, &QPushButton::clicked, this, &MainWindow::onDificultadAleatoriaClicked);
    connect(ui->btnDificultadEstrategica, &QPushButton::clicked, this, &MainWindow::onDificultadEstrategicaClicked);
    connect(ui->btnDificultadSuperIA, &QPushButton::clicked, this, &MainWindow::onDificultadSuperIAClicked);
    connect(ui->btnModoComun, &QPushButton::clicked, this, &MainWindow::onModoComunClicked);
    connect(ui->btnModoMixto, &QPushButton::clicked, this, &MainWindow::onModoMixtoClicked);

    // Navegación
    connect(ui->btnContinuarJuego, &QPushButton::clicked, this, &MainWindow::onContinuarJuegoClicked);
    connect(ui->btnVolverDificultad, &QPushButton::clicked, this, &MainWindow::onVolverDificultadClicked);
    connect(ui->btnNuevaPartidaFin, &QPushButton::clicked, this, &MainWindow::onNuevaPartidaFinClicked);
    // Acciones in-game
    connect(ui->btnAtacar, &QPushButton::clicked, this, &MainWindow::onAtacarClicked);
    connect(ui->btnAyudaIA, &QPushButton::clicked, this, &MainWindow::onAyudaIAClicked);
    connect(ui->btnOpciones, &QPushButton::clicked, this, &MainWindow::onOpcionesClicked);
    connect(ui->btnGuardarFin, &QPushButton::clicked, this, &MainWindow::onGuardarFinClicked);
    connect(ui->btnVolverMenu, &QPushButton::clicked, this, &MainWindow::onVolverMenuClicked);
    connect(ui->btnContinuarPartida, &QPushButton::clicked, this, &MainWindow::onContinuarPartidaClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onReglasClicked() {
    paginaAnteriorReglas = ui->pageInicio;
    ui->stackedWidget->setCurrentWidget(ui->pageReglas);
}

void MainWindow::onReglasJuegoClicked() {
    paginaAnteriorReglas = ui->pageJuego;
    ui->stackedWidget->setCurrentWidget(ui->pageReglas);
}

void MainWindow::onVolverReglasClicked() {
    if (paginaAnteriorReglas) {
        ui->stackedWidget->setCurrentWidget(paginaAnteriorReglas);
    } else {
        ui->stackedWidget->setCurrentWidget(ui->pageInicio);
    }
}

void MainWindow::limpiarLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
}

void MainWindow::actualizarInterfaz() {
    limpiarLayout(ui->layoutCartasHumano);
    limpiarLayout(ui->layoutCartasIA);

    if (!partida.estaTerminada()) {
        ui->btnAyudaIA->setEnabled(pistasRestantes > 0);
    }

    auto renderizarCarta = [this](Elemento* elem, bool esHumano, int index, bool seleccionada) -> QWidget* {
        QWidget* contenedor = new QWidget();
        QHBoxLayout* layoutPrincipal = new QHBoxLayout(contenedor);
        layoutPrincipal->setContentsMargins(0, 0, 0, 0);
        layoutPrincipal->setSpacing(5);

        QVBoxLayout* layoutBarra = new QVBoxLayout();
        layoutBarra->setContentsMargins(0, 0, 0, 0);
        layoutBarra->setSpacing(2);

        QProgressBar* barraVida = new QProgressBar();
        barraVida->setOrientation(Qt::Vertical);
        barraVida->setRange(0, 100);
        barraVida->setFixedWidth(8);
        barraVida->setTextVisible(false);

        int hpActual = elem->getEnergia();
        int hpAnterior = hpActual;

        if (esHumano) {
            if (saludAnteriorHumano.count(index)) hpAnterior = saludAnteriorHumano[index];
            saludAnteriorHumano[index] = hpActual;
        } else {
            if (saludAnteriorIA.count(index)) hpAnterior = saludAnteriorIA[index];
            saludAnteriorIA[index] = hpActual;
        }

        barraVida->setValue(hpAnterior);

        QString colorBarra = hpActual > 30 ? "#e74c3c" : "#c0392b";
        if (hpActual > 50) colorBarra = "#27ae60";

        barraVida->setStyleSheet(QString(
                                     "QProgressBar { border: 1px solid #7f8c8d; border-radius: 4px; background-color: rgba(236, 240, 241, 200); }"
                                     "QProgressBar::chunk { background-color: %1; border-radius: 3px; }"
                                     ).arg(colorBarra));

        if (hpAnterior != hpActual) {
            QPropertyAnimation *anim = new QPropertyAnimation(barraVida, "value", contenedor);
            anim->setDuration(600);
            anim->setStartValue(hpAnterior);
            anim->setEndValue(hpActual);
            anim->setEasingCurve(QEasingCurve::OutCubic);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }

        QLabel* lblPorcentaje = new QLabel(QString::number(hpActual) + "%");
        lblPorcentaje->setAlignment(Qt::AlignCenter);
        lblPorcentaje->setStyleSheet("font-size: 11px; font-weight: bold; color: black; background-color: rgba(255, 255, 255, 180); border-radius: 3px; padding: 1px;");
        if (!elem->estaVivo()) lblPorcentaje->setText("0%");

        layoutBarra->addWidget(barraVida);
        layoutBarra->addWidget(lblPorcentaje);

        QToolButton* btnCarta = new QToolButton();
        btnCarta->setFixedSize(110, 150);

        QString archivoImg = "";
        if (elem->getTipo() == TipoElemento::AGUA) archivoImg = "agua.png";
        else if (elem->getTipo() == TipoElemento::TIERRA) archivoImg = "tierra.png";
        else if (elem->getTipo() == TipoElemento::FUEGO) archivoImg = "fuego.png";
        else if (elem->getTipo() == TipoElemento::BARRO) archivoImg = "barro.png";
        else if (elem->getTipo() == TipoElemento::LAVA) archivoImg = "lava.png";
        else if (elem->getTipo() == TipoElemento::VAPOR) archivoImg = "vapor.png";

        QString rutaBase = ":/imagenes/";

        if (!elem->estaVivo()) {
            btnCarta->setText("💀\nELIMINADO");
            btnCarta->setToolButtonStyle(Qt::ToolButtonTextOnly);
            btnCarta->setStyleSheet("QToolButton { background-color: rgba(236, 240, 241, 180); border: 2px dashed #95a5a6; border-radius: 10px; font-weight: bold; color: #7f8c8d; }");
        } else {
            QString estiloBorde = seleccionada ? "border: 4px solid #f1c40f;" : "border: 2px solid transparent;";

            bool esElementoBasico = (elem->getTipo() == TipoElemento::AGUA ||
                                     elem->getTipo() == TipoElemento::TIERRA ||
                                     elem->getTipo() == TipoElemento::FUEGO);

            if (esElementoBasico) {
                btnCarta->setStyleSheet(QString(
                                            "QToolButton {"
                                            "    border-image: url('%1') 0 0 0 0 stretch stretch;"
                                            "    background-color: transparent;"
                                            "    border-radius: 8px;"
                                            "    %2"
                                            "}"
                                            "QToolButton:hover {"
                                            "    border: 2px solid #3498db;"
                                            "}"
                                            ).arg(rutaBase + archivoImg, estiloBorde));
            } else {
                btnCarta->setIcon(QIcon(rutaBase + archivoImg));
                btnCarta->setIconSize(QSize(110, 150));
                btnCarta->setStyleSheet(QString(
                                            "QToolButton {"
                                            "    background-color: transparent;"
                                            "    padding: 0px;"
                                            "    margin: 0px;"
                                            "    border-radius: 8px;"
                                            "    %1"
                                            "}"
                                            "QToolButton:hover {"
                                            "    border: 2px solid #3498db;"
                                            "    background-color: rgba(255, 255, 255, 50);"
                                            "}"
                                            ).arg(estiloBorde));
            }
        }

        if (!esHumano || !elem->estaVivo()) {
            btnCarta->setAttribute(Qt::WA_TransparentForMouseEvents);
            btnCarta->setFocusPolicy(Qt::NoFocus);
        } else {
            connect(btnCarta, &QToolButton::clicked, this, [this, index]() {
                cartaSeleccionadaIndex = index;
                actualizarInterfaz();
            });
        }

        layoutPrincipal->addLayout(layoutBarra);
        layoutPrincipal->addWidget(btnCarta);

        return contenedor;
    };

    const auto& elementosIA = partida.getIA().getElementos();
    for (size_t i = 0; i < elementosIA.size(); ++i) { 
        ui->layoutCartasIA->addWidget(renderizarCarta(elementosIA[i].get(), false, i, false));
    }

    const auto& elementosHumano = partida.getHumano().getElementos();
    for (size_t i = 0; i < elementosHumano.size(); ++i) { 
        bool estaSeleccionada = (i == cartaSeleccionadaIndex);
        ui->layoutCartasHumano->addWidget(renderizarCarta(elementosHumano[i].get(), true, i, estaSeleccionada));
    }

    if (partida.estaTerminada()) {
        ui->lblEstadoJuego->setStyleSheet("color: white; font-size: 16px; font-weight: bold; background-color: rgba(0,0,0,150); border-radius: 5px;");
        ui->lblEstadoJuego->setText("FIN DE LA PARTIDA");
        ui->btnAtacar->setEnabled(false);
        ui->btnAyudaIA->setEnabled(false);
        ui->btnNuevaPartidaFin->setVisible(true);
        QString ganador = partida.getGanador();

        // Si el ganador es Jugador 1, usamos el nombre personalizado visualmente
        if(ganador == "Jugador 1") ganador = nombreJugadorActual;

        ui->lblResultadoFin->setText(QString("¡PARTIDA FINALIZADA!\nGanador: %1").arg(ganador));

        // --- LÓGICA DINÁMICA DE VICTORIA / DERROTA BASADA EN EL NOMBRE ---
        if (ganador != "IA Bot" && ganador != "IA") {
            ui->pageFin->setStyleSheet("#pageFin { border-image: url(':/imagenes/victoria.png') 0 0 0 0 stretch stretch; }");
        } else {
            ui->pageFin->setStyleSheet("#pageFin { border-image: url(':/imagenes/derrota.png') 0 0 0 0 stretch stretch; }");
        }

        ui->lblResultadoFin->setStyleSheet("color: white; background-color: rgba(0,0,0,150); border-radius: 10px; padding: 10px;");

        ui->btnGuardarFin->setEnabled(false);
        ui->btnContinuarPartida->setVisible(false);
        ui->stackedWidget->setCurrentWidget(ui->pageFin);
    } else {
        ui->lblEstadoJuego->setStyleSheet("color: white; font-size: 16px; font-weight: bold; background-color: rgba(0,0,0,150); border-radius: 5px; padding: 5px;");
        ui->lblEstadoJuego->setText(QString("Ronda actual: %1").arg(partida.getRonda()));
        ui->btnAtacar->setEnabled(true);
    }
}



void MainWindow::onIniciarJuegoClicked() {
    ui->btnDificultadAleatoria->setStyleSheet(
        "QPushButton { border-image: url(':/imagenes/facil_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: none; border-radius: 20px; }"
        "QPushButton:hover { border: 3px solid #3498db; }"
        );
    ui->btnDificultadEstrategica->setStyleSheet(
        "QPushButton { border-image: url(':/imagenes/normal_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: none; border-radius: 20px; }"
        "QPushButton:hover { border: 3px solid #2ecc71; }"
        );
    ui->btnDificultadSuperIA->setStyleSheet(
        "QPushButton { border-image: url(':/imagenes/dificil_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: none; border-radius: 20px; }"
        "QPushButton:hover { border: 3px solid #e74c3c; }"
        );

    ui->btnModoComun->setStyleSheet("");
    ui->btnModoMixto->setStyleSheet("");

    // --- OCULTAR NOMBRE Y LABEL SI YA EXISTE ---
    bool yaTieneNombre = !ui->txtNombreJugador->text().trimmed().isEmpty();
    ui->lblIngresoNombre->setVisible(!yaTieneNombre);
    ui->txtNombreJugador->setVisible(!yaTieneNombre);
    // ------------------------------------------

    seleccionoDificultad = false;
    seleccionoModo = false;
    verificarInicioPermitido();

    ui->stackedWidget->setCurrentWidget(ui->pageDificultad);
}
void MainWindow::resaltarBotonDificultad(QPushButton* botonActivo) {
    ui->btnDificultadAleatoria->setStyleSheet(
        "QPushButton { border-image: url(':/imagenes/facil_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: none; border-radius: 20px; }"
        "QPushButton:hover { border: 3px solid #3498db; }"
        );
    ui->btnDificultadEstrategica->setStyleSheet(
        "QPushButton { border-image: url(':/imagenes/normal_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: none; border-radius: 20px; }"
        "QPushButton:hover { border: 3px solid #2ecc71; }"
        );
    ui->btnDificultadSuperIA->setStyleSheet(
        "QPushButton { border-image: url(':/imagenes/dificil_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: none; border-radius: 20px; }"
        "QPushButton:hover { border: 3px solid #e74c3c; }"
        );

    if (botonActivo == ui->btnDificultadAleatoria) {
        botonActivo->setStyleSheet(
            "QPushButton { border-image: url(':/imagenes/facil_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: 4px solid #3498db; border-radius: 20px; }"
            );
    } else if (botonActivo == ui->btnDificultadEstrategica) {
        botonActivo->setStyleSheet(
            "QPushButton { border-image: url(':/imagenes/normal_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: 4px solid #2ecc71; border-radius: 20px; }"
            );
    } else if (botonActivo == ui->btnDificultadSuperIA) {
        botonActivo->setStyleSheet(
            "QPushButton { border-image: url(':/imagenes/dificil_1.png') 0 0 0 0 stretch stretch; background-color: transparent; border: 4px solid #e74c3c; border-radius: 20px; }"
            );
    }
}

void MainWindow::onDificultadAleatoriaClicked() { dificultadSeleccionada = TipoIA::ALEATORIA; resaltarBotonDificultad(ui->btnDificultadAleatoria); seleccionoDificultad = true; verificarInicioPermitido(); }
void MainWindow::onDificultadEstrategicaClicked() { dificultadSeleccionada = TipoIA::ESTRATEGICA; resaltarBotonDificultad(ui->btnDificultadEstrategica); seleccionoDificultad = true; verificarInicioPermitido(); }
void MainWindow::onDificultadSuperIAClicked() { dificultadSeleccionada = TipoIA::SUPER_IA; resaltarBotonDificultad(ui->btnDificultadSuperIA); seleccionoDificultad = true; verificarInicioPermitido(); }

void MainWindow::onModoComunClicked() {
    modoSeleccionado = ModoJuego::COMUN;
    ui->btnModoComun->setStyleSheet("background-color: #27ae60; color: white; border: 2px solid #2ecc71;");
    ui->btnModoMixto->setStyleSheet("");
    seleccionoModo = true;
    verificarInicioPermitido();
}

void MainWindow::onModoMixtoClicked() {
    modoSeleccionado = ModoJuego::MIXTO;
    ui->btnModoMixto->setStyleSheet("background-color: #8e44ad; color: white; border: 2px solid #9b59b6;");
    ui->btnModoComun->setStyleSheet("");
    seleccionoModo = true;
    verificarInicioPermitido();
}

void MainWindow::verificarInicioPermitido() {
    bool nombreValido = !ui->txtNombreJugador->text().trimmed().isEmpty() || !nombreJugadorActual.isEmpty();
    ui->btnContinuarJuego->setEnabled(seleccionoDificultad && seleccionoModo && nombreValido);
}

void MainWindow::onContinuarJuegoClicked() {
    iniciarPartidaConDificultad(dificultadSeleccionada);
}

void MainWindow::onVolverDificultadClicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);
}

// --- INICIO DE PARTIDA Y ACCIONES IN-GAME ---

void MainWindow::iniciarPartidaConDificultad(TipoIA tipo) {
    nombreJugadorActual = ui->txtNombreJugador->text().trimmed();
    if(nombreJugadorActual.isEmpty()) nombreJugadorActual = "Jugador 1";

    
    GestorConfiguracion::guardarParametrosPorDefecto("config.json", nombreJugadorActual, static_cast<int>(tipo), static_cast<int>(modoSeleccionado), 3);

    partida.setTipoIA(tipo);
    partida.setModoJuego(modoSeleccionado);
    partida.inicializarNuevaPartida();
    cartaSeleccionadaIndex = -1;

    saludAnteriorHumano.clear();
    saludAnteriorIA.clear();

    QString nombreIA;
    if (tipo == TipoIA::ALEATORIA) {
        nombreIA = "Modo: IA Aleatoria (Fácil)";
        pistasRestantes = 3;
    }
    else if (tipo == TipoIA::ESTRATEGICA) {
        nombreIA = "Modo: IA Estratégica (Normal)";
        pistasRestantes = 2;
    }
    else {
        nombreIA = "Modo: Súper IA (Difícil)";
        pistasRestantes = 0;
    }

    ui->btnAyudaIA->setText(QString("💡 Pista de IA (%1)").arg(pistasRestantes));
    ui->btnAyudaIA->setEnabled(pistasRestantes > 0);

    QString nombreModo = (modoSeleccionado == ModoJuego::MIXTO) ? " - MIXTO" : " - COMÚN";
    ui->lblTipoIA->setText(nombreIA + nombreModo);

    ui->logBatalla->clear();
    ui->logBatalla->append(QString("<span style='color: #2980b9;'><b>¡Buena suerte, %1! ¡Que comience la batalla elemental!</b></span><br>").arg(nombreJugadorActual));

    actualizarInterfaz();
    ui->stackedWidget->setCurrentWidget(ui->pageJuego);
}

void MainWindow::onCargarJuegoInicioClicked() {
    QString file = QFileDialog::getOpenFileName(this, "Cargar Partida", "", "Archivos Binarios (*.dat)");
    if (!file.isEmpty()) {
        if (GestorPersistencia::cargarPartida(file, partida)) {
            cartaSeleccionadaIndex = -1;
            saludAnteriorHumano.clear();
            saludAnteriorIA.clear();

            QString nombreIA;
            if (partida.getTipoIA() == TipoIA::ALEATORIA) {
                nombreIA = "Modo: IA Aleatoria (Fácil)";
                pistasRestantes = 3;
            }
            else if (partida.getTipoIA() == TipoIA::ESTRATEGICA) {
                nombreIA = "Modo: IA Estratégica (Normal)";
                pistasRestantes = 2;
            }
            else {
                nombreIA = "Modo: Súper IA (Difícil)";
                pistasRestantes = 0;
            }

            ui->btnAyudaIA->setText(QString("💡 Pista de IA (%1)").arg(pistasRestantes));
            ui->btnAyudaIA->setEnabled(pistasRestantes > 0);

            QString nombreModo = (partida.getModoJuego() == ModoJuego::MIXTO) ? " - MIXTO" : " - COMÚN";
            ui->lblTipoIA->setText(nombreIA + nombreModo);

            ui->logBatalla->clear();
            ui->logBatalla->append("<span style='color: #27ae60;'><b>--- Partida cargada correctamente ---</b></span><br>");
            actualizarInterfaz();
            ui->stackedWidget->setCurrentWidget(ui->pageJuego);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo cargar la partida.");
        }
    }
}

void MainWindow::onAyudaIAClicked() {
    if (pistasRestantes <= 0) return;

    const auto& elementosIA = partida.getIA().getElementos();
    QString posibleAtaque = "Desconocido";

    for (const auto& elem : elementosIA) {
        if (elem->estaVivo()) {
            if (elem->getTipo() == TipoElemento::AGUA) posibleAtaque = "Agua";
            else if (elem->getTipo() == TipoElemento::TIERRA) posibleAtaque = "Tierra";
            else if (elem->getTipo() == TipoElemento::FUEGO) posibleAtaque = "Fuego";
            else if (elem->getTipo() == TipoElemento::BARRO) posibleAtaque = "Barro";
            else if (elem->getTipo() == TipoElemento::LAVA) posibleAtaque = "Lava";
            else if (elem->getTipo() == TipoElemento::VAPOR) posibleAtaque = "Vapor";
            break;
        }
    }

    QTextCursor cursor = ui->logBatalla->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ui->logBatalla->setTextCursor(cursor);
    ui->logBatalla->insertHtml(QString("<span style='color: #f39c12;'><b>[💡 PISTA]</b> El enemigo prepara una carta de <b>%1</b>.</span><br>").arg(posibleAtaque));

    pistasRestantes--;
    ui->btnAyudaIA->setText(QString("💡 Pista de IA (%1)").arg(pistasRestantes));
    ui->btnAyudaIA->setEnabled(false);
}

void MainWindow::onAtacarClicked() {
    if (cartaSeleccionadaIndex < 0) {
        QMessageBox::warning(this, "Atención", "¡Debes hacer clic en una de tus cartas vivas para poder atacar!");
        return;
    }

    QString res = partida.ejecutarRonda(cartaSeleccionadaIndex);

    QTextCursor cursor = ui->logBatalla->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ui->logBatalla->setTextCursor(cursor);
    ui->logBatalla->insertHtml(res);

    cartaSeleccionadaIndex = -1;
    actualizarInterfaz();
}

void MainWindow::onOpcionesClicked() {
    if (!partida.estaTerminada()) {
        ui->lblResultadoFin->setText(QString("Partida Pausada - Ronda %1").arg(partida.getRonda()));
        ui->btnGuardarFin->setEnabled(true);
        ui->btnContinuarPartida->setVisible(true);
        ui->lblResultadoFin->setStyleSheet("color: white; background-color: rgba(0,0,0,150); border-radius: 10px; padding: 10px;");
        ui->btnNuevaPartidaFin->setVisible(false);
        ui->pageFin->setStyleSheet("#pageFin { border-image: url(':/imagenes/fondo juego.jpg') 0 0 0 0 stretch stretch; }");
    }
    ui->stackedWidget->setCurrentWidget(ui->pageFin);
}

void MainWindow::onContinuarPartidaClicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageJuego);
}

void MainWindow::onGuardarFinClicked() {
    QString file = QFileDialog::getSaveFileName(this, "Guardar Partida", "", "Archivos Binarios (*.dat)");
    if (!file.isEmpty()) {
        if (GestorPersistencia::guardarPartida(file, partida)) {
            QMessageBox::information(this, "Éxito", "Partida guardada correctamente.");
        } else {
            QMessageBox::critical(this, "Error", "No se pudo guardar la partida.");
        }
    }
}

void MainWindow::onVolverMenuClicked() {
    ui->txtNombreJugador->clear(); // Limpia el nombre para pedirlo de nuevo si regresa al menú inicial
    nombreJugadorActual = "Jugador 1";
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);
}
void MainWindow::onNuevaPartidaFinClicked() {
    onIniciarJuegoClicked();
}
