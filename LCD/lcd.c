//James Andrews

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int eh();//E -> High
int el();//E -> Low
int init();
int display(unsigned char data);

int main(){
	DDRD = 0xFF;//data byte
	DDRC = 0xFF;

	init();//setup display
	display(0b01010010);//send J to LCD
}

int init(){
	PORTC = 0x00;//RS = 0;
	eh();
	PORTD = 0x38;
	el();
	eh();
	PORTD = 0x0E;
	el();
	eh();
	PORTD = 0x01;
	el();
	eh();
	PORTD = 0x02;//clear display
	el();
}

int display( unsigned char data ){
	PORTC = 0x00;	 //RS=0, E=0
	PORTC &= ~(1<<1);//RS=1
	eh();
	PORTD = data;
	_delay_ms(2);
	PORTC = 0x00;
}

int eh(){//set E High
	PORTC &= ~(1<<0);
	_delay_ms(2);
}

int el(){//set E Low
	PORTC |= (1<<0);
	_delay_ms(2);
}
