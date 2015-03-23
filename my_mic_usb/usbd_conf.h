

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"

#define USBD_IN_AUDIO_FREQ                (uint16_t)(16000) //MIC frequency in Hz.

/* Audio frequency in Hz */
#ifndef EXTERNAL_CRYSTAL_25MHz
 #define USBD_AUDIO_FREQ                (uint16_t)(16000) /* Audio frequency in Hz.
                                                 It is advised to set standard frequencies >= 24KHz to get best quality
                                                 except for STM32F10 devices, when the HSE value is 25MHz, it is advised to
                                                 set audio frequencies reachable with this HSE value (refer to RM0008 for
                                                 more details). ie. it is advised to set 16KHz value in this case. 
                                                 Note that maximum allowed audio frequency is 96KHz (this limitation is 
                                                 due to the codec used on the Evaluation board. The STM32 I2S cell allows
                                                 to  reach 192KHz frequency).
                                                 @note
                                                    When modifying this value, make sure that the I2S PLL configuration allows
                                                    to get minimum error on audio frequency. This configuration is set in file
                                                    system_stm32f2xx.c or system_stm32f10x.c.*/
#else
 #define USBD_AUDIO_FREQ                48000  /* Audio frequency in Hz for STM32F10x devices family when 25MHz HSE value
                                                  is used. */
#endif /* EXTERNAL_CRYSTAL_25MHz */

#define DEFAULT_VOLUME                  80    /* Default volume in % (Mute=0%, Max = 100%) in Logarithmic values.
                                                 To get accurate volume variations, it is possible to use a logarithmic
                                                 coversion table to convert from percentage to logarithmic law.
                                                 In order to keep this example code simple, this conversion is not used.*/
#define AUDIO_TOTAL_IF_NUM              0x02
#define USBD_CFG_MAX_NUM                1
#define USBD_ITF_MAX_NUM                1
#define USB_MAX_STR_DESC_SIZ            200 
#define AUDIO_IN_EP                     0x81

#endif //__USBD_CONF__H__

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

