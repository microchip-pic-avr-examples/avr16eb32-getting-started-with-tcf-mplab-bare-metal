/* Used by util/delay.h */
#define F_CPU 20000000UL

/* Formula to map the requested frequency to the CMP register */
#define TCF0_NCOFD_HZ_TO_INCREMENT(HZ, F_CLOCK, TCF0_PRESCALER)   (uint32_t)(((float)(HZ) * 33554432.0 * (TCF0_PRESCALER)) / ((float)(F_CLOCK)) + 0.5)

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
    TCF0.CTRLB |= TCF_CLKSEL_CLKPER_gc;    
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

void TCF0_Initialize(void)
{
   /* Enable the pin outputs */
   TCF0_OutputsSet(TCF_WO0EN_bm | TCF_WO1EN_bm);
   
   /* Select the 20 MHz Peripheral Clock */
   TCF0_ClockSet(TCF_CLKSEL_CLKPER_gc);
   
   /* Set Prescaler Division to 1 */
   TCF0_PrescalerSet(TCF_PRESC_DIV1_gc); 
   
   /* Configure the TCF in Numerically Controlled Oscillator Fixed Duty Cycle mode */
   TCF0_ModeSet(TCF_WGMODE_NCOFDC_gc); 
   
   /* Configure the TCF to start counting from 0 */
   TCF0_CounterSet(0);
   
   /* Load CMP register with the frequency */
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(10, 20000000, 1));
}

void NCO_Fixed_DutyCycle_Demo(void)
{   
    /* Enable the TCF */
    TCF0_Start();
    
    /* Delay for 600 ms */
   _delay_ms(600);
   
   /* Load the CMP register with a frequency of 100 Hz */
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(100, 20000000, 1));
   
    /* Delay for 60 ms */
   _delay_ms(60);
   
   /* Load the CMP register with a frequency of 1 KHz */
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(1000, 20000000, 1));
   
    /* Delay for 6 ms */
   _delay_ms(6);
   
   /* Load the CMP register with a frequency of 10 KHz */
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(10000, 20000000, 1));
   
    /* Delay for 600 us */
   _delay_us(600);
   
   /* Load the CMP register with a frequency of 100 KHz */
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(100000, 20000000, 1));
   
    /* Delay for 60 us */
   _delay_us(60);
   
    /* Stop the TCF */
   TCF0_Stop();
   
   /* Load the CMP register with a frequency of 10 Hz */
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(10, 20000000, 1));
}


void main(void) 
{   
    CLOCK_Initialize();
    TCF0_Initialize();
    while(1)
    {
        NCO_Fixed_DutyCycle_Demo();
        _delay_ms(1000);
    }    
}
