#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

/**
 * @brief Inicializa os pinos GPIO configurados para os LEDs RGB.
 */
void leds_init(void);

/**
 * @brief Atualiza o estado dos LEDs de acordo com as leituras dos dois sensores.
 * 
 * @param distancia_superior Distância do sensor superior em cm.
 * @param distancia_inferior Distância do sensor inferior em cm.
 */
void leds_processar_sensor(uint32_t distancia_superior, uint32_t distancia_inferior);

/**
 * @brief Funções de controle direto de cada LED.
 */
void led_vermelho_on(void);
void led_vermelho_off(void);
void led_azul_on(void);
void led_azul_off(void);
void led_verde_on(void);
void led_verde_off(void);

#endif // LEDS_H