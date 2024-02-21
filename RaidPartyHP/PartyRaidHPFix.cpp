#include "pch.h"

#include "pch.h"
#include <string>
#include <sstream>
int Addr1 = 0;
int Addr2 = 0;
int result = 0;

int byteGetValue() {

    std::stringstream ss1, ss2;
    ss1 << std::hex << Addr1;
    ss2 << std::hex << Addr2;

    std::string strAddr1 = ss1.str();
    std::string strAddr2 = ss2.str();

    
    std::string resultStr = strAddr2 + strAddr1;

    
    int result;

    std::stringstream(resultStr) >> std::hex >> result;

    return result;
}
char userStatInfo[24]; 
char userStatInfo2[13];
DWORD sendCorrectValuePacketReturn = 0x005734C0;
_declspec(naked) void sendCorrectValuePacket() {
    _asm {

        pushad
        mov esi, eax
        movzx eax, word ptr ds : [esp + 0x38]
        mov [Addr1], eax
        movzx ebx, word ptr ds : [userStatInfo + 0x09]
        mov [Addr2], ebx
        call byteGetValue
        mov [esi + 0x20], eax
        popad


        movzx edx, word ptr ds : [esp + 0x18]
        jmp sendCorrectValuePacketReturn


    }
}


_declspec(naked) void sendCorrectValuePacketRaid() {
    _asm {
        pushad
        mov esi, eax
        movzx eax, word ptr ds : [esp + 0x2C]
        mov[Addr1], eax
        movzx ebx, word ptr ds : [userStatInfo2 + 0x09]
        mov[Addr2], ebx
        call byteGetValue
        mov [esi + 0x20], eax
        popad

        ret 0x010
    }
}

DWORD isGetPackethpReturn = 0x0059FA1A;
_declspec(naked) void isGetPackethp() {
    _asm {
        cmp word ptr ds : [esp + 0x20] , 0x050B
        je raidPacket
        cmp word ptr ds : [esp + 0x20] , 0x0C02
        jne originalcode

        pushad
        mov esi, esp
        mov ebx, offset userStatInfo
        mov ecx, 18
        loop_get_packet:
        mov al, [esi+0x2044]
        mov[ebx], al
        inc esi
        inc ebx
        dec ecx
        jnz loop_get_packet

        pop_out :
        popad

        originalcode:
        lea ecx, [esp + 0x00002024]
        jmp isGetPackethpReturn


        raidPacket:
        pushad
        mov esi, esp
        mov ebx, offset userStatInfo2
        mov ecx, 12
        loop_get_packet_raid :
        mov al, [esi + 0x2044]
        mov[ebx], al
        inc esi
        inc ebx
        dec ecx
        jnz loop_get_packet_raid

        jmp pop_out
    }
}



void PartyRaidHPFix() {
    Hook((PVOID)0x005734B8, sendCorrectValuePacket, 5);
    Hook((PVOID)0x0059FA13, isGetPackethp, 7);
    Hook((PVOID)0x00573429, sendCorrectValuePacketRaid, 5);
}