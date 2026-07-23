#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "drivers/buzzer/buzzer.h"
#include "config/config.h" // Traz as macros de distância e o BUZZER_PIN de pinos.h

// --- Variáveis Estáticas (Encapsuladas no módulo) ---
static bool s_buzzer_estado = false;
static uint64_t s_ultimo_toggle_us = 0;

// --- Função Interna/Privada (static) ---
static void pwm_init_buzzer(uint pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    
    // Cálculo exato do divisor de clock para o PWM no RP2040 (BitDogLab)
    float clk_div = (float)clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * (PWM_WRAP + 1));
    pwm_config_set_clkdiv(&config, clk_div);
    pwm_config_set_wrap(&config, PWM_WRAP);
    pwm_init(slice_num, &config, true);
    
    pwm_set_gpio_level(pin, 0);
}

// --- Funções Públicas ---

void buzzer_init(void) 
{
    pwm_init_buzzer(BUZZER_PIN);
}

void buzzer_on(void)
{
    // Duty cycle em 50% para onda quadrada perfeita (som mais alto e limpo)
    pwm_set_gpio_level(BUZZER_PIN, (PWM_WRAP + 1) / 2);
    s_buzzer_estado = true;
}

void buzzer_off(void)
{
    pwm_set_gpio_level(BUZZER_PIN, 0);
    s_buzzer_estado = false;
}

void buzzer_beep_blocking(uint32_t tempo_ms)
{
    buzzer_on();
    sleep_ms(tempo_ms);
    buzzer_off();
}

void buzzer_alerta_distancia(uint32_t distancia_cm)
{
    // Fora do alcance (> 100 cm): desliga o buzzer e reseta a temporização
    if (distancia_cm > DISTANCIA_DISTANTE)
    {
        if (s_buzzer_estado)
        {
            buzzer_off();
        }
        s_ultimo_toggle_us = 0; 
        return;
    }

    // Tabela de mapeamento de intervalo usando as constantes do projeto
    uint32_t intervalo_us;

    if (distancia_cm <= DISTANCIA_CRITICA) // <= 20 cm: Som contínuo de emergência
    {
        buzzer_on();
        return;
    }
    else if (distancia_cm <= DISTANCIA_PERTO) // <= 40 cm
    {
        intervalo_us = 80000;   // Beep rápido (80 ms)
    }
    else if (distancia_cm <= DISTANCIA_MEDIA) // <= 70 cm
    {
        intervalo_us = 180000;  // Beep médio (180 ms)
    }
    else // <= 100 cm (DISTANCIA_DISTANTE)
    {
        intervalo_us = 350000;  // Beep lento (350 ms)
    }

    uint64_t agora_us = to_us_since_boot(get_absolute_time());

    // Se é a primeira vez após ter ficado desligado, inicializa o tempo
    if (s_ultimo_toggle_us == 0)
    {
        s_ultimo_toggle_us = agora_us;
        buzzer_on();
        return;
    }

    // Controle do tempo de alternância não-bloqueante
    if ((agora_us - s_ultimo_toggle_us) >= intervalo_us)
    {
        s_ultimo_toggle_us = agora_us;

        if (s_buzzer_estado)
        {
            buzzer_off();
        }
        else
        {
            buzzer_on();
        }
    }
}