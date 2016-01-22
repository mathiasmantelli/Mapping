#ifndef BRAIN_MAPPING_H
#define BRAIN_MAPPING_H

#include <QThread>
#include <crobot.h>
#include <mapa.h>
#include <trigonometria.h>
#include <QImage>
#include <vector>
#include <thread_robot.h>

#define LIMITE 10


class brain_mapping : public QThread
{
public:
    brain_mapping(thread_robot *Nav,Mapa *map, CRobot *robot,int time);
    static QImage img;
    void Map_HIMM();
    void Map_BAYES();
    void run();

private:
    int a, i, j, Dst_Robo_Obst,T, Dst_Robo_Cel;
    coord robo,obstaculo,Vet_Robo_Ponto,Vet_Robo_Cel,cel;
    double Ang_Vetores, SONARS[8] = {90, 50, 30, 10, -10, -30, -50, -90};
    trigonometria tri;
    Mapa *map;
    CRobot *MyRobot;
    thread_robot *Navegador;
    double Laser;
    int time;
    bool Metodo;
    int maxX,maxY,minX,minY;
};

#endif // BRAIN_MAPPING_H
