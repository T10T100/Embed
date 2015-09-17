#include "device.h"
extern SRAM_HandleTypeDef            hsram;
extern FMC_NORSRAM_TimingTypeDef     SRAM_Timing;
extern DMA_HandleTypeDef             DmaHandle,
                                     DmaHandleGraphic;
extern SPI_HandleTypeDef             SpiHandle;
extern TIM_HandleTypeDef             TimHandle;
extern TIM_HandleTypeDef             Tim2_Handle;

extern MemoryAllocator Heap;
extern SpiSoftTypeDef LcdSpi;
extern LcdDriverDef TFT;

extern Frame2DManager<gbasic_t> FrameManager;
extern ScreenManager ScreenMang;



/*Res*/
extern const tImage Image_Rose;
/*Res*/

/*End Of File*/
