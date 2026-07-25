#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "drivers/alert/alert.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/motor/motor.h"
#include "drivers/leds/leds.h"

// Habilite (1) ou desabilite (0) prints de depuração
#define DEBUG_ALERTA 1

void alerta_init(void)
{
    buzzer_init();
    motor_init();
    leds_init();
}
void alerta_processar_sensor(uint32_t distancia_superior, uint32_t distancia_inferior)
{
    // 1. Atualiza os LEDs com base nas distâncias
    leds_processar_sensor(distancia_superior, distancia_inferior);

    // 2. Descobre a menor distância registrada pelos sensores
    uint32_t menor_distancia = (distancia_inferior < distancia_superior) ? distancia_inferior : distancia_superior;

    if (menor_distancia == 0)
{
    motor_stop();
    return;
}

    // 3. Atualiza os beeps do buzzer
    buzzer_alerta_distancia(menor_distancia);

    #if DEBUG_ALERTA
printf("Sup=%lu Inf=%lu Menor=%lu Buzzer=%d\n",
       distancia_superior,
       distancia_inferior,
       menor_distancia,
       buzzer_estado());
#endif

    // 4. Lógica do Motor:
    // Só vibra se estiver na zona de perigo (<= 40 cm) E se o buzzer estiver apitando agora
    if ((menor_distancia <= DISTANCIA_PERTO) && buzzer_estado())
    {
        int8_t potencia = motor_calcular_velocidade(menor_distancia);
        motor_set_speed(potencia);
    }
    else
    {
        // Fora de perigo (> 40 cm) ou na pausa do beep: desliga o motor
        motor_stop();
    }
}