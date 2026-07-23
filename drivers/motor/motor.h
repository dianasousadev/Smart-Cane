#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

/**
 * @brief Inicializa o pino do motor de vibração e o periférico PWM.
 */
void motor_init(void);

/**
 * @brief Ajusta a velocidade/intensidade do motor em porcentagem (0 a 100%).
 * 
 * @param speed_percent Porcentagem do Duty Cycle de 0 a 100.
 */
void motor_set_speed(uint8_t speed_percent);

/**
 * @brief Desliga o motor de vibração imediatamente.
 */
void motor_stop(void);

/**
 * @brief Ajusta a intensidade de vibração do motor proporcionalmente à distância.
 * 
 * @param distancia_cm Menor distância lida pelos sensores em centímetros.
 */
void motor_alerta_distancia(uint32_t distancia_cm);

#endif // MOTOR_H