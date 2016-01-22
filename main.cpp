#include <QApplication>
#include <QApplication>
#include "mainwindow.h"
#include <QImage>
#include <QtGui>
#include <QLabel>
#include <bits/stdc++.h>
#include <crobot.h>
#include <Aria.h>
#include <mapa.h>
#include <time.h>
#include <math.h>
#include <threadmap.h>
#include <trigonometria.h>
#include <brain_mapping.h>

#define dist 50

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mw;

    mw.showMaximized();
    return app.exec();
}
