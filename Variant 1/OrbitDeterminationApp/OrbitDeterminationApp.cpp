#include "stdafx.h"
#include "OrbitDeterminationApp.h"

OrbitDeterminationApp::OrbitDeterminationApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //ui.fileResultsGroupBox
    m_pConcreteMediator1 = new ConcreteMediator1(&ui);
}

void OrbitDeterminationApp::resizeEvent(QResizeEvent* event)
{
    QPixmap bkgnd("Fantastic-scenery-mountains-space-planet_1920x1080.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    this->setPalette(p);
    ui.inputDataFrame->setStyleSheet("background-color: rgba(255, 255, 255, 127);");
    ui.measurementsFrame->setStyleSheet("background-color: rgba(255, 255, 255, 127);");
    ui.resultsGroupBox->setStyleSheet("background-color: rgba(255, 255, 255, 127);");
    //ui->statusbar->addWidget()
    //this->setAttribute(Qt::WA_TranslucentBackground);
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    QMainWindow::resizeEvent(event);
}

OrbitDeterminationApp::~OrbitDeterminationApp()
{
    delete m_pConcreteMediator1;
}
