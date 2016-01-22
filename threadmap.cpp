#include "threadmap.h"
#include "mapa.h"
#include <QtCore>
#include <QDebug>


ThreadMap::ThreadMap(Mapa *m, int t) : map(m),time(t){
}


void ThreadMap::run(){
   for(;;){
        map->update();
        QThread::msleep(time);
    }
}

