#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mapa.h>
#include <QLabel>
#include "ui_mainwindow.h"
#include <QTimer>
#include <brain_mapping.h>
#include <crobot.h>
#include <thread_robot.h>
#include <QtGui>
#include <QGraphicsView>
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateTime();
//    void Mostra_Imagem(QImage img);



private slots:
    void on_actionForward_triggered();

    void on_actionBack_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionStop_triggered();

private:
    Ui::MainWindow *ui;
    QLabel label;
    CRobot *MyRobot;
    Mapa *map;
    thread_robot *Navegador;
    QTimer Timer;
    brain_mapping *bm;
    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
