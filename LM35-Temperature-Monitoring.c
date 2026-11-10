#include <reg51.h>
#define ADC_DATA P3
#define LCD_DATA P2

sbit rs =P0^0;
sbit rw=P0^1;
sbit en=P0^2;

sbit CS=P1^0;
sbit wr=P1^1;
sbit rd=P1^2;
sbit INTR=P1^3;

void init_LCD(void);
void LCD_command(unsigned char cmd);
void LCD_data(unsigned char val);
void LCD_write_string(char *str);
void msdelay(unsigned int time);



void main() {

char msg1[] = "LM35 Temp Sensor";
char msg2[] = "Temperature:";
char msg3[] = {0xDF, 0x43, 0x00};

unsigned char i, Tens, Ones;
unsigned char adc_val;
float temperature;
unsigned char int_part;
unsigned char dec_part;

ADC_DATA=0xFF;

CS = 0;
WR = 0;
RD = 1;

init_LCD();
LCD_write_string(msg1);
LCD_command(0xC0);
LCD_write_string(msg2);

while(1)
{

CS = 0 ;
WR = 0;
msdelay(1);
WR = 1;
while (INTR==1);

RD=0;
adc_val=ADC_DATA;
RD=1;
temperature=((float)adc_val/255.0)*500.0;
int_part=(int)temperature;
dec_part=(int)((temperature - int_part) * 10);
LCD_command(0xCC);

i=(adc_val% 100)/10;
Tens=i+0x30;
LCD_data(Tens);

i=(adc_val % 100) % 10;
Ones=i+0x30;
LCD_data(Ones);
msdelay(300);
}
}

void msdelay(unsigned int time) {

unsigned int i, j;

for (i=0; i<time; i++)

for(j=0; j<113; j++);
}


void init_LCD(void)

{

LCD_command(0x38);
msdelay(15);
LCD_command(0x01);
msdelay(15);
LCD_command(0x0C);
msdelay(15);
LCD_command(0x80);
msdelay(15);
}

void LCD_command(unsigned char cmd) {
LCD_DATA=cmd;
rs = 0;
rw = 0;
en = 1;
msdelay(15);
en = 0;
 }

void LCD_data(unsigned char val)

{

LCD_DATA=val;

rs=1;
rw = 0;
en=1;
msdelay(15);
en = 0;
}
void LCD_write_string(char *str) {
int i=0;
while (str[i] != 0) {
LCD_data(str[i]);
msdelay(15);
i++;
}
}
