#include "functions.h"

/*
 * Função que faz o led piscar de acordo com a intensidade
 */
void blinkLED(int led, int intensity){
  analogWrite(led, intensity);
  delay(500);
  analogWrite(led, LOW);
  delay(500);
}

/*
 * Função que incementa ou descrementa o valor do sinal PWM para alterar a intensidade do led
 */
int incrementPWM(int val, int inc){
  val += inc;
  val = (val > 255) ? 255 : (val < 10) ? 10 : val;
  return val;
}
