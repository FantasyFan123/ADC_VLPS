/*
 * File:		platinum.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "adc16.h"
#include "lptmr.h"
#include "vectors.h"
#include "smc.h"

tADC_Config Master_Adc_Config;
int adcresult;
unsigned char flag_wakeup;
void init_ADC16(void);
void clockMonitor(unsigned char state);

#ifdef CMSIS
#include "start.h"
#endif

/********************************************************************/
int main (void)
{      
#ifdef CMSIS  // If we are conforming to CMSIS, we need to call start here
    start();
#endif      
    lptmr_init(1000,LPTMR_USE_LPOCLK);   //trigger ADC per 1000ms
    init_ADC16(); 
    enable_irq(ADC0_irq_no);
    printf("Enter VLPS mode...\r\n");
    clockMonitor(OFF);
    enter_vlps();   
	while(1)
	{        
          if(flag_wakeup == 1)
          {
            flag_wakeup = 0;
            ADC0_SC2 &= ~ADC_SC2_ACFE_MASK;  
            disable_irq(ADC0_irq_no);
            printf("\n\r");
            printf("\n\r");
            printf("Wake up from VLPS..\n");
            printf("adcresult = %d\n",adcresult);
          }                    
          if((ADC0_SC1(0) & ADC_SC1_COCO_MASK) == ADC_SC1_COCO_MASK)
          {
            adcresult = ADC0_R(0);
            printf("wake up adcresult = %d\n",adcresult);
            if((adcresult>= 10000) && (adcresult<= 50000))
            {
              ADC0_SC2 |= ADC_SC2_ACFE_MASK;
              enable_irq(ADC0_irq_no);
              printf("Enter VLPS mode...\n");
              clockMonitor(OFF);
              enter_vlps();
            }
          }            
	} 
}
/********************************************************************/

void init_ADC16(void){
  
          // Turn on the ADC0 clock as well as the PDB clocks to test ADC triggered by PDB
            SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );
          // set lptmr as the ADC0 trigger source 
            SIM_SOPT7 = SIM_SOPT7_ADC0ALTTRGEN_MASK | SIM_SOPT7_ADC0TRGSEL(14);           
            PMC_REGSC |= PMC_REGSC_BGBE_MASK ;                             
            Master_Adc_Config.CONFIG1  = ADLPC_LOW
              | ADC_CFG1_ADIV(ADIV_1)
              | ADLSMP_LONG
              | ADC_CFG1_MODE(MODE_16)
              | ADC_CFG1_ADICLK(ADICLK_ADACK);
            Master_Adc_Config.CONFIG2  = MUXSEL_ADCA
              | ADACKEN_DISABLED
              | ADHSC_HISPEED
              | ADC_CFG2_ADLSTS(ADLSTS_20) ;
            Master_Adc_Config.COMPARE1 = 10000 ;                 // can be anything
            Master_Adc_Config.COMPARE2 = 50000 ;                 // can be anything
            Master_Adc_Config.STATUS2  = ADTRG_HW
              | ACFE_ENABLED
              | ACFGT_LESS
              | ACREN_ENABLED
              | DMAEN_DISABLED
              | ADC_SC2_REFSEL(REFSEL_EXT);            
            Master_Adc_Config.STATUS3  = CAL_OFF
              | ADCO_SINGLE
              | !AVGE_ENABLED
              | ADC_SC3_AVGS(AVGS_4);            
            Master_Adc_Config.STATUS1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(0);             
            
            ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc_Config);  // config ADC                        
            // Calibrate the ADC in the configuration in which it will be used:
            ADC_Cal(ADC0_BASE_PTR);                    // do the calibration         
            // The structure still has the desired configuration.  So restore it.
            // Why restore it?  The calibration makes some adjustments to the
            // configuration of the ADC.  The are now undone:            
            // config the ADC again to desired conditions
            ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc_Config);
}

void adc0_isr(void)
{
  adcresult = ADC0_R(0);
  flag_wakeup = 1; 
  clockMonitor(ON);
  //printf("Wake up from VLPS...\r\n");
  //printf("adcresult = %d\r\n",adcresult);
}


void clockMonitor(unsigned char state)
{
    if(state)
      MCG_C6 |= MCG_C6_CME0_MASK;
    else
      MCG_C6 &= ~MCG_C6_CME0_MASK;
}

