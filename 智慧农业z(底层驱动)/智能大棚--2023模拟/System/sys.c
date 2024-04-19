#include "sys.h"


void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//ژҕ̹Ԑא׏
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//ߪǴ̹Ԑא׏
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//ʨ׃ջַ֥֘
//addr:ջַ֥֘
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
