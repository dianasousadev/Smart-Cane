import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# 1. CARREGAR OS DADOS
df = pd.read_csv('dados_bengala_ic.csv')
df['tempo_s'] = df['tempo_ms'] / 1000.0

# 2. CÁLCULO DAS ESTATÍSTICAS
total_registros = len(df)
duracao_s = df['tempo_s'].max() - df['tempo_s'].min()

stats_sup = {
    'min': df['distancia_superior_cm'].min(),
    'max': df['distancia_superior_cm'].max(),
    'media': df['distancia_superior_cm'].mean(),
    'std': df['distancia_superior_cm'].std()
}

stats_inf = {
    'min': df['distancia_inferior_cm'].min(),
    'max': df['distancia_inferior_cm'].max(),
    'media': df['distancia_inferior_cm'].mean(),
    'std': df['distancia_inferior_cm'].std()
}

qtd_alertas = (df['alerta_ativo'] == 1).sum()
perc_alertas = (qtd_alertas / total_registros) * 100

# Exibir resumo no terminal
print("=== RESUMO DAS MEDIÇÕES ===")
print(f"Total de registos: {total_registros}")
print(f"Duração total: {duracao_s:.2f} s")
print(f"Sensor Superior -> Mín: {stats_sup['min']} cm | Máx: {stats_sup['max']} cm | Média: {stats_sup['media']:.2f} cm | Desvio Padrão: {stats_sup['std']:.2f} cm")
print(f"Sensor Inferior -> Mín: {stats_inf['min']} cm | Máx: {stats_inf['max']} cm | Média: {stats_inf['media']:.2f} cm | Desvio Padrão: {stats_inf['std']:.2f} cm")
print(f"Alertas ativos: {qtd_alertas} ({perc_alertas:.2f}%)")

# 3. GERAR FIGURA 1: TELEMETRIA TEMPORAL MULTI-PAINEL
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 7), sharex=True, gridspec_kw={'height_ratios': [3, 1]})
t = df['tempo_s']

# Subplot 1: Leituras dos Sensores
ax1.plot(t, df['distancia_superior_cm'], label='Sensor Superior (Tórax/Cabeça)', color='#1f77b4', linewidth=1.8)
ax1.plot(t, df['distancia_inferior_cm'], label='Sensor Inferior (Solo/Pernas)', color='#2ca02c', linewidth=1.8)
ax1.fill_between(t, 0, 200, where=(df['alerta_ativo'] == 1), color='#d62728', alpha=0.18, label='Alerta Ativo')

ax1.axhline(100, color='gray', linestyle='--', linewidth=1, alpha=0.7, label='Limiar de Atenção (100 cm)')
ax1.axhline(50, color='red', linestyle=':', linewidth=1, alpha=0.7, label='Limiar Crítico (50 cm)')

ax1.set_ylabel('Distância Medida (cm)')
ax1.set_ylim(-5, 205)
ax1.set_title('Figura 1: Telemetria Contínua dos Sensores de Proximidade e Estado de Alerta', fontweight='bold', pad=12)
ax1.legend(loc='lower left', frameon=True, facecolor='white', framealpha=0.9, ncol=3)

# Subplot 2: Sinal Digital do Alerta
ax2.step(t, df['alerta_ativo'], where='post', color='#d62728', linewidth=1.5, label='Estado do Alerta (0/1)')
ax2.fill_between(t, 0, df['alerta_ativo'], step='post', color='#d62728', alpha=0.3)
ax2.set_xlabel('Tempo Decorrido (segundos)')
ax2.set_ylabel('Alerta')
ax2.set_yticks([0, 1])
ax2.set_yticklabels(['Inativo (0)', 'Ativo (1)'])
ax2.set_ylim(-0.1, 1.15)
ax2.grid(True, linestyle=':', alpha=0.6)

plt.tight_layout()
plt.savefig('figura1_telemetria_bengala.png', dpi=300) # Salva a imagem automaticamente
plt.close()

# 4. GERAR FIGURA 2: ESPAÇO DE ESTADOS E BOXPLOTS
fig, (ax_scat, ax_box) = plt.subplots(1, 2, figsize=(13, 5.5), gridspec_kw={'width_ratios': [1.2, 1]})

# Scatter Plot
ax_scat.scatter(df[df['alerta_ativo'] == 0]['distancia_inferior_cm'],
                df[df['alerta_ativo'] == 0]['distancia_superior_cm'],
                c='#1f77b4', alpha=0.6, label='Alerta Inativo (Normal)', s=35)

ax_scat.scatter(df[df['alerta_ativo'] == 1]['distancia_inferior_cm'],
                df[df['alerta_ativo'] == 1]['distancia_superior_cm'],
                c='#d62728', alpha=0.8, label='Alerta Ativo (Obstáculo)', s=45, marker='^', edgecolors='k', linewidths=0.3)

ax_scat.set_xlabel('Distância Sensor Inferior (cm)')
ax_scat.set_ylabel('Distância Sensor Superior (cm)')
ax_scat.set_title('(A) Espaço de Estados dos Sensores e Disparo do Alerta', fontweight='bold')
ax_scat.axvline(100, color='gray', linestyle='--', alpha=0.5)
ax_scat.axhline(100, color='gray', linestyle='--', alpha=0.5)
ax_scat.legend(loc='upper left', frameon=True, facecolor='white')
ax_scat.grid(True, linestyle=':', alpha=0.6)

# Boxplots
df_melted = pd.melt(df, id_vars=['alerta_ativo'], value_vars=['distancia_superior_cm', 'distancia_inferior_cm'],
                    var_name='Sensor', value_name='Distancia_cm')
df_melted['Sensor'] = df_melted['Sensor'].map({'distancia_superior_cm': 'Superior', 'distancia_inferior_cm': 'Inferior'})
df_melted['Estado'] = df_melted['alerta_ativo'].map({0: 'Inativo', 1: 'Ativo'})

sns.boxplot(data=df_melted, x='Sensor', y='Distancia_cm', hue='Estado', palette={'Inativo': '#1f77b4', 'Ativo': '#d62728'}, ax=ax_box, width=0.5)
ax_box.set_title('(B) Distribuição das Distâncias por Sensor e Estado', fontweight='bold')
ax_box.set_xlabel('Sensor de Proximidade')
ax_box.set_ylabel('Distância (cm)')
ax_box.grid(True, linestyle=':', alpha=0.6)

plt.tight_layout()
plt.savefig('figura2_analise_fronteira_boxplots.png', dpi=300) # Salva a imagem automaticamente
plt.close()

print("\nProcesso concluído! Os gráficos foram salvos na pasta como 'figura1_telemetria_bengala.png' e 'figura2_analise_fronteira_boxplots.png'.")