# AquaSentry

O AquaSentry é um sistema de monitoramento ambiental projetado para ambientes marinhos, fornecendo dados em tempo real sobre os níveis de oxigênio, temperatura da água e luz solar. Este projeto é uma solução inovadora para promover a saúde dos oceanos e capacitar comunidades costeiras a adotarem práticas sustentáveis de conservação.

![Captura_de_tela_2024-06-07_201113-removebg-preview](https://github.com/aquasentry/AquaSentry-GS-Edge/assets/91989307/a5c46d73-2448-4992-8819-0f371145d2fa)

## Tabela de Conteúdos

1. [Descrição](#descrição)
2. [Funcionalidades](#funcionalidades)
3. [Configuração](#configuração)
4. [Instruções de Uso](#instruções-de-uso)
5. [Exemplo de Uso em Simulação](#exemplo-de-uso-em-simulação)
6. [Contribuição](#contribuição)
7. [Licença](#licença)
8. [Conclusão](#conclusão)

## Descrição

O AquaSentry é um dispositivo autônomo de monitoramento ambiental projetado para ambientes marinhos. Utilizando sensores de alta precisão, ele coleta dados vitais sobre as condições da água, incluindo temperatura, níveis de oxigênio e intensidade da luz solar. Esses dados são exibidos em um display LCD e podem ser armazenados para referência futura.

## Funcionalidades

- **Monitoramento em Tempo Real**: Fornece dados precisos e atualizados sobre a qualidade da água em tempo real.
- **Exibição no Display LCD**: Apresenta informações sobre temperatura, níveis de oxigênio e luz solar em um display de fácil leitura.
- **Armazenamento de Dados**: Os dados podem ser armazenados na memória EEPROM para análise posterior.
- **Alimentação Solar**: Opera de forma autônoma, sendo alimentado por energia solar e uma bateria recarregável.

## Configuração

### Componentes Utilizados

- Sensor de temperatura e umidade DHT22
- Display LCD 16x2 com interface I2C
- Módulo RTC DS1307
- Potenciômetro para simular o nível de oxigênio
- Sensor de luz (LDR)
- EEPROM interna do Arduino para armazenamento de dados

### Pinagem

- Pino do sensor DHT: D2
- Pino do LDR: A1
- Pino do potenciômetro: A0

### Bibliotecas Necessárias

- DHT Sensor Library
- LiquidCrystal I2C Library
- RTClib

## Instruções de Uso

1. Conecte os componentes conforme a pinagem especificada.
2. Carregue o código para a placa Arduino.
3. Certifique-se de ajustar a data e hora no módulo RTC.
4. Posicione o AquaSentry em um ambiente marinho apropriado.
5. Monitore os dados exibidos no display LCD e observe as condições ambientais.

## Exemplo de Uso em Simulação

Suponha que você esteja realizando uma simulação em um ambiente controlado, como um aquário, para avaliar o desempenho do AquaSentry. Você configura o AquaSentry dentro do aquário e inicia a simulação. Aqui está o que você poderia observar:

1. **Configuração Inicial**: Você posiciona o AquaSentry no aquário e o conecta à fonte de energia. O display LCD do AquaSentry começa a exibir as leituras dos sensores.
2. **Monitoramento da Temperatura**: Você observa como as leituras de temperatura da água variam ao longo do tempo. Por exemplo, você pode notar um aumento na temperatura durante o dia devido à exposição à luz artificial.
3. **Ajuste do Nível de Oxigênio**: Usando o potenciômetro para simular o nível de oxigênio, você ajusta manualmente os valores para ver como o AquaSentry responde. Por exemplo, ao reduzir o nível de oxigênio simulado, você pode observar uma queda correspondente nos valores exibidos no display.
4. **Variação da Luz Solar**: Você altera a intensidade da luz no ambiente do aquário para simular diferentes condições de luz solar. O AquaSentry registra essas mudanças e exibe os valores correspondentes no display LCD.
5. **Análise dos Dados**: Você coleta os dados registrados pelo AquaSentry ao longo da simulação. Isso pode incluir registros de temperatura, níveis de oxigênio e luz solar. Você pode então analisar esses dados para entender melhor como o AquaSentry responde a diferentes condições ambientais simuladas.

## Contribuição

Contribuições para melhorias são bem-vindas! Sinta-se à vontade para abrir problemas ou enviar solicitações de pull.

## Conclusão

O AquaSentry representa uma solução inovadora para monitoramento ambiental em ambientes marinhos. Sua capacidade de fornecer dados em tempo real sobre os níveis de oxigênio, temperatura da água e luz solar o torna uma ferramenta valiosa para a preservação dos oceanos e a sustentabilidade dos ecossistemas costeiros.

Ao possibilitar a análise detalhada das condições ambientais e promover a conscientização sobre a importância da saúde dos oceanos, o AquaSentry desempenha um papel fundamental na proteção dos ecossistemas marinhos e na promoção de práticas de conservação sustentáveis.

Com sua facilidade de uso e funcionalidades avançadas, o AquaSentry é uma escolha ideal para pesquisadores, conservacionistas e comunidades costeiras interessadas em monitorar e proteger os ambientes marinhos.
