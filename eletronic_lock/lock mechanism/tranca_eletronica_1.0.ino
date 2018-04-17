// Programa : Mecanismo da trancaEletrônica 1.0  
// Autor : Patrick Viana

#include <Servo.h>

//DEFINE O NOME DOS PINOS
#define buzzer 6
#define sensor 7
//POSIÇÃO DO ANGULO DO SERVO MOTOR
int pos = 0; 
//VARIAVEL AUXILIAR PARA O SENSOR REFLEXIVO
int objeto = 0; 
//VARIÁVEL AUXILIAR PARA O BUZZER
int som = 0;
//CRIA O OBJETO MYSERVO
Servo myservo;
 
   
void setup()  {  
  //DEFINE O PINO 8 COMO EMISSOR DOS PULSOS PARA O SERVO MOTOR
  myservo.attach(8);
  //DEFINIÇÃO IO DOS PINOS
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT); //Pino ligado ao coletor do fototransistor  
  //INICIALIZA A COMUNICAÇÃO SERIAL
  Serial.begin(9600);  
  //GARANTE QUE O BUZZER NÃO VAI APITAR A MENOS QUE SOLICITADO
  digitalWrite(buzzer, LOW);
}  
   
void loop()  {  
  //GUARDA VALOR ATUAL DO SENSOR REFLEXIVO NA PORTA DIGITAL 7
  objeto = digitalRead(sensor);  
  //VERIFICA SE O SENSOR DETECTOU O BATENTE DA PORTA{O = SIM E 1 = NÃO}.
  if (objeto == 0)  {  
    //CHAMA A FUNÇÃO FECHAR PORTA E GUARDA O RESULTADO NA FUNÇÃO NA VARIAVEL SOM
    som = fechar(som);
    /*
      A VARIAVEL "SOM" IMPEDE QUE O BUZZER FIQUE CONTINUAMENTE EMITINDO O ALERTA DE PORTA FECHADA
      POIS SEM ESTA VARIÁVEL O BUZZER CONTINUARIA EMITINDO O SOM A CADA 2 SEGUNDOS MESMO COM A PORTA JÁ FECHADA.
    */
  }  
  else  {  
    //CHAMA A FUNÇÃO ABRIR PORTA
    abrir();
  }  
} 


//FUNÇÕES

int fechar (int x)  {
    //ESCREVE NA PORTA SERIAL
    Serial.println("Objeto : Detectado"); 
    //AGUARDA 2 SEGUNDOS POR SEGURANÇA
    delay (2000);
    //POSICIONA A PALHETA DO SERVO MOTOR AO ANGULO DE 180 GRAUS = PORTA FECHADA
    myservo.write(180); 

    //A VARIAVEL "X"  RECEBE O VALOR DA VARIÁVEL "SOM" INICIALMENTE EM ZERO
    while(x == 0){
     // 2 BIPES CONSECUTIVOS PARA ALERTAR O FECHAMENTO DA PORTA
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    //INCREMENTO NA VARIÁVEL "X"
    x = 1;
    }
    //RETORNA O VALOR DA VARIAVEL "X" QUE SERÁ GUARDADA NA VARIÁVEL SOM PARA AS PRÓXIMAS ITERAÇÕES.
     return x;
}

int abrir (){
    //DECREMENTO NA VARIAVEL "SOM"
     som = 0;
     Serial.println("Objeto : Ausente !");  
     //POSICIONA A PALHETA DO SERVO MOTOR AO ANGULO DE 90 GRAUS = PORTA ABERTA
     myservo.write(90);
  }
