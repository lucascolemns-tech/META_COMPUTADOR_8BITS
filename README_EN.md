# 8-Bit Educational Computer — SAP-1

[Versão em português](README.md)

An academic project to design and build an educational 8-bit computer inspired by the SAP-1 architecture. It demonstrates how memory, registers, the arithmetic and logic unit (ALU), control unit, and bus communicate.

> **Goal:** connect computer architecture and digital electronics concepts to the physical operation of a computer.

## Contents

- [Overview](#overview)
- [Phenolic PCB fabrication](#phenolic-pcb-fabrication)
- [Architecture and modules](#architecture-and-modules)
- [Development method](#development-method)
- [Tools](#tools)
- [Results](#results)
- [Suggested repository structure](#suggested-repository-structure)
- [Team](#team)
- [Supporting documentation](#supporting-documentation)
- [References](#references)

## Overview

Based on the SAP-1 architecture presented by Albert Paul Malvino, this project explores fundamental principles in a computer's operating cycle. The goal is to make data storage, processing, and transfer between modules visible and accessible.

The work included studying and simulating the circuits, assembling modules on breadboards, testing and troubleshooting, and designing and manufacturing printed circuit boards (PCBs).

## Phenolic PCB fabrication

The project progressed from module-level breadboard tests to printed circuit boards. The project log documents the production and revision of boards for modules such as the bus, clock, registers, program counter, and RAM. Photos are grouped by stage and paired with context.

### 1. Prototypes and module validation

Before PCB fabrication, modules were assembled and debugged on breadboards. These records show test circuits and early component assemblies used to check connections and module behavior.

| Record | Record |
|:--:|:--:|
| <img src="assets/processo/imagem_1_processo_computador8bits.jpg" alt="Prototype, image 1" width="360"> | <img src="assets/processo/imagem_2_processo_computador8bits.jpg" alt="Prototype, image 2" width="360"> |
| <img src="assets/processo/imagem_3_processo_computador8bits.jpg" alt="Prototype, image 3" width="360"> | <img src="assets/processo/imagem_4_processo_computador8bits.jpg" alt="Prototype, image 4" width="360"> |
| <img src="assets/processo/imagem_5_processo_computador8bits.jpg" alt="Prototype, image 5" width="360"> |  |

### 2. Pattern transfer and etching

For the bus simulator, the PCB pattern was transferred onto phenolic board using a heat press. The first attempt used a single-sided board, although the original design called for a double-sided board; the team adapted the design to continue. Etching then removed copper from unprotected areas, leaving the circuit traces and pads. According to the team, hydrogen peroxide and muriatic acid were used with support from CEFET-MG laboratory technicians.

| Record | Record |
|:--:|:--:|
| <img src="assets/processo/imagem_6_processo_computador8bits.jpg" alt="Phenolic board fabrication, image 6" width="360"> | <img src="assets/processo/imagem_7_processo_computador8bits.jpg" alt="Phenolic board fabrication, image 7" width="360"> |
| <img src="assets/processo/imagem_8_processo_computador8bits.jpg" alt="Phenolic board fabrication, image 8" width="360"> | <img src="assets/processo/imagem_9_processo_computador8bits.jpg" alt="Phenolic board fabrication, image 9" width="360"> |
| <img src="assets/processo/imagem_10_processo_computador8bits.jpg" alt="Phenolic board fabrication, image 10" width="360"> |  |

### 3. Drilling, soldering, and revision

After etching and inspecting the traces, holes were drilled for component leads and connections. The project log also records component assembly and soldering. During revisions, the team identified issues such as soldering orientation, footprints, and connections; each module was checked before integration.

| Record | Record |
|:--:|:--:|
| <img src="assets/processo/imagem_11_processo_computador8bits.jpg" alt="Drilling and assembly, image 11" width="360"> | <img src="assets/processo/imagem_12_processo_computador8bits.jpg" alt="Drilling and assembly, image 12" width="360"> |
| <img src="assets/processo/imagem_13_processo_computador8bits.jpg" alt="Drilling and assembly, image 13" width="360"> | <img src="assets/processo/imagem_14_processo_computador8bits.jpg" alt="Drilling and assembly, image 14" width="360"> |
| <img src="assets/processo/imagem_15_processo_computador8bits.jpg" alt="Drilling and assembly, image 15" width="360"> | <img src="assets/processo/imagem_16_processo_computador8bits.jpg" alt="Drilling and assembly, image 16" width="360"> |

### 4. Computer integration and testing

With the modules assembled, testing focused on their combined operation. The records show the large breadboard assembly and circuits running, with LEDs and displays indicating system states.

| Record | Record |
|:--:|:--:|
| <img src="assets/processo/imagem_17_processo_computador8bits.jpg" alt="Integration and testing, image 17" width="360"> | <img src="assets/processo/imagem_18_processo_computador8bits.jpg" alt="Integration and testing, image 18" width="360"> |
| <img src="assets/processo/imagem_19_processo_computador8bits.jpg" alt="Integration and testing, image 19" width="360"> |  |

## Architecture and modules

The implementation includes these functional blocks:

- **Memory:** stores data and instructions.
- **Registers:** temporarily hold values during operations.
- **ALU:** performs arithmetic and logic operations.
- **Control unit:** coordinates operations through control signals.
- **Bus:** shared path for data transfer between modules.
- **Clock:** provides timing for circuit synchronization.

Modules were checked individually before integration, allowing the team to observe and debug them step by step.

## Development method

1. Study the SAP-1 architecture and digital electronics fundamentals.
2. Design and simulate modules in **Logisim Evolution**.
3. Assemble circuits on breadboards, with repeated testing and correction.
4. Analyze signals using laboratory equipment, including an oscilloscope.
5. Design PCBs in **Altium Designer**.
6. Manufacture boards at CEFET-MG laboratories and integrate the modules.

## Tools

- **Logisim Evolution** — digital circuit design and simulation.
- **Altium Designer** — printed circuit board design.
- **Laboratory instruments** — signal measurement and analysis during testing.

## Results

An 8-bit computer was developed and tested on breadboards, with memory, ALU, registers, bus, and clock modules. Simulation helped validate circuits before physical assembly. Testing uncovered and corrected timing, power, and module communication issues, supporting system integration.

The project provided practical experience in digital electronics, assembly, measurement, and circuit debugging, and made it easier to understand how information is stored, processed, and transferred.

## Suggested repository structure

Organize files according to the materials actually published. One possible structure is:

```text
.
├── README.md
├── simulacao/       # Logisim Evolution files
├── pcb/             # PCB projects and manufacturing files
├── documentacao/    # Instructions, project log, and EEPROM truth table
├── assets/processo/ # Process and test photos
└── referencias/     # Datasheets and supporting references
```

> This is a suggested layout; include only files that are part of the published project.

## Team

- Arthur Miguel Rodrigues Pereira
- Elias Sousa Pinheiro
- Gabriel Listen da Silva Ferreira
- Lucas Colem Nunes
- Mateus Henrique de Souza Godinho

**Advisor:** M.e Emerson Guilherme Alves Estevam  
**Project code:** 26212-C0  
**Institution:** CEFET-MG

## Supporting documentation

- [SAP-1 instructions and clock sequence](documentacao/instrucoes-sap1.pdf)
- [Project logbook](documentacao/diario-de-bordo.pdf)
- [EEPROM truth table](documentacao/tabela-verdade-eeprom.pdf)

The EEPROM table maps carry, opcode, and clock step to control signals and the bytes programmed into the three EEPROMs. The instruction sheet documents the shared fetch cycle and implemented operations, including LDA, ADD, SUB, STA, LDI, JMP, OR, AND, XOR, JC, OUT, and HLT.

## References

- MALVINO, Albert Paul. *Digital Computer Electronics: An Introduction to Microcomputers*.
- EATER, Ben. *Digital Electronics*. Educational material on digital electronics and computer architecture.
- **Logisim Evolution.** Software used for digital circuit simulation.
- **Altium Designer.** Software used for printed circuit board design.
- **Texas Instruments.** Datasheets for integrated circuits used in the project.

