# TAREFA INTERRUPÇÕES

Este repósitorio foi criado para implemnetação da tarefa 1 da unidade de interrupções do curso de fomrção básica em software Embarcado do Embarcatech.

## Diagrama do circuito

Na imagem abaixo tem-se o diagrama do circuito montado no simulador wocki.]

 Foi  utilizado o microcontrolador raspberry pi pico w que é o empregado na placa bitdoglab, uma matriz de leds 5x5com leds rgb ws2812, dois push buttons e três leds para representar a led RGB.

![img](https://github.com/ALrEcompUefs/Tarefa_Interrupcao/blob/main/img/img1.png?raw=true "diagrama do circuito")

## Funcionalidades Exiigidas

1. O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo
2. O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado.
3. O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado.
4. Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.

## Requisitos

1. A leitura dos botões deve ser realizada através de rotinas de interrupção utilizando a SDK do raspberry pi pico w
2. Deve ser implemenatado um recurso de debouncer via software para leitura dos botões.

## Matriz de leds

Para o controle da matriz de leds foi implementada um biblioteca: ws2812 com o arquivo de cabeçalho ws2812.h e o arquivo executavél da biblioteca ws2812.c. A biblioteca utiliza o recurso da PIO disponível no microcontrolador da pico w que é o rp2040 para se comunicar e configurar a matriz de leds, o uso das funções e a importação da biblioteca podem ser visualziados no codigo principal Interrupcao.c

## LED RGB

A placa bitdoglab possui um led RGB do tipo catódo comum que pode ser usado através da GPIO do raspberry pi pico w. os pinos do led RGB estão conectados nos respectivos pinos da pico w: vermelho GPIO 13, verde GPIO 12 e azul GPIO 11. Para uso do led RGB foram implementadas duas funções, a função inicializar_leds que configura os pinos da GPIO correspondentes ao led RGB como uma saída e a função set_rgb que recebe um caractere como parâmetro e ativa o led correspondente ou apaga os leds.

## PUSH BUTTONS

A placa bitdoglab possui dois pushs buttons nomeados A e B que podem ser usados para entrada do usuário além de um push button do  joystick pinado ao GPIO 22.  A função inicializar_botoes configura os botões como um entrada e os coloca em modo pull-up deixando a entrada em nivél alto quando o botão não está sendo pressionado para evitar flutuações de leitura na entrada.

## INTERRUPÇÕES

Como solicitado nos requisitos a leitura dos botões foi implementada com o uso de interrupções.

No codigo abaixo a função da sdk é utilizada para registrar as interrupções para os pinos do GPIO que estão com os botões

```c
//cria gatilhos de interrupções para os os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_JkT,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
```

A interrupção é gerada numa borda de descida de clock e o enderço da função de tratamento da interrupção é gerada.

A função do tratamento de interrupção é declarada como abaixo, nela é escrita uma breve rotina que atualiza o valor do contador ou a a variavél de flag do modo bootsel.

```
static void gpio_irq_handler(uint gpio, uint32_t events);
```

## DEBOUNCER

Para evitar o efeito do bounce foi implementada uma verificação com temporizadores como é mostrado no codigo abaixo.

```
// Variavél para registro de tempo e controle de bounce da interrupção
static volatile uint32_t tempo_anterior = 0; 
```

```
// implementando debounce 
    // obtém tempo absoluto do instante atual
    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());

    if(tempo_atual - tempo_anterior > 200000){
        tempo_anterior = tempo_atual;
	.
	.
	.
     }
```

Nesta configuração a interrupção vai ser gerada varias vezes devido ao bounce entretanto apenas uma ativação do tratamento dessa interrupção vai acontecer devido a espera de pelo menos 200ms do botão apertado.
