/*  
O que o programa faz?
basicamente imagine uma tabela, nesta tabela temos valores para acessar, assim, de forma geral, o código é uma forma da 
gente não ter que escrever 1 a 1 bit do EEPROM, e sim acessar o endereço do bit, e escrever o valor que queremos, 
ou ler o valor que queremos, ou seja, é uma forma de abstração para facilitar a leitura e escrita de dados na EEPROM.

Assim podemos utilizar e "artimanhas" para acessar os dados de forma mais facil é não ter que escrever
a correspondencia dos 8 bits do barramento.

Como o display é?

          aaa
        f     b
        f     b
          ggg
        e     c
        e     c
          ddd

Imagine que cada letra tem um led para acender, temos 8 bits, como mapeamos para 7 combinações de leds?
    A resposta é simples, o bit 0 é o a, o bit 1 é o b, o bit 2 é o c, 
    o bit 3 é o d, o bit 4 é o e, o bit 5 é o f, o bit 6 é o g, e o bit 7 é o ponto decimal. 

    o ponto decimal significa que ele é o bit mais significativo, ou seja, ele tem o valor mais alto, 
    e é utilizado para indicar se o número é negativo ou positivo, 
    ou seja, se o ponto decimal está aceso, significa que o número é negativo, 
    e se o ponto decimal está apagado, significa que o número é positivo.

    não é necessário no instante inicial

bit:   7    6    5    4    3    2    1    0
bar:   dp   g    f    e    d    c    b    a

para você dizer a linguagem C que algum valor é hexadecimal você coloca 0x[valor], exemplo: 0x3F, 
isso significa que o valor é 3F em hexadecimal, ou seja, 63 em decimal, ou seja, 0011 1111 
em binário, ou seja, os bits a, b, c, d, e, f estão acesos, e o bit g está apagado.

tabela para hexadecimais
(binario) 0000 >>> (hexadecimal) 0 >>> (decimal) 0
(binario) 0001 >>> (hexadecimal) 1 >>> (decimal) 1   
(binario) 0010 >>> (hexadecimal) 2 >>> (decimal) 2
(binario) 0011 >>> (hexadecimal) 3 >>> (decimal) 3
(binario) 0100 >>> (hexadecimal) 4 >>> (decimal) 4
(binario) 0101 >>> (hexadecimal) 5 >>> (decimal) 5
(binario) 0110 >>> (hexadecimal) 6 >>> (decimal) 6
(binario) 0111 >>> (hexadecimal) 7 >>> (decimal) 7
(binario) 1000 >>> (hexadecimal) 8 >>> (decimal) 8
(binario) 1001 >>> (hexadecimal) 9 >>> (decimal) 9
(binario) 1010 >>> (hexadecimal) A >>> (decimal) 10
(binario) 1011 >>> (hexadecimal) B >>> (decimal) 11
(binario) 1100 >>> (hexadecimal) C >>> (decimal) 12
(binario) 1101 >>> (hexadecimal) D >>> (decimal) 13
(binario) 1110 >>> (hexadecimal) E >>> (decimal) 14
(binario) 1111 >>> (hexadecimal) F >>> (decimal) 15

logo vamos escrever de 0 a 9 e ver como fica em hexadecimal

lembrando que: 

bit:   7    6    5    4    3    2    1    0
bar:   dp   g    f    e    d    c    b    a

PS: deixe dp em 0 para não acender o ponto decimal

0 display - somente g desligado, 0011 1111, equivalente 0011 = 3, 1111 = F, ou seja, 0x3F
1 display - somente a, b acesos, 0000 0110, equivalente 0000 = 0, 0110 = 6, ou seja, 0x06
2 display - somente a, b, d, e, g acesos, 0101 1011, equivalente 0101 = 5, 1011 = B, ou seja, 0x5B
3 display - somente a, b, c, d, g acesos, 0100 1111, equivalente 0100 = 4, 1111 = F, ou seja, 0x4F
4 display - somente b, c, f, g acesos, 0110 0110, equivalente 0110 = 6, 0110 = 6, ou seja, 0x66
5 display - somente a, c, d, f, g acesos, 0110 1101, equivalente 0110 = 6, 1101 = D, ou seja, 0x6D
6 display - somente a, c, d, e, f, g acesos, 0111 1101, equivalente 0111 = 7, 1101 = D, ou seja, 0x7D
7 display - somente a, b, c acesos, 0000 0111, equivalente 0000 = 0, 0111 = 7, ou seja, 0x07
8 display - todos os leds acesos, 0111 1111, equivalente 0111 = 7, 1111 = F, ou seja, 0x7F
9 display - somente a, b, c, d, f, g acesos, 0110 1111, equivalente 0110 = 6, 1111 = F, ou seja, 0x6F


tabela final 
    0x3F - 0 (display)
    0x06 - 1 (display)
    0x5B - 2 (display)
    0x4F - 3 (display)
    0x66 - 4 (display)
    0x6D - 5 (display)
    0x7D - 6 (display)
    0x07 - 7 (display)
    0x7F - 8 (display)
    0x6F - 9 (display)


*/
#include <stdio.h>
#include <stdlib.h>

#define ZERO 0x00
#define SINAL_MENOS 0x40 //somente g

//const para ser do tipo da ROM, somente leitura
const unsigned char display[10] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};

void escrever_digitos(int numero_do_barramento, int tipo_negativo_postivo, unsigned char output[4])
{
    /*
    A ideia do "negativo_positivo é se o valor um tipo que de variavel que inclui negativos até um certo valor, ou somente
    positivo 0-255
    */

    int negativo=0;

    if (tipo_negativo_postivo == 1 && numero_do_barramento > 127) 
    {
        // Verifica se o número é negativo
        negativo = 1;
        numero_do_barramento -= 256; //converte para o valor negativo correspondente
        numero_do_barramento = -numero_do_barramento; //pega o valor absoluto para calcular os dígitos
    }

/*essa ideia do output é simplesmente genial, 
temos 
    possibilidades nos displays 4 possibilidades de números(são quatro BCD)

    veja o calculo do primeiro BCD, dos "milhares", peguemos o valor 76, o número correspondendo no barramento é 
    76 em decimal é 0x4C em hexadecimal, (binario é 0100 1100)

    76 / 1000 = 0.076 >>> divisão por resto %10 vai dar um valor igual a 0
    76 / 100 = 0.76 >>> divisão por resto %10 vai dar um valor igual a 0
    76 / 10 = 7.6 >>> divisão por resto %10 vai dar um valor igual a 7
    76 / 1 = 76 >>> divisão por resto %10 vai dar um valor igual a 6

genial não? isto funciona para QUALQUER NÚMERO
*/

output[0] = display[(numero_do_barramento / 1000) % 10]; 
output[1] = display[(numero_do_barramento / 100) % 10];
output[2] = display[(numero_do_barramento / 10) % 10];
output[3] = display[numero_do_barramento % 10];

if (negativo) 
    { 
        for (int i = 0; i < 4; i++) 
    {
        if (output[i] == display[0]) 
            output[i] = ZERO; // Mantém o dígito como zero 
        else
            {
                if (i > 0)
                    output[i-1] = SINAL_MENOS; // Coloca o sinal de menos no dígito anterior
                else
                    output[i] = SINAL_MENOS; // Se for o primeiro dígito, coloca o sinal de menos nele mesmo
            break;
            }   
    }
}

for (int i = 0; i < 4; i++) 
    {
        if (output[i] == display[0]) 
            output[i] = ZERO; // Mantém o dígito como zero 
        else
            break; 
        
    }
}

/*a memoria rom tem 2kb, logo 2048 endereços, precisamos suprir TODOS

DETALHE MUITO IMPORTANTE, LOGISM EVOLUTION PRA ACEITAR O ARQUIVO ELE PRECISA SER FORMATADO DA SEGUINTE FORMA
int main(void)
    FILE *file = fopen("EEPROM.txt", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

*/
int main (void)
{
FILE *file = fopen("EEPROM.txt", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
fprintf(file, "v2.0 raw\n"); //não entendi ao certo, mas o logisim evolution para reconhecer o arquivo precisa ser formatado desta forma, ou seja, a primeira linha tem que ser "v2.0 raw", e a partir da segunda linha tem que ser os valores em hexadecimal, separados por espaço, exemplo: "3F 06 5B 4F 66 6D 7D 07 7F 6F", ou seja, os valores correspondentes aos dígitos de 0 a 9.

    for (int modo_negativo_ou_positivosomente = 0; modo_negativo_ou_positivosomente <= 1; modo_negativo_ou_positivosomente++)
    {
    for (int preencher_valores = 0; preencher_valores <= 255; preencher_valores++)
        {
        unsigned char output[4];
            escrever_digitos(preencher_valores, modo_negativo_ou_positivosomente, output);    
        for (int output_contagem = 0; output_contagem < 4; output_contagem++) 
            {
                fprintf(file, "%02X\n", output[output_contagem]);
            }
        }
    }

fclose(file);
printf("PERFEITO!!! carregue display_rom.txt no logisim evolution\n");
return 0;
}






