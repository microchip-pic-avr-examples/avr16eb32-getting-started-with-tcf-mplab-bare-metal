[![MCHP](../images/microchip.png)](https://www.microchip.com)

## Use case 2: Generate Two Two Constant On-Time PWM Signals in NCO-Pulse Length Mode using the TCF

Below is an example of how to set TCF to generate Two Constant On-Time PWM Signals.
The On-Time is always constant even if the frequency is changed.

## Related Documentation
More details and code examples on the AVR16EB32 can be found at the following links:
- [TBxxxx - Getting Started with Timer/Counter Type F (TCF)](insert url link here)
- [AVR16EB32 Product Page](insert url link here)
- [AVR16EB32 Code Examples on GitHub](insert url link here)

## Software Used
- [MPLAB X IDE v6.15 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [AVR-Ex DFP-2.5.184 or newer Device Pack](insert url link here)

## Hardware Used
- AVR16EB32 Cnano [(AVR16EB32)](insert url link here)(insert url link here)


## Functionality
<br>After we initialize the peripheral clock and the TCF, we call in an infinite loop the NCO_Pulse_Length_Demo function.

The purpose of this function is to change the pulse length of the waveform which  the timer outputs on the pin. We first start the timer  with a pulse length of 2 clock-cycles and then run up to the maximum of 128 clock-cycles. 

At the end we stop the timer and reset the pulse length to default.

```
void NCO_Pulse_Length_Demo(void)
{
   TCF0_Start(); 
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK2_gc);
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK4_gc);
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK8_gc);
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK16_gc);
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK32_gc);
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK64_gc);
   _delay_us(20);
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK128_gc);
   _delay_us(18);
   TCF0_Stop();
   TCF0_NCO_PulseLengthSet(TCF_WGPULSE_CLK1_gc);
}

```
<br><img src="../images/ncoPlFlowchart.png">

## Setup
The AVR16EB32 Cnano Development Board is used as test platform.
<br><img src="../images/AVR16EB32_Cnano_Board.png">

## Operation
 1. Connect the board to the PC.

 2. Open the  **TCF_NCO_Fixed_Duty_Cycle.X** solution in MPLAB X IDE.

 3. Right click on the project and select **Set as main project**.

<br><img src="../images/setAsMain.png">

 4. Build the  **TCF_NCO_Fixed_Duty_Cycle.X**  project: click on **Clean and Build Project**.

<br><img src="../images/cleanAndBuild.png">

 5. Program the project to the board: click on **Make and Program Device**.

<br><img src="../images/flashProject.png">


## Results

Below is illustrated a logic analyzer capture, to help understanding a little bit better how the TCF generates a waveform signal in NCO Pulse-Length mode.

<br>Result: TCF is used to generate two output signals with a frequnecy of 125 kHz and pulse-wdth-modulated with a variable duration ranging from 1 clock-cycle up to 128 clock-cycles.
In this case one clock-cycle takes 50 ns.
<br><img src="../images/ncoPlResult.png">


## Summary

This example depicted how to create a project in bare-metal using the TCF peripheral of ARVR16EB32. The TCF was configured to generate two PWM output signals on the default TCF output pins. The pulse length varies between 1 clock-cycle and 128 clock-cylces.The measured output confirms the expected result.