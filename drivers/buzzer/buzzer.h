#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h>
#include <stdint.h>
#include "pico/stdlib.h"

/**
 * @brief Inicializa o pino do buzzer e o periférico PWM.
 */
void buzzer_init(void);

/**
 * @brief Liga o buzzer continuamente (Duty Cycle 50%).
 */
void buzzer_on(void);

/**
 * @brief Desliga o buzzer.
 */
void buzzer_off(void);

bool buzzer_estado(void);
/**
 * @brief Emite um beep bloqueante pela duração especificada.
 * 
 * @param tempo_ms Duração do beep em milissegundos.
 */
void buzzer_beep_blocking(uint32_t tempo_ms);

/**
 * @brief Atualiza a frequência de beeps do buzzer de forma não-bloqueante baseada na distância.
 * 
 * @param distancia_cm Distância lida em centímetros do obstáculo mais próximo.
 */
void buzzer_alerta_distancia(uint32_t distancia_cm);

#endif // BUZZER_H