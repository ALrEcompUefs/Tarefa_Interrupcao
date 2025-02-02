#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.h"

// Arquivo .pio para controle da matriz
#include "pio_matrix.pio.h"

// Pino que realizará a comunicação do microcontrolador com a matriz
#define OUT_PIN 7

Quadros ANIMACOES[10];
Matriz_leds_config *Numeros[10];
/*s
|   Declaração das animações
|   Cada tipo Quadro representa uma animação com 5 quadros 
*/
// PRIMEIRA ANIMAÇÃO
    Matriz_leds_config numero_0 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_1 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_2 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_3 ={
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_4 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_5 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_6 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_7 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
     Matriz_leds_config numero_8 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    Matriz_leds_config numero_9 = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    
void configurar_numero(){
    Numeros[0]=&numero_0;
    Numeros[1]=&numero_1;
    Numeros[2]=&numero_2;
    Numeros[3]=&numero_3;
    Numeros[4]=&numero_4;
    Numeros[5]=&numero_5;
    Numeros[6]=&numero_6;
    Numeros[7]=&numero_7;
    Numeros[8]=&numero_8;
    Numeros[9]=&numero_9;
} 

//------------------------------------------------------------------------------------------------------------//
// Gera o binário que controla a cor de cada célula do LED
//rotina para definição da intensidade de cores do led
uint32_t gerar_binario_cor(double red, double green, double blue)
{
  unsigned char RED, GREEN, BLUE;
  RED = red * 255.0;
  GREEN = green * 255.0;
  BLUE = blue * 255.0;
  return (GREEN << 24) | (RED << 16) | (BLUE << 8);
}

uint configurar_matriz(PIO pio){
    bool ok;

    // Define o clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    return sm;
}

void imprimir_desenho(Matriz_leds_config configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = gerar_binario_cor(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = gerar_binario_cor(
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green,
                    configuracao[contadorLinha][contadorColuna].blue
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

RGB_cod obter_cor_por_parametro_RGB(int red, int green, int blue){
    RGB_cod cor_customizada = {red/255.0,green/255.0,blue/255.0};

    return cor_customizada;
}

void imprimir_numero(uint numero,PIO pio, uint sm){
    imprimir_desenho(*Numeros[numero],pio,sm);
}

void apagar_matriz(PIO pio, uint sm){
    Matriz_leds_config reset = {
        //   Coluna 0         Coluna 1         Coluna 2         Coluna 3         Coluna 4
        // R    G    B      R    G    B      R    G    B      R    G    B      R    G    B
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 4
    };
    imprimir_desenho(reset,pio,sm);
}