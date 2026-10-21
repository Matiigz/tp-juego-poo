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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), partida("Jugador 1")
{
    ui->setupUi(this);

    GestorConfiguracion::cargarConfiguracion("config.json", partida);
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);

    // Conexiones
    connect(ui->btnIniciarJuego, &QPushButton::clicked, this, &MainWindow::onIniciarJuegoClicked);
    connect(ui->btnCargarJuegoInicio, &QPushButton::clicked, this, &MainWindow::onCargarJuegoInicioClicked);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MainWindow::close);

    connect(ui->btnDificultadAleatoria, &QPushButton::clicked, this, &MainWindow::onDificultadAleatoriaClicked);
    connect(ui->btnDificultadEstrategica, &QPushButton::clicked, this, &MainWindow::onDificultadEstrategicaClicked);
    connect(ui->btnDificultadSuperIA, &QPushButton::clicked, this, &MainWindow::onDificultadSuperIAClicked);
    connect(ui->btnContinuarJuego, &QPushButton::clicked, this, &MainWindow::onContinuarJuegoClicked);
    connect(ui->btnVolverDificultad, &QPushButton::clicked, this, &MainWindow::onVolverDificultadClicked);

    connect(ui->btnAtacar, &QPushButton::clicked, this, &MainWindow::onAtacarClicked);
    connect(ui->btnOpciones, &QPushButton::clicked, this, &MainWindow::onOpcionesClicked);
    connect(ui->btnGuardarFin, &QPushButton::clicked, this, &MainWindow::onGuardarFinClicked);
    connect(ui->btnVolverMenu, &QPushButton::clicked, this, &MainWindow::onVolverMenuClicked);
}

MainWindow::~MainWindow() {
    delete ui;
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

    auto renderizarCarta = [this](Elemento* elem, bool esHumano, int index, bool seleccionada) -> QWidget* {
        QWidget* contenedor = new QWidget();
        QHBoxLayout* layoutPrincipal = new QHBoxLayout(contenedor);
        layoutPrincipal->setContentsMargins(0, 0, 0, 0);
        layoutPrincipal->setSpacing(5);

        // --- 1. BARRA DE VIDA ANIMADA ---
        QVBoxLayout* layoutBarra = new QVBoxLayout();
        layoutBarra->setContentsMargins(0, 0, 0, 0);
        layoutBarra->setSpacing(2);

        QProgressBar* barraVida = new QProgressBar();
        barraVida->setOrientation(Qt::Vertical);
        barraVida->setRange(0, 100);
        barraVida->setFixedWidth(8);
        barraVida->setTextVisible(false);

        // Calculamos la vida actual y anterior para la animación
        int hpActual = elem->getEnergia();
        int hpAnterior = hpActual;

        if (esHumano) {
            if (saludAnteriorHumano.count(index)) hpAnterior = saludAnteriorHumano[index];
            saludAnteriorHumano[index] = hpActual;
        } else {
            if (saludAnteriorIA.count(index)) hpAnterior = saludAnteriorIA[index];
            saludAnteriorIA[index] = hpActual;
        }

        barraVida->setValue(hpAnterior); // Inicia en el valor viejo

        QString colorBarra = hpActual > 30 ? "#e74c3c" : "#c0392b";
        if (hpActual > 50) colorBarra = "#27ae60";

        barraVida->setStyleSheet(QString(
                                     "QProgressBar { border: 1px solid #7f8c8d; border-radius: 4px; background-color: #ecf0f1; }"
                                     "QProgressBar::chunk { background-color: %1; border-radius: 3px; }"
                                     ).arg(colorBarra));

        // Animación de daño suave
        if (hpAnterior != hpActual) {
            QPropertyAnimation *anim = new QPropertyAnimation(barraVida, "value", contenedor);
            anim->setDuration(600); // 0.6 segundos de animación
            anim->setStartValue(hpAnterior);
            anim->setEndValue(hpActual);
            anim->setEasingCurve(QEasingCurve::OutCubic); // Curva fluida
            anim->start(QAbstractAnimation::DeleteWhenStopped);
        }

        QLabel* lblPorcentaje = new QLabel(QString::number(hpActual) + "%");
        lblPorcentaje->setAlignment(Qt::AlignCenter);
        lblPorcentaje->setStyleSheet("font-size: 10px; font-weight: bold; color: #2c3e50;");
        if (!elem->estaVivo()) lblPorcentaje->setText("0%");

        layoutBarra->addWidget(barraVida);
        layoutBarra->addWidget(lblPorcentaje);

        // --- 2. CARTA (IMAGEN COMPLETA) ---
        QToolButton* btnCarta = new QToolButton();
        btnCarta->setFixedSize(110, 150);

        QString archivoImg = "";
        if (elem->getTipo() == TipoElemento::AGUA) archivoImg = "agua.png";
        else if (elem->getTipo() == TipoElemento::TIERRA) archivoImg = "tierra.png";
        else if (elem->getTipo() == TipoElemento::FUEGO) archivoImg = "fuego.png";

        QString rutaBase = ":/imagenes/";

        if (!elem->estaVivo()) {
            btnCarta->setText("💀\nELIMINADO");
            btnCarta->setToolButtonStyle(Qt::ToolButtonTextOnly);
            btnCarta->setStyleSheet("QToolButton { background-color: #ecf0f1; border: 2px dashed #95a5a6; border-radius: 10px; font-weight: bold; color: #7f8c8d; }");
        } else {
            QString estiloBorde = seleccionada ? "border: 4px solid #f1c40f;" : "border: 2px solid transparent;";
            btnCarta->setStyleSheet(QString(
                                        "QToolButton {"
                                        "    border-image: url(%1) 0 0 0 0 stretch stretch;"
                                        "    border-radius: 8px;"
                                        "    %2"
                                        "}"
                                        "QToolButton:hover { border: 2px solid #3498db; }"
                                        ).arg(rutaBase + archivoImg, estiloBorde));
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
    for (int i = 0; i < elementosIA.size(); ++i) {
        ui->layoutCartasIA->addWidget(renderizarCarta(elementosIA[i].get(), false, i, false));
    }

    const auto& elementosHumano = partida.getHumano().getElementos();
    for (int i = 0; i < elementosHumano.size(); ++i) {
        bool estaSeleccionada = (i == cartaSeleccionadaIndex);
        ui->layoutCartasHumano->addWidget(renderizarCarta(elementosHumano[i].get(), true, i, estaSeleccionada));
    }

    if (partida.estaTerminada()) {
        ui->lblEstadoJuego->setText("FIN DE LA PARTIDA");
        ui->btnAtacar->setEnabled(false);
        ui->lblResultadoFin->setText(QString("¡PARTIDA FINALIZADA!\nGanador: %1").arg(partida.getGanador()));
        ui->btnGuardarFin->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(ui->pageFin);
    } else {
        ui->lblEstadoJuego->setText(QString("Ronda actual: %1").arg(partida.getRonda()));
        ui->btnAtacar->setEnabled(true);
    }
}

// --- LÓGICA DE DIFICULTAD ---

void MainWindow::onIniciarJuegoClicked() {
    ui->btnDificultadAleatoria->setStyleSheet("");
    ui->btnDificultadEstrategica->setStyleSheet("");
    ui->btnDificultadSuperIA->setStyleSheet("");
    ui->btnContinuarJuego->setEnabled(false);
    ui->stackedWidget->setCurrentWidget(ui->pageDificultad);
}

void MainWindow::resaltarBotonDificultad(QPushButton* botonActivo) {
    ui->btnDificultadAleatoria->setStyleSheet("");
    ui->btnDificultadEstrategica->setStyleSheet("");
    ui->btnDificultadSuperIA->setStyleSheet("");
    botonActivo->setStyleSheet("background-color: #3498db; color: white; border: 2px solid #2980b9;");
    ui->btnContinuarJuego->setEnabled(true);
}

void MainWindow::onDificultadAleatoriaClicked() { dificultadSeleccionada = TipoIA::ALEATORIA; resaltarBotonDificultad(ui->btnDificultadAleatoria); }
void MainWindow::onDificultadEstrategicaClicked() { dificultadSeleccionada = TipoIA::ESTRATEGICA; resaltarBotonDificultad(ui->btnDificultadEstrategica); }
void MainWindow::onDificultadSuperIAClicked() { dificultadSeleccionada = TipoIA::SUPER_IA; resaltarBotonDificultad(ui->btnDificultadSuperIA); }

void MainWindow::onContinuarJuegoClicked() {
    iniciarPartidaConDificultad(dificultadSeleccionada);
}

void MainWindow::onVolverDificultadClicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);
}

