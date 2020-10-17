/*P1.1:Caminata 4 bits
  Martín Ricardo Del Río Grageda 15300067
  Lázaro Fabricio Torres Orozco 15300277
  */
 #INCLUDE <16F886.H>
 #DEVICE ADC=8
 #USE DELAY(CLOCK=4000000)
 #FUSES INTRC_IO,NOWDT,NOPUT,NOMCLR,NOPROTECT,NOCPD,NOBROWNOUT
 #FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21
 #BYTE PORTA=0X05
 #BYTE TRISA=0X85
 #BYTE PORTB=0X06
 #BYTE TRISB=0X86
 int x=0;
 int16 ana=0;
 float y=0.0;
void main(void)
{
 while(true)
 {
 TRISB=0X00;
 TRISA=0XFF;
 SETUP_ADC(ADC_CLOCK_INTERNAL);
 SET_ADC_CHANNEL(0);
 SETUP_ADC_PORTS(sAN0);
 y=READ_ADC();
 Ana=((y+10)*20);
 PORTB=0b1000;
 delay_ms(Ana);
 x=0;
 for(x=1;x<=3;++x)
   {
   PORTB=PORTB>>1;
   y=READ_ADC();
   Ana=((y+10)*20);
   delay_ms(Ana);
   }
 for(x=1;x<3;++x)
   {
   PORTB=PORTB<<1;
   y=READ_ADC();
   Ana=((y+10)*20);
   delay_ms(Ana);
   }
 }
}
