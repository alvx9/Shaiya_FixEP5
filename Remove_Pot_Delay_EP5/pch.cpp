#include "pch.h"

DWORD No_Delay_Return = 0x00598B85;
DWORD Continue_No_Delay = 0x00598BB4;
DWORD Packet_Address = 0x005CD2A0;
DWORD Exit = 0x00598BDF;
_declspec(naked) void dwRemoveDelay()
{
	_asm {
		push eax
		mov eax,[esp + 0x04]
		cmp eax,0x0049206A
		pop eax
		je OriginalCode 


		mov eax, 0x00002000
		call Packet_Address 
		call dword ptr ds:[0x006BB2C0]
		mov ecx, dword ptr ds:[0x0070C3C8]
		cmp byte ptr ds : [ebp + 0x10F5] , 25 // type id
		je Continue_No_Delay
		
              // ebp + 0x10F5 = Type , 0x10F6 = Type ID , if you want add more type and type id just edit this

		Delay_Function:
		test ecx, ecx
		jne No_Delay_Addr 
		mov ecx, dword ptr ds:[0x224E34C]
		add ecx, 0x000003E8
		cmp eax, ecx
		jna Exit_Function
		mov dword ptr ds:[0x70C3C8], 0x00000001
		jmp Continue_No_Delay



	     OriginalCode:
		 mov eax, 0x00002000
		 jmp No_Delay_Return 

		 Exit_Function:
		 jmp Exit
		 
		 No_Delay_Addr:
		 jmp Continue_No_Delay

	}
}

void Remove_Delay_Pot(){
     Hook((void*)0x00598B80, dwRemoveDelay, 5);
     }