void MainWindow::iniciarPartidaConDificultad(TipoIA tipo) {
    partida.setTipoIA(tipo);
    partida.inicializarNuevaPartida();
    cartaSeleccionadaIndex = -1;

    // Reseteamos las memorias de vida para la animación
    saludAnteriorHumano.clear();
    saludAnteriorIA.clear();

    QString nombreIA;
    if (tipo == TipoIA::ALEATORIA) nombreIA = "Modo: IA Aleatoria (Fácil)";
    else if (tipo == TipoIA::ESTRATEGICA) nombreIA = "Modo: IA Estratégica (Normal)";
    else nombreIA = "Modo: Súper IA (Difícil)";
    ui->lblTipoIA->setText(nombreIA);

    ui->logBatalla->clear();
    ui->logBatalla->append("<span style='color: #2980b9;'><b>¡Que comience la batalla elemental!</b></span><br>");

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
            if (partida.getTipoIA() == TipoIA::ALEATORIA) nombreIA = "Modo: IA Aleatoria (Fácil)";
            else if (partida.getTipoIA() == TipoIA::ESTRATEGICA) nombreIA = "Modo: IA Estratégica (Normal)";
            else nombreIA = "Modo: Súper IA (Difícil)";
            ui->lblTipoIA->setText(nombreIA);

            ui->logBatalla->clear();
            ui->logBatalla->append("<span style='color: #27ae60;'><b>--- Partida cargada correctamente ---</b></span><br>");
            actualizarInterfaz();
            ui->stackedWidget->setCurrentWidget(ui->pageJuego);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo cargar la partida.");
        }
    }
}

void MainWindow::onAtacarClicked() {
    if (cartaSeleccionadaIndex < 0) {
        QMessageBox::warning(this, "Atención", "¡Debes hacer clic en una de tus cartas vivas para poder atacar!");
        return;
    }

    QString res = partida.ejecutarRonda(cartaSeleccionadaIndex);

    // El cursor pone el texto arriba de todo (como pediste antes)
    QTextCursor cursor = ui->logBatalla->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ui->logBatalla->setTextCursor(cursor);
    ui->logBatalla->insertHtml(res);

    cartaSeleccionadaIndex = -1;
    actualizarInterfaz();
}

void MainWindow::onOpcionesClicked() {
    if (partida.estaTerminada()) {
        ui->lblResultadoFin->setText(QString("¡PARTIDA FINALIZADA!\nGanador: %1").arg(partida.getGanador()));
        ui->btnGuardarFin->setEnabled(false);
    } else {
        ui->lblResultadoFin->setText(QString("Partida Pausada - Ronda %1").arg(partida.getRonda()));
        ui->btnGuardarFin->setEnabled(true);
    }
    ui->stackedWidget->setCurrentWidget(ui->pageFin);
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
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);
}