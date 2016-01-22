#ifndef MAPA_H
#define MAPA_H
#include <bits/stdc++.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <QLabel>
#include <iostream>
#include <QImage>
#include <unistd.h>
#include <math.h>
#include <QApplication>
#include <QtGui>
#include <cstdlib>
#include <trigonometria.h>




#define TAM 1000
#define ESC 100
#define MED 10
#define Beta 15.0
#define REGIAO_OCUPADA 1
#define REGIAO_LIVRE 2
#define BAYES 1
#define HIMM 2
#define DEAD 3
#define MAX_DIST 50.0
#define MAX_DIST_LASER 190.0
#define maxx 0.95

using namespace std;

typedef struct matriz{
    double bayes;
    int himm;
    double potencial;
    int tipo; //0 - LIVRE, 1 - OBSTACULO, 2 - DESCONHECIDA
    int visitada;
    int cor;
    double angulo;
    bool caminho;
    bool robo;
}matriz;


class Mapa
{
public:
    void Atualiza_Mapa(int i, int j, int Metodo, int Regiao_Sonar, double Ang_Vetor, int Dst_Robo_Cel);
    void Gera_Imagem_PGM();
    int Mascara(int i,int j);
    int Get_Cel(int i, int j);
    void Bresenham(int x1,int y1,int const x2, int const y2);
    void Decisao(int distancia_robo_celula,int xo,int yo, int Dst_Robo_Obst);
    void Campo_Potencial(int maxX, int minX, int maxY, int minY);
    double Get_Ang_Potencial(int x,int y);
    bool v(int i, int j);
    void Set_Cel(int i, int j, int value);
    void Set_Lido();
    void Vizinhos(int i, int j);
    void Set_Caminho(int i, int j);
    void Set_Robo_V(int i, int j);
    void Set_Robo_F(int i, int j);
    QImage Gera_Imagem_Pixmap(bool Metodo, int max_x, int minx, int maxy, int miny);
    Mapa();
    trigonometria tri;

signals:
    void Apresenta_Imagem(QImage img);

private:
    matriz **map;
};

#endif // MAPA_H
