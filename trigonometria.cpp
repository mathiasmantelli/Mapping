#include "trigonometria.h"

trigonometria::trigonometria()
{
}


int trigonometria::Dst_Dois_Pontos(coord robo,coord ponto){
    return (int)hypot((ponto.x-robo.x),(ponto.y-robo.y));
}

int trigonometria::Dst_Dois_Pontos2(int x1, int y1, int x2, int y2){
    return (int)hypot((x1-x2),(y1-y2));
}

double trigonometria::Norma_Vetor(coord ponto){
    return hypot(ponto.x,ponto.y);
}

coord trigonometria::Calcula_Vetor(coord robo, coord ponto){
    coord result;
    result.x = (ponto.x - robo.x);
    result.y = (ponto.y - robo.y);
    return result;
}

double trigonometria::Ang_Entre_Vetores(coord vetu, coord vetv){
                //PRODUTO ENTRE DOIS VETORES    //PRODUTO ENTRE A NORMA DE DOIS VETORES
    return acos(((vetu.x*vetv.x)+(vetu.y*vetv.y))/(this->Norma_Vetor(vetu)*this->Norma_Vetor(vetv)))*(180/M_PI);
}
