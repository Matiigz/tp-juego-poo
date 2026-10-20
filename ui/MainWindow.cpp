#include "MainWindow.h"
#include "ui_MainWindow.h" 
#include "../persistence/GestorConfiguracion.h"
#include "../persistence/GestorPersistencia.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QToolButton>
#include <QIcon>
#include <QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), partida("Jugador 1") 
{
    ui->setupUi(this); 
    
    GestorConfiguracion::cargarConfiguracion("config.json", partida);
    ui->stackedWidget->setCurrentWidget(ui->pageInicio);

    // Conexiones de botones
    connect(ui->btnIniciarJuego, &QPushButton::clicked, this, &MainWindow::onIniciarJuegoClicked);
    connect(ui->btnCargarJuegoInicio, &QPushButton::clicked, this, &MainWindow::onCargarJuegoInicioClicked);
    
    // Conexiones de dificultad
    connect(ui->btnDificultadAleatoria, &QPushButton::clicked, this, &MainWindow::onDificultadAleatoriaClicked);
    connect(ui->btnDificultadEstrategica, &QPushButton::clicked, this, &MainWindow::onDificultadEstrategicaClicked);
    connect(ui->btnDificultadSuperIA, &QPushButton::clicked, this, &MainWindow::onDificultadSuperIAClicked);
    connect(ui->btnContinuarJuego, &QPushButton::clicked, this, &MainWindow::onContinuarJuegoClicked);
    connect(ui->btnVolverDificultad, &QPushButton::clicked, this, &MainWindow::onVolverDificultadClicked);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MainWindow::close);
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

    auto renderizarCarta = [](Elemento* elem, bool esHumano, bool seleccionada) -> QToolButton* {
        QToolButton* btnCarta = new QToolButton();
        btnCarta->setFixedSize(120, 170);
        btnCarta->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        QString archivoImg = "";
        QString colorFondo = "#ffffff";
        QString colorBorde = "#cccccc";

        if (elem->getTipo() == TipoElemento::AGUA) { archivoImg = "agua.png"; colorFondo = "#e0f7fa"; colorBorde = "#00bcd4"; }
        else if (elem->getTipo() == TipoElemento::TIERRA) { archivoImg = "tierra.png"; colorFondo = "#e8f5e9"; colorBorde = "#4caf50"; }
        else if (elem->getTipo() == TipoElemento::FUEGO) { archivoImg = "fuego.png"; colorFondo = "#ffebee"; colorBorde = "#f44336"; }

        QString rutaBase = ":/imagenes/";

        if (!elem->estaVivo()) {
            colorFondo = "#eeeeee"; 
            colorBorde = "#9e9e9e"; 
        } else {
            btnCarta->setIcon(QIcon(rutaBase + archivoImg));
            btnCarta->setIconSize(QSize(70, 70));
        }

        QString estiloBorde = seleccionada ? "border: 4px solid #f1c40f;" : QString("border: 2px solid %1;").arg(colorBorde);
        
        btnCarta->setStyleSheet(QString(
            "QToolButton { background-color: %1; %2 border-radius: 10px; font-size: 14px; font-weight: bold; }"
            "QToolButton:hover { background-color: #ffffff; }"
        ).arg(colorFondo, estiloBorde));

        QString txt = QString("\n%1\nHP: %2").arg(elem->getNombreTipo(), QString::number(elem->getEnergia()));
        if (!elem->estaVivo()) txt = "\n💀 ELIMINADO\nHP: 0";
        
        btnCarta->setText(txt);
        
        if (!esHumano || !elem->estaVivo()) {
            btnCarta->setAttribute(Qt::WA_TransparentForMouseEvents);
            btnCarta->setFocusPolicy(Qt::NoFocus);
        }

        return btnCarta;
    };

    const auto& elementosIA = partida.getIA().getElementos();
    for (const auto& elem : elementosIA) {
        ui->layoutCartasIA->addWidget(renderizarCarta(elem.get(), false, false));
    }

    const auto& elementosHumano = partida.getHumano().getElementos();
    for (int i = 0; i < elementosHumano.size(); ++i) {
        bool estaSeleccionada = (i == cartaSeleccionadaIndex);
        auto btnCarta = renderizarCarta(elementosHumano[i].get(), true, estaSeleccionada);
        
        if (elementosHumano[i]->estaVivo()) {
            connect(btnCarta, &QToolButton::clicked, this, [this, i]() {
                cartaSeleccionadaIndex = i;
                actualizarInterfaz();
            });
        }
        ui->layoutCartasHumano->addWidget(btnCarta);
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
    // Reseteamos la vista por si vuelven a jugar
    ui->btnDificultadAleatoria->setStyleSheet("");
    ui->btnDificultadEstrategica->setStyleSheet("");
    ui->btnDificultadSuperIA->setStyleSheet("");
    ui->btnContinuarJuego->setEnabled(false); // Deshabilitar el botón verde hasta que elijan algo

    ui->stackedWidget->setCurrentWidget(ui->pageDificultad);
}

void MainWindow::resaltarBotonDificultad(QPushButton* botonActivo) {
    ui->btnDificultadAleatoria->setStyleSheet("");
    ui->btnDificultadEstrategica->setStyleSheet("");
    ui->btnDificultadSuperIA->setStyleSheet("");

    // Pintar de azul el botón seleccionado
    botonActivo->setStyleSheet("background-color: #3498db; color: white; border: 2px solid #2980b9;");
    
    // Habilitar el botón de continuar
    ui->btnContinuarJuego->setEnabled(true);
}

void MainWindow::onDificultadAleatoriaClicked() { 
    dificultadSeleccionada = TipoIA::ALEATORIA; 
    resaltarBotonDificultad(ui->btnDificultadAleatoria);
}
void MainWindow::onDificultadEstrategicaClicked() { 
    dificultadSeleccionada = TipoIA::ESTRATEGICA; 
    resaltarBotonDificultad(ui->btnDificultadEstrategica);
}
void MainWindow::onDificultadSuperIAClicked() { 
    dificultadSeleccionada = TipoIA::SUPER_IA; 
    resaltarBotonDificultad(ui->btnDificultadSuperIA);
}

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
    ui->logBatalla->clear();
    ui->logBatalla->append(QString("¡Batalla iniciada! Dificultad IA: %1").arg(tipo == TipoIA::ALEATORIA ? "Fácil" : (tipo == TipoIA::ESTRATEGICA ? "Normal" : "Difícil")));
    actualizarInterfaz();
    ui->stackedWidget->setCurrentWidget(ui->pageJuego);
}

// ----------------------------

void MainWindow::onCargarJuegoInicioClicked() {
    QString file = QFileDialog::getOpenFileName(this, "Cargar Partida", "", "Archivos Binarios (*.dat)");
    if (!file.isEmpty()) {
        if (GestorPersistencia::cargarPartida(file, partida)) {
            cartaSeleccionadaIndex = -1;
            ui->logBatalla->clear();
            ui->logBatalla->append("--- Partida cargada correctamente ---");
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
    ui->logBatalla->append(res);
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
void MainWindow::on_pushButton_clicked()
{

}

