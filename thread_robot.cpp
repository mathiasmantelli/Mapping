#include "thread_robot.h"
#include <iostream>

thread_robot::thread_robot(Mapa *m,CRobot *Robot, int t)
{
    MyRobot = Robot;
    map = m;
    time = t;
}

void thread_robot::run(){
    int leitura,x_robo,y_robo;
    double ang,ang_robo,diff,tamCel=50;
    while(true){
        x_robo = (int)MyRobot->GetX_Robot()/tamCel + TAM/2;
        y_robo = (int)MyRobot->GetY_Robot()/tamCel + TAM/2;

        ang = map->Get_Ang_Potencial(x_robo,y_robo);
        ang_robo = MyRobot->Robot.getTh();

        diff = (ang-ang_robo);
        diff = fmod((diff+180+360),360) - 180;
        if(diff <= 90){
            diff = diff * (M_PI/180);
            MyRobot->Robot.setVel2(50-50*sin(diff),50+50*sin(diff));
        }else{
            diff = diff * (M_PI/180);
            MyRobot->Robot.setVel2(10-20*sin(diff),10+20*sin(diff));
        }
        QThread::msleep(time);
    }
}
