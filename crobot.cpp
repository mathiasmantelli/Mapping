#include "crobot.h"

CRobot::CRobot(){
      int argc = 4;
      char** argv = (char **) new char[4];

      Aria::init();

      argv[0] = "-rh";
//      argv[1] = "192.168.1.11";
      argv[1] = "localhost";
      argv[2] = "-remoteLaserTcpPort";
      argv[3] = "10002";

      Parser = new ArArgumentParser (&argc, argv);

      ConectorRobot =  new ArRobotConnector(Parser, &Robot);
      Robot.addRangeDevice(&Sick);

      if(!ConectorRobot->connectRobot()){
        cout<<" -> Nao foi possivel conectar com o robo."<<endl;
        Aria::exit(1);
      }else cout<<" -> Robot conectado."<<endl;

      ConectorLaser = new ArLaserConnector(Parser, &Robot, ConectorRobot);
      ConectorLaser->setupLaser(&Sick);

      Sick.runAsync();
      Robot.setHeading(0);
      Robot.runAsync(true);
      Robot.enableMotors();

      if(!ConectorLaser->connectLaser(&Sick)) cout<<" Nao foi possivel conectar com o laser."<<endl;
      else cout<<" -> Laser conectado."<<endl;
}


bool CRobot::Is_Connect(){
    return Robot.isConnected();
}

void CRobot::Disconect(){
    Robot.stopRunning(true);
}

void CRobot::Read_Sensors(){
    for(int i = 0; i < SENSORES; i++){
        Sensores[i] = (int)Robot.getSonarRange(i);
    }
}

double CRobot::GetX_Robot(){
    return Robot.getX();
}

double CRobot::GetY_Robot(){
    return Robot.getY();
}

double CRobot::GetAng_Robot(){
    return Robot.getTh();
}

int CRobot::GetSonar_Robot(int posicao){
    this->Read_Sensors();
    return Sensores[posicao];
}

void CRobot::readingLaser(){
    if(Sick.isConnected()){
        Sick.lockDevice();
        lasers = Sick.getRawReadingsAsVector();
        Sick.unlockDevice();
    }
}


int CRobot::GetLaser_Robot(int angle){
    readingLaser();
    if((this->lasers == NULL) || (this->lasers->size() < angle)){
        return 0;
    }
    return this->lasers->at(angle).getRange();
}

void CRobot::Start_Moving(double esq, double dir){
    Robot.lock();
    Robot.setVel2(esq, dir);
    Robot.unlock();
}

void CRobot::End_Moving(){
    Robot.stop();
}

void CRobot::Move(double Dist){
    Robot.lock();
    Robot.move(Dist);
    Robot.unlock();
}

void CRobot::Rotate(double Graus, int Accion){
    Robot.setDeltaHeading(Graus);

    /* 0-detenido  1-avanzando 2-retrocediendo*/
    if(Accion == 0) Robot.setVel(0);
    if(Accion == 1) Robot.setVel(50);
    if(Accion == 2) Robot.setVel(-50);
}

void CRobot::Destructor(){
    Disconect();
    Aria::shutdown();
}

int CRobot::Xobst(int x_robo,double angulo_robo, int dst_obst, double ang_sonar){
    return x_robo + dst_obst * cos((angulo_robo + ang_sonar)*(M_PI/180));  //X  obst

}

int CRobot::Yobst(int y_robo,double angulo_robo, int dst_obst, double ang_sonar){
    return y_robo + dst_obst * sin((angulo_robo + ang_sonar)*(M_PI/180));  //X  obst
}
