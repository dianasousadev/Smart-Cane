#ifndef WIFI_H
#define WIFI_H

#include <stdbool.h>

/**
 * @brief Inicializa a arquitetura CYW43 da Pico W e conecta à rede Wi-Fi.
 * 
 * @param ssid Nome da rede Wi-Fi (SSID).
 * @param password Senha da rede Wi-Fi.
 * @return true Se a conexão foi estabelecida com sucesso.
 * @return false Se ocorreu falha na inicialização do hardware ou ao conectar.
 */
bool wifi_init(const char *ssid, const char *password);

/**
 * @brief Verifica se a placa continua conectada ao roteador.
 * 
 * @return true Se estiver conectada.
 * @return false Se a conexão caiu.
 */
bool wifi_conectado(void);

/**
 * @brief Desconecta do Wi-Fi e desliga o chip de rádio para economizar energia.
 */


//void wifi_enviar_dados();

void wifi_desconectar();


#endif