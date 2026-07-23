#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

/**
 * @brief Inicializa os pinos GPIO dos sensores ultrassônicos superior e inferior.
 */
void ultrassonico_init(void);

/**
 * @brief Realiza a leitura da distância do sensor superior.
 * 
 * @return uint32_t Distância calculada em centímetros (retorna 999 se estiver fora de alcance).
 */
uint32_t ultrassonico_superior_medir_cm(void);

/**
 * @brief Realiza a leitura da distância do sensor inferior.
 * 
 * @return uint32_t Distância calculada em centímetros (retorna 999 se estiver fora de alcance).
 */
uint32_t ultrassonico_inferior_medir_cm(void);

#endif // ULTRASSONICO_H