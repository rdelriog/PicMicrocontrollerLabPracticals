  /*
  CETI COLOMOS                                        EN EL TECLADO MATRICIAL LAS NEGRAS SON FILAS Y SÍ VAN EN ORDEN
  TGO EN CONTROL AUTOMÁTICO E INSTRUMENTACIÓN         DEL PIC, EL BARRIDO VA A LAS FILAS DESPUÉS DE PASAR POR RESISTENCIAS DE 
  Práctica 1.3:Teclado matricial                      1 K.
  Martín Ricardo Del Río Grageda 15300067             LO QUE LEE EL PIC VA ENTRE UNA RESISTENCIA Y TIERRA, EL OTRO EXTREMO DE LA 
  Lázaro Fabricio Torres Orozco 15300277              RESISTENCIA VA A VOLTAJE.
  04/MARZO/2019
  */
 #INCLUDE <16F886.H>
 #USE DELAY(CLOCK=4000000)
 #INCLUDE <LCD1.C>
 #FUSES INTRC_IO,NOWDT,NOPUT,NOMCLR,NOPROTECT,NOCPD,NOBROWNOUT
 #FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21
 #BYTE TRISA=0X85
 #BYTE PORTA=0X05
 #BYTE TRISB=0X86
 #BYTE PORTB=0X06
 #BYTE TRISC=0X87
 #BYTE PORTC=0X07
 
void main(void)
{
 int x=0;
 signed int i;
 int Tecla_presionada;
 char Tecla[16]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
 LCD_INIT();
 TRISA=0xFF;
 TRISB=0X00;
 TRISC=0X00;
LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"CETI            \nTgo Control     ");
       delay_ms(1000);
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"LAZARO TORRES          \nREG.15300277     ");
       delay_ms(1000);
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"RICARDO DEL RIO      \nREG.15300067");
       delay_ms(1000);
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"PRACTICA 1.3      \nTECLADO MAT");
       delay_ms(1000);
 while(1)
 {
   PORTC=0XEF;
   x=255;
   for(i=0; i<=4; i++)
   {
      IF(BIT_TEST(PORTA,0)==0)
      {
         x=0;
         break;
      }
      IF(BIT_TEST(PORTA,1)==0)
      {
         x=1;
         break;
      }
      IF(BIT_TEST(PORTA,2)==0)
      {
         x=2;
         break;
      }
      IF(BIT_TEST(PORTA,3)==0)
      {
         x=3;
         break;
      }
      delay_ms(20);
      PORTC=PORTC>>1;
   }
   Tecla_presionada=(4*(i-1)+x);
   LCD_GOTOXY(1,1);
   if(x==255)
   {
   PRINTF(LCD_PUTC,"TECLA =         \nCONTADOR =       ");
   }else
   {
   PRINTF(LCD_PUTC,"TECLA = %C      \nCONTADOR = %U    ",Tecla[Tecla_presionada],Tecla_presionada);
   }
 }
}
