#ifndef MOTOR_H
#define MOTOR_H
#include <stdint.h>

/**
 * @brief Inicializa o pino do motor e o módulo PWM.
 */
void motor_init(void);

/**
 * @brief Ajusta a velocidade/intensidade do motor (0 a 100%).
 * 
 * @param speed_percent Porcentagem do Duty Cycle (0-100).
 */
void motor_set_speed(int8_t speed_percent);

/**
 * @brief Desliga o motor de vibração.
 */
void motor_stop(void);


/**
 * @brief Calcula a velocidade ideal do motor com base na distância.
 * 
 * @param distancia_cm Distância em centímetros do obstáculo.
 * @return int8_t Velocidade/Intensidade em porcentagem (0 a 100).
 */
int8_t motor_calcular_velocidade(uint32_t distancia_cm);

#endif 