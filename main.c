#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

//Define display pins to be used for the LCD 
#define lcdBitD7	(1 << 0)		//D7 connected to PD0
#define lcdBitD6	(1 << 1)		//D6 connected to PD1
#define lcdBitD5	(1 << 2)		//D5 connected to PD2
#define lcdBitD4	(1 << 3)		//D4 connected to PD3
#define lcdBitD3	(1 << 4)		//D3 connected to PD4
#define lcdBitD2	(1 << 5)		//D2 connected to PD5
#define lcdBitD1	(1 << 6)		//D1 connected to PD6
#define lcdBitD0	(1 << 7)		//D0 connected to PD7

//Define Enable and RS pins of LCD
#define lcdBitE         (1 << 0)		//E  connected to PB0
#define lcdBitRS        (1 << 1)		//RS connected to PB1

// LCD instructions (from the book)
#define clearDisplay	0x01    //Clear display screen
#define returnHome	0x02    //Return home
#define displayOff	0x08    //Turn off display
#define displayOn	0x0C    //Turn on display, cursor off
#define setLCD		0x38    //2 lines and 5 x 7 matrix (8 bit)
#define firstLine	0x80	//Force cursor to the start of first line
#define secondLine	0xC0	//Force cursor to the start of second line

// Function Prototypes
void initialize();
void writeCharacter(uint8_t);
void writeString(uint8_t *);
void writeInstruction(uint8_t);
void sendCommand(uint8_t);

unsigned int increaseFrequency(unsigned int);
void lcdWriteFrequency(unsigned int freq);
void lcdSendPulse();

unsigned int frequency = 100;

int main(){
	//Define Port D as output
	DDRD = 0xFF;

	//Define Enable and RS bits as high (output)
	DDRB |= (lcdBitE); 
	DDRB |= (lcdBitRS);

	DDRC &= ~(0b00110000);		//Set PC4, PC5 as input
	
	//Initialize LCD display
	initialize();                    
	
	uint8_t freq[] = "Frequency:100";
	uint8_t send[] = "Ready to send...";             

	//Display name
	writeString(freq);
	writeInstruction(secondLine);
	_delay_us(80);                                  
	writeString(send);
	
	uint8_t prevState = 0;
	
	while(1){
		if((PINC & (1 << 5)) != 0){
			lcdSendPulse();
		}else{
			writeInstruction(secondLine);
			_delay_us(80);
			writeString(send);
		}
		
		if((PINC & (1 << 4)) != 0 && prevState == 0){
			frequency = increaseFrequency(frequency);
			lcdWriteFrequency(frequency);
		}
		
		prevState = (PINC & (1 << 4));
	}
	return 0;
}

//(From the book) to initialize send 0x38, 0x0C, 0x01.
void initialize(){
	//15 ms power up delay
	_delay_ms(15);                                 

	// Function Set instruction
	writeInstruction(setLCD);  
	_delay_us(80);                                 

	//Turn on display
	writeInstruction(displayOn);       
	_delay_us(80);                                  

	// Clear display 
	writeInstruction(clearDisplay);            
	_delay_ms(2);                                   
}

void writeCharacter(uint8_t c){
	//To send data, data register must be high, enable must be low
	PORTB |= (lcdBitRS);
	PORTB &= ~(lcdBitE);
	sendCommand(c);
}

void writeString(uint8_t str[]){
	for(int i = 0; str[i] != 0; i++){
		writeCharacter(str[i]);
		_delay_us(80);
	}
}

void writeInstruction(uint8_t instr){
	//To send instruction, data register must be low, enable must be low
	PORTB &= ~(lcdBitRS);                
	PORTB &= ~(lcdBitE);                  
	sendCommand(instr);                    
}

void sendCommand(uint8_t cmd){
	//Set all values of Port D to zero
	PORTD = 0;		
	
	//Check the command values that are sent
	if (cmd & 1<<7)
		PORTD |= (lcdBitD7);    
	if (cmd & 1<<6)
		PORTD |= (lcdBitD6);
	if (cmd & 1<<5)
		PORTD |= (lcdBitD5);
	if (cmd & 1<<4)
		PORTD |= (lcdBitD4);
	if (cmd & 1<<3)
		PORTD |= (lcdBitD3);
	if (cmd & 1<<2)
		PORTD |= (lcdBitD2);
	if (cmd & 1<<1)
		PORTD |= (lcdBitD1);
	if (cmd & 1<<0)
		PORTD |= (lcdBitD0);

	//Send pulse to Enable pin
	PORTB |= (lcdBitE);                   
	_delay_us(1);                           
	PORTB &= ~(lcdBitE);                 
	_delay_us(1);                        
}

unsigned int increaseFrequency(unsigned int frequency){
	const uint8_t freqChange = 50;	//Change between 50
	
	if(frequency >= 300)
		frequency = 0;
	else
		frequency += freqChange;
		
	return frequency;
}

void lcdWriteFrequency(unsigned int freq){
	unsigned char str[3];
	
	for(uint8_t i = 0; i < 3; i++){
		str[i] = freq % 10 + '0';
		freq /= 10;
	}
	
	writeInstruction(0x8A);
	_delay_us(80);
	writeCharacter(str[2]);
	_delay_us(80);
	writeCharacter(str[1]);
	_delay_us(80);
	writeCharacter(str[0]);
	_delay_us(80);
}

void lcdSendPulse(){
	uint8_t str[] = "Sending Pulse...";
	
	writeInstruction(secondLine);
	_delay_us(80);
	writeString(str);
	_delay_us(80);
}
