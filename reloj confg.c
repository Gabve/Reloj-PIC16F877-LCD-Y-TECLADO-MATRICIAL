#include <16F877.h>
#FUSES HS,NOWDT
#USE DELAY (CLOCK = 20M)
#DEFINE LCD_DATAPORT GETENV("SFR:PORTC")
#DEFINE LCD_ENABLE_PIN PIN_D0
#DEFINE LCD_RS_PIN PIN_D1
#DEFINE LCD_RW_PIN PIN_D2
#DEFINE USE_PORTB_KBD TRUE
#INCLUDE <LCD.C>
#INCLUDE <kbd4X4_1.C>
#use standard_io(a)
#include <stdlib.h>

void main (){
int i=0;
char k='0';
lcd_init();
printf(LCD_PUTC,"\f");
int hi=1,hd=2,md,mi,sd,si,T=0;
int d=1,m=1,s=6,hl=0;
int16 a=2000;
char ss[10],h[3];
h="AM ";
int febrero;
int total_m;

while (1){

kbd_init();
port_b_pullups(true);
k=kbd_getc();

//configuración
if(k=='C')
{
k='0';
while((k!='A')||(k!='B'))
      {  
         printf(LCD_PUTC,"\f");
         printf(LCD_PUTC,"1.hora 2.fecha");
      if(k=='1')
         {
         while((k!='A')||(k!='B')){
         printf(LCD_PUTC,"\f");
         printf(LCD_PUTC,"/.ok *.atras");
         lcd_gotoxy(1,2);
         printf(LCD_PUTC,"%d%d:%d%d:%d%d ",hi,hd,mi,md,si,sd);
         if(((k=='0')||(k=='1')||(k=='2')||(k=='3')||(k=='4')||(k=='5')||(k=='6')||(k=='7')||(k=='8')||(k=='9')||(k=='*')||(k=='#')))
            {
            switch(i)
            {
               case 0:
               hi=(k-48);
               break;
               case 1:
               hd=(k-48);
               break;
               case 2:
               mi=(k-48);
               break;
               case 3:
               md=(k-48);
               break;
               case 4:
               si=(k-48);
               break;
               case 5:
               sd=(k-48);
               break;
            }
            i++;
            }
         }
        }
}}

//conteo
if ((a%4==0) && (a%100!=0) || (a%400==0))
febrero=29;
else
febrero=28;


switch (m)
{
case 4: case 6: case 9: case 11: 
total_m=30; 
break; 
case 2: 
total_m=febrero; 
break; 
case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
total_m=31; 
break; 
}

      switch (s)
         {
case 0:(ss="DOMIN.");break;
case 1:(ss="LUNES ");break;
case 2:(ss="MARTES");break;
case 3:(ss="MIERC.");break;
case 4:(ss="JUEVES");break;
case 5:(ss="VIERN.");break;
case 6:(ss="SABADO");break;


s=((a-1)%7+((a-1)/4-(3*((a-1)/100+1)/4))%7+m+d%7)%7;
      }
      
lcd_gotoxy(1,1);
printf(LCD_PUTC," %d%d:%d%d:%d%d",hi,hd,mi,md,si,sd);
printf(LCD_PUTC,&h);

lcd_gotoxy(1,2);
printf(LCD_PUTC,&ss);
printf(LCD_PUTC,"%d/%d/%ld",d,m,a); 

delay_ms(1000);

sd++;
if(sd==10){si++;sd=0;}
if(si==7){si=0;md++;}
if(md==10){md=0;mi++;}
if(mi==6)
   {hd++;
   mi=0;}
if(hd==10)
   {
   hd=0;hi=1;
   }
if((hd==3)&&(hi==1)){hd=1;hi=0;}
if((hd==2)&&(hi==1)&&(T!=0))
{  T=0;
if(hl==1)
   { 
   h="AM ";d++;s++;hl=0;}
   else
   {h="PM ";hl=1;}
}
if(d==total_m+1){m++;d=1;}
if(m==13){m=1;a++;}
if(s==7){s=0;}
if(hd!=2){T=1;}
//conteo
}}
