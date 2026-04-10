# 🍷 Vinheria Agnello — Sistema de Monitoramento de Luminosidade

Projeto desenvolvido para a disciplina de Edge Computing & Computer Systems da FIAP.

## 📌 Descrição do Projeto

Sistema embarcado utilizando Arduino Uno (ATmega 328P) para monitoramento da luminosidade no ambiente de armazenamento de vinhos da Vinheria Agnello.

O sistema realiza a leitura de um sensor LDR, processa os dados via conversor analógico-digital (ADC) e fornece feedback visual e sonoro com base nos níveis de luminosidade detectados.

## 🚀 Tecnologias Utilizadas

- Arduino IDE  
- Linguagem C/C++  
- Simulação com Tinkercad 

## ⚙️ Funcionalidades

- 📊 Leitura contínua do sensor LDR com conversão analógico-digital  
- 🔄 Mapeamento do valor bruto para porcentagem de luminosidade (0% a 100%) utilizando `map()`  
- 🟢 LED verde indica nível OK (0% a 80%)  
- 🟡 LED amarelo + buzzer por 3 segundos em nível de alerta (81% a 90%)  
- 🔁 Buzzer volta a soar caso o nível permaneça  
- 🔴 LED vermelho + buzzer intermitente em nível crítico (91% a 100%)  
- 📟 Display LCD 16x2 com:
  - Animação de boas-vindas  
  - Exibição do nome/logotipo da Vinheria Agnello  
  - Status em tempo real  
  - Porcentagem de luminosidade  

## 🧰 Componentes Utilizados

- 1x Arduino Uno (ATmega 328P)  
- 1x Sensor LDR (fotorresistor)  
- 1x Display LCD 16x2  
- 1x LED verde  
- 1x LED amarelo  
- 1x LED vermelho  
- 1x Buzzer  
- Resistores  
- Protoboard  

## 🧪 Simulação no Tinkercad

Acesse a simulação completa do projeto:

🔗 https://www.tinkercad.com/things/fT5qrLSh0Dl-amazing-elzing

## 👥 Integrantes do Grupo

- Eduardo Guzeli Nogueira — RM: 571143  
- Octávio Mello Covre de Souza — RM: 571811  
- Juliano Galhardo de Oliveira — RM: 572493  
- Gabriel Torres Zambo — RM: 569883  
- Hiago Silva de Oliveira — RM: 572664   
