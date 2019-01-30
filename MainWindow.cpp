#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer();

    //connect signals and slots
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(helpAboutSLot()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close())); //close slot is part of QMainWindow
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerTickSlot()));

    m_timer->setInterval(34); //about 30 frames per second, calculated using equation (1000 milliseconds divided by 30 fps)
    m_timer->setSingleShot(true);
    m_timer->start();
    raise(); //prevents window from starting up minimized
}
MainWindow::~MainWindow()
{
    delete m_timer;
    delete ui;
}

//slots
void MainWindow::helpAboutSLot()
{
    QString help_title = "About this game";
    QString help_text = "This program is a very simple game using Qt. Use the arrow keys to move the player and the left mouse button to shoot projectiles.";
    QMessageBox::about(this, help_title, help_text);
}
void MainWindow::timerTickSlot()
{
    ui->widget_gv->updateLoop();
    m_timer->start();
}

//keyboard events passed to the game view
void MainWindow::keyPressEvent(QKeyEvent* ev)
{
    ui->widget_gv->keyPressEvent(ev);
}
void MainWindow::keyReleaseEvent(QKeyEvent* ev)
{
    ui->widget_gv->keyReleaseEvent(ev);
}
