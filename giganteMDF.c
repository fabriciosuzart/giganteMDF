#include <avr/io.h>
#include <util/delay.h>

// Definições dos pinos
#define MOTOR_PWM_LEFT PD5
#define MOTOR_PWM_RIGHT PD6

// Funções auxiliares
void setup();
void mover_frente();
void mover_tras();
void girar_direita();
void girar_esquerda();

// Função principal
int main() {
    setup();

    while (1) {
        // Andar para frente
        mover_frente();
        _delay_ms(2000); // Move por 2 segundos

        // Andar para trás
        mover_tras();
        _delay_ms(2000); // Move por 2 segundos

        // Girar para a direita
        girar_direita();
        _delay_ms(1000); // Ajustar para giro de 90º

        // Girar para a esquerda
        girar_esquerda();
        _delay_ms(1000); // Ajustar para giro de 90º
    }

    return 0;
}

// Configuração inicial
void setup() {
    // Configura motores como saída
    DDRD |= (1 << MOTOR_PWM_LEFT) | (1 << MOTOR_PWM_RIGHT);

    // Configura PWM para motores (Fast PWM, Prescaler de 8)
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS01); // Prescaler de 8
}

// Função para mover o robô para frente
void mover_frente() {
    OCR0A = 128; // PWM de 50% no motor esquerdo
    OCR0B = 128; // PWM de 50% no motor direito
}

// Função para mover o robô para trás
void mover_tras() {
    OCR0A = 64; // PWM para trás no motor esquerdo (ajuste dependendo da polaridade)
    OCR0B = 64; // PWM para trás no motor direito
}

// Função para girar para a direita
void girar_direita() {
    OCR0A = 128; // Ativa apenas o motor esquerdo
    OCR0B = 0;   // Desativa o motor direito
}

// Função para girar para a esquerda
void girar_esquerda() {
    OCR0A = 0;   // Desativa o motor esquerdo
    OCR0B = 128; // Ativa apenas o motor direito
}