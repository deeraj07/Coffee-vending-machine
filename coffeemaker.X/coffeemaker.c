#include <xc.h>
#include<string.h>
#include<stdio.h>
// CONFIG
#define _XTAL_FREQ 1000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)


#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2

#define heat PORTEbits.RE0

#define R1 RB4
#define R2 RB5
#define R3 RB6
#define R4 RB7
#define C1 RB2
#define C2 RB1
#define C3 RB0

#define coffee RA0
#define tea RA1
#define milk RA2
#define directmilk RD3
#define mix RA3
#define in1 RA5
#define co RD4
#define te RD5
#define mi RD6


void store(unsigned char data)
{
    PORTC=data;
    RS=1;
    RW=0;
    EN=1;
    EN=0;   
}

 

void instruct(unsigned char inst)
{
    PORTC=inst;
    RS=0;
    RW=0;
    EN=1;
    EN=0;
}

 

void strin (char *stri,int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        store(stri[i]);
    }
}

 

void init()
{
    instruct(0x38);
    instruct(0x06);
    instruct(0x0C);
    instruct(0x01);
}
void making(char t)
{
    unsigned int i;
    unsigned int j;
    if(t =='1')
   {    
        co = 1;
        for(i=0;i<50;i++)
        {
           coffee = 1;
          __delay_us(800); // pulse of 800us
           coffee = 0;
          __delay_us(19200);
        }
        __delay_ms(2000);
        for(j=0;j<50;j++)
        {
           coffee = 1;
           __delay_us(1500); // pulse of 2200us
           coffee = 0;
           __delay_us(18500);
        }
        for(i=0;i<50;i++)
        {
           milk = 1;
          __delay_us(800); // pulse of 800us
           milk = 0;
          __delay_us(19200);
        }
        __delay_ms(3000);
        for(j=0;j<50;j++)
        {
           milk = 1;
           __delay_us(1500); // pulse of 2200us
           milk = 0;
           __delay_us(18500);
        }
        in1=1;
        __delay_ms(2000);
        in1 =0;
        for(i=0;i<50;i++)
        {
          mix = 1;
          __delay_us(800); // pulse of 800us
          mix = 0;
          __delay_us(19200);
        }
        __delay_ms(5000);
        for(j=0;j<50;j++)
        {
           mix = 1;
           __delay_us(1500); // pulse of 2200us
           mix = 0;
           __delay_us(18500);
        }
        co = 0;
        
        
   }
   else if(t =='2')
   {
       te = 1;
        for(i=0;i<50;i++)
        {
           tea = 1;
          __delay_us(800); // pulse of 800us
           tea = 0;
          __delay_us(19200);
        }
        __delay_ms(5000);
        for(j=0;j<50;j++)
        {
           tea = 1;
           __delay_us(1500); // pulse of 2200us
           tea = 0;
           __delay_us(18500);
        }
        te=0;
        
   }
   else if(t =='3')
   { 
       mi=1;
        for(i=0;i<50;i++)
        {
           directmilk = 1;
          __delay_us(800); // pulse of 800us
          directmilk = 0;
          __delay_us(19200);
        }
        __delay_ms(5000);
        for(j=0;j<50;j++)
        {
           directmilk = 1;
           __delay_us(1500); // pulse of 2200us
           directmilk = 0;
           __delay_us(18500);
        }
        
        mi=0;
                
   }

}
 

