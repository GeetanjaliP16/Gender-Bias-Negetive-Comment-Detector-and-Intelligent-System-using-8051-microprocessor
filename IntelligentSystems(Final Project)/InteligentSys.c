//NOTE: if rs=0 command is send rs=1 data is sent
//RW=0(read/write) writes data to the led

#include<at89x52.h>
#define display_port P2 //Data pins connected to port 2 on microcontroller



//Declaring the 3 control lines for LCD interfacing. These are the main lines which control the LCD
sbit rs = P3^2;  //RS pin connected to pin 2 of port 3
sbit rw = P3^3;  // RW pin connected to pin 3 of port 3
sbit e =  P3^4;  //E pin connected to pin 4 of port 3
//sbit sensor=P1^0;//Connecting sensor to pin 0 of port 1
//sbit buzzer=P3^0;//Buzzer connected at pin0 port3

sbit load1=P1^0;//Connecting load to P1 first since it contains only IO lines(lecture 12/03/2021)
sbit load2=P1^1;
sbit load3=P1^2;
sbit load4=P1^3;
sbit light=P0^7;



void delay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<1275;j++);
}
void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD-> The basic commands like switching on led 
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    delay(1);
    e=0;
}

void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data; //Assigning data to Port 2 indirectly
	//prerequisities of these special lines to display data
    rs= 1;
    rw=0;
    e=1;
    delay(1);
    e=0;
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    delay(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    delay(10);
    lcd_cmd(0x01);  //clear screen
    delay(10);
    lcd_cmd(0x81);  // bring cursor to position 1 of line 1
    delay(10);
}
void main()
{

unsigned int commentType=1;

unsigned char x;
//Starting basic declaration 

SCON=0x50;//Used for serial data input 
TMOD=0x20;//timer
TH1=-3;//setting bod rate to 9600
TR1=1;//Starting time

//TO recieve characters from PC keyboard
while(1)
{
while(RI==0);//If RI is 0 stay here else go ahead. HERE WE ARE WAITING TO RECIEVE CHARACTER FROM KEYBOARD
//If RI is 1 data is ready on SBUF
//Once character recieved tranfering it from microcontroller to peripheral
x=SBUF;//Data recieved on SBUF is transfered to variable x
SBUF=x;//To see which character you recieved


while(TI==0);

TI=0;//clearing TI logic
RI=0;//To allow the next character to be inputed
//TO operate the loads

//Based on what character is recived we are doing the operations
if(x=='0')
{
load1=1;//load 1 off
}
if(x=='1')
{
load1=0;//load 1 on
}
if(x=='2')
{
load2=1;//load 2 off
}
if(x=='3')
{
load2=0;//load2 on
}
if(x=='4')
{
load3=1;//load3 off
}
if(x=='5')
{
load3=0;//load3 on
}
if(x=='6')
{
load4=1;//load 4 off
}
if(x=='7')
{
load4=0;//load 4 on
}

if(x=='8')//GENDER BIAS INDICATOR
{
if (commentType==1)
{
unsigned char a[100]="Sexist Comment";    //string of 14 characters with a null terminator.
int l=0;//used to iterate through the array of a which contains the strings to print
lcd_init();//Initializing the LCD and starting it
while(a[l] != '\0') // searching the null terminator in the sentence
{
lcd_data(a[l]);
l++;
delay(50);
}
light=0;
}

if (commentType=0)
{
unsigned char c[100]="Safe Comments";    //string of 14 characters with a null terminator.
int l=0;//used to iterate through the array of a which contains the strings to print
lcd_init();//Initializing the LCD and starting it
while(c[l] != '\0') // searching the null terminator in the sentence
{
lcd_data(c[l]);
l++;
delay(50);
}
}
}

if(x=='9')//GENDER BIAS INDICATOR
{
unsigned char d[100]="Comment Deleted";    //string of 14 characters with a null terminator.
int l=0;//used to iterate through the array of a which contains the strings to print
lcd_init();//Initializing the LCD and starting it
while(d[l] != '\0') // searching the null terminator in the sentence
{
lcd_data(d[l]);
l++;
delay(50);
}
}

}
//buzzer=1;
}