#pragma once

#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include "ui_OrbitDeterminationApp.h"
#include "ConcreteMediator1.h"

class OrbitDeterminationApp : public QMainWindow
{
    Q_OBJECT
protected:
    void resizeEvent(QResizeEvent* event) override;
public:
    OrbitDeterminationApp(QWidget* parent = nullptr);
    ~OrbitDeterminationApp();
private:
    void ReadSettings();
    void WriteSettings();
private:
    Ui::OrbitDeterminationAppClass ui;
    ConcreteMediator1* m_pConcreteMediator1;
    QSettings m_applicationSettings;
};
