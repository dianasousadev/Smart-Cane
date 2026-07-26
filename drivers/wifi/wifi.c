#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "drivers/wifi/wifi.h"

static bool s_wifi_conectado = false;

bool wifi_init(const char *ssid, const char *password)
{
    printf("[WI-FI] Inicializando hardware CYW43...\n");

    // 1. Inicializa a arquitetura do chip Wi-Fi
    if (cyw43_arch_init())
    {
        printf("[WI-FI ERRO] Falha ao inicializar o chip Wi-Fi!\n");
        s_wifi_conectado = false;
        return false;
    }

    // 2. Habilita o modo Estação (Cliente Wi-Fi)
    cyw43_arch_enable_sta_mode();

    printf("[WI-FI] Conectando a rede: %s ...\n", ssid);

    // 3. Tenta conectar com timeout de 10 segundos (10000 ms)
    int status = cyw43_arch_wifi_connect_timeout_ms(
        ssid, 
        password, 
        CYW43_AUTH_WPA2_AES_PSK, 
        10000
    );

    if (status == 0)
    {
        s_wifi_conectado = true;
        printf("[WI-FI OK] Conectado com sucesso!\n");

        // Opcional: Imprime o IP atribuído à Pico W
        uint8_t *ip = (uint8_t *)&cyw43_state.netif[0].ip_addr.addr;
        printf("[WI-FI IP] Endereco IP: %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
        
        return true;
    }
    else
    {
        s_wifi_conectado = false;
        printf("[WI-FI ERRO] Falha na conexao (Codigo: %d)\n", status);
        return false;
    }
}

bool wifi_conectado(void)
{
    // Verifica o estado atual do link no chip
    int link_status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
    s_wifi_conectado = (link_status == CYW43_LINK_UP);
    return s_wifi_conectado;
}

void wifi_desconectar(void)
{
    cyw43_arch_deinit();
    s_wifi_conectado = false;
    printf("[WI-FI] Desconectado e hardware desligado.\n");
}