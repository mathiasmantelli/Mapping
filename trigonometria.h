#ifndef TRIGONOMETRIA_H
#define TRIGONOMETRIA_H
#include <math.h>

typedef struct coord{
    double x;
    double y;
}coord;


class trigonometria
{
public:
    trigonometria();
    coord Calcula_Vetor(coord robo, coord ponto);
    double Norma_Vetor(coord ponto);
    int Dst_Dois_Pontos(coord robo,coord ponto);
    int Dst_Dois_Pontos2(int x1, int y1, int x2, int y2);
    double Ang_Entre_Vetores(coord vetu, coord vetv);
};

#endif // TRIGONOMETRIA_H
