#define	FIFO_SIZE (256*1024)

//external variables
extern Mtx view;
extern Mtx projection;
extern GXColor backgroundColor;
extern void* fifoBuffer;
extern GXRModeObj* screenMode;
static void* frameBuffer;
static vu8 readyForCopy;

static void copy_buffers(u32 unused);

void GX_VIDEO_INIT() 
{
	// Initialize video
	screenMode = VIDEO_GetPreferredMode(NULL);
	frameBuffer = MEM_K0_TO_K1(SYS_AllocateFramebuffer(screenMode));
	PAD_Init();
	VIDEO_Init();
	VIDEO_Configure(screenMode);
	VIDEO_SetNextFramebuffer(frameBuffer);
	VIDEO_SetPostRetraceCallback(copy_buffers);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();

	fifoBuffer = MEM_K0_TO_K1(memalign(32, FIFO_SIZE));
	memset(fifoBuffer, 0, FIFO_SIZE);

	// Other GX setup
	GX_Init(fifoBuffer, FIFO_SIZE);
	GX_SetCopyClear(backgroundColor, 0x00ffffff);
	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(frameBuffer, GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);
	guPerspective(projection, 60, 1.33F, 0.0F, 300.0F);
	GX_LoadProjectionMtx(projection, GX_PERSPECTIVE);
}

void update_screen(Mtx viewMatrix, guVector view)
{
	Mtx	modelView;

	c_guMtxIdentity(modelView);
	c_guMtxTransApply(modelView, modelView, view.x, view.y, -50.0F);

	c_guMtxConcat(viewMatrix, modelView, modelView);

	GX_LoadPosMtxImm(modelView, GX_PNMTX0);

	GX_Begin(GX_TRIANGLES, GX_VTXFMT0, 3);

	GX_Position1x8(0);
	GX_Color1x8(0);
	GX_Position1x8(1);
	GX_Color1x8(1);
	GX_Position1x8(2);
	GX_Color1x8(2);

	GX_End();

	readyForCopy = GX_TRUE;

	VIDEO_WaitVSync();
	return;
}

static void copy_buffers(u32 count __attribute__((unused)))
{
	if (readyForCopy == GX_TRUE) {
		GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		GX_SetColorUpdate(GX_TRUE);
		GX_CopyDisp(frameBuffer, GX_TRUE);
		GX_Flush();
		readyForCopy = GX_FALSE;
	}
}