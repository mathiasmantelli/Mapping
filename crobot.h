#ifndef CROBOT_H
#define CROBOT_H

#include <ArRobot.h>
#include <bits/stdc++.h>
#include <Aria.h>
#include <trigonometria.h>
#include <math.h>
#include <mapa.h>


#define SENSORES 8

using namespace std;

class CRobot{
    public:
        //-- Atributos
        ArRobot Robot;
        ArSonarDevice Sonar;
        ArSick Sick;
        ArLaserConnector *ConectorLaser;
        ArRobotConnector *ConectorRobot;
        ArArgumentParser *Parser;
        int Sensores[SENSORES];
        vector<ArSensorReading> *lasers;

        //-- Costructores
        CRobot();

        //-- Metodos
        bool Is_Connect();
        void Disconect();


        double GetX_Robot();
        double GetY_Robot();
        double GetAng_Robot();
        int GetSonar_Robot(int posicao);
        int GetLaser_Robot(int angle);
        void readingLaser();

        void Start_Moving(double esq, double dir);
        void End_Moving();
        void Move(double Dist);
        void Rotate(double Graus, int Sentido);

        int Xobst(int x_robo,double angulo_robo,int dst_obst, double ang_sonar);
        int Yobst(int y_robo,double angulo_robo,int dst_obst, double ang_sonar);


        //-- Destructor
        void Destructor();

private:
        void Read_Sensors();
};

#endif // CROBOT_H
