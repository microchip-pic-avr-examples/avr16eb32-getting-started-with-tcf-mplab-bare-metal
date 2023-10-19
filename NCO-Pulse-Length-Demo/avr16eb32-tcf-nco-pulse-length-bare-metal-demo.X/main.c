/* Used by util/delay.h */
#define F_CPU 20000000UL

/* Formula to map the requested frequency to the CMP register */
#define TCF0_NCOPL_HZ_TO_INCREMENT(HZ, F_CLOCK)   (uint32_t)(((float)(HZ) * 16777216.0) / (float)(F_CLOCK) + 0.5)

#include <util/delay.h>
#include <avr/io.h>


void CLOCK_Initialize(void)
{
    /* Disable the clock prescaler */
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0x0);
}

void TCF0_OutputsSet(uint8_t value)     
{      
    while((TCF0.STATUS & TCF_CTRLABUSY_bm) != 0){};
    TCF0.CTRLC = value;
}

void TCF0_ClockSet(TCF_CLKSEL_t config)
{
    TCF0.CTRLB |= config;    
}

void TCF0_PrescalerSet(TCF_PRESC_t config)
{     
    while((TCF0.STATUS & TCF_CTRLABUSY_bm) != 0){};
    TCF0.CTRLA  |= config;
}
void TCF0_ModeSet(TCF_WGMODE_t mode)
{    
    TCF0.CTRLB |= mode;
}

void TCF0_CounterSet(uint32_t value)
{
    while((TCF0.STATUS & TCF_CNTBUSY_bm) != 0){};   
    TCF0.CNT0 = (uint8_t)value;  
}

void TCF0_CompareSet(uint32_t value)
{
    while((TCF0.STATUS & TCF_CMP0BUSY_bm) != 0){};
    TCF0.CMP = value; 
}

void TCF0_Start(void)
{
    while((TCF0.STATUS & TCF_CTRLABUSY_bm) != 0){};
    TCF0.CTRLA |=  TCF_ENABLE_bm;
}

void TCF0_Stop(void)
{
    while((TCF0.STATUS & TCF_CTRLABUSY_bm) != 0){};
    TCF0.CTRLA &= ~TCF_ENABLE_bm;   
}

void TCF0_NCO_PulseLengthSet(TCF_WGPULSE_t config)
{
    uint8_t temp; 
    while((TCF0.STATUS & TCF_CTRLCBUSY_bm) != 0){};       
    temp = (TCF0.CTRLC & ~TCF_WGPULSE_gm) |
               (  config   &  TCF_WGPULSE_gm); 
    TCF0.CTRLC = temp;
}

void TCF0_Initialize(void)
{
   /* Enable the pin outputs */
   TCF0_OutputsSet(TCF_WO0EN_bm | TCF_WO1EN_bm);
   
   /* Select the 20 MHz Peripheral Clock */
   TCF0_ClockSet(TCF_CLKSEL_CLKPER_gc);
   
   /* Configure the TCF in Numerically Controlled Oscillator Pulse-Frequency mode */
   TCF0_ModeSet(TCF_WGMODE_NCOPF_gc);
   
   /* Load CMP register with the frequency */
   TCF0_CompareSet(TCF0_NCOPL_HZ_TO_INCREMENT(125000, 20000000)); 
   
   /* Configure the pulse length to be 1 clock cycle */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK1_gc);
   
   /* Configure the TCF to start counting from 0 */
   TCF0_CounterSet(0);
}

void NCO_Pulse_Length_Demo(void)
{
{
  /* Enable the TCF */
    TCF0_Start(); 
    
    /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 2 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK2_gc);
   
   /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 4 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK4_gc);
   
   /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 8 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK8_gc);
   
   /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 6 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK16_gc);
   
   /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 32 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK32_gc);
   
   /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 64 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK64_gc);
   
   /* Delay for 20 us */
   _delay_us(20);
   
   /* Configure the pulse-length to 128 clock cycles */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK128_gc);
   
   /* Delay for 20 us */
   _delay_us(18);
   
   /* Stop the timer */
   TCF0_Stop();
   
   /* Configure the pulse-length to 1 clock cycle */
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK1_gc);
}
}


void main(void) 
{  
    CLOCK_Initialize();
    TCF0_Initialize();
    while(1)
    {
        NCO_Pulse_Length_Demo();
        _delay_ms(20);
    }    
}
