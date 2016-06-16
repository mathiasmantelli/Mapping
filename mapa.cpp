#include "mapa.h"

Mapa::Mapa(){
    map = (matriz**) malloc (TAM * sizeof(matriz*));
    for(int i = 0; i < TAM; i++){
        map[i] = (matriz*) malloc (TAM * sizeof(matriz));
        for(int j = 0; j < TAM; j++){
            map[i][j].bayes = 0.5;
            map[i][j].himm = 0;
            map[i][j].potencial = 0;
            map[i][j].tipo = 2;
            map[i][j].visitada = 0;
            map[i][j].cor = 140;
            map[i][j].angulo = 0;
            map[i][j].caminho = false;
            map[i][j].robo = false;
        }
    }
}

void Mapa::Set_Lido(){
    memset(*map,false, sizeof(map));
}

void Mapa::Set_Caminho(int i, int j){ map[i][j].caminho = true;/*map[i+1][j].caminho = true;map[i-1][j].caminho = true;map[i][j+1].caminho = true;map[i][j-1].caminho = true;*/}
void Mapa::Set_Robo_V(int i, int j){ map[i][j].robo = true;/*map[i+1][j].robo = true;map[i-1][j].robo = true;map[i][j+1].robo = true;map[i][j-1].robo = true;*/}
void Mapa::Set_Robo_F(int i, int j){map[i][j].robo = false;/*map[i+1][j].robo = false;map[i-1][j].robo = false;map[i][j+1].robo = false;map[i][j-1].robo = false;*/}

//                                       bayes/himm,   I/II
void Mapa::Atualiza_Mapa(int i, int j, int Metodo, int Regiao_Sonar, double Ang_Vetor, int Dst_Robo_Cel){
    double pso,psv;

    if(Metodo == BAYES){ // metodo = 1: BAYES
        if(Regiao_Sonar == REGIAO_OCUPADA){ //regiao = 1: regiao I do sonar
            pso = 0.5 * ((2*MAX_DIST - Dst_Robo_Cel)/(2*MAX_DIST) + (2.0*Beta - Ang_Vetor)/(2*Beta)) * maxx;
        }else{ //regiao = REGIAO_LIVRE: regiao II do sonar
            psv = 0.5 * ((2*MAX_DIST - Dst_Robo_Cel)/(2*MAX_DIST) + (2.0*Beta - Ang_Vetor)/(2*Beta));
            max(psv,1.0-maxx);
            pso = 1.0 -psv;
        }
        map[i][j].bayes = (pso*map[i][j].bayes) / (pso * map[i][j].bayes + (1.0 - pso) * (1.0 - map[i][j].bayes));

    }else if (Metodo==2){ //metodo = 2: HIMM
        map[i][j].visitada = 1;

        if(Regiao_Sonar == REGIAO_OCUPADA){ //regiao = 1: regiao I do sonar
//            if(!map[i][j].lido){  //EVITA QUE ACONTEÇA MAIS DE UMA LEITURA, EM POUCO TEMPO, NA MESMA CÉLULA
                map[i][j].himm += 3;
                map[i][j].tipo = 1;
                map[i][j].potencial = 1;
                map[i][j].himm = min(map[i][j].himm,15);
//                map[i][j].himm = min(Mascara(i,j) ,15);
//                map[i][j].lido = true;
//            }
        }else{ //regiao = REGIAO_LIVRE: regiao II do sonar
//            if(!map[i][j].lido){  //EVITA QUE ACONTEÇA MAIS DE UMA LEITURA, EM POUCO TEMPO, NA MESMA CÉLULA
                map[i][j].himm -= 0.3;
                map[i][j].tipo = 0;
                map[i][j].himm = max(map[i][j].himm ,0);
//                map[i][j].lido = true;
//            }
        }


    }else{ //metodo = 3: DEAD
        if(Regiao_Sonar == REGIAO_OCUPADA){ //regiao = 1: regiao I do sonar
            map[i][j].bayes = 0;
        }else{ //regiao = REGIAO_LIVRE: regiao II do sonar
            map[i][j].bayes = Beta;
        }
    }
}