char  keypad()
{
    while(1)
    {
      C1=1;C2=0;C3=0;
      if (R1==1)
       {
         store('1');
         while(R1==1);
         return '1';
       }
      if (R2==1)
       {
         store('4');
         while(R2==1);
         return '4';
       }
      if (R3==1)
       {
         store('7');
         while(R3==1);
         return '7';
       }
       if (R4==1)
       {
         store('*');
         while(R4==1);
         return '*';
       }
       C1=0;C2=1;C3=0;
       if (R1==1)
       {
         store('2');
         while(R1==1);
         return '2';
       }
       if (R2==1)
       {
         store('5');
         while(R2==1);
         return '5';
       }
       if (R3==1)
       {
         store('8');
         while(R3==1);
         return '8';
       }
       if (R4==1)
       {
         store('0');
         while(R4==1);
         return '0';
       }
       C1=0;C2=0;C3=1;
       if (R1==1)
       {
         store('3');
         while(R1==1);
         return '3';
       }
       if (R2==1)
       {
         store('6');
         while(R2==1);
         return '6';
       }
       if (R3==1)
       {
         store('9');
         while(R3==1);
         return '9';
       }
       if (R4==1)
       {
         store('#');
         while(R4==1);
         return '#';
       }
    }
}
int compare(char str1[],char str2[],int len)
{
    for (int i=0;i<len;i++)
    {
        if(str1[i]!=str2[i])
        {
            return 1;
        }
    }
    return 0;
}
char middle(char str)
{
    char k;
    char x[1];
        k = keypad();
        if(k =='1')
        {
            instruct(0x01);
            instruct(0x80);
            strin(" PLEASE WAIT...",15);
            instruct(0xC0);
            strin("FOR YOUR COFFEE",16);
            making(k);                                                     
            instruct(0x01);
            instruct(0x80);
            strin(" want to save ?",15);
            instruct(0xC0);
            strin("1:YES 2:NO :",12);
            x[0] = keypad();
            int d = compare(x,"1",1);
            if( d == 0)
            {
                str = '1';
                           
            }

        }
        else if(k =='2')
        {
            instruct(0x01);
            instruct(0x80);
            strin(" PLEASE WAIT...",15);
            instruct(0xC0);
            strin("FOR YOUR TEA",12);
            making(k);
            instruct(0x01);
            instruct(0x80);
            strin(" want to save ?",15);
            instruct(0xC0);
            strin("1:YES 2:NO :",12);
            x[0] = keypad();
            int d = compare(x,"1",1);
            if( d == 0)
            {
                str = '2';                  
            }
                           
        } 
        else if(k =='3')
        {
            instruct(0x01);
            instruct(0x80);
            strin(" PLEASE WAIT...",15);
            instruct(0xC0);
            strin("FOR YOUR MILK",13);
            making(k);
            instruct(0x01);
            instruct(0x80);
            strin(" want to save ?",15);
            instruct(0xC0);
            strin("1:YES 2:NO :",12);
            x[0] = keypad();
            int d = compare(x,"1",1);
            if( d == 0)
            {
                str = '3';    
            }
        } 
    
    return str;
}

void main(void)
{ 
    
    TRISC=0x00;
    TRISD=0x00;
    TRISB=0xF0;
    TRISA=0x00;
    TRISE=0x00;
    heat=0;
    init();
    coffee=0;
    co =0;
    tea=0;
    te =0;
    milk =0;
    directmilk =1;
    mix=0;
    in1=0;
    mi =0;
    char arr[8][10]={"deeraj","naveen","shreyas","vishwas","yashwanth","sam","venkat","teja"};
    char arr2[8][5]={" 1234"," 5678"," 1028"," 7923"," 5210"," 2964"," 5791"," 0024"};
    char arr3[8][1]={"0","0","0","0","0","0","0","0"};
    instruct(0x80);
    strin(" WELCOME",8);
    __delay_ms(1000);
    while(1)
    {
        instruct(0x01);
        strin(" ENTER ID :",11);
        __delay_ms(10);
        int i;
        i=1;
        char  pass[]="     ";
        char k;
        while(i<5)
        {
            k=keypad();
            pass[i]=k;
            i=i+1;
        }
        heat=1;
        instruct(0x01);   
        //0-no choice made
        //1-coffee
        //2-tea
        //3-milk
        int var;
        int count;
        count=1;
        char x[1];
        int flag=0;
        for (int j = 0;j<7;j++)
        {
            int value = compare(arr2[j],pass,5);
            if( value == 0 )
            {
                var = j;
                flag=1;
                instruct(0x80);
                strin(" HI ",4);
                instruct(0xC0);
                strin(arr[j],9); 
                __delay_ms(1000);
                //display choices
                instruct(0x01);
            }
            
        }
          
        if(flag==0)
        {
            instruct(0x80);
            strin(" WRONG ID!!",11);
            __delay_ms(1000);              
        }
        else
        { 
            int f = compare(arr3[var],"0",1); 
            instruct(0x01);
            if(f == 0)
            {
                instruct(0x80);
                strin(" 1:COFFEE 2:TEA",15);
                instruct(0xC0);
                strin(" 3:MILK :",9);
                arr3[var][0]= middle(arr3[var][0]); 
            }    
            else
            {
                instruct(0x01);
                instruct(0x80);
                strin(" 1:regular ",11);
                instruct(0xC0);
                strin(" 2.new : ",9);
                k = keypad();
                if (k == '1')
                {
                    instruct(0x01);
                    instruct(0x80);
                    strin(" PREPARING YOUR",15);
                    instruct(0xC0);
                    strin("REGULAR ORDER",13);
                    making(arr3[var][0]);
                    
                }
                else if(k =='2')
                {
                    instruct(0x01);
                    instruct(0x80);
                    strin(" 1:COFFEE 2:TEA",15);
                    instruct(0xC0);
                    strin(" 3:MILK :",9);
                    arr3[var][0]= middle(arr3[var][0]); 
                }
                
            }
        }   
    instruct(0x01);
    instruct(0x80);
    strin(" THANK YOU!!",12);
    __delay_ms(1000);
    instruct(0x01);
    heat=0;
    }
}