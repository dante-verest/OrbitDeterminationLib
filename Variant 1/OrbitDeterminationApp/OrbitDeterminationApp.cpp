#include "stdafx.h"
#include "OrbitDeterminationApp.h"

OrbitDeterminationApp::OrbitDeterminationApp(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->ReadSettings();
    m_pConcreteMediator1 = new ConcreteMediator1(&ui);
};

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
    ui.statusBar->setStyleSheet("background-color: rgba(255, 255, 255, 127);");
    //ui->statusbar->addWidget()
    //this->setAttribute(Qt::WA_TranslucentBackground);
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    QMainWindow::resizeEvent(event);
};

OrbitDeterminationApp::~OrbitDeterminationApp()
{
    delete m_pConcreteMediator1;
    this->WriteSettings();
};

void OrbitDeterminationApp::ReadSettings()
{
    m_applicationSettings.beginGroup("/Settings for the application window");

    int x = m_applicationSettings.value("/x", QWidget::x()).toInt();
    int y = m_applicationSettings.value("/y", QWidget::y()).toInt();
    int width = m_applicationSettings.value("/width", QWidget::width()).toInt();
    int height = m_applicationSettings.value("/height", QWidget::height()).toInt();

    m_applicationSettings.endGroup();

    QWidget::move(x, y);
    QWidget::resize(width, height);
};

void OrbitDeterminationApp::WriteSettings()
{
    m_applicationSettings.beginGroup("/Settings for the application window");

    m_applicationSettings.setValue("/x", QWidget::x());
    m_applicationSettings.setValue("y", QWidget::y());
    m_applicationSettings.setValue("width", QWidget::width());
    m_applicationSettings.setValue("/height", QWidget::height());

    m_applicationSettings.endGroup();
};