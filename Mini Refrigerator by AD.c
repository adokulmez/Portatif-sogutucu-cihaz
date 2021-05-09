#include <16f877A.h>
#device ADC=10
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock=4000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)

signed int32 set_sicaklik=-1,tolerans_sicaklik;
float voltaj,sicaklik,bilgi,bilgi1,bilgi2;
int8 birler=0, onlar=0, ondabirler=0, sbirler=0, sonlar=0, sondabirler=0;

void main ()
{
   setup_psp(PSP_DISABLED);                   // PSP birimi devre dýþý
   setup_spi(SPI_SS_DISABLED);
   setup_timer_1(T1_DISABLED);                // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1);            // T2 zamanlayýcýsý devre dýþý
   setup_CCP1(CCP_OFF);                       // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);                       // CCP2 birimi devre dýþý

   set_tris_a(0xFF);                          // RA0 Giriþ olarak yönlendiriliyor
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   output_b(0x00);
   output_c(0x00); 
   output_d(0x00);
   
   setup_adc(adc_clock_div_32);               // ADC clock frekansý fosc/32
   setup_adc_ports(RA0_RA1_RA3_ANALOG);       //RA0/AN0 giriþi analogü
   

   
  
   char dizi[]={63,6,91,79,102,109,125,7,127,111};  
   
   while(True)
   {     
         set_adc_channel(0);                        // RA0/AN0 ucundaki sinyal A/D iþlemine tabi tutulacak
         delay_ms(2);                              // Kanal seçiminde sonra bu bekleme süresi verilmelidir
         bilgi1=read_adc();                         // ADC sonucu okunuyor ve bilgi deðiþkenine aktarýlýyor

         set_adc_channel(1);                        // RA0/AN0 ucundaki sinyal A/D iþlemine tabi tutulacak
         delay_ms(2);                              // Kanal seçiminde sonra bu bekleme süresi verilmelidir
         bilgi2=read_adc();                         // ADC sonucu okunuyor ve bilgi deðiþkenine aktarýlýyor
         
         bilgi=bilgi1-bilgi2;
         
         voltaj=(4.8828125*bilgi);
         sicaklik=(voltaj/10);               // Her 10mV'ta 1 derece artma 
         
         if(sicaklik<0)
         {
           sicaklik=sicaklik * -1;
           output_b(0x00);
           output_high(pin_B6);
           birler=(int)sicaklik%10;            // birler hanesi hesaplaniyor
           onlar=sicaklik/10;                  // onlar hanesi hesaplaniyor
           ondabirler=(int)(sicaklik*10)%10;
         
           sbirler=set_sicaklik%10;
           sonlar=set_sicaklik/10;
           sondabirler=(set_sicaklik*10)%10;

           output_c(dizi[birler]);        // displaye bilgi gönderiliyor
           output_d(dizi[ondabirler]);    // displaye bilgi gönderiliyor
           output_high(pin_C7);
           sicaklik=sicaklik * -1;
         }
         
        else
         {
         
         birler=(int)sicaklik%10;            // birler hanesi hesaplaniyor
         onlar=sicaklik/10;                  // onlar hanesi hesaplaniyor
         ondabirler=(int)(sicaklik*10)%10;
         

         sbirler=set_sicaklik%10;
         sonlar=set_sicaklik/10;
         sondabirler=(set_sicaklik*10)%10;

        
         output_b(dizi[onlar]);         // displaye bilgi gönderiliyor
         output_c(dizi[birler]);        // displaye bilgi gönderiliyor
         output_d(dizi[ondabirler]);    // displaye bilgi gönderiliyor
         output_high(pin_C7);
         }       
         delay_ms(20);                   // gecikme veriliyor
         
         tolerans_sicaklik=set_sicaklik-1;

      if (input(pin_A5))                 // Ayar menüsüne giriþ
      {
         while(input(Pin_A5));
                     for (int set_time=0;set_time<100;set_time++) // 4 saniye menü süresi için 320000 verilmeli
                  {
                        if(set_sicaklik<0)
                       {
                  output_b(0x00);
                  if(set_sicaklik<0)output_high(pin_B6);
                     delay_ms(1);
                     if (set_time<=20)
                        {
                        if(set_sicaklik<0)output_high(pin_B6);
                        output_c(dizi[sbirler]);         // displaye bilgi gönderiliyor
                        output_high(pin_C7);
                        output_d(dizi[sondabirler]);     // displaye bilgi gönderiliyor
                        delay_ms(20);                    // gecikme veriliyor
                        }
                        delay_ms(20);
                     if ((20<set_time) && (set_time<=40))
                        {
                        output_b(0x00);
                        output_c(0x00); 
                        output_d(0x00);
                        delay_ms(20);
                        }
                     if ((40<set_time) && (set_time<=60))
                        {
                         if(set_sicaklik<0)output_high(pin_B6);
                         output_c(dizi[sbirler]);        // displaye bilgi gönderiliyor
                         output_d(dizi[sondabirler]);    // displaye bilgi gönderiliyor
                         output_high(pin_C7);
                         delay_ms(20);                    // gecikme veriliyor
                        }
                     if ((60<set_time) && (set_time<=80))
                        {
                        output_b(0x00);
                        output_c(0x00); 
                        output_d(0x00);
                        delay_ms(20);
                        }
                      if ((80<set_time) && (set_time<=99))
                        {
                         if(set_sicaklik<0)output_high(pin_B6);         // displaye bilgi gönderiliyor
                         output_c(dizi[sbirler]);        // displaye bilgi gönderiliyor
                         output_d(dizi[sondabirler]);    // displaye bilgi gönderiliyor
                         output_high(pin_C7);
                         delay_ms(20);                    // gecikme veriliyor
                        }
            
                     if (input(pin_A2))                   
                        {
                         set_time=0;
                        while(input(Pin_A2));
                        set_sicaklik=(set_sicaklik-1); 
                        if(tolerans_sicaklik>=99)tolerans_sicaklik=0;
                        delay_ms(20);
                        }
                     if (input(pin_A4))
                        { 
                        set_time=0;
                        while(input(Pin_A4));
                        set_sicaklik=(set_sicaklik+1);
                        if(set_sicaklik>=99)set_sicaklik=0;
                        if(set_sicaklik>=0)output_low(pin_B6);
                        delay_ms(20);
                        }
                    sbirler=set_sicaklik%10;
                    sonlar=set_sicaklik/10;
                    sondabirler=(set_sicaklik*10)%10;
                    delay_ms(20);
                  }
                  else
               {
            if (set_time<=20)
               {
         output_b(dizi[sonlar]);          // displaye bilgi gönderiliyor
         output_c(dizi[sbirler]);         // displaye bilgi gönderiliyor
         output_d(dizi[sondabirler]);     // displaye bilgi gönderiliyor
         output_high(pin_C7);
         delay_ms(20);                    // gecikme veriliyor
               }
            if ((20<set_time) && (set_time<=40))
            {
              output_b(0x00);
              output_c(0x00); 
              output_d(0x00);
              delay_ms(20);
            }
            if ((40<set_time) && (set_time<=60))
            {
            output_b(dizi[sonlar]);         // displaye bilgi gönderiliyor
            output_c(dizi[sbirler]);        // displaye bilgi gönderiliyor
            output_d(dizi[sondabirler]);    // displaye bilgi gönderiliyor
            output_high(pin_C7);
            delay_ms(20);                    // gecikme veriliyor
            }
            if ((60<set_time) && (set_time<=80))
            {
              output_b(0x00);
              output_c(0x00); 
              output_d(0x00);
              delay_ms(20);
            }
             if ((80<set_time) && (set_time<=99))
            {
            output_b(dizi[sonlar]);         // displaye bilgi gönderiliyor
            output_c(dizi[sbirler]);        // displaye bilgi gönderiliyor
            output_d(dizi[sondabirler]);    // displaye bilgi gönderiliyor
            output_high(pin_C7);
            delay_ms(20);                    // gecikme veriliyor
            }
            
          if (input(pin_A2))                   
          {
          set_time=0;
          while(input(Pin_A2));
           set_sicaklik=(set_sicaklik-1);
          if(tolerans_sicaklik>=99)tolerans_sicaklik=0;
          delay_ms(20);
           }
         if (input(pin_A4))
           { 
           set_time=0;
          while(input(Pin_A4));
          set_sicaklik=(set_sicaklik+1);
         if(set_sicaklik>=99)set_sicaklik=0;
            }
         sbirler=set_sicaklik%10;
         sonlar=set_sicaklik/10;
         sondabirler=(set_sicaklik*10)%10;
         delay_ms(20);

           }
               }       
       
         }
   delay_ms(5);
   if(sicaklik>set_sicaklik)
   output_high(Pin_E0);
   
   if (sicaklik<=tolerans_sicaklik)
   output_low(Pin_E0);

   if((sicaklik>tolerans_sicaklik) && (sicaklik<set_sicaklik))
      {
            output_low(pin_E0);
      }
    }
}
