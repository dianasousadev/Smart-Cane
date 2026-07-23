#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"

#include "drivers/motor/motor.h"
#include "config/config.h" // Inclui MOTOR_PIN de pinos.h e os limites de distância

static uint s_slice_num;

void motor_init(void)
{
    gpio_set_function(MOTOR_PIN, GPIO_FUNC_PWM);

    s_slice_num = pwm_gpio_to_slice_num(MOTOR_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, PWM_WRAP);

    pwm_init(s_slice_num, &config, true);

    motor_stop();
}

void motor_set_speed(uint8_t speed_percent)
{
    if (speed_percent > 100)
    {
        speed_percent = 100;
    }

    uint16_t level = (PWM_WRAP * speed_percent) / 100;
    pwm_set_gpio_level(MOTOR_PIN, level);
}

void motor_stop(void)
{
    pwm_set_gpio_level(MOTOR_PIN, 0);
}

void motor_alerta_distancia(uint32_t distancia_cm)
{
    // Fora do alcance (> 100 cm): Desliga a vibração
    if (distancia_cm > DISTANCIA_DISTANTE)
    {
        motor_stop();
    }
    // Zona Crítica (<= 20 cm): Vibração máxima (100%)
    else if (distancia_cm <= DISTANCIA_CRITICA)
    {
        motor_set_speed(100);
    }
    // Zona Perto (<= 40 cm): Vibração forte (80%)
    else if (distancia_cm <= DISTANCIA_PERTO)
    {
        motor_set_speed(MOTOR_SPEED_ALERTA);
    }
    // Zona Média (<= 70 cm): Vibração moderada (50%)
    else if (distancia_cm <= DISTANCIA_MEDIA)
    {
        motor_set_speed(50);
    }
    // Zona Distante (<= 100 cm): Vibração leve (25%)
    else
    {
        motor_set_speed(25);
    }
}