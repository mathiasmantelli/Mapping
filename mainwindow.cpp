#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QImage myImage;
    map = new Mapa();
    MyRobot = new CRobot();
    Navegador = new thread_robot(map,MyRobot,100);

    bm = new brain_mapping(Navegador,map,MyRobot,100);
    bm->start();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QTimer *timer = new QTimer( this );
    timer->setInterval(300);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()) );
    timer->start();

    updateTime();
}

void MainWindow::updateTime(){

    scene->addPixmap(QPixmap::fromImage(brain_mapping::img));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionForward_triggered()
{
    MyRobot->Robot.setVel2(20,20);
}

void MainWindow::on_actionBack_triggered()
{
    MyRobot->Robot.setVel2(-20,-20);
}

void MainWindow::on_actionLeft_triggered()
{
    MyRobot->Robot.setVel2(15,-15);
}

void MainWindow::on_actionRight_triggered()
{
    MyRobot->Robot.setVel2(-15,15);
}

void MainWindow::on_actionStop_triggered()
{
    MyRobot->Robot.setVel2(0,0);
}
