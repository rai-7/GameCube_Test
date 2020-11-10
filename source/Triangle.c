//WARNING very ugly code. you will die if you look

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <gccore.h>
#include "Structs.h"
#include "GxInit.h"

//global variables :vomiting_face:
GXColor backgroundColor = { 0, 0, 0, 255 };
void* fifoBuffer = NULL;
Mtx projection;
Mtx view;
GXRModeObj	*screenMode;
static void	*frameBuffer;
static vu8	readyForCopy;
ivec2 Stick;
//struct ivec2 CStick;

camera cam = {
	{0.0F, 0.0F, 0.0F },
	{0.0F, 1.0F, 0.0F },
	{0.0F, 0.0F, -1.0F}
};

u16	vertices[] ATTRIBUTE_ALIGN(32) = {
	-1, 1, 0,
	-1,-1, 0,
	 1,-1, 0
};

u8 colors[]	ATTRIBUTE_ALIGN(32)	= {
	255, 50, 50, 255,		// red
	50, 255, 50, 255,		// green
	50, 50, 255, 255,		// blue
};	

void walkplayer(ivec2);
//void movecamera(struct ivec2);

// some GX stuff
void update_screen(Mtx, guVector);
void draw_init();

int	main()
{
	GX_VIDEO_INIT();
	draw_init();
	
	while (1)
	{
		// Camera controls
		PAD_ScanPads();
		Stick.x = PAD_StickX(0);
		Stick.y = PAD_StickY(0);
		int deadzone = 1;

		//CStick.x = PAD_SubStickX(0);
		//CStick.y = PAD_SubStickY(0);

		if ((Stick.y > deadzone || Stick.y < -deadzone) || (Stick.x > deadzone || Stick.x < -deadzone))
		{
			walkplayer(Stick);
		}
		/*
		if ((CStick.y > 18 || CStick.y < -18) || (CStick.x > 18 || CStick.x < -18))
		{
			movecamera(CStick);
		}*/

		VIDEO_Flush();
		update_screen(view, cam.pos);
		guLookAt(view, &cam.pos, &cam.up, &cam.view);
	}
	return 0;
}

void draw_init() 
{
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_INDEX8);
	GX_SetVtxDesc(GX_VA_CLR0, GX_INDEX8);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetArray(GX_VA_POS, vertices, 3 * sizeof(s16));
	GX_SetArray(GX_VA_CLR0, colors, 4 * sizeof(u8));
	GX_SetNumChans(1);
	GX_SetNumTexGens(0);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

void walkplayer(ivec2 speed) 
{
	speed.x /= 50;
	speed.y /= 50;

	guVector v;

	// X axis
	v.x = cam.view.x - cam.pos.x;
	cam.view.x += v.x * speed.x;
	cam.pos.x += v.x * speed.x;

	// Z axis
	v.z = cam.view.z - cam.pos.z;
	cam.view.z += v.z * speed.y;
	cam.pos.z += v.z * speed.y;
}

/*
void movecamera(struct ivec2 speed) 
{

}*/