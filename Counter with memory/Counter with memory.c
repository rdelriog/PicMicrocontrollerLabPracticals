/*CETI COLOMOS                                        
TGO EN CONTROL AUTOMÁTICO E INSTRUMENTACIÓN         
Práctica 2.2: Contador con eeprom                      
Martín Ricardo Del Río Grageda 15300067             
Lázaro Fabricio Torres Orozco 15300277              
07/MARZO/2019*/

#INCLUDE <16F886.H>                                            
#USE DELAY(CLOCK=4000000)                                      
#INCLUDE <LCD1.C>                                              
#FUSES INTRC_IO,NOWDT,NOPUT,MCLR,NOPROTECT,NOCPD,NOBROWNOUT 
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21              
#BYTE TRISA = 0X85            
#BYTE PORTA = 0X05      
#BYTE TRISB = 0X86        
#BYTE PORTB = 0X06         
#BYTE TRISC = 0X87              
#BYTE PORTC = 0X07
INT CUENTA_TECLADO,CUENTA_BARRIDO,BARRIDO,TECLA,DECENAS,UNIDADES,I,T=0;
INT TECLADO();
INT ARRAY_TECLA[16]={1,2,3,16,4,5,6,16,7,8,9,16,10,0,11,16};
INT16 TIEMPO[4]={200,500,1000,2000};

VOID MAIN(VOID)
{
   TRISA=0XFF;
   TRISB=0X00;
   TRISC=0X0F;
   
   LCD_INIT();
   
   IF(READ_EEPROM(0X02)!=101)
   {
     FOR(I=(READ_EEPROM(0X02)); I<=(READ_EEPROM(0X00)); I++)
      {
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"CONTAR HASTA: %U%U\nCUENTA:       %U",DECENAS,UNIDADES,I);
         IF(BIT_TEST(PORTA,0)==1)
         {
            WRITE_EEPROM(0X02,I);
         }
         DELAY_MS(TIEMPO[READ_EEPROM(0X01)]); 
      }
   }ELSE{
      
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"CETI             \nTgo Control     ");
      delay_ms(500);
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"LAZARO TORRES    \nREG 15300277    ");
      delay_ms(500);
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"RICARDO DEL RIO  \nREG 15300067    ");
      delay_ms(500);
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"PRACTICA 2.2     \nCONTADOR EEPROM ");
      
      TECLA=0;
      WHILE(TECLA!=10)
         TECLADO();
   }
   
   WHILE(TRUE)
   {
      WRITE_EEPROM(0X02,101);
      
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"CONTADOR 0 A 99 \n       00       ");
      
      TECLA=0;
      WHILE(TECLA!=10)
      {
         TECLADO();
         
         IF(TECLA!=10&&TECLA!=11)
         {
            DECENAS=TECLA;
            LCD_GOTOXY(8,2);
            PRINTF(LCD_PUTC,"%U",DECENAS);
         }
      }
      
      TECLA=0;
      WHILE(TECLA!=10)
      {
         TECLADO();
         
         IF(TECLA!=10&&TECLA!=11)
         {
            UNIDADES=TECLA;
            LCD_GOTOXY(9,2);
            PRINTF(LCD_PUTC,"%U",UNIDADES);
         }
      }
      
      WRITE_EEPROM(0X00,(DECENAS*10+UNIDADES));
      
      TECLA=0;
      WHILE(TECLA!=10)
      {
         TECLADO();
         
         IF(TECLA==1)
            T=0;
         IF(TECLA==2)
            T=1;
         IF(TECLA==3)
            T=2;
         IF(TECLA==4)
            T=3;
         
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"TIEMPO(MS): %LU  \n0.2S 0.5S 1S 2S",TIEMPO[T]);
      }
      
      WRITE_EEPROM(0X01,T);
      
      FOR(I=0; I<=(DECENAS*10+UNIDADES); I++)
      {
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"CONTAR HASTA: %U%U\nCUENTA:       %U",DECENAS,UNIDADES,I);
         IF(BIT_TEST(PORTA,0)==1)
         {
            WRITE_EEPROM(0X02,I);
         }
         DELAY_MS(TIEMPO[T]);  
      }
   }

}

INT TECLADO()
{
   CUENTA_TECLADO=0;
   BARRIDO=0B11110111;
   
   FOR(CUENTA_BARRIDO=0; CUENTA_BARRIDO<=3; CUENTA_BARRIDO++)
   {
      BARRIDO=BARRIDO<<1;
      PORTC=((PORTC&0X0F)|(BARRIDO&0XF0));
      DELAY_MS(20);
      
      IF(BIT_TEST(PORTC,0)==0)
      {
         WHILE(BIT_TEST(PORTC,0)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
      IF(BIT_TEST(PORTC,1)==0)
      {
         WHILE(BIT_TEST(PORTC,1)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
      IF(BIT_TEST(PORTC,2)==0)
      {
         WHILE(BIT_TEST(PORTC,2)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
      IF(BIT_TEST(PORTC,3)==0)
      {
         WHILE(BIT_TEST(PORTC,3)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
   }
   IF(CUENTA_TECLADO!=3&&CUENTA_TECLADO!=7&&CUENTA_TECLADO!=11&&CUENTA_TECLADO!=15&&CUENTA_TECLADO!=16)
   {
      TECLA=ARRAY_TECLA[CUENTA_TECLADO];
   }
   RETURN(TECLA);
}

