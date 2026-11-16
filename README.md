# Computador Didático de 8 Bits — SAP-1

[English version](README_EN.md)

Projeto acadêmico de desenvolvimento e implementação de um computador didático de 8 bits inspirado na arquitetura SAP-1. O sistema evidencia, de forma prática e visual, como memória, registradores, unidade lógica e aritmética (ULA), unidade de controle e barramento se comunicam.

> **Objetivo:** aproximar os conceitos de arquitetura de computadores e eletrônica digital do funcionamento físico de um computador.

## Sumário

- [Visão geral](#visão-geral)
- [Fabricação das placas de fenolite](#fabricação-das-placas-de-fenolite)
- [Arquitetura e módulos](#arquitetura-e-módulos)
- [Metodologia](#metodologia)
- [Ferramentas](#ferramentas)
- [Resultados](#resultados)
- [Estrutura sugerida do repositório](#estrutura-sugerida-do-repositório)
- [Equipe](#equipe)
- [Documentação complementar](#documentação-complementar)
- [Referências](#referências)

## Visão geral

O projeto parte da arquitetura SAP-1 apresentada por Albert Paul Malvino para explorar os princípios fundamentais presentes no ciclo de operação de um computador. A proposta é tornar visíveis o armazenamento, o processamento e a transferência de informações entre os módulos do sistema.

O trabalho incluiu estudo e simulação dos circuitos, montagem dos módulos em protoboard, testes e correções, além do desenvolvimento e da fabricação de placas de circuito impresso (PCBs).

## Fabricação das placas de fenolite

O projeto avançou dos testes modulares em protoboard para placas de circuito impresso. O diário de bordo documenta a produção e revisão de placas para módulos como barramento, clock, registradores, contador de programa e RAM. As imagens estão organizadas abaixo por etapa, com uma explicação junto a cada conjunto.

### 1. Protótipos e validação dos módulos

Antes da fabricação das placas, os módulos foram montados e depurados em protoboard. Os registros mostram circuitos de teste e primeiras montagens com componentes, usados para verificar as ligações e o comportamento de cada bloco.

| Registro | Registro |
|:--:|:--:|
| <img src="assets/processo/imagem_1_processo_computador8bits.jpg" alt="Protótipo, imagem 1" width="360"> | <img src="assets/processo/imagem_2_processo_computador8bits.jpg" alt="Protótipo, imagem 2" width="360"> |
| <img src="assets/processo/imagem_3_processo_computador8bits.jpg" alt="Protótipo, imagem 3" width="360"> | <img src="assets/processo/imagem_4_processo_computador8bits.jpg" alt="Protótipo, imagem 4" width="360"> |
| <img src="assets/processo/imagem_5_processo_computador8bits.jpg" alt="Protótipo, imagem 5" width="360"> |  |

### 2. Transferência do desenho e corrosão

No processo registrado para o simulador de barramento, o desenho da PCB foi transferido para a fenolite com uma prensa térmica. A primeira tentativa usou placa de face simples, embora o desenho original previsse dupla face; a equipe fez adaptações para continuar. Depois, a corrosão removeu o cobre das áreas sem proteção e deixou as trilhas e ilhas do circuito. Segundo o relato da equipe, foi usada água oxigenada com ácido muriático, com acompanhamento dos técnicos do laboratório do CEFET-MG.

| Registro | Registro |
|:--:|:--:|
| <img src="assets/processo/imagem_6_processo_computador8bits.jpg" alt="Fabricação fenolite, imagem 6" width="360"> | <img src="assets/processo/imagem_7_processo_computador8bits.jpg" alt="Fabricação fenolite, imagem 7" width="360"> |
| <img src="assets/processo/imagem_8_processo_computador8bits.jpg" alt="Fabricação fenolite, imagem 8" width="360"> | <img src="assets/processo/imagem_9_processo_computador8bits.jpg" alt="Fabricação fenolite, imagem 9" width="360"> |
| <img src="assets/processo/imagem_10_processo_computador8bits.jpg" alt="Fabricação fenolite, imagem 10" width="360"> |  |

### 3. Furação, soldagem e revisão

Após a corrosão e a inspeção das trilhas, foram feitos furos para os terminais dos componentes e conexões. O diário também registra montagem e soldagem de componentes nas placas. Durante as revisões, a equipe identificou pontos como orientação de soldagem, footprint e conexões que exigiam correção; cada módulo era verificado antes de seguir para integração.

| Registro | Registro |
|:--:|:--:|
| <img src="assets/processo/imagem_11_processo_computador8bits.jpg" alt="Furação e montagem, imagem 11" width="360"> | <img src="assets/processo/imagem_12_processo_computador8bits.jpg" alt="Furação e montagem, imagem 12" width="360"> |
| <img src="assets/processo/imagem_13_processo_computador8bits.jpg" alt="Furação e montagem, imagem 13" width="360"> | <img src="assets/processo/imagem_14_processo_computador8bits.jpg" alt="Furação e montagem, imagem 14" width="360"> |
| <img src="assets/processo/imagem_15_processo_computador8bits.jpg" alt="Furação e montagem, imagem 15" width="360"> | <img src="assets/processo/imagem_16_processo_computador8bits.jpg" alt="Furação e montagem, imagem 16" width="360"> |

### 4. Integração e testes do computador

Com os módulos montados, os testes passaram a observar o funcionamento em conjunto. Os registros mostram a montagem extensa em protoboard e circuitos em operação, com sinais luminosos e displays indicando estados do sistema.

| Registro | Registro |
|:--:|:--:|
| <img src="assets/processo/imagem_17_processo_computador8bits.jpg" alt="Integração e testes, imagem 17" width="360"> | <img src="assets/processo/imagem_18_processo_computador8bits.jpg" alt="Integração e testes, imagem 18" width="360"> |

## Arquitetura e módulos

A implementação contempla os seguintes blocos funcionais:

- **Memória:** armazenamento de dados e instruções.
- **Registradores:** retenção temporária de valores durante a execução das operações.
- **ULA:** realização de operações aritméticas e lógicas.
- **Unidade de controle:** coordenação das operações por meio de sinais de controle.
- **Barramento:** meio compartilhado para transferência de dados entre os módulos.
- **Clock:** referência temporal para sincronização dos circuitos.

Os módulos foram verificados individualmente antes da integração, permitindo observar e depurar seu funcionamento por etapas.

## Metodologia

1. Estudo da arquitetura SAP-1 e dos fundamentos de eletrônica digital.
2. Projeto e simulação dos módulos no **Logisim Evolution**.
3. Montagem dos circuitos em protoboard, com ciclos de teste e correção.
4. Análise de sinais com equipamentos de laboratório, incluindo osciloscópio.
5. Projeto das placas de circuito impresso no **Altium Designer**.
6. Manufatura das placas nos laboratórios do CEFET-MG e integração dos módulos.

## Ferramentas

- **Logisim Evolution** — projeto e simulação de circuitos digitais.
- **Altium Designer** — desenvolvimento das placas de circuito impresso.
- **Instrumentos de laboratório** — medição e análise dos sinais durante os testes.

## Resultados

Foi desenvolvido e testado um computador de 8 bits em protoboard, com módulos de memória, ULA, registradores, barramento e clock. A simulação auxiliou na validação dos circuitos antes da montagem física. Durante os testes, foram identificados e corrigidos problemas de temporização, alimentação e comunicação entre módulos, apoiando a integração do sistema.

A construção proporcionou experiência prática em eletrônica digital, montagem, medição e depuração de circuitos, além de facilitar a compreensão de como as informações são armazenadas, processadas e transferidas.

## Equipe

- Arthur Miguel Rodrigues Pereira
- Elias Sousa Pinheiro
- Gabriel Listen da Silva Ferreira
- Lucas Colem Nunes
- Mateus Henrique de Souza Godinho

**Orientador:** M.e Emerson Guilherme Alves Estevam  
**Código do projeto:** 26212-C0  
**Instituição:** CEFET-MG

## Documentação complementar

- [Instruções e sequência de clock do SAP-1](documentacao/instrucoes-sap1.pdf)
- [Diário de bordo do projeto](documentacao/diario-de-bordo.pdf)
- [Tabela verdade para gravação das EEPROMs](documentacao/tabela-verdade-eeprom.pdf)

A tabela EEPROM relaciona carry, opcode e passo de clock aos sinais de controle e bytes gravados nas três EEPROMs. As instruções documentam o ciclo comum de busca e as operações implementadas, incluindo LDA, ADD, SUB, STA, LDI, JMP, OR, AND, XOR, JC, OUT e HLT.

## Referências

- MALVINO, Albert Paul. *Digital Computer Electronics: An Introduction to Microcomputers*.
- EATER, Ben. *Digital Electronics*. Conteúdos educacionais sobre eletrônica digital e arquitetura de computadores.
- **Logisim Evolution.** Software utilizado para simulação de circuitos digitais.
- **Altium Designer.** Software utilizado para desenvolvimento das placas de circuito impresso.
- **Texas Instruments.** Datasheets dos circuitos integrados utilizados no projeto.









