#ifndef THREADMAP_H
#define THREADMAP_H
#include "mapa.h"
#include <QtCore>


class ThreadMap : public QThread
{
public:
    explicit ThreadMap(Mapa *m, int time);
    void run();

private:
    Mapa *map;
    int time;

};

#endif // THREADMAP_H
