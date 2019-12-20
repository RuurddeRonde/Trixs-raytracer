#include "ImageIO.h"

#ifndef STBI_MSC_SECURE_CRT
#define STBI_MSC_SECURE_CRT
#endif // !STBI_MSC_SECURE_CRT
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STBI_MSC_SECURE_CRT


#include "stb_image_write.h"

namespace Trixs
{
	namespace Core
	{
		bool ImageIO::WriteJPG(char const *filename, int w, int h, int comp, const void *data, int quality)
		{
			if (stbi_write_jpg(filename, w, h, comp, data, quality))
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		bool ImageIO::WritePNG(char const *filename, int w, int h, int comp, const void *data, int quality)
		{
			if (stbi_write_png(filename, w, h, comp, data, quality))
			{
				return true;
			}
			else
			{
				return false;
			}
		}bool ImageIO::WriteBPM(char const *filename, int w, int h, int comp, const void *data)
		{
			if (stbi_write_bmp(filename, w, h, comp, data))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool ImageIO::WriteTGA(char const *filename, int w, int h, int comp, const void *data)
		{
			if (stbi_write_tga(filename, w, h, comp, data))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool ImageIO::WriteHDR(char const *filename, int w, int h, int comp, const void *data)
		{
			if (stbi_write_hdr(filename, w, h, comp, (float*)data))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
