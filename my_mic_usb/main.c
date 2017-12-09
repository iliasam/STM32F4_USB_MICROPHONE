//STM32F4-Discovery USB MICROPHONE
//by ILIASAM

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4_discovery_audio_codec.h"
#include "usbd_audio_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_audio_core.h"
#include "waverecorder.h"


__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

__IO uint8_t UserButtonPressed = 0;

__IO uint32_t TimingDelay;

int16_t audiodata[64];//this data is playing by speaker

extern uint16_t RecBuf0[MIC_FILTER_RESULT_LENGTH]; //buffer for filtered PCM data from MIC
extern uint16_t RecBuf1[MIC_FILTER_RESULT_LENGTH]; //buffer for filtered PCM data from MIC
extern uint8_t buffer_ready;

void init_audio_dac(void);

int main(void)
{
  
  RCC_ClocksTypeDef RCC_Clocks;
  
  /* Initialize LEDs and User_Button on STM32F4-Discovery --------------------*/
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO); 
  
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  
  
  RCC_GetClocksFreq(&RCC_Clocks);//test
  
  EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 86, I2S_AudioFreq_16k);//init speaker (optional)
  
  USBD_Init(&USB_OTG_dev,      
            USB_OTG_FS_CORE_ID,
            &USR_desc, 
            &AUDIO_cb, 
            &USR_cb);
  
  
  simple_rec_start();//initialise MIC and start capture data from MIC
  
  EVAL_AUDIO_Play((uint16_t*)(&audiodata[0]),MIC_FILTER_RESULT_LENGTH*2*2);//play data to speaker (optional)
  
  while(1)
  {
    asm("nop");
  }
}


void delay_ms(uint32_t ms)
{
  volatile uint32_t nCount;
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);
  nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
  for (; nCount!=0; nCount--);
}


void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

//speaker CallBack - optional
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t* pBuffer, uint32_t Size)
{
  uint8_t i;
  //called after speaker data TransferComplete
  asm("nop");
#ifdef AUDIO_MAL_MODE_NORMAL
  for (i=0;i<(MIC_FILTER_RESULT_LENGTH*2);i++)
  {
    if (buffer_ready == 1) {audiodata[i] = RecBuf1[i>>1];} else {audiodata[i] = RecBuf0[i>>1];}//make pseudo-stereo
  }
  
  EVAL_AUDIO_Play((uint16_t*)(&audiodata[0]),MIC_FILTER_RESULT_LENGTH*2*2);
#endif
}
