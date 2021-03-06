#include "gcSdk.h"
#include "testImages.h"

void testRotation(gcSURFACEINFO* Target)
{
	gcIMAGEDESCRIPTOR* Image;
	float imgRatio;
	float trgRatio;
	UINT32 imgWidth, imgHeight;
	UINT32 trgWidth, trgHeight;
	gcRECT rect;
	UINT32 xStep;
	UINT32 srcRotAngle;
	UINT32 dstRotAngle;
	UINT32 loopCount =1;
	UINT32 i,j;

	// Load the image.
	gcLoadImage(&exige_0160x108x24);

	// Set image.
	Image = &exige_0160x108x24;
	for (i=0; i<10; i++) {
		//src/dest rotate 90 degree;
		srcRotAngle = 0x4 + i%3;
		dstRotAngle = 0x6 - i%3;
		
		// Compute sizes.
		// source window;
		if (srcRotAngle == 0x04 | srcRotAngle == 0x06) {
			imgWidth  = gcImageHeight(Image);
			imgHeight = gcImageWidth(Image);
		} else {
			imgWidth  = gcImageWidth(Image);
			imgHeight = gcImageHeight(Image);
		}

		// destination window;
		trgWidth  = gcSurfaceWidth(Target);
		trgHeight = gcSurfaceHeight(Target);
		
		// Compute ratios.
		imgRatio = (float) imgWidth / imgHeight;
		trgRatio = (float) trgWidth / trgHeight;


		rect.left   = Target->rect.left;
		rect.top    = Target->rect.top;
		rect.right  = Target->rect.right;
		rect.bottom = Target->rect.bottom;

		// Determine the step.
		xStep = (trgWidth / 2 - 1) / loopCount;

		// Clear the frame.
		//gcClear(Target, &Target->rect, DEADBEEF16);

		// Blit the image.
		
		gcBitBltRot(Target, &Image->surface,
				 &rect, &Image->surface.rect,
				 0xCC, 0xCC,
				 NULL,			// No brush.
				 AQDE_SRC_CONFIG_TRANSPARENCY_OPAQUE,
				 ~0,			// Transparency color is ignored.
				 NULL,			// No mask.
				 ~0,			// Mask pack is ignored.
				 0,		    // Absolute coordinates.
				 srcRotAngle,   // source rotation angle
	 			 dstRotAngle,   // dst rotation angle
				 imgWidth,		// src surface width;  
				 imgHeight,   	// src surface height;
				 trgWidth,		// dest surface width;
				 trgHeight);	// dest surface height;

		// Start.
		gcFlush2DAndStall();
		gcStart();
		gcFlushDisplay();	
		for (j=1500;j>1;j--) {
			printf("");
		}
	}
	
	gcBitBltRot(Target, &Image->surface,
				 &rect, &Image->surface.rect,
				 0xCC, 0xCC,
				 NULL,			// No brush.
				 AQDE_SRC_CONFIG_TRANSPARENCY_OPAQUE,
				 ~0,			// Transparency color is ignored.
				 NULL,			// No mask.
				 ~0,			// Mask pack is ignored.
				 0,		    // Absolute coordinates.
				 0,   // source rotation angle
	 			 0,   // dst rotation angle
				 0,		// src surface width;  
				 0,   	// src surface height;
				 0,		// dest surface width;
				 0);	// dest surface height;

	// Start.
	gcFlush2DAndStall();
	gcStart();
	gcFlushDisplay();	
	// Free the image.
	gcMemFree();	
}

void testRotation_1(unsigned int winx, unsigned int winy)
{
	UINT32 imgWidth, imgHeight;
	UINT32 trgWidth, trgHeight;
	UINT32 srcRotAngle;
	UINT32 dstRotAngle;
	UINT32 i,j;

	gcSURFACEINFO* Target = &gcDisplaySurface;
	gcSURFACEINFO Src;

	// Init target surface.
	Src.address = Target->address;
	Src.stride  = Target->stride; // gcSCREENWIDTH * gcGetPixelSize(gcSCREENFORMAT) / 8;
	Src.format  = Target->format;

	// Init clipping.
	Src.clip.left   = 0;
	Src.clip.top    = 0; // font_height; //zgj
	Src.clip.right  = winx;
	Src.clip.bottom = winy;

	// Compute initial rect.
	Src.rect.left   = 0;
	Src.rect.right  = winx;
	Target->rect.left = winx;
	Target->rect.right = winx + winx;
	Src.rect.top = 0;
	Src.rect.bottom = winy;
	Target->rect.top = winy;
	Target->rect.bottom = winy + winy;

	for (i=0; i<10; i++) {
		//src/dest rotate 90 degree;
		srcRotAngle = 0x4 + i%3;
		dstRotAngle = 0x6 - i%3;
		
		// Compute sizes.
		// source window;
	    if (srcRotAngle == 0x04 | srcRotAngle == 0x06) {
	    	imgWidth  = winy;
			imgHeight = winx;
	    } else {
			imgWidth  = winx;
			imgHeight = winy;
		}

		// destination window;
		trgWidth  = gcSurfaceWidth(Target);
		trgHeight = gcSurfaceHeight(Target);

		// Clear the frame.
		//gcClear(Target, &Target->rect, DEADBEEF16);

		// Blit the image.
		
		gcBitBltRot(Target, &Src, &Target->rect, &Src.rect,
				 0xCC, 0xCC,
				 NULL,			// No brush.
				 AQDE_SRC_CONFIG_TRANSPARENCY_OPAQUE,
				 ~0,			// Transparency color is ignored.
				 NULL,			// No mask.
				 ~0,			// Mask pack is ignored.
				 0,		    // Absolute coordinates. ???????????????
				 srcRotAngle,   // source rotation angle
	 			 dstRotAngle,   // dst rotation angle
				 imgWidth,		// src surface width;  
				 imgHeight,   	// src surface height;
				 trgWidth,		// dest surface width;
				 trgHeight);	// dest surface height;

		// Start.
		gcFlush2DAndStall();
		gcStart();
		gcFlushDisplay();	
		for (j=1500;j>1;j--) {
			printf("");
		}
	}
/*
	gcBitBltRot(Target, &Src, &Target->rect, &Src.rect,
				 0xCC, 0xCC,
				 NULL,			// No brush.
				 AQDE_SRC_CONFIG_TRANSPARENCY_OPAQUE,
				 ~0,			// Transparency color is ignored.
				 NULL,			// No mask.
				 ~0,			// Mask pack is ignored.
				 0,		    // Absolute coordinates.
				 0,   // source rotation angle
	 			 0,   // dst rotation angle
				 0,		// src surface width;  
				 0,   	// src surface height;
				 0,		// dest surface width;
				 0);	// dest surface height;

	// Start.
	gcFlush2DAndStall();
	gcStart();
	gcFlushDisplay();*/
	// Free the image.
	gcMemFree();	
}
