# Lorrany SafeStep 🚶‍♀️🦯

Projeto de Iniciação Científica desenvolvido na UFBRA.

## Bengala inteligente baseada em sistemas embarcados para auxílio à mobilidade de pessoas com deficiência visual

## 📌 Sobre o projeto

O **Lorrany SafeStep** é um protótipo de bengala inteligente desenvolvido com o objetivo de auxiliar pessoas com deficiência visual na identificação de obstáculos durante a locomoção.

O sistema utiliza sensores ultrassônicos para detectar obstáculos em diferentes alturas, permitindo identificar objetos que normalmente não seriam percebidos por uma bengala convencional, como obstáculos suspensos, galhos, placas e objetos no caminho.

O projeto utiliza um microcontrolador **RP2040** e foi desenvolvido utilizando a linguagem **C/C++**, com organização modular baseada em drivers.

---

# 🎯 Objetivo

Desenvolver um sistema embarcado assistivo capaz de:

- Detectar obstáculos utilizando sensores ultrassônicos;
- Diferenciar obstáculos superiores e inferiores;
- Emitir alertas ao usuário através de vibração;
- Auxiliar na tomada de decisão durante a caminhada;
- Possibilitar futuras expansões com novos recursos.

---

# 🛠️ Hardware utilizado

| Componente | Descrição | Quantidade |
|------------|-----------|------------|
| Microcontrolador | RP2040 (BitDogLab / Raspberry Pi Pico) | 1 unidade |
| Sensor ultrassônico | US-015 | 2 unidades |
| Atuador de alerta | Motor vibratório | 1 unidade |
| Jumpers | Macho e Fêmea | Diversos (fase de testes) |
| Protoboard | Utilizada para montagem dos testes | 1 (fase de testes) |
| Chave liga/desliga | Liga e desliga a bengala sem desconectar a bateria | 1 unidade |
| Bateria recarregável | Li-Ion CR18650 3,7 V 2200 mAh | 1 unidade |
| Alerta auxiliar | Buzzer integrado na BitDogLab (fase de testes) | 1 |
| Indicadores visuais | LEDs RGB integrados na BitDogLab (fase de testes) | 3 |
| Linguagem | C/C++ | - |
| SDK | Raspberry Pi Pico SDK | - |

---
# 📐 Arquitetura do sistema

O projeto foi desenvolvido utilizando uma arquitetura modular:

```
Bengala_Safe_Step
│
├── drivers
│   │
│   ├── ultrassonico
│   │   ├── ultrassonico.c
│   │   └── ultrassonico.h
│   │
│   ├── leds
│   │   ├── leds.c
│   │   └── leds.h
│   │
│   ├── buzzer
│   │   ├── buzzer.c
│   │   └── buzzer.h
│   │
│   ├── motor
│   │   ├── motor.c
│   │   └── motor.h
│   │
│   └── alerta
│       ├── alerta.c
│       └── alerta.h
│
├── config
│   └── config.h
|   |__ constantes.h
|   |__ pinos.h
│
├── Bengala_Safe_Step.c
│
└── CMakeLists.txt
```

---

# ⚙️ Funcionamento

O sistema realiza continuamente a leitura dos sensores:

```
Sensor Superior
       |
       |
       ↓

Sensor Inferior
       |
       |
       ↓

Processamento RP2040
       |
       |
       +------------+
       |            |
       ↓            ↓

 LEDs        Sistema de alerta

              |
              |
       Motor vibratório
       Buzzer (teste)
```

---

# 🚨 Lógica de alerta atual

## Obstáculo detectado pelo sensor superior

- LED vermelho acionado;
- Motor vibratório ativado;
- Buzzer acionado durante testes.

## Obstáculo detectado pelo sensor inferior

- LED azul acionado;
- Motor vibratório ativado;
- Buzzer acionado durante testes.

## Caminho livre

- LED verde acionado;
- Motor desligado;
- Buzzer desligado.

---

# 🔬 Testes realizados

✅ Leitura de distância utilizando sensores ultrassônicos;

✅ Comunicação serial para monitoramento das medições;

✅ Controle individual dos LEDs;

✅ Controle PWM do motor vibratório;

✅ Controle PWM do buzzer;

✅ Integração dos sensores com sistema de alerta.

---

# 🚀 Próximas melhorias

- [ ] Implementação de diferentes níveis de vibração conforme distância;
- [ ] Testes de precisão dos sensores;
- [ ] Redução de falsos positivos;
- [ ] Desenvolvimento de PCB própria;
- [ ] Uso de bateria recarregável;
- [ ] Inclusão de GPS para localização;
- [ ] Integração com aplicativo móvel;
- [ ] Validação com usuários.

---

# 💻 Compilação

Requisitos:

- Raspberry Pi Pico SDK;
- CMake;
- GCC ARM Toolchain;
- Visual Studio Code.

Compilação:

```bash
mkdir build
cd build

cmake ..
make
```

---

# 📚 Tecnologias utilizadas

- C/C++;
- Raspberry Pi Pico SDK;
- PWM;
- GPIO;
- Sensores ultrassônicos;
- Sistemas embarcados;
- Arquitetura modular.

---

# 👩‍💻 Autora

Projeto desenvolvido como pesquisa e protótipo de tecnologia assistiva.

**Lorrany SafeStep**  
Sistema embarcado para auxílio à mobilidade de pessoas com deficiência visual.

---

# 📄 Licença

Este projeto está em desenvolvimento para fins acadêmicos e de pesquisa.