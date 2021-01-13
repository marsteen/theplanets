
#ifndef CPIXEL24_H
#define CPIXEL24_H

class CPixel24
{
	public:

  	unsigned char rgb[3];

    void operator=(CPixel24& p2)
    {
			rgb[0] = p2.rgb[0];
			rgb[1] = p2.rgb[1];
			rgb[2] = p2.rgb[2];
		}


    void operator=(int i)
    {
			rgb[0] = i >> 16;
			rgb[1] = (i >> 8) & 0xFF;
			rgb[2] = i & 0xFF;
		}

		unsigned int GetInt()
		{
			return (rgb[2] << 16) | (rgb[1] << 8) | rgb[0];
		}


    bool operator==(CPixel24& p2);
    bool operator!=(CPixel24& p2);
		void Set(unsigned char r, unsigned char g, unsigned char b);
		void Set(unsigned int b);
		void SwapRedBlue(void);
		int  Brightness(void);
};

#endif


