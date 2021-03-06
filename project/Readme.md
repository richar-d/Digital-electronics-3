<h1> Project DE-2 </h1>
Authors: Alexandr Voronin, Richard Šebo
<h2> Project objectives </h2>
<p>Application of parking assistant using two HC-SR04 sensors. Output interface:LCD, frequency audio, led stripe</p>
<h2> Hardware description </h3>
<h3> HC-SR04 </h3>
<p>HC-SR04 is a distance measuring sensor with range from 2cm to 4m. It has 4 pins:Vcc,Gnd, trigger, echo. To start its function it must first recieve pulse of at least 10us to the trigger pin. Sensor then transmits a sonic burst of eight pulses at 40 KHz. This pattern makes the signal unique, which allows it to differentiate between emited signal and ambient ultrasonic noise. The echo pin is set high and if the pulses are not reflected back it times out after 38ms  and is set to low (no obstacle in range). If the pulses are reflected, echo is set to low when the signal is recieved producing pulse with width between 150 µS to 25 mS based on how long it took the signal to come back. Based on that and knowing the speed of light we can calculate the distance between the sensor and object that reflected the original pulses. In our program we let the MCU itterate as fast as it can as long as echo is HIGH, and then convert to distance by multiplying precalculated constant</p>
<h3> Atmega328p </h3>
<p>Application was brought to life using Atmega328p, 8-bit microchip controller. It has 21 GPIO pins accessed through registers PORTB,PORTC,PORTD. We are using external interrupt pins (PD3,PD2) for echo signals and I/O pins (PB3,PB2) for sending trigger signal to the sensor. I/0 ports PC1-5 are used for the led stripe output. I/0 pin PB4 is used for output to led replacing audio signaling by blinking in different frequencies. Freqeuncies are generated based on different overflow times for internal timer overflow. For LCD pins PD4-7 are used for data ports, pin PB0 asi RS pin and port PB1 as E pin. </p>
 
<h2> Software description </h3>
<p>SimulIDE: Simple real time electronic circuit simulator, with acces to atmega328p</p>
<p>Atmel Studio: Integrated Development Environment (IDE) for developing and debugging AVR® and SAM microcontroller applications</p>


<h2> Code description </h2>
<h3> Flow chart</h3>

![logic](../Images/flowchart_parkings.png)

<h3> Function documentation </h3>

| **Function name** | **Function parameters** | **Description** |
| :-: | :-: | :-: | 
|  `lcd_config` | - | Creates and stores custom character for the loading bar, initializes LCD (display strings which do not change), sets pointer at the beginning of CGRAM and sets DDRAM adress  |
| `pins_config` | - | Configures and initializes LED, alarm, echo and trigger pins |
| `LEDs_off` | - | Sets all LED pins to logic low |
| `LED_toggle` | `int number_of_LEDs` | Toggle 1 up to 5 LEDs |
| `LoadBar` | `int distance` | Displays loading bar on LCD based on the smaller distance |
| `Display_dist` | `uint8_t id`, `volatile float dist[]`, `char string[]` | Displays front and back distance on LCD | 
| `Update_warning` | `int sm_dist` | Displays warning messages on LCD |
| `Uart_info` | `volatile float dist []` | Displays warning messages via UART |

| **Function name** | **Function parameters** | **Description** |
| :-- | :-- | :-- | 
| `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>&nbsp;<br>&nbsp;<br>&nbsp; |
| `lcd_clrscr` | - |Clear display and set cursor to home position. |
| `lcd_gotoxy` | `uint8_t x` <br> `uint8_t y`  |Set cursor to specified position. |
| `lcd_putc` | `char 	c` | Display character at current cursor position.|
| `lcd_puts` | `const char * 	s` | Display string without auto linefeed.|
| `lcd_command` | `uint8_t 	cmd` |Send LCD controller instruction command. |
| `lcd_data` | `uint8_t 	data` |Send data byte to LCD controller.Similar to lcd_putc(), but without interpreting LF |
| `uart_init` | `UART_BAUD_SELECT(9600, F_CPU)` | Initialize UART to 8N1 and set baudrate to 9600&nbsp;Bd |
| `uart_getc` | `none(void)`  |  Get received byte from ringbuffer &nbsp;Bd |
| `uart_putc` | `unsigned char data`  | Put byte to ringbuffer for transmitting via UART. |
| `uart_puts` | `const char* s` | Put string to ringbuffer for transmitting via UART. |
| `GPIO_config_output` | `volatile uint8_t *reg_name, uint8_t pin_num` | Configure one output pin in Data Direction Register |
| `GPIO_config_input_nopull` | `volatile uint8_t *reg_name, uint8_t pin_num` | Configure one input pin in DDR without pull-up resistor |
| `GPIO_config_input_pullup` | `volatile uint8_t *reg_name, uint8_t pin_num` | Configure one input pin in DDR and enable pull-up resistor |
| `GPIO_write_low` | `volatile uint8_t *reg_name, uint8_t pin_num` | Set one output pin in PORT register to low |
| `GPIO_write_high` | `volatile uint8_t *reg_name, uint8_t pin_num` | Set one output pin in PORT register to high |
| `GPIO_toggle` | `volatile uint8_t *reg_name, uint8_t pin_num` | Toggle one output pin value in PORT register |
| `GPIO_read` | `volatile uint8_t *reg_name, uint8_t pin_num` | Get input pin value from PIN register, returns `uint8_t