void Mapa::Gera_Imagem_PGM(){

    int i, j;
    char nome[50];
    FILE *fp,*fp2;
    sprintf(nome, "%s.pgm", "saida_mapa_BAYES");
    fp = fopen(nome,"wb");
    fprintf(fp,"P5\n%d %d\n%d\n", TAM,TAM,255);
    for(i = 0; i < TAM;i++){
        for(j = 0; j < TAM;j++){
            fprintf(fp,"%c",(int)(map[i][j].bayes*255));
        }
    }
    fclose(fp);
    sprintf(nome, "%s.pgm", "saida_mapa_HIMM");
    fp2 = fopen(nome,"wb");
    fprintf(fp2,"P5\n%d %d\n%d\n", TAM,TAM,Beta);
    for(i = 0; i < TAM;i++){
        for(j = 0; j < TAM;j++){
            fprintf(fp2,"%c",(map[i][j].himm));
        }
    }
    fclose(fp2);
}

int Mapa::Get_Cel(int i, int j){
    return map[i][j].himm;
}

void Mapa::Set_Cel(int i, int j, int value){
    map[i][j].himm = value;
}


QImage Mapa::Gera_Imagem_Pixmap(bool Metodo, int max_x, int minx, int maxy, int miny){
    QImage img(TAM, TAM, QImage::Format_RGB32);
    float value;
    img.fill(QColor(Qt::white).rgb());
    for (int x = minx; x < max_x; ++x) {
        for (int y = miny; y < maxy; ++y) {
            //HIMM
            if(Metodo){
                if(map[x][y].visitada){
                    if(map[x][y].tipo == 0 && map[x][y].tipo != 2){
                        double a = map[x][y].potencial;
                        img.setPixel(x,TAM-y,qRgb(0,0,255-(a*255))); //REGIÃO LIVRE CONHECIDA
                    }else{
                        img.setPixel(x,TAM-y,qRgb(255,255,255)); //OBSTÁCULOS
                    }
                }else{
                    img.setPixel(x, TAM-y, qRgb(0, 255, 0));  //REGIOES DESCONHECIDAS
                }
                if(map[x][y].caminho) img.setPixel(x,TAM-y,qRgb(255,0,0));
                if(map[x][y].robo) img.setPixel(x,TAM-y,qRgb(255,255,0));


            }else{ //BAYES
                value = (1-map[x][y].bayes) *255.;
                img.setPixel(x, TAM-y, qRgb(value, value, value));
            }

        }
   }

//    img.save(QString("map.png"));
    return img;
}

int Mapa::Mascara(int i,int j){
    int x, y;
    double resultado = 0;
    for(x = max(0, i-1); x <= min(TAM,i+1);x++){
        for(y = max(0,j-1); y <= min(TAM,j+1);y++){
            if(x == i && y == j){
            resultado += map[x][y].himm;
            }
            resultado += map[x][y].himm * 0.5;
        }
    }
    return (int)resultado;
}

void Mapa::Bresenham(int x_robot, int y_robot, int  x_obst, int y_obst){
    int dx, dy, p, incE, incNE, stepx, stepy, value;
    int tempx = x_robot;
    int tempy = y_robot;

    dx = (x_obst - x_robot);
    dy = (y_obst - y_robot);

    if(dy < 0) dy = -dy, stepy = -1;
    else stepy = 1;

    if(dx < 0) dx = -dx, stepx = -1;
    else stepx = 1;

    this->Atualiza_Mapa(tempx,tempy,HIMM,REGIAO_LIVRE,0,0);

    if(dx > dy){
        p = 2*dy-dx;
        incE = 2*dy;
        incNE = 2*(dy-dx);

        while(tempx != x_obst){
            tempx += stepx;
            if(p < 0) p+= incE;
            else tempy += stepy, p+=incNE;

            this->Atualiza_Mapa(tempx,tempy,HIMM,REGIAO_LIVRE,0,0);
        }
    }else{
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx-dy);
        while(tempy != y_obst){
            tempy += stepy;
            if(p < 0) p += incE;
            else tempx += stepx, p += incNE;

            this->Atualiza_Mapa(tempx,tempy,HIMM,REGIAO_LIVRE,0,0);

        }
    }
}

