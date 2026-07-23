#ifndef CONSTANTES_H
#define CONSTANTES_H

/**
 * @brief Limites de distância para os níveis de alerta (em cm).
 */
#define DISTANCIA_CRITICA           20
#define DISTANCIA_PERTO             40
#define DISTANCIA_MEDIA             70
#define DISTANCIA_DISTANTE          100

/**
 * @brief Configurações de acionamento do LED indicador.
 */
#define LED_DISTANCIA_DESLIGADO_CM  100
#define LED_DISTANCIA_PISCAR_CM     70
#define LED_PISCA_INTERVAL_US       250000  // 250 ms em microsegundos

/**
 * @brief Configurações do PWM e Buzzer (BitDogLab).
 */
#define BUZZER_PIN                  21      // Buzzer A integrado na BitDogLab
#define BUZZER_FREQUENCY            2000    // Frequência do som em Hz (2 kHz)
#define PWM_WRAP                    10000u  // Resolução da contagem do PWM

/**
 * @brief Mapeamento das conexões externas (Sensores e Motor).
 */
#define SENSOR_SUP_TRIG_PIN         2
#define SENSOR_SUP_ECHO_PIN         3

#define SENSOR_INF_TRIG_PIN         4
#define SENSOR_INF_ECHO_PIN         5

#define MOTOR_VIBRACAO_PIN          18      // Pino de saída para a base do transistor do motor

/**
 * @brief Configurações de velocidade dos atuadores.
 */
#define MOTOR_SPEED_ALERTA          80      // Velocidade do motor durante o alerta (0 a 100%)

#endif // CONSTANTES_H