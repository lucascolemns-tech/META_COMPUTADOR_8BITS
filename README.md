# Computador Didático de 8 Bits — SAP-1

Projeto acadêmico de desenvolvimento e implementação de um computador didático de 8 bits inspirado na arquitetura SAP-1. O sistema evidencia, de forma prática e visual, como memória, registradores, unidade lógica e aritmética (ULA), unidade de controle e barramento se comunicam.

> **Objetivo:** aproximar os conceitos de arquitetura de computadores e eletrônica digital do funcionamento físico de um computador.

## Sumário

- [Visão geral](#visão-geral)
- [Arquitetura e módulos](#arquitetura-e-módulos)
- [Metodologia](#metodologia)
- [Ferramentas](#ferramentas)
- [Resultados](#resultados)
- [Estrutura sugerida do repositório](#estrutura-sugerida-do-repositório)
- [Equipe](#equipe)
- [Referências](#referências)

## Visão geral

O projeto parte da arquitetura SAP-1 apresentada por Albert Paul Malvino para explorar os princípios fundamentais presentes no ciclo de operação de um computador. A proposta é tornar visíveis o armazenamento, o processamento e a transferência de informações entre os módulos do sistema.

O trabalho incluiu estudo e simulação dos circuitos, montagem dos módulos em protoboard, testes e correções, além do desenvolvimento e da fabricação de placas de circuito impresso (PCBs).

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

## Estrutura sugerida do repositório

Organize os arquivos do projeto de acordo com os materiais efetivamente publicados. Uma estrutura possível é:

```text
.
├── README.md
├── simulacao/       # Arquivos do Logisim Evolution
├── pcb/             # Projetos e arquivos de fabricação das placas
├── documentacao/    # Diagramas, fotos e materiais técnicos
└── referencias/     # Datasheets e referências complementares
```

> Os diretórios acima são uma sugestão de organização; inclua apenas arquivos que façam parte da versão publicada do projeto.

## Equipe

- Arthur Miguel Rodrigues Pereira
- Elias Sousa Pinheiro
- Gabriel Listen da Silva Ferreira
- Lucas Colem Nunes
- Mateus Henrique de Souza Godinho

**Orientador:** M.e Emerson Guilherme Alves Estevam  
**Código do projeto:** 26212-C0  
**Instituição:** CEFET-MG

## Referências

- MALVINO, Albert Paul. *Digital Computer Electronics: An Introduction to Microcomputers*.
- EATER, Ben. *Digital Electronics*. Conteúdos educacionais sobre eletrônica digital e arquitetura de computadores.
- **Logisim Evolution.** Software utilizado para simulação de circuitos digitais.
- **Altium Designer.** Software utilizado para desenvolvimento das placas de circuito impresso.
- **Texas Instruments.** Datasheets dos circuitos integrados utilizados no projeto.