bool Mapa::v(int i, int j){
  return  i >= 0 && i < TAM && j >= 0 && j < TAM;
}

void Mapa::Campo_Potencial(int maxX, int minX, int maxY, int minY){

    double new_pot = 0.0,esq,dir,cima,baixo;
    double erro_pot = 1.,erro_max = 0.000001;

    //CALCULANDO O POTENCIAL POR VÁRIOS SENTIDOS NA MATRIZ
    while(erro_pot > erro_max){
        erro_pot = 0;

        //CIMA-BAIXO, ESQ-DIR
        for(int i = minX; i < maxX; i++){
            for(int j = minY; j < maxY; j++){
                if(map[i][j].visitada == 1 && map[i][j].tipo == 0){
                    esq = dir = cima = baixo = 0.0;

                    esq = map[i-1][j].potencial;
                    dir = map[i+1][j].potencial;
                    cima = map[i][j-1].potencial;
                    baixo = map[i][j+1].potencial;

                    map[i][j].potencial = (esq + dir + cima + baixo)*0.25;
                }
            }
        }

//        //BAIXO-CIMA,ESQ-DIR
        for(int i = maxX; i > minX; i--){
            for(int j = minY; j < maxY; j++){
                if(map[i][j].visitada == 1 && map[i][j].tipo == 0){
                    esq = dir = cima = baixo = 0.0;

                    esq = map[i-1][j].potencial;
                    dir = map[i+1][j].potencial;
                    cima = map[i][j-1].potencial;
                    baixo = map[i][j+1].potencial;

                    map[i][j].potencial = (esq + dir + cima + baixo)*0.25;

                }
            }
        }

//        //CIMA-BAIXO, DIR-ESQ
        for(int i = minX; i < maxX; i++){
            for(int j = maxY; j > minY; j--){
                if(map[i][j].visitada == 1 && map[i][j].tipo == 0){
                    esq = dir = cima = baixo = 0.0;

                    esq = map[i-1][j].potencial;
                    dir = map[i+1][j].potencial;
                    cima = map[i][j-1].potencial;
                    baixo = map[i][j+1].potencial;

                    map[i][j].potencial = (esq + dir + cima + baixo)*0.25;
                }
            }
        }
        //BAIXO-CIMA, DIR-ESQ
        for(int i = maxX; i > minX; i--){
            for(int j = maxY; j > minY; j--){
                if(map[i][j].visitada == 1 && map[i][j].tipo == 0){
                    esq = dir = cima = baixo = 0.0;

                    esq = map[i-1][j].potencial;
                    dir = map[i+1][j].potencial;
                    cima = map[i][j-1].potencial;
                    baixo = map[i][j+1].potencial;
                    new_pot = (esq + dir + cima + baixo)*0.25;
                    erro_pot += pow(map[i][j].potencial-new_pot,2);  //CALCULANDO O ERRO PRA SABER QUANDO DEVE PARAR DE ATUALIZAR O POTENCIAL
                    map[i][j].potencial = new_pot;
//                    map[i][j].angulo = atan2(-(baixo-cima),-(dir-esq))*180/M_PI; //CALCULANDO O GRADIENTE DESCENDENTE

                }
            }
        }
    }//FIM-WHILE
}

double Mapa::Get_Ang_Potencial(int i,int j){
    double esq,dir,cima,baixo;
    esq = map[i-1][j].potencial;
    dir = map[i+1][j].potencial;
    cima = map[i][j-1].potencial;
    baixo = map[i][j+1].potencial;
    return map[i][j].angulo = atan2(-(baixo-cima),-(dir-esq))*180/M_PI;
}

void Mapa::Vizinhos(int x, int y){
    int i, j;
    for(i = x - 1; i <= x + 1; i++){
        for(j = y - 1; j <= y + 1; j++){
            if(v(i,j)){
                map[i][j].himm += 3;
                map[i][j].tipo = 1;
                map[i][j].potencial = 1;
                map[i][j].himm = min(Mascara(i,j) ,15);
            }
        }
    }
}
