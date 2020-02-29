/*
 * Desafio: Interrupções
 * Autores: Alisson Cerutti e Lucas Steffens
 * Descrição: Quando um botão é pressionado, o LED definido para o pino, liga e desliga
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

// Variaveis do estado das led
uint8_t pin = 5; // Saida do GPIO5
uint8_t pin2 = 4; // Saida do GPIO4
uint8_t pin3 = 2; // Saida do GPIO2


void GPIO_INTERRUPT()
{

  uint32_t gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS); // lê  status da interrupção
  GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status); //limpa a mascara de interrupção

  if (gpio_status & BIT(14)) // Verifica o pino 14
      {
	    gpio_output_set((1 << pin),0,(1 << pin), 0);
	    gpio_output_set(0,(1 << pin),(1 << pin), 0);
      }

  else if (gpio_status & BIT(12)) // Verifica o pino 12
      {
	  gpio_output_set((1 << pin2),0,(1 << pin2), 0);
	  gpio_output_set(0,(1 << pin2),(1 << pin2), 0);
      }
  else if (gpio_status & BIT(13)) // Verifica o pino 13
      {
	  gpio_output_set((1 << pin3),0,(1 << pin3), 0);
	  gpio_output_set(0,(1 << pin3),(1 << pin3), 0);
      }
}

void ICACHE_FLASH_ATTR user_init()
{
  gpio_init();//inicializa o modulo de GPIO

  //Configura os gpios
  //Saídas
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); // Cada GPIO tem um codigo, basta consultar manual
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
  //Entradas
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); // Cada GPIO tem um codigo, basta consultar manual
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);

  GPIO_DIS_OUTPUT(GPIO_ID_PIN(14)); //pino 5 como entrada
  GPIO_DIS_OUTPUT(GPIO_ID_PIN(12)); //pino 4 como entrada
  GPIO_DIS_OUTPUT(GPIO_ID_PIN(13)); //pino 2 como entrada
  //Habilita os pull ups
  PIN_PULLUP_EN(PERIPHS_IO_MUX_MTMS_U);
  PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDI_U);
  PIN_PULLUP_EN(PERIPHS_IO_MUX_MTCK_U);

  ETS_GPIO_INTR_DISABLE(); //Desativa todas as interrupções
  ETS_GPIO_INTR_ATTACH(GPIO_INTERRUPT,NULL); // Definir a função do manipulador da interrupção
  //Configura o GPIO para o tipo de interrupção
  gpio_pin_intr_state_set(GPIO_ID_PIN(14), GPIO_PIN_INTR_LOLEVEL);
  gpio_pin_intr_state_set(GPIO_ID_PIN(12), GPIO_PIN_INTR_LOLEVEL);
  gpio_pin_intr_state_set(GPIO_ID_PIN(13), GPIO_PIN_INTR_LOLEVEL);
  ETS_GPIO_INTR_ENABLE(); //ativa interrupção
}
