# Fabrication of the 8-bit computer boards

[🇧🇷 Português](README.md) · [🇺🇸 English](README.en.md)

---

## Bus simulator

The bus simulator board was manufactured using the limited prior knowledge we had. We chose to etch the traces by removing the copper all around them because we did not know other methods. It is noticeable that this method takes longer to etch, since there is more copper to remove. In addition, the remaining traces become more fragile because they remain exposed to the etching process for longer.

![Visual record 1 — Bus simulator](imagens/placa-01.png)

![Visual record 2 — Bus simulator](imagens/placa-02.png)

---

## Program counter (PC)

When making the program counter for our PC, we encountered some problems. Due to the lack of instructions, we did not know that we should wait for the top layer instead of the bottom layer. We mirrored the bottom layer, which meant that all our PCB design work—aimed at keeping traces from running underneath the IC to make soldering easier—was lost. It took us a while to discover this, but we learned through trial and error. We also added Polygon Pour, which makes the copper get etched away only around the traces.

![Visual record 1 — Program counter (PC)](imagens/placa-03.png)

![Visual record 2 — Program counter (PC)](imagens/placa-04.png)

---

## Clock

Making the clock was one of the most difficult stages. The design itself had no errors. However, soldering failures caused us to lose progress. Gradually, we improved our work.

![Visual record 1 — Clock](imagens/placa-05.png)

![Visual record 2 — Clock](imagens/placa-06.png)

---

## Register

Making the register was relatively simple because the design consisted of only four modules. However, jumpers had to be added to all four modules because a connection was missing from the design. Soldering was relatively quick and simple, and it was one of the team's best soldering jobs.

![Visual record 1 — Register](imagens/placa-07.png)

![Visual record 2 — Register](imagens/placa-08.png)

---

## RAM memory

Manufacturing the RAM memory board was also simpler, with no major difficulties during the fabrication and assembly process.

![Visual record 1 — RAM memory](imagens/placa-09.png)

![Visual record 2 — RAM memory](imagens/placa-10.png)

---

## AMAR

Designing this board was one of the most difficult tasks because of the wide variety of components and the difficulty of repositioning the traces. However, etching was successful. We expected it to be difficult because of the large copper contact area, but the Eagle polygon pour tool made it easier. The board was not soldered because some components were missing.

![Visual record 1 — AMAR](imagens/placa-11.png)

![Visual record 2 — AMAR](imagens/placa-12.png)
