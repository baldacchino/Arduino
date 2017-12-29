


#include <U8glib.h>


U8GLIB_SH1106_128X64 display1(13, 11, 10, 9, 8);

U8GLIB_SSD1306_128X64 display2(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 



void setup(void)
{
  display1.setColorIndex(1);
  display2.setColorIndex(1);
  pinMode(8, OUTPUT);
}
void loop(void)
{
  display1.firstPage();
  do
  {
    draw1();
  } while ( display1.nextPage() );

  display2.firstPage();
  do
  {
    draw2();
  } while ( display2.nextPage() );

  delay(100);
}

void draw1(void)
{
  display1.setFont(u8g_font_unifont);
  display1.drawStr(0, 22, "Display 1");
}
void draw2(void)
{
  display2.setFont(u8g_font_unifont);
  display2.drawStr(0, 22, "Display 2");
}




