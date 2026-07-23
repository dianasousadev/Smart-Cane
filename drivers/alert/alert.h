#ifndef ALERT_H
#define ALERT_H

#include <stdint.h>

// Inclui as constantes globais do projeto a partir da pasta config
#include "config/constantes.h"

// --- Valor padrão de segurança (Fallback) ---
// Caso MOTOR_SPEED_ALERTA não tenha sido definido em constantes.h
#ifndef MOTOR_SPEED_ALERTA
#define MOTOR_SPEED_ALERTA  80
#endif

// --- Protótipos das Funções ---

/**
 * @brief Inicializa os atuadores do alerta (buzzer e motor).
 */
void alerta_init(void);

/**
 * @brief Processa as distâncias dos dois sensores e atualiza os atuadores.
 * 
 * @param distancia_superior Leitura do sensor superior em cm.
 * @param distancia_inferior Leitura do sensor inferior em cm.
 */
void alerta_processar_sensor(uint32_t distancia_superior, uint32_t distancia_inferior);

#endif // ALERTA_H