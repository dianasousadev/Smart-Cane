#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "config/config.h" // Traz as constantes de distância e os pinos de pinos.h
#include "drivers/leds/leds.h"

// --- Variáveis Estáticas ---
static bool s_led_estado = false;
static uint64_t s_ultimo_toggle_us = 0;

// --- Funções Auxiliares dos LEDs ---

void led_vermelho_on(void)
{
    gpio_put(LED_VERMELHO, 1);
}

void led_vermelho_off(void)
{
    gpio_put(LED_VERMELHO, 0);
}

void led_azul_on(void)
{
    gpio_put(LED_AZUL, 1);
}

void led_azul_off(void)
{
    gpio_put(LED_AZUL, 0);
}

void led_verde_on(void)
{
    gpio_put(LED_VERDE, 1);
}

void led_verde_off(void)
{
    gpio_put(LED_VERDE, 0);
}

// --- Funções Principais de Inicialização e Processamento ---

void leds_init(void)
{
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);

    s_led_estado = false;
    s_ultimo_toggle_us = 0;
}

void leds_processar_sensor(uint32_t distancia_superior, uint32_t distancia_inferior)    
{
    // Sensor superior aciona o LED Vermelho
    if (distancia_superior <= DISTANCIA_MEDIA)
    {
        led_vermelho_on();
    }
    else
    {
        led_vermelho_off();
    }

    // Sensor inferior aciona o LED Azul
    if (distancia_inferior <= DISTANCIA_MEDIA)
    {
        led_azul_on();
    }
    else
    {
        led_azul_off();
    }

    // LED Verde aceso somente se ambos os sensores não detectarem nada próximo
    if (distancia_superior > DISTANCIA_MEDIA && distancia_inferior > DISTANCIA_MEDIA)
    {
        led_verde_on();
    }
    else
    {
        led_verde_off();
    }
}