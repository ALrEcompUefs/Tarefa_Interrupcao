#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "ws2812.h"

/* Definição dos pinos dos perifericos */
// LED RGB
const uint8_t LED_R=13, LED_G=11, LED_B= 12;
// BOTÕES
const uint8_t BOTAO_A=5,BOTAO_B=6;
// BOTÃO DOP JOYSTICK
const uint8_t BOTAO_JkT = 22;

// Variável global para controle de incremento do botão
static volatile uint contador=0;
// Variavél para registro de tempo e controle de bounce da interrupção
static volatile uint32_t tempo_anterior = 0; 
// Variavél de flag para ativar o bootsel
static volatile bool modo_boot = false;

// protótipos de funções
void inicializar_leds();
void inicializar_botoes();
void set_rgb(char cor);
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    // Inicializa entrad e saida padrão
    stdio_init_all();

    // incializa PIO para utilizar matriz de leds
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);
    configurar_numero();

    // Configura GPIO para os leds e botões
    inicializar_leds();
    inicializar_botoes();
    //cria gatilhos de interrupções para os os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_JkT,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);

    while (true) {
        imprimir_numero(contador,pio,sm);
        if(modo_boot){
            printf("Entrando em bootsel em 5 segundos\n");
            // pisca led azul
            for(int i =0;i<5;i++){
                set_rgb('B');
                sleep_ms(500);
                set_rgb('A');
                sleep_ms(500);
            }
            apagar_matriz(pio,sm);
            printf("Em modo bootsel\n");
            reset_usb_boot(0,0);
        }
        // Deixa o led vermelho piscando 5 vezes por segundo
        for(int i =0;i<5;i++){
            set_rgb('R');
            sleep_ms(100);
            set_rgb('A');
            sleep_ms(100);
        }
        
    }
}
/*
|   Função inicializar_leds
|   Configura os pinos da LED RGB
*/
void inicializar_leds(){
    // led vermelha
    gpio_init(LED_R);
    gpio_set_dir(LED_R,GPIO_OUT);
    // led verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G,GPIO_OUT);
    // led azul
    gpio_init(LED_B);
    gpio_set_dir(LED_B,GPIO_OUT);
}
/*
|   Função inicializar_botoes
|   Configura o botões como entrada em modo pull_up
*/
void inicializar_botoes(){
    //botão A
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A,GPIO_IN);
    gpio_pull_up(BOTAO_A);
    // botão b
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B,GPIO_IN);
    gpio_pull_up(BOTAO_B);
    // botão joystick
    gpio_init(BOTAO_JkT);
    gpio_set_dir(BOTAO_JkT,GPIO_IN);
    gpio_pull_up(BOTAO_JkT);
}
/*
|   Função set_rgb
|   Ativa a cor rgb de acordo ao parâmetro cor
|   char cor: 'R'= vermelho 'G' = verde 'B' = azul 'W' = branco 'A' = apagada  
*/
void set_rgb(char cor){
    switch (cor)
    {
    case 'R':
        gpio_put(LED_R,1);
        gpio_put(LED_G,0);
        gpio_put(LED_B,0);
        break;
    case 'G':
        gpio_put(LED_R,0);
        gpio_put(LED_G,1);
        gpio_put(LED_B,0);
        break;
    case 'B':
        gpio_put(LED_R,0);
        gpio_put(LED_G,0);
        gpio_put(LED_B,1);
        break;
    case 'W':
        gpio_put(LED_R,1);
        gpio_put(LED_G,1);
        gpio_put(LED_B,1);
        break;
    case 'A':
        gpio_put(LED_R,0);
        gpio_put(LED_G,0);
        gpio_put(LED_B,0);
        break;
    default:
        printf("Caractere invalido!!\n informe R,G,B,W ou A\n");
        break;
    }
}
/*
|   Função gpio_irq_handler
|   Realiza o tratamento da interrupção de GPIO
|   
*/
static void gpio_irq_handler(uint gpio, uint32_t events){
    // implementando debounce 
    // obtém tempo absoluto do instante atual
    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());

    // se passou por um intervalo de ao menos 2ms
    if(tempo_atual - tempo_anterior > 200000){
        tempo_anterior = tempo_atual;
        printf("Interrupção gerada no botão:%d\n",gpio);
        // A estrutura if else indentifica qual pino da GPIO lançou a interrupção
        // e faz o tratamento de acordo a cada pino
        if(gpio == BOTAO_A){
            contador >= 9? contador:contador++;
        }
        else if (gpio == BOTAO_B)
        {
            contador > 0? contador--:contador;
        }
        else{
            printf("Bootsel ativado\n");
            modo_boot= true;
        }
        printf("Contador em:%d\n",contador);
    }
}
