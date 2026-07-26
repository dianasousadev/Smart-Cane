#ifndef TELEMETRIA_H
#define TELEMETRIA_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Configura o socket UDP para envio de dados ao notebook.
 * @param ip_notebook Endereço IP do notebook na rede Wi-Fi (ex: "192.168.1.15").
 * @param porta Porta UDP para envio (ex: 5005).
 */
void telemetria_init(const char *ip_notebook, uint16_t porta);

/**
 * @brief Envia uma amostra das leituras no formato CSV via UDP.
 * @param dist_sup Distância medida pelo sensor superior (cm).
 * @param dist_inf Distância medida pelo sensor inferior (cm).
 * @param alerta_ativo Se o buzzer/motor foi acionado no instante.
 */

void telemetria_enviar_dados(uint32_t dist_sup, uint32_t dist_inf, bool alerta_ativo);

#endif 