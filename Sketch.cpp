/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//inclusão de bibliotecas
#include <IRremote.h>
#include "functions.h"
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio



//definições dos códigos dos botões do controle IR
#define on_off 16753245
#define down 16730805
#define up 16718055
#define bot2 16736925

const int IRpin = 11; //pino do sensor IR
int led = 5;  //pino do led que está conectado no relé
int intensity = 255;  //intensidade inicial (pwm = 255)

bool ligado = false; //condição que define se o led está ligado ou não
bool comando = false; //condição que define se um comando foi recebido ou não (true = recebeu, false = não recebeu)
bool piscando = false; //condição que define se o led está piscando ou não

//declaração do objeto sensor IR
IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
  pinMode(led, OUTPUT); //declara led como OUTPUT
  Serial.begin(9600); //inicia o Serial
  irrecv.enableIRIn(); //Inicia o sensor
}

/*Função que realiza as repetições
*/
void loop()
{
  //verifica se comando = true
  if(comando){
    //verifica se ligado = true
    if(ligado){
      //verifica se piscando = true
      if(piscando){
        blinkLED(led, intensity);
      }
      else{
        analogWrite(led, intensity);
        comando = false;
      }
  }
  else{
    digitalWrite(led, LOW);
  }
}
  //verifica se o sensor recebeu sinal
  if (irrecv.decode(&results)){
    unsigned long value = results.value;  //variável que armazena os valores dos botões respectivos
    Serial.println(value);

    //se valor = ligar/desligar, liga ou desliga o led
    if(value == on_off){
      ligado = !ligado;
      comando = true;
    }

    //se valor = cima, chama a função incrementPWM
    else if(value == up){
      intensity = incrementPWM(intensity, 30);
      comando = true;
    }

    //se valor = baixo, chama a função incrementPWM
    else if(value == down){
      intensity = incrementPWM(intensity, -30);
      comando = true;
    }

    //se valor = botão 2, troca o estado da variável piscando
    else if(value == bot2){
      piscando = !piscando;
      comando = true;
    }
  irrecv.resume(); // Receive the next value
  }
}
