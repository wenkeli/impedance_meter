#ifndef _BOARD_HY_MINISTM32V_H_
#define _BOARD_HY_MINI_STM32V_H_

#define Port2Pin(port, bit) ((port-'A')*16+bit)

	#define CYCLES_PER_MICROSECOND  72

//#define CYCLES_PER_MICROSECOND	(F_CPU/1000000)

#define SYSTICK_RELOAD_VAL      (CYCLES_PER_MICROSECOND*1000-1)

#define BOARD_LED_PIN           Port2Pin('B', 0)
#define BOARD_LED1_PIN			Port2Pin('B', 1)
#define BOARD_BUTTON_PIN        Port2Pin('C', 13)
#define BOARD_BUTTON1_PIN		Port2Pin('B', 2)

#define BOARD_NR_USARTS         5
#define BOARD_USART1_TX_PIN     Port2Pin('A', 9)
#define BOARD_USART1_RX_PIN     Port2Pin('A',10)
#define BOARD_USART2_TX_PIN     Port2Pin('D', 5)
#define BOARD_USART2_RX_PIN     Port2Pin('D', 6)
#define BOARD_USART3_TX_PIN     Port2Pin('D', 8)
#define BOARD_USART3_RX_PIN     Port2Pin('D', 9)
#define BOARD_UART4_TX_PIN      Port2Pin('C',10)
#define BOARD_UART4_RX_PIN      Port2Pin('C',11)
#define BOARD_UART5_TX_PIN      Port2Pin('C',12)
#define BOARD_UART5_RX_PIN      Port2Pin('D', 2)

#define BOARD_NR_SPI            3
#define BOARD_SPI1_NSS_PIN      Port2Pin('A', 4)
#define BOARD_SPI1_MOSI_PIN     Port2Pin('A', 7)
#define BOARD_SPI1_MISO_PIN     Port2Pin('A', 6)
#define BOARD_SPI1_SCK_PIN      Port2Pin('A', 5)
#define BOARD_SPI2_NSS_PIN      Port2Pin('B',12)
#define BOARD_SPI2_MOSI_PIN     Port2Pin('B',15)
#define BOARD_SPI2_MISO_PIN     Port2Pin('B',14)
#define BOARD_SPI2_SCK_PIN      Port2Pin('B',13)
#define BOARD_SPI3_NSS_PIN      Port2Pin('A',15)
#define BOARD_SPI3_MOSI_PIN     Port2Pin('B', 5)
#define BOARD_SPI3_MISO_PIN     Port2Pin('B', 4)
#define BOARD_SPI3_SCK_PIN      Port2Pin('B', 3)

#define BOARD_NR_GPIO_PINS      80
#define BOARD_NR_PWM_PINS       16
#define BOARD_NR_ADC_PINS       16
#define BOARD_NR_USED_PINS      35 // ala42 not set yet
#define BOARD_JTMS_SWDIO_PIN    Port2Pin('A',13)
#define BOARD_JTCK_SWCLK_PIN    Port2Pin('A',14)
#define BOARD_JTDI_PIN          Port2Pin('A',15)
#define BOARD_JTDO_PIN          Port2Pin('B', 3)
#define BOARD_NJTRST_PIN        Port2Pin('B', 4)

#define BOARD_USB_DISC_DEV      GPIOB
#define BOARD_USB_DISC_BIT      7

#endif
