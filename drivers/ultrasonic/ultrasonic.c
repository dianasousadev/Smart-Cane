#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "drivers/ultrasonic/ultrasonic.h"
#include "config/config.h" // Traz os pinos de pinos.h e limites do sistema

// --- Função Auxiliar Privada (static) ---
static uint32_t medir_distancia_generica(uint trig_pin, uint echo_pin)
{
    // Garante pulso limpo no Trigger
    gpio_put(trig_pin, 0);
    sleep_us(2);

    // Envia o pulso de acionamento de 10us
    gpio_put(trig_pin, 1);
    sleep_us(10);
    gpio_put(trig_pin, 0);

    // Timeout de 30ms (~5 metros de alcance máximo)
    absolute_time_t timeout = make_timeout_time_ms(30);

    // Aguarda o pino Echo ir para HIGH
    while (gpio_get(echo_pin) == 0 && !time_reached(timeout))
    {
        tight_loop_contents();
    }

    // Se estourou o tempo sem o Echo subir, retorna fora de alcance
    if (gpio_get(echo_pin) == 0)
    {
        return 999; 
    }

    uint32_t inicio = time_us_32();

    // Aguarda o pino Echo voltar para LOW
    while (gpio_get(echo_pin) == 1 && !time_reached(timeout))
    {
        tight_loop_contents();
    }

    // Se estourou o tempo sem o Echo baixar, retorna fora de alcance
    if (gpio_get(echo_pin) == 1)
    {
        return 999;
    }

    uint32_t largura_pulso = time_us_32() - inicio;

    // Cálculo do tempo de voo para centímetros (Velocidade do som ~340m/s -> us / 58)
    return largura_pulso / 58;
}

// --- Funções Públicas ---

void ultrassonico_init(void)
{
    // Configura Sensor Superior
    gpio_init(TRIG_SUPERIOR);
    gpio_set_dir(TRIG_SUPERIOR, GPIO_OUT);
    gpio_put(TRIG_SUPERIOR, 0);

    gpio_init(ECHO_SUPERIOR);
    gpio_set_dir(ECHO_SUPERIOR, GPIO_IN);

    // Configura Sensor Inferior
    gpio_init(TRIG_INFERIOR);
    gpio_set_dir(TRIG_INFERIOR, GPIO_OUT);
    gpio_put(TRIG_INFERIOR, 0);

    gpio_init(ECHO_INFERIOR);
    gpio_set_dir(ECHO_INFERIOR, GPIO_IN);
}

uint32_t ultrassonico_superior_medir_cm(void)
{
    return medir_distancia_generica(TRIG_SUPERIOR, ECHO_SUPERIOR);
}

uint32_t ultrassonico_inferior_medir_cm(void)
{
    return medir_distancia_generica(TRIG_INFERIOR, ECHO_INFERIOR);
}