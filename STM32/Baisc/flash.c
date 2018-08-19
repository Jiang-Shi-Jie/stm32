#include "flash.h"

// page大小根据单片机FLASH容量来定 因为一页地址从0x000-0x3fff  所以offset小于0X400
u32 FLASH_page(u16 page,u16 offset) {
	return 0X08000000 + 0X400*page + offset;
}

void FLASH_write(u32 addr,u16 data){
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(addr);
	FLASH_ProgramHalfWord(addr, data);
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPRTERR);
	FLASH_Lock();
}

u16 FLASH_read(u32 addr){
	 u16 data;
	 data = *(u16*)(addr);
	 return data;
}
