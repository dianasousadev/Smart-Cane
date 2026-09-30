#include <stdio.h>
#include "pico/stdlib.h"
#include "config/config.h"
#include "drivers/ultrasonic/ultrasonic.h"
#include "drivers/alert/alert.h"
#include "drivers/wifi/wifi.h"
#include "drivers/telemetria/telemetria.h"
#include "drivers/buzzer/buzzer.h"

#define WIFI_SSID "FULL-STACK"  // Substitua pelo nome da sua rede Wi-Fi
#define WIFI_PASS "52391810" // Substitua pela senha da sua rede Wi-Fi
#define IP_NOTEBOOK "192.168.0.35" // <-- Coloque o IP do seu notebook aqui!
#define PORTA_UDP     5005


int main(void)
{
    // Inicializa a comunicação Serial via USB para o Monitor Serial
    stdio_init_all();
    sleep_ms(2000); // Aguarda a serial USB
    
      printf("=== BENGALA SAFE STEP ===\n");
    printf("Iniciando sistema...\n");

    ultrassonico_init();
    alerta_init();
    ultrassonico_init();
    alerta_init();
    // Conecta ao Wi-Fi e inicializa o emissor UDP
    if (wifi_init(WIFI_SSID, WIFI_PASS))
    {
        telemetria_init(IP_NOTEBOOK, PORTA_UDP);
    }
    // Loop Principal (Super Loop)
    while (true)
    {
        // 1. Leitura dos sensores ultrassônicos (em cm)
        uint32_t distancia_superior = ultrassonico_superior_medir_cm();
        uint32_t distancia_inferior = ultrassonico_inferior_medir_cm();

        // 2. Processa os alertas visuais, sonoros e táteis
        // Nota: alerta_processar_sensor ja atualiza os LEDs internamente!
        alerta_processar_sensor(distancia_superior, distancia_inferior);
       // Envia as leituras pela rede sem travar o loop
        bool nivel_alerta = buzzer_estado();
        telemetria_enviar_dados(distancia_superior, distancia_inferior, nivel_alerta);

        sleep_ms(100); // Envia 10 amostras por segundo (10 Hz)
    }

    return 0;
}