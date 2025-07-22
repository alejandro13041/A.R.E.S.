void moveServo(Servo servo, int prev, int curr, int vel){

    /* 
        extraigo los caracteres desde la poisicion 2 en adelante 
        ejem:"s1120" a "120"
     */

    btS = bt.substring(2,bt.length());   

    //convierto de string a entero

    curr = btS.toInt();

    //MUEVO EL SERVOMOTOR CON UN BARRIDO 

    if(prev > curr){

        for(int j = prev; j >= curr; j--){   
            servo1.write(j);
            delay(vel);
        }

    }else{

        for(int j= prev; j <= curr; j++){   
            servo.write(j);
            delay(vel);
        }

     }
  
    /*el angulo movido(s1Act) se convierte en la posicion anterior */

    prev = curr;
     
 } 
void save(){

    for (int i = 0; i < 7; i++)
        

    s1[index]= s1Ant;
    s2[index]= s2Ant;
    s4[index]= s4Ant;
    s5[index]= s5Ant;
    s6[index]= s6Ant;
    s7[index]= s7Ant;
    
    index++;

 }



void reset(){

    for (int i = 0; i < ; i++)

        memset(s1,0,sizeof(s1));
        memset(s2,0,sizeof(s2));
        memset(s4,0,sizeof(s4));
        memset(s5,0,sizeof(s5));
        memset(s6,0,sizeof(s6));
        memset(s7,0,sizeof(s7)); 

    index=0; 

 }

void servo(int arr*, Servo servo,int velG){

    if(arr[i] == arr[i+1]){

     } 

    if(arr[i] > arr[i+1]){

        for(int j = arr[i]; j >= arr[i+1];j--){
            servo.write(j);
            delay(velG);
         }

     }
            
    if(arr[i] < arr[i+1]){ 

        for(int j = arr[i]; j <= arr[i+1];j++){
            servo.write(j);
            delay(velG);
         }
     }  
 } 
