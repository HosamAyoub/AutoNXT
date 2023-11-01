#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/STK/MSTK_Interface.h"
#include "../include/STP/HSTP_Interface.h"

u8 local_u8Arr1[31] = {129, 129, 255, 129, 129, 0, 0, 255, 1, 7, 1, 255, 0, 0, 255, 1, 126, 64, 63, 0, 0, 126, 129, 255, 129, 0, 0, 195, 165, 153, 129};
u8 local_u8Arr2[35] = {255, 8, 8, 8, 255, 0, 0, 255, 145, 129, 0, 0, 159, 145, 241, 0, 0, 255, 8, 8, 8, 255, 0, 0, 254, 17, 17, 254, 0, 0, 255, 1, 6, 1, 255};
u64 local_u64Arr3[8] = {18493073361, 29280702545, 22838251601, 18781889503, 18543345745, 18543345745, 18543343569, 0};
u64 local_u64Arr4[8] = {16634209169, 18270655569, 18270655562, 16361514948, 18274649156, 18274649156, 18777699396, 0};
void main (void)
{
	u8 local_u8Iterator = 0;
	u8 local_u8FlagVal = 0;
	u64 * Ptr = local_u64Arr3;
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(RCC_AHB1 , RCC_AHB1_GPIOA);
	MSTK_voidInit();
	HSTP_voidInit();
	while (1)
	{

		MSTK_voidSetPreloadValue(3200000);
		MSTK_voidEnableSTK();
		while (!local_u8FlagVal)
		{
			HSTP_voidLedMatrixScrollingAsync(Ptr , local_u8Iterator);
			MSTK_voidGetFlagValue(&local_u8FlagVal);
		}
		local_u8FlagVal = 0;
		if (local_u8Iterator < 40)
		{
			local_u8Iterator++;
		}
		else
		{
			local_u8Iterator = 0;
			Ptr = local_u64Arr4;
		}
	}
}

