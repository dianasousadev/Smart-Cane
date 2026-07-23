#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
// Inclui o header do próprio módulo (que já traz as constantes)
#include "drivers/alert/alert.h"

// Drivers dos periféricos
#include "drivers/buzzer/buzzer.h"
#include "drivers/motor/motor.h"

// Habilite (1) ou desabilite (0) prints de depuração
#define DEBUG_ALERTA 0

void alerta_init(void)
{
    buzzer_init();
    motor_init();
}

void alerta_processar_sensor(uint32_t distancia_superior, uint32_t distancia_inferior)
{
    // Pega o valor mais crítico (menor distância)
    uint32_t menor_distancia = (distancia_superior < distancia_inferior)
                                   ? distancia_superior
                                   : distancia_inferior;

#if DEBUG_ALERTA
    printf("[ALERTA] Sup: %lu | Inf: %lu | Menor: %lu cm\n",
           distancia_superior, distancia_inferior, menor_distancia);
#endif

    if (menor_distancia <= DISTANCIA_DISTANTE)
    {
        // Dispara o alerta não-bloqueante no buzzer
        buzzer_alerta_distancia(menor_distancia);

        // Ajusta a velocidade do motor usando a constante da pasta config
        motor_set_speed(MOTOR_SPEED_ALERTA);
    }
    else
    {
        // Atualiza o buzzer para fora de alcance (desliga e reseta o tempo)
        buzzer_alerta_distancia(menor_distancia);

        // Desliga o motor
        motor_stop();
    }
}