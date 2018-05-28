#include <stdio.h>
#include "mraa/api/mraa/pwm.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>


#define PINO_PWM 3

#define PWM_FREQ 200

mraa_pwm_context initPWM(){     //Inicializa PWM com frequencia de 200
    mraa_pwm_context pwm;    //Declara variavel para PWM
    pwm = mraa_pwm_init(PINO_PWM);     //Seta pino 3 para PWM
    mraa_pwm_period_us(pwm, PWM_FREQ);     //Seta periodo do PWM baseado na frequencia
    mraa_pwm_enable(pwm, 1);     //Habilita pwm

    return pwm;
}

void setPWM(mraa_pwm_context pwm, float valor){     //Seta PWM e recebe como valor a porcentagem alta do ciclo
    mraa_pwm_write(pwm, valor);
}

float readPWM(mraa_pwm_context pwm){     //Le valor do PWM
    return mraa_pwm_read(pwm);
}

float geraValor(float *x){
    float w[4];
    float valor = 0, temp = 0;


    for (int i = 0; i < 4; i++) {
        w[i] = (unsigned)(rand()/RAND_MAX);  //Gera valores aleatorios
        temp = *x++;
        valor = valor + temp * w[i];
    }

    return valor;

}

void encerraPWM(mraa_pwm_context pwm){
    mraa_pwm_close(pwm);
}

int main() {
    float dados[4] = {1, 2, 4, 6};

    mraa_pwm_context pwmGerado = initPWM();     //Inicializa o PWM

    float valor = geraValor(dados);     //Gera valor para o PWM

    setPWM(pwmGerado, valor);     //Seta PWM a ser transmitido

    printf("PWM = %f", readPWM(pwmGerado));     //Imprime valor de PWM

    encerraPWM(pwmGerado);     //Encerra PWM

    return 0;
}