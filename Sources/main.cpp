#define _WINDLL_IMPORT
#include <PVRTextureUtilities.h>

#define dynfunc extern "C" __declspec(dllexport)

namespace {
	int pow(int pow) {
		int ret = 1;
		for (int i = 0; i < pow; ++i) ret *= 2;
		return ret;
	}

	int getPower2(int i) {
		for (int power = 0; ; ++power)
			if (pow(power) >= i) return pow(power);
	}

	int imax(int a, int b) {
		return a > b ? a : b;
	}
}

dynfunc char* format() {
	return "pvrtc";
}

dynfunc void encode(int width, int height, int stride, int format, unsigned char* pixels_, int* out_width, int* out_height, int* out_size, void** out_data) {
	int w = getPower2(width);
	int h = getPower2(height);
	w = h = imax(w, h);
	unsigned char* pixels = new unsigned char[w * h * 4];
	for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
		pixels[y * w * 4 + x * 4 + 0] = 0;
		pixels[y * w * 4 + x * 4 + 1] = 0;
		pixels[y * w * 4 + x * 4 + 2] = 0;
		pixels[y * w * 4 + x * 4 + 3] = 0;
	}
	for (int y = 0; y < height; ++y) for (int x = 0; x < width; ++x) {
		pixels[y * w * 4 + x * 4 + 0] = pixels_[y * stride + x * 4 + 0];
		pixels[y * w * 4 + x * 4 + 1] = pixels_[y * stride + x * 4 + 1];
		pixels[y * w * 4 + x * 4 + 2] = pixels_[y * stride + x * 4 + 2];
		pixels[y * w * 4 + x * 4 + 3] = pixels_[y * stride + x * 4 + 3];
	}
	pvrtexture::CPVRTextureHeader header(pvrtexture::PVRStandard8PixelType.PixelTypeID, w, h);
	pvrtexture::CPVRTexture texture(header, pixels);
	pvrtexture::Transcode(texture, ePVRTPF_PVRTCI_4bpp_RGBA, ePVRTVarTypeUnsignedByteNorm, ePVRTCSpacelRGB);

	MetaDataBlock widthBlock;
	widthBlock.DevFOURCC = 0;
	widthBlock.u32Key = 0;
	widthBlock.u32DataSize = 4;
	widthBlock.Data = new unsigned char[4];
	unsigned char* ww = (unsigned char*)&width;
	for (int i = 0; i < 4; ++i) widthBlock.Data[i] = ww[i];
	texture.addMetaData(widthBlock);

	MetaDataBlock heightBlock;
	heightBlock.DevFOURCC = 1;
	heightBlock.u32Key = 0;
	heightBlock.u32DataSize = 4;
	heightBlock.Data = new unsigned char[4];
	unsigned char* hh = (unsigned char*)&height;
	for (int i = 0; i < 4; ++i) heightBlock.Data[i] = hh[i];
	texture.addMetaData(heightBlock);

	*out_width = w;
	*out_height = h;
	*out_size = texture.getDataSize();
	*out_data = texture.getDataPtr();
	
	//delete[] pixels;
}
