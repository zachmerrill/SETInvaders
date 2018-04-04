/*
FILE		:	SpriteSheet.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the SpriteSheet class.
*/
#include "SpriteSheet.h"

/*
METHOD		:	SpriteSheet - Constructor
AUTHOR		:	Russ Foubert
DESCRIPTION	:	This method creates a SpriteSheet object given the bmp filename and graphics object.
PARAMETERS	:	const wchar_t* filename - the file path of the bitmap
				Graphics* gfx - the graphics object
RETURNS		:	void
*/
SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* gfx, CHROMA_COLOUR colour, float scaleX, float scaleY) {
	this->gfx = gfx; // Save the gfx parameter for later
	bmp = NULL; // This needs to be NULL to start off
	ID2D1Effect* chromakeyEffect;
	HRESULT hr;

	// Step 1: Create a WIC Factory
	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory, // CLS ID of the object about to be made
		NULL, // Not needed here, but just denotes this isn't part of an aggregate
		CLSCTX_INPROC_SERVER, // Indicates this DLL runs in the same process
		IID_IWICImagingFactory, // Reference to an Interface that talks to the object
		(LPVOID*)&wicFactory); // This is our pointer to the WICFactory, once set up.

	// Step 2: Create a Decoder to read file into a WIC Bitmap
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, // The filename we passed in already
		NULL, // This can be used to indicate other/preferred decoders. Not something we need.
		GENERIC_READ, // Indicates we're reading from the file, vs writing, etc.
		WICDecodeMetadataCacheOnLoad, // Needed, but would only help if we were keeping this in WIC
		&wicDecoder); // Our pointer to the Decoder we've setup

	// Step 3: Read a 'frame'. We're really just moving the whole image into a frame here
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame); // 0 here means the first frame... or only one in our case
											 // Now, we've got a WICBitmap... we want it to be a D2D bitmap

	// Step 4: Create a WIC Converter
	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// Step 5: Configure the Converter
	hr = wicConverter->Initialize(
		wicFrame, // Our frame from above
		GUID_WICPixelFormat32bppPBGRA, // Pixelformat
		WICBitmapDitherTypeNone, // Not important for us here
		NULL, // Indicates no palette is needed, not important here
		0.0, // Alpha Transparency, can look at this later
		WICBitmapPaletteTypeCustom // Not important for us here
	);

	// Step 6: Create the D2D Bitmap! Finally!
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, // Our friend the converter
		NULL, // Can specify D2D1_Bitmap_Properties here, not needed now
		&bmp // Our destination bmp we specified earlier in the header
	);

	// Scale image
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1Scale, &bmpEffect);
	bmpEffect->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(scaleX, scaleY));

	// Determine chromakeying
	if (colour != CHROMA_COLOUR::NONE) {
		gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect);

		if (colour == CHROMA_COLOUR::RED) {
			D2D1_VECTOR_3F vector{ 1.0f, 0.0f, 0.0f };
			chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, vector);
		} else if (colour == CHROMA_COLOUR::GREEN) {
			D2D1_VECTOR_3F vector{ 0.0f, 1.0f, 0.0f };
			chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, vector);
		} else if (colour == CHROMA_COLOUR::BLUE) {
			D2D1_VECTOR_3F vector{ 0.0f, 0.0f, 1.0f };
			chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, vector);
		}

		chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.8f);
		chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
		chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);

		// Apply chromakey and scale
		chromakeyEffect->SetInput(0, bmp);
		bmpEffect->SetInputEffect(0, chromakeyEffect);
		if (chromakeyEffect) chromakeyEffect->Release();
	} else {
		// No chromakey, just apply scale
		bmpEffect->SetInput(0, bmp);
	}

	// Let us do some private object cleanup!
	if (bmp) bmp->Release();
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}

SpriteSheet::~SpriteSheet() {
	if (bmpEffect) bmpEffect->Release();
}

/*
void SpriteSheet::Draw() {
	gfx->GetRenderTarget()->DrawBitmap(
		bmp, // Bitmap we built from WIC
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height), //Destination rectangle
		0.8f, //Opacity or Alpha
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		// Above - the interpolation mode to use if this object is 'stretched' or 'shrunk'. 
		// Refer back to lecture notes on image/bitmap files
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height) // Source Rect
	);
}*/

/*
METHOD		:	Draw
DESCRIPTION	:	This method draws the current sprite at the given x and y coordinates.
PARAMETERS	:	float x - x coordinate
				float y - y coordinate
RETURNS		:	void
 */
void SpriteSheet::Draw(float x, float y) {
	gfx->GetDeviceContext()->DrawImage(
		bmpEffect,
		D2D1::Point2F(x, y),
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1_COMPOSITE_MODE::D2D1_COMPOSITE_MODE_SOURCE_OVER);
}

/*
METHOD		:	DrawRotated
DESCRIPTIN	:	This method draws the current sprite rotated on its axis toward another point.
PARAMETERS	:	float x1 - x of axis
				float y1 - y of axis
				float x2 - x of target
				float y2 - y of target
RETURNS		:	void
REFERENCED	:	https://stackoverflow.com/a/2339510 (math)
 */
void SpriteSheet::DrawRotated(float x1, float y1, float x2, float y2) {
	ID2D1Effect* transformEffect = NULL;
	float angle = (atan2(y1 - y2, x1 - x2) * 180 / PI) - 90;

	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D12DAffineTransform, &transformEffect);

	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(bmp->GetSize().width/4, bmp->GetSize().height/4));
	transformEffect->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, matrix);
	transformEffect->SetInputEffect(0, bmpEffect);

	gfx->GetDeviceContext()->DrawImage(
		transformEffect,
		D2D1::Point2F(x1, y1),
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1_COMPOSITE_MODE::D2D1_COMPOSITE_MODE_SOURCE_OVER);

	if (transformEffect) transformEffect->Release();
}