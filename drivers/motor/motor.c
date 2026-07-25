#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "drivers/motor/motor.h"
#include "config/config.h" 

static uint slice_num;

void motor_init(void)
{
    // 2. Configura a função PWM no pino
    gpio_set_function(MOTOR_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(MOTOR_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, PWM_WRAP);
    // 3. Inicializa o PWM mas garante o nível de desligado
    pwm_init(slice_num, &config, true);
    // 4. Força o desligamento imediato
    motor_stop();
}

void motor_set_speed(int8_t speed_percent)
{
    if (speed_percent > 100) speed_percent = 100;
    if (speed_percent < 0)   speed_percent = 0;

    uint16_t level = (PWM_WRAP * speed_percent) / 100;
    pwm_set_gpio_level(MOTOR_PIN, level);
}

void motor_stop(void)
{
     pwm_set_gpio_level(MOTOR_PIN, PWM_WRAP);
}

int8_t motor_calcular_velocidade(uint32_t distancia_cm)
{
    if (distancia_cm <= DISTANCIA_CRITICA)
    {
        return 100;
    }
    else if (distancia_cm <= DISTANCIA_PERTO)
    {
        return 70;
    }
    else
    {
        return 0;
    }
}