//Used this tutorial:
// http://lodev.org/cgtutor/plasma.html
static const unsigned char pal[]=
{
  "\0\370\40\370`\370\200\370\300\370\340\370\40\371@\371\200\371\240\371\300"
    "\371\0\372@\372`\372\240\372\300\372\0\373\40\373@\373\200\373\240\373\340"
    "\373\40\374@\374`\374\200\374\300\374\0\375\40\375`\375\200\375\240\375\340"
    "\375\0\376@\376\200\376\240\376\340\376\40\377@\377`\377\240\377\300\377"
    "\340\377\340\367\340\367\340\357\340\347\340\347\340\337\340\327\340\317"
    "\340\307\340\307\340\277\340\267\340\257\340\257\340\247\340\237\340\227"
    "\340\217\340\217\340\207\340\177\340\177\340w\340o\340g\340_\340_\340W\340"
    "W\340O\340G\340?\340?\3407\340/\340'\340'\340\37\340\27\340\17\340\17\340"
    "\7\340\7\341\7\342\7\342\7\343\7\344\7\345\7\346\7\346\7\347\7\347\7\350"
    "\7\351\7\352\7\353\7\353\7\354\7\355\7\355\7\356\7\357\7\360\7\361\7\361"
    "\7\362\7\363\7\363\7\364\7\365\7\366\7\366\7\367\7\370\7\370\7\371\7\372"
    "\7\373\7\374\7\374\7\375\7\376\7\377\7\377\7\337\7\237\7\177\7?\7\377\6\337"
    "\6\237\6\177\6_\6\37\6\377\5\277\5\177\5_\5?\5\377\4\337\4\237\4\177\4?\4"
    "\37\4\337\3\277\3\237\3_\3?\3\377\2\337\2\237\2_\2?\2\37\2\377\1\277\1\177"
    "\1_\1\37\1\337\0\277\0\177\0_\0?\0\37\0\37\10\37\10\37\20\37\20\37\30\37"
    "\40\37(\37""0\37""8\37""8\37@\37H\37P\37P\37X\37`\37`\37h\37p\37x\37\200"
    "\37\200\37\210\37\220\37\220\37\230\37\240\37\250\37\250\37\260\37\270\37"
    "\300\37\300\37\310\37\320\37\320\37\330\37\340\37\350\37\360\37\360\37\370"
    "\37\370\36\370\35\370\34\370\34\370\33\370\32\370\31\370\31\370\30\370\27"
    "\370\27\370\26\370\25\370\24\370\23\370\23\370\22\370\21\370\21\370\20\370"
    "\17\370\16\370\16\370\15\370\14\370\14\370\13\370\12\370\11\370\11\370\10"
    "\370\7\370\6\370\5\370\5\370\4\370\3\370\3\370\2\370\1\370\1\370"
};
static const unsigned char sinetable[256]=
{
  127,130,133,136,139,142,145,148,151,154,157,160,163,166,169,172,175,178,181,184,186,
  189,192,194,197,200,202,205,207,209,212,214,216,218,221,223,225,227,229,230,232,
  234,235,237,239,240,241,243,244,245,246,247,248,249,250,250,251,252,252,253,253,
  253,253,253,254,253,253,253,253,253,252,252,251,250,250,249,248,247,246,245,244,
  243,241,240,239,237,235,234,232,230,229,227,225,223,221,218,216,214,212,209,207,
  205,202,200,197,194,192,189,186,184,181,178,175,172,169,166,163,160,157,154,151,
  148,145,142,139,136,133,130,127,123,120,117,114,111,108,105,102,99,96,93,90,87,
  84,81,78,75,72,69,67,64,61,59,56,53,51,48,46,44,41,39,37,
  35,32,30,28,26,24,23,21,19,18,16,14,13,12,10,9,8,7,6,5,
  4,3,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,2,
  3,3,4,5,6,7,8,9,10,12,13,14,16,18,19,21,23,24,26,28,
  30,32,35,37,39,41,44,46,48,51,53,56,59,61,64,67,69,72,75,78,
  81,84,87,90,93,96,99,102,105,108,111,114,117,120,123
};
void appPlasma()
{
   unsigned char t;
   unsigned short int ii;
   unsigned short int jj;
   LCD_SetCursor(0,0);
   LCD_WriteIndex(0x22);
   for(;;)
   {
   if(!returnButtonState)break;
   for(jj=0;jj<320;jj++)
   {
   for(ii=0;ii<240;ii++)
   {
   LCD_WriteData(pal[ ((sinetable[(t+jj)&255]+sinetable[(t+ii)&255]+t)&0xff)|1 ] , pal[ (sinetable[(t+jj)&255]+sinetable[(t+ii)&255]+t)&0xfe ]);
   }
   }
   t++;
   } 
//Below is code(not mine, I only modified it to work with my LCD functions) to draw fancy bouncing Amiga ball
//You may comment above plasma code and decomment the following to see it.
//Works, but it is slow. About 5-6 fps.
  /* Derived from the 2011 IOCCC submission by peter.eastman@gmail.com
   * http://www.ioccc.org/2011/eastman/eastman.c
   * --
   * Public Domain -- but you're looking at this for ideas of techniques
   * and methods, not trying to cut&paste an entire application, anyway.
   * --
   * When you need to blit an entire screenfull of data to an LCD
   * display, the basic idea is to exploit the auto-increment feature of
   * the display controller when it writes to screen memory. You start
   * by resetting the 'cursor' to the 0,0 position, and then stream
   * width*height pixels out.
   * --
   * Chris Baird,, <cjb@brushtail.apana.org.au> April 2013
   */
/*#define HTML2COLOR(__x) (RGB((__x>>16),((__x>>8)&0xFF),(__x&0xFF)))
#define Lightgrey (HTML2COLOR(0xC0C0C0))
#define Midgrey (HTML2COLOR(0x606060))
#define Darkgrey (HTML2COLOR(0x303030))

  uint16_t xx, yy, colour;

  uint16_t width = 240;
  uint16_t height = 320;
FPUEnable();
  float i=height/5+height%2+1, floorstart=height/5-1, spherespin=0.0,
  l=width/2, m=height/4, n=.01*width, o=0.0, rotspeed=0.1, h, f, g;
  LCD_SetCursor(0,0);
  LCD_WriteIndex(0x22);
  while (TRUE)
  {
    //      reset_cursor ();
    //      StartStream ();

    for (xx=yy=0;
	   h = (m-yy)/i, f=-.3*(g=(l-xx)/i)+.954*h, yy<height;
	   yy += (xx = ++xx%width)==0 )
    {
      if (g*g < 1-h*h) 
        if (((int)(9-spherespin+(.954*g+.3*h)/sqrtf(1-f*f))+(int)(2+f*2))%2==0)
          colour = RED;
        else
          colour = WHITE;
      else
      {
        if (xx<floorstart || xx>width-floorstart)
          colour = Darkgrey; 
        else
          colour = Lightgrey; 

        if (yy > height-floorstart)
          if (xx < height-yy || height-yy > width-xx) 
            colour = Darkgrey;
          else
            colour = Midgrey;

        if (g*(g+.6)+.09+h*h < 1)
          colour >>= 1; 	
      }

      LCD_WriteData (colour); 	
    }

    //    StopStream();
    spherespin += rotspeed;
    m += o;
    o = m > height-1.75*floorstart ? -.04*height : o+.002*height;
    n = (l+=n)<i || l>width-i ? rotspeed=-rotspeed,-n : n;
  }

*/
}




