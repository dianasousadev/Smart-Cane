#include <stdio.h>
#include "pico/stdlib.h"
#include "config/config.h"
#include "drivers/leds/leds.h"
#include "drivers/ultrasonic/ultrasonic.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/motor/motor.h"
#include "drivers/alert/alert.h"

int main(void)
{
    // Inicializa a comunicação Serial via USB para o Monitor Serial
    stdio_init_all();

    // Aguarda 2 segundos para dar tempo de abrir o Monitor Serial após ligar a BitDogLab
    sleep_ms(2000);
    printf("\n=========================================\n");
    printf("   BENGALA INTELIGENTE - INICIAÇÃO CIENTÍFICA\n");
    printf("   Inicializando periféricos e sensores...\n");
    printf("=========================================\n");

    ultrassonico_init();
    alerta_init();
    leds_init();
    buzzer_init();
    printf("[SISTEMA] Inicializacao concluida com sucesso!\n\n");

    // Loop Principal (Super Loop)
    while (true)
    {
        // 1. Leitura dos sensores ultrassônicos (em cm)
        uint32_t distancia_superior = ultrassonico_superior_medir_cm();
        uint32_t distancia_inferior = ultrassonico_inferior_medir_cm();

        // 2. Processa os alertas visuais, sonoros e táteis
        // Nota: alerta_processar_sensor ja atualiza os LEDs internamente!
        leds_processar_sensor(distancia_superior, distancia_inferior);
        alerta_processar_sensor(distancia_superior, distancia_inferior);
        
        // 3. Monitoramento Serial (Imprime as leituras em tempo real para coleta de dados)
        printf("[LEITURA] Sup: %3lu cm | Inf: %3lu cm\n", distancia_superior, distancia_inferior);

        // 4. Intervalo de amostragem responsivo (~10 leituras por segundo)
        sleep_ms(2000);
    }

    return 0;
}