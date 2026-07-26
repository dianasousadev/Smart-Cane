import socket
import csv

PORTA_UDP = 5005
ARQUIVO_SAIDA = "dados_bengala_ic.csv"

# Configura o receptor UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", PORTA_UDP))

print("==================================================")
print(" 📡 RECEPTOR DE TELEMETRIA - BENGALA INTELIGENTE")
print("==================================================")
print(f" Port: {PORTA_UDP} | Target: {ARQUIVO_SAIDA}\n")

# Abre o arquivo CSV para gravação
with open(ARQUIVO_SAIDA, mode="w", newline="") as f:
    writer = csv.writer(f)
    # Cabeçalho padrão do CSV
    writer.writerow(["tempo_ms", "distancia_superior_cm", "distancia_inferior_cm", "alerta_ativo"])
    
    total_amostras = 0

    try:
        while True:
            data, addr = sock.recvfrom(1024)
            linha = data.decode("utf-8").strip()
            valores = linha.split(",")
            
            if len(valores) == 4:
                # 1. Salva a amostra detalhada no CSV
                writer.writerow(valores)
                f.flush() # Força o salvamento em disco em tempo real
                
                total_amostras += 1
                tempo, sup, inf, alerta = valores
                status_alerta = "🚨 ALERTA!" if alerta == "1" else "🟢 NORMAL "
                
                # 2. Atualiza a exibição em uma linha fixa no terminal (\r)
                msg_painel = (
                    f"\r📊 Amostras: {total_amostras:>5} | "
                    f"⏱️ Tempo: {tempo:>7} ms | "
                    f"📐 Sup: {sup:>3} cm | "
                    f"📐 Inf: {inf:>3} cm | "
                    f"Status: {status_alerta}"
                )
                print(msg_painel, end="", flush=True)

    except KeyboardInterrupt:
        print(f"\n\n==================================================")
        print(f" ✅ Coleta finalizada! Total de {total_amostras} amostras salvas.")
        print(f" 💾 Arquivo gerado: {ARQUIVO_SAIDA}")
        print(f"==================================================")