#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/udp.h"

#include "drivers/telemetria/telemetria.h"

static struct udp_pcb *s_pcb = NULL;
static ip_addr_t s_ip_dest;
static uint16_t s_porta_dest = 5005;

void telemetria_init(const char *ip_notebook, uint16_t porta)
{
    s_porta_dest = porta;
    ip4addr_aton(ip_notebook, &s_ip_dest);

    // Cria o bloco de controle do protocolo UDP
    s_pcb = udp_new();
}

void telemetria_enviar_dados(uint32_t dist_sup, uint32_t dist_inf, bool alerta_ativo)
{
    if (s_pcb == NULL) return;

    // Obtém o tempo desde a inicialização (em milissegundos)
    uint32_t tempo_ms = to_ms_since_boot(get_absolute_time());

    // Monta o pacote de texto no formato CSV: tempo_ms,dist_sup,dist_inf,alerta
    char buffer[64];
    int len = snprintf(buffer, sizeof(buffer), "%lu,%lu,%lu,%d\n", 
                       tempo_ms, dist_sup, dist_inf, alerta_ativo ? 1 : 0);

    // Aloca buffer do LWIP para envio
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
    if (p != NULL)
    {
        memcpy(p->payload, buffer, len);
        udp_sendto(s_pcb, p, &s_ip_dest, s_porta_dest);
        pbuf_free(p); // Libera memória após o envio
    }
}