[![MCHP](../images/microchip.png)](https://www.microchip.com)

## Use case 1: Generate Two Variable-Frequency Signals in NCO-Fixed Mode Using  the TCF
The example below shows how to set the TCF to generate Two Variable-Frequency signals, ranging from 10 Hz to 100 khz, with one magnitude step change. The TCF is operating in Numerically Controlled Oscillator (NCO) mode, and has an important advantage over classical Pulse-Width Modulation (PWM) control, as it offers liniar ferquency regulation.


## Related Documentation
More details and code examples on the AVR16EB32 can be found at the following links:
- [TBxxxx - Getting Started with Timer/Counter Type F (TCF)](insert url link here)
- [AVR16EB32 Product Page](insert url link here)
- [AVR16EB32 Code Examples on GitHub](insert url link here)

## Software Used
- [MPLAB® X IDE v6.15 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [AVR-Ex_DFP-2.5.184 or newer Device Pack](insert url link here)

## Hardware Used
- AVR16EB32 Curiosity Nano [(AVR16EB32)](insert url link here)



## Functionality
<br>After the peripheral clock and TCF are initialized, an infinite loop is called, using the NCO_Fixed_DutyCycle_Demo function.

We first start the timer with a frequency of 100 Hz and run up until we reach 100 KHz. -> The timer starts running with a frequency of 100 Hz, and continues to run until it reaches 100 kHz.

At the end we stop the timer and reset the frequency to default.

```
void NCO_Fixed_DutyCycle_Demo(void)
{   
   TCF0_Start();
   _delay_ms(600);
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(100, 20000000, 1));
   _delay_ms(60);
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(1000, 20000000, 1));
   _delay_ms(6);
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(10000, 20000000, 1));
   _delay_us(600);
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(100000, 20000000, 1));
   _delay_us(60);
   TCF0_Stop();
   TCF0_CompareSet(TCF0_NCOFD_HZ_TO_INCREMENT(10, 20000000, 1));
}

```
<br><img src="../images/ncoFixedDutyCycleFlowchart.png">

## Setup
The AVR16EB32 Curiosity Nano Development Board is used as a test platform.
<br><img src="../images/AVR16EB32_Cnano_Board.png">

## Operation

 1. Connect the board to the PC.

 2. Open the  **TCF_NCO_Fixed_Duty_Cycle.X** solution in MPLAB<sup>®</sup> X IDE.

 3. Right click the project and select **Set as main project**.

<br><img src="../images/setAsMain.png">

 4. Build the  **TCF_NCO_Fixed_Duty_Cycle.X**  project: click on **Clean and Build Project**.

<br><img src="../images/cleanAndBuild.png">

 5. Program the project to the board, click Make and Program Device.

<br><img src="../images/flashProject.png">


## Results

The logic analyzer capture below shows hot the TCF generates a waveform signal in NCO Fixed Duty Cycle (FDC) mode.


<br>Result 1: generates two idential signals with a frequency of 10 Hz and duty cycle of 50%.
<br><img src="../images/10Hz.png">

<br>Result 2: generates two idential signals with a frequency of 100 Hz and duty cycle of 50%.
<br><img src="../images/100Hz.png">

<br>Result 3: TCF generates two idential signals with a frequency of 1 kHz and duty cycle of 50%.
<br><img src="../images/1KHz.png">

<br>Result 4: generates two idential signals with a frequency of 10 kHz and duty cycle of 50%.
<br><img src="../images/10KHz.png">

<br>Result 5: generates two idential signals with a frequency of 100 kHz and duty cycle of 50%.
<br><img src="../images/100KHz.png">



## Summary

This example shows how to create a project in bare-metal using the TCF peripheral of AVR16EB32. The TCF was configured to generate two PWM output signals on the default TCF output pins. The PWM sequence changes the frequency from 10 Hz to 100 KHz with one magnitude step maintaining 50% duty cycle. The measured output confirms the expected result.
