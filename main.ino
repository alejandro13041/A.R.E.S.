#include <Servo.h>
#include <SoftwareSerial.h>
#include "aux.h"

SoftwareSerial Bluetooth(3, 4); // RX, TX

/*

    Estas son las estructuras utiles para el programa
    Objetos servo   :
    Velocidad servo :
    posicion anterior de los servos:
    poscicion acutal de los servos:
    matrices para almacenas las posiciones de cada servo:

 */

int posServos[6][50];

Servo servos[6];
int   velServos[6];
int   posCurr[6];
int   posPrev[6];

int index=0;
int velG=25;

std::String bt;
std::string btS;

void setup(){

    Serial.begin(115200);
    Bluetooth.begin(9600);
    Bluetooth.setTimeout(10);

    /*rangos calibrados a 510–1200 µs para evitar daño mecánico */

    servo1.attach(5,510,1200);  
    servo2.attach(11,650,1400); 
    servo3.attach(6,650,1400);  
    servo4.attach(7,650,1400);  
    servo5.attach(8,650,1400);  
    servo6.attach(9,800,1290);  
    servo7.attach(10,700,1290); 

    /*
        
        La estructura VelServos, se encarga de almacenar
        la configuración de la velocidad inicial de los 
        servomotores del brazo.

        Base   : 15
        Hombro : 25
        Codo1  : 20
        Codo2  : 20
        Muñeca : 15
        Gripper: 15

     */

    velServos[0] = 15;   
    velServos[1] = 25; 
    velServos[3] = 20; 
    velServos[4] = 20; 
    velServos[5] = 15; 
    velServos[6] = 15; 

    /*
        
        El arreglo posPrev, se encarga de almacenar
        la configuración de la Poscicion previa
        de los servomotores del brazo.

        Base    : 90
        Hombro1 : 100
        Hombro2 : 80
        Codo1   : 115
        Codo2   : 60
        Muñeca  : 90
        Gripper : 60

     */

    posPrev[0] =  90;   
    posPrev[1] = 100; 
    posPrev[3] =  80; 
    posPrev[4] = 115; 
    posPrev[5] =  60; 
    posPrev[6] =  90; 
    posPrev[7] =  60; 


    //Importante empezar s2 y s3 complementados a 180°;es decir; s2+s3=180;
 
    for (int i = 0; i < 7; i++)
        servos[i].write(posPrev[i]);

    delay(50);

 }
void loop(){

    if(Bluetooth.available()>0){

        bt = Bluetooth.readString();  

        switch(bt){

            case 1: moveServo(servos[0], posPrev[0], posCurr[0], velServos[0]);
            case 2: moveServo(servos[1], posPrev[1], posCurr[1], velServos[1]);
            case 3: moveServo(servos[2], posPrev[2], posCurr[2], velServos[2]);
            case 4: moveServo(servos[3], posPrev[3], posCurr[3], velServos[3]);
            case 5: moveServo(servos[4], posPrev[4], posCurr[4], velServos[4]);
            case 6: moveServo(servos[5], posPrev[5], posCurr[5], velServos[5]);
            case 7: moveServo(servos[6], posPrev[6], posCurr[6], velServos[6]);
            case 8: save();
            case 9: reset();

         }
       
        if(bt.startsWith("RUN")){

           /*Ejecuta los pasos una y otra vez hasta que 
             se pulse el botón "RESET" o espera hasta que
             se vuelva a pulsar "RESET".
             */

            /*
                MIENTRAS NO SE PRESIONE 'RESET' SE MANTIENE 
                EN EL BUCLE y SOLO FUNCIONA BOTON "PAUSE"
             */

            while(bt.startsWith("RESET") != true){

                for(int i=0; i<= index-2;i++){   

                    if(Bluetooth.available()>0){

                        bt = Bluetooth.readString(); 

                        /* Ejecuta los pasos una y otra vez hasta que se pulse el botón "RUN" 
                           o espera hasta que se vuelva a pulsar "RUN" 
                         */

                        if(bt.startsWith("PAUSE") == true){

                            /*MIENTRAS NO SE PRESIONE 'RUN' SE MANTIENE EN EL BUCLE Y SOLO FUNCIONA BOTON "RESET" */

                            while(bt.startsWith("RUN") != true){

                                if(Bluetooth.available()>0){

                                    bt = Bluetooth.readString();

                                    if(bt.startsWith("RESET") == true)
                                        break;

                                 }
                             }                                            
                         }

                        if(bt.startsWith("ss")){

                            btS  = bt.substring(2,bt.length());   
                            velG = btS.toInt();

                         }
                     }

                    servo(); //1
                    servo(); //2
                    servo(); //3
                    servo(); //4
                    servo(); //5
                    servo(); //6
                    servo(); //7
                                                                                                        
                 }                 
             }
         }          
     }         
 }
