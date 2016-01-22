#ifndef THREAD_ROBOT_H
#define THREAD_ROBOT_H
#include <QThread>
#include <crobot.h>
#include <mapa.h>
#include <bits/stdc++.h>


class thread_robot : public QThread
{
public:
    thread_robot(Mapa *m,CRobot *MyRobot, int time);
    void run();
    //

private:
    CRobot *MyRobot;
    Mapa *map;
    int time;

};

#endif // THREAD_ROBOT_H
