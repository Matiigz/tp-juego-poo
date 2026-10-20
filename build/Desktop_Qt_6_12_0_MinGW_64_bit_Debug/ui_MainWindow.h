/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageInicio;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *lblTitulo;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnIniciarJuego;
    QPushButton *btnCargarJuegoInicio;
    QPushButton *btnSalir;
    QSpacerItem *verticalSpacer_3;
    QWidget *pageDificultad;
    QVBoxLayout *verticalLayout_dif;
    QSpacerItem *verticalSpacer_dif1;
    QLabel *lblTituloDificultad;
    QSpacerItem *verticalSpacer_dif2;
    QPushButton *btnDificultadAleatoria;
    QPushButton *btnDificultadEstrategica;
    QPushButton *btnDificultadSuperIA;
    QSpacerItem *verticalSpacer_dif3;
    QPushButton *btnContinuarJuego;
    QPushButton *btnVolverDificultad;
    QWidget *pageJuego;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblEstadoJuego;
    QLabel *lblIA;
    QHBoxLayout *layoutCartasIA;
    QTextEdit *logBatalla;
    QLabel *lblHumano;
    QHBoxLayout *layoutCartasHumano;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAtacar;
    QPushButton *btnOpciones;
    QWidget *pageFin;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_4;
    QLabel *lblResultadoFin;
    QSpacerItem *verticalSpacer_5;
    QPushButton *btnGuardarFin;
    QPushButton *btnVolverMenu;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(850, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageInicio = new QWidget();
        pageInicio->setObjectName("pageInicio");
        pageInicio->setStyleSheet(QString::fromUtf8("#pageInicio {\n"
"    border-image: url(:/imagenes/cc70f896-a6ee-4185-a978-6fd627721f1e.png) 0 0 0 0 stretch stretch;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(pageInicio);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        lblTitulo = new QLabel(pageInicio);
        lblTitulo->setObjectName("lblTitulo");
        QFont font;
        font.setPointSize(36);
        font.setBold(true);
        lblTitulo->setFont(font);
        lblTitulo->setStyleSheet(QString::fromUtf8("\302\241<span style=\"color: #2980b9;\">Agua</span>, <span style=\"color: #27ae60;\">Tierra</span> y <span style=\"color: #c0392b;\">Fuego</span>!"));
        lblTitulo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(lblTitulo);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        btnIniciarJuego = new QPushButton(pageInicio);
        btnIniciarJuego->setObjectName("btnIniciarJuego");
        btnIniciarJuego->setMinimumSize(QSize(50, 50));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        btnIniciarJuego->setFont(font1);
        btnIniciarJuego->setStyleSheet(QString::fromUtf8("    color: rgba(255, 255, 255, 1);              /* Color de la letra: blanco */\n"
"    background-color: rgba(255, 0, 0, 1);       /* Fondo rojo */\n"
"    border: 2px solid rgba(0, 0, 0, 1);          /* Borde negro */\n"
"    border-radius: 10px;                        /* Bordes redondeados */\n"
"    text-transform: uppercase;                   /* Texto en may\303\272sculas */"));

        verticalLayout_2->addWidget(btnIniciarJuego);

        btnCargarJuegoInicio = new QPushButton(pageInicio);
        btnCargarJuegoInicio->setObjectName("btnCargarJuegoInicio");
        btnCargarJuegoInicio->setMinimumSize(QSize(50, 50));
        btnCargarJuegoInicio->setFont(font1);
        btnCargarJuegoInicio->setStyleSheet(QString::fromUtf8("    color: rgba(255, 255, 255, 1);              /* Color de la letra: blanco */\n"
"    background-color: rgba(255, 0, 0, 1);       /* Fondo rojo */\n"
"    border: 2px solid rgba(0, 0, 0, 1);          /* Borde negro */\n"
"    border-radius: 10px;                        /* Bordes redondeados */\n"
"    text-transform: uppercase;                   /* Texto en may\303\272sculas */"));

        verticalLayout_2->addWidget(btnCargarJuegoInicio);

        btnSalir = new QPushButton(pageInicio);
        btnSalir->setObjectName("btnSalir");
        btnSalir->setMinimumSize(QSize(50, 50));
        btnSalir->setFont(font1);
        btnSalir->setStyleSheet(QString::fromUtf8("    color: rgba(255, 255, 255, 1);              /* Color de la letra: blanco */\n"
"    background-color: rgba(255, 0, 0, 1);       /* Fondo rojo */\n"
"    border: 2px solid rgba(0, 0, 0, 1);          /* Borde negro */\n"
"    border-radius: 10px;                        /* Bordes redondeados */\n"
"    text-transform: uppercase;                   /* Texto en may\303\272sculas */"));

        verticalLayout_2->addWidget(btnSalir);

        verticalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        stackedWidget->addWidget(pageInicio);
        pageDificultad = new QWidget();
        pageDificultad->setObjectName("pageDificultad");
        verticalLayout_dif = new QVBoxLayout(pageDificultad);
        verticalLayout_dif->setObjectName("verticalLayout_dif");
        verticalSpacer_dif1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_dif->addItem(verticalSpacer_dif1);

        lblTituloDificultad = new QLabel(pageDificultad);
        lblTituloDificultad->setObjectName("lblTituloDificultad");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        lblTituloDificultad->setFont(font2);
        lblTituloDificultad->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_dif->addWidget(lblTituloDificultad);

        verticalSpacer_dif2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_dif->addItem(verticalSpacer_dif2);

        btnDificultadAleatoria = new QPushButton(pageDificultad);
        btnDificultadAleatoria->setObjectName("btnDificultadAleatoria");
        btnDificultadAleatoria->setMinimumSize(QSize(0, 50));
        btnDificultadAleatoria->setFont(font1);

        verticalLayout_dif->addWidget(btnDificultadAleatoria);

        btnDificultadEstrategica = new QPushButton(pageDificultad);
        btnDificultadEstrategica->setObjectName("btnDificultadEstrategica");
        btnDificultadEstrategica->setMinimumSize(QSize(0, 50));
        btnDificultadEstrategica->setFont(font1);

        verticalLayout_dif->addWidget(btnDificultadEstrategica);

        btnDificultadSuperIA = new QPushButton(pageDificultad);
        btnDificultadSuperIA->setObjectName("btnDificultadSuperIA");
        btnDificultadSuperIA->setMinimumSize(QSize(0, 50));
        btnDificultadSuperIA->setFont(font1);

        verticalLayout_dif->addWidget(btnDificultadSuperIA);

        verticalSpacer_dif3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_dif->addItem(verticalSpacer_dif3);

        btnContinuarJuego = new QPushButton(pageDificultad);
        btnContinuarJuego->setObjectName("btnContinuarJuego");
        btnContinuarJuego->setEnabled(false);
        btnContinuarJuego->setMinimumSize(QSize(0, 55));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        btnContinuarJuego->setFont(font3);

        verticalLayout_dif->addWidget(btnContinuarJuego);

        btnVolverDificultad = new QPushButton(pageDificultad);
        btnVolverDificultad->setObjectName("btnVolverDificultad");
        btnVolverDificultad->setMinimumSize(QSize(0, 40));
        btnVolverDificultad->setStyleSheet(QString::fromUtf8("    color: rgba(255, 255, 255, 1);              /* Color de la letra: blanco */\n"
"    background-color: rgba(255, 0, 0, 1);       /* Fondo rojo */\n"
"    border: 2px solid rgba(0, 0, 0, 1);          /* Borde negro */\n"
"    border-radius: 10px;                        /* Bordes redondeados */\n"
"    text-transform: uppercase;                   /* Texto en may\303\272sculas */"));

        verticalLayout_dif->addWidget(btnVolverDificultad);

        stackedWidget->addWidget(pageDificultad);
        pageJuego = new QWidget();
        pageJuego->setObjectName("pageJuego");
        verticalLayout_3 = new QVBoxLayout(pageJuego);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lblEstadoJuego = new QLabel(pageJuego);
        lblEstadoJuego->setObjectName("lblEstadoJuego");
        lblEstadoJuego->setFont(font3);
        lblEstadoJuego->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(lblEstadoJuego);

        lblIA = new QLabel(pageJuego);
        lblIA->setObjectName("lblIA");
        QFont font4;
        font4.setBold(true);
        lblIA->setFont(font4);

        verticalLayout_3->addWidget(lblIA);

        layoutCartasIA = new QHBoxLayout();
        layoutCartasIA->setObjectName("layoutCartasIA");

        verticalLayout_3->addLayout(layoutCartasIA);

        logBatalla = new QTextEdit(pageJuego);
        logBatalla->setObjectName("logBatalla");
        logBatalla->setMaximumSize(QSize(16777215, 150));
        logBatalla->setReadOnly(true);

        verticalLayout_3->addWidget(logBatalla);

        lblHumano = new QLabel(pageJuego);
        lblHumano->setObjectName("lblHumano");
        lblHumano->setFont(font4);

        verticalLayout_3->addWidget(lblHumano);

        layoutCartasHumano = new QHBoxLayout();
        layoutCartasHumano->setObjectName("layoutCartasHumano");

        verticalLayout_3->addLayout(layoutCartasHumano);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnAtacar = new QPushButton(pageJuego);
        btnAtacar->setObjectName("btnAtacar");
        btnAtacar->setMinimumSize(QSize(0, 40));
        btnAtacar->setFont(font1);

        horizontalLayout->addWidget(btnAtacar);

        btnOpciones = new QPushButton(pageJuego);
        btnOpciones->setObjectName("btnOpciones");
        btnOpciones->setMinimumSize(QSize(0, 40));
        btnOpciones->setFont(font4);

        horizontalLayout->addWidget(btnOpciones);


        verticalLayout_3->addLayout(horizontalLayout);

        stackedWidget->addWidget(pageJuego);
        pageFin = new QWidget();
        pageFin->setObjectName("pageFin");
        verticalLayout_4 = new QVBoxLayout(pageFin);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_4 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        lblResultadoFin = new QLabel(pageFin);
        lblResultadoFin->setObjectName("lblResultadoFin");
        lblResultadoFin->setFont(font2);
        lblResultadoFin->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(lblResultadoFin);

        verticalSpacer_5 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        btnGuardarFin = new QPushButton(pageFin);
        btnGuardarFin->setObjectName("btnGuardarFin");
        btnGuardarFin->setMinimumSize(QSize(0, 45));
        btnGuardarFin->setStyleSheet(QString::fromUtf8("    color: rgba(255, 255, 255, 1);              /* Color de la letra: blanco */\n"
"    background-color: rgba(255, 0, 0, 1);       /* Fondo rojo */\n"
"    border: 2px solid rgba(0, 0, 0, 1);          /* Borde negro */\n"
"    border-radius: 10px;                        /* Bordes redondeados */\n"
"    text-transform: uppercase;                   /* Texto en may\303\272sculas */"));

        verticalLayout_4->addWidget(btnGuardarFin);

        btnVolverMenu = new QPushButton(pageFin);
        btnVolverMenu->setObjectName("btnVolverMenu");
        btnVolverMenu->setMinimumSize(QSize(0, 45));
        btnVolverMenu->setStyleSheet(QString::fromUtf8("    color: rgba(255, 255, 255, 1);              /* Color de la letra: blanco */\n"
"    background-color: rgba(255, 0, 0, 1);       /* Fondo rojo */\n"
"    border: 2px solid rgba(0, 0, 0, 1);          /* Borde negro */\n"
"    border-radius: 10px;                        /* Bordes redondeados */\n"
"    text-transform: uppercase;                   /* Texto en may\303\272sculas */"));

        verticalLayout_4->addWidget(btnVolverMenu);

        verticalSpacer_6 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        stackedWidget->addWidget(pageFin);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "POO - Batalla de Elementos", nullptr));
        lblTitulo->setText(QCoreApplication::translate("MainWindow", "\302\241<span style=\"color: #2980b9;\">Agua</span>, <span style=\"color: #27ae60;\">Tierra</span> y <span style=\"color: #c0392b;\">Fuego</span>!", nullptr));
        btnIniciarJuego->setText(QCoreApplication::translate("MainWindow", "Iniciar Nueva Partida", nullptr));
        btnCargarJuegoInicio->setText(QCoreApplication::translate("MainWindow", "Cargar Partida Existente", nullptr));
        btnSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        lblTituloDificultad->setText(QCoreApplication::translate("MainWindow", "Selecciona la Dificultad de la IA", nullptr));
        btnDificultadAleatoria->setText(QCoreApplication::translate("MainWindow", "F\303\241cil (IA Aleatoria)", nullptr));
        btnDificultadEstrategica->setText(QCoreApplication::translate("MainWindow", "Normal (IA Estrat\303\251gica)", nullptr));
        btnDificultadSuperIA->setText(QCoreApplication::translate("MainWindow", "Dif\303\255cil (Super IA)", nullptr));
        btnContinuarJuego->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #27ae60; color: white;", nullptr));
        btnContinuarJuego->setText(QCoreApplication::translate("MainWindow", "COMENZAR BATALLA", nullptr));
        btnVolverDificultad->setText(QCoreApplication::translate("MainWindow", "Volver al Men\303\272", nullptr));
        lblEstadoJuego->setText(QCoreApplication::translate("MainWindow", "Ronda 1", nullptr));
        lblIA->setText(QCoreApplication::translate("MainWindow", "Cartas de la IA Enemiga:", nullptr));
        lblHumano->setText(QCoreApplication::translate("MainWindow", "Tus Cartas (Selecciona una para atacar):", nullptr));
        btnAtacar->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #e74c3c; color: white;", nullptr));
        btnAtacar->setText(QCoreApplication::translate("MainWindow", "ATACAR CON CARTA", nullptr));
        btnOpciones->setText(QCoreApplication::translate("MainWindow", "Pausar / Guardar", nullptr));
        lblResultadoFin->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2c3e50;", nullptr));
        lblResultadoFin->setText(QCoreApplication::translate("MainWindow", "Estado de la partida", nullptr));
        btnGuardarFin->setText(QCoreApplication::translate("MainWindow", "Guardar Partida", nullptr));
        btnVolverMenu->setText(QCoreApplication::translate("MainWindow", "Volver al Men\303\272 Principal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
