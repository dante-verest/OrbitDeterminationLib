#include "stdafx.h"
#include "OrbitDeterminationApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("OrbitDeterminationApp");
    //QTextCodec* p_utfCodec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForLocale(p_utfCodec);
    QApplication a(argc, argv);
    OrbitDeterminationApp w;
    w.show();
    return a.exec();
}
