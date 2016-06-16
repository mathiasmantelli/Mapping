#include "brain_mapping.h"

QImage brain_mapping::img;

brain_mapping::brain_mapping(thread_robot *Nav, Mapa *m, CRobot *Robot, int t)
{
    map = m;
    MyRobot = Robot;
    Navegador = Nav;
    time = t;
    Metodo = true;  //TRUE = HIMM - FALSE = BAYES
    maxX = maxY = 0;
    minX = minY = TAM;
}

void brain_mapping::Map_HIMM(){
    double tamCel = 50;
    int vet[180],angulo;
    robo.x = MyRobot->GetX_Robot()/tamCel + TAM/2;
    robo.y = MyRobot->GetY_Robot()/tamCel + TAM/2;
    map->Set_Caminho((int)robo.x,(int)robo.y);
    map->Set_Robo_V((int)robo.x,(int)robo.y);
    for(a = 1; a <= 177; a+=3){
        vet[a] = MyRobot->GetLaser_Robot(a);
        vet[a+1] = MyRobot->GetLaser_Robot(a+1);
        vet[a+1] = MyRobot->GetLaser_Robot(a+2);
        Dst_Robo_Obst = min(MyRobot->GetLaser_Robot(a),min(MyRobot->GetLaser_Robot(a+1),MyRobot->GetLaser_Robot(a+2)));
        if(Dst_Robo_Obst == vet[a])angulo = a;
        if(Dst_Robo_Obst == vet[a+1])angulo = a+1;
        if(Dst_Robo_Obst == vet[a+2])angulo = a+2;
        Dst_Robo_Obst /= tamCel;

//        Dst_Robo_Obst = MyRobot->GetLaser_Robot(a)/tamCel;
        if(Dst_Robo_Obst <= MAX_DIST_LASER){
            obstaculo.x = MyRobot->Xobst(robo.x,MyRobot->GetAng_Robot(),Dst_Robo_Obst,90 - a);
            obstaculo.y = MyRobot->Yobst(robo.y,MyRobot->GetAng_Robot(),Dst_Robo_Obst,90 - a);

            map->Bresenham(robo.x,robo.y,obstaculo.x,obstaculo.y); //FUNCAO QUE VAI DESENHAR A MINHA LINHA NA MATRIZ;
            map->Atualiza_Mapa(obstaculo.x,obstaculo.y,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x-1,obstaculo.y-1,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x-1,obstaculo.y,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x-1,obstaculo.y+1,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x,obstaculo.y-1,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x,obstaculo.y+1,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x+1,obstaculo.y-1,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x+1,obstaculo.y,HIMM,REGIAO_OCUPADA,0,0);
            map->Atualiza_Mapa(obstaculo.x+1,obstaculo.y+1,HIMM,REGIAO_OCUPADA,0,0);
        }else{
            obstaculo.x = MyRobot->Xobst(robo.x,MyRobot->GetAng_Robot(),MAX_DIST_LASER,90 - a);
            obstaculo.y = MyRobot->Yobst(robo.y,MyRobot->GetAng_Robot(),MAX_DIST_LASER,90 - a);
            map->Bresenham(robo.x,robo.y,obstaculo.x,obstaculo.y); //FUNCAO QUE VAI DESENHAR A MINHA LINHA NA MATRIZ;
        }


        maxX = max((int)robo.x,max(maxX,max((int)obstaculo.x,max((int)obstaculo.x+1,(int)obstaculo.x-1))));
        minX = min((int)robo.x,min(minX,min((int)obstaculo.x,min((int)obstaculo.x+1,(int)obstaculo.x-1))));
        maxY = max((int)robo.y,max(maxY,max((int)obstaculo.y,max((int)obstaculo.y+1,(int)obstaculo.y-1))));
        minY = min((int)robo.y,min(minY,min((int)obstaculo.y,min((int)obstaculo.y+1,(int)obstaculo.y-1))));
//        maxX = max((int)robo.x,max(maxX,(int)obstaculo.x));
//        minX = min((int)robo.x,min(minX,(int)obstaculo.x));
//        maxY = max((int)robo.y,max(maxY,(int)obstaculo.y));
//        minY = min((int)robo.y,min(minY,(int)obstaculo.y));
    }

    brain_mapping::img = map->Gera_Imagem_Pixmap(Metodo,maxX,minX,maxY,minY);
    map->Set_Robo_F((int)robo.x,(int)robo.y);
}

void brain_mapping::Map_BAYES(){
    double tamCel = 50;
    robo.x = MyRobot->GetX_Robot()/tamCel + TAM/2;
    robo.y = MyRobot->GetY_Robot()/tamCel + TAM/2;
    for(a = 0; a < SENSORES; a++){
        Dst_Robo_Obst = MyRobot->GetSonar_Robot(a)/tamCel;
        obstaculo.x = MyRobot->Xobst(robo.x,MyRobot->GetAng_Robot(),Dst_Robo_Obst,SONARS[a]);
        obstaculo.y = MyRobot->Yobst(robo.y,MyRobot->GetAng_Robot(),Dst_Robo_Obst,SONARS[a]);

        for(i = MAX(0,robo.x-MAX_DIST); i <= MIN(TAM, robo.x+MAX_DIST); i++){        //PERCORRO
            for(j = MAX(0,robo.y-MAX_DIST); j <= MIN(TAM,robo.y+MAX_DIST);j++){    //A MATRIZ
                cel.x = i;
                cel.y = j;
                Vet_Robo_Ponto = tri.Calcula_Vetor(robo,obstaculo); //VETOR ENTRE O ROBO E O OBSTACULO
                Vet_Robo_Cel = tri.Calcula_Vetor(robo,cel);   //VETOR ENTRE O ROBO E A CELULA DA MATRIZ
                Ang_Vetores = tri.Ang_Entre_Vetores(Vet_Robo_Cel,Vet_Robo_Ponto);
                Dst_Robo_Cel = tri.Dst_Dois_Pontos(robo,cel);
                if(Ang_Vetores <= Beta){  //METODO BAYES
                    if((Dst_Robo_Obst != MAX_DIST) && (Dst_Robo_Cel <= Dst_Robo_Obst+5) && (Dst_Robo_Cel > Dst_Robo_Obst-5)){
                        map->Atualiza_Mapa(cel.y,cel.x,BAYES,REGIAO_OCUPADA,Ang_Vetores,Dst_Robo_Cel);
                    }
                    if(Dst_Robo_Cel < (Dst_Robo_Obst - 5)){
                        //                                    cout <<  Dst_Robo_Cel << "<" << (Dst_Robo_Obst - 5)  << endl;
                        map->Atualiza_Mapa(cel.y,cel.x,BAYES,REGIAO_LIVRE,Ang_Vetores,Dst_Robo_Cel);
                    }
                }

            }

        }
    }
    brain_mapping::img = map->Gera_Imagem_Pixmap(Metodo,TAM,0,TAM,0);
}

void brain_mapping::run(){

    //GIRO 360
    while(MyRobot->GetAng_Robot() <= 0){
        MyRobot->Robot.setVel2(40,0);
        Map_HIMM();
    }

    Navegador->start();
    while(true){
        map->Campo_Potencial(maxX,minX,maxY,minY);
        Map_HIMM();
        QThread::msleep(time);
    }

}
