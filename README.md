TR:
Bu projede IS31FL3236a led driver entegresini PWM ile 36 kanalını aktif ederek kullandım.
SDB denen kanalını aktif lojik 1 yapıyoruz. 
2 tane buton vardır, bunlardan biriyle R-G-B renkleri arası geçiş yapıyoruz, diğer butonla ise PWM değerini ayarlıyoruz.

Eng:
In this project, I used the IS31FL3236a led driver IC by activating the 36 channel with PWM.
We make the channel called SDB active logic 1.
There are 2 buttons, with one of them we switch between R-G-B colors, and with the other button we adjust the PWM value.

main.c dosyasındaki for döngüsünü şu şekilde düzenledim.
for(uint8_t i = 0x03; i <= 0x24; i+=3)
{
  if(count2 == 255)
  {
      UsrAllLEDFadeOnRed(5);
      UsrAllLEDFadeOffRed(5);          
  }
  else if(count2 == 270)
  {
    UsrSetPWM(i, 255); 
  } 
  else{
    UsrSetPWM(i, count2);
  }  
}
