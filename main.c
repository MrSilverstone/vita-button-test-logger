#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>

#include "debugScreen.h"
#define printf psvDebugScreenPrintf

int main() {
	psvDebugScreenInit();

    if (sceCtrlSetSamplingModeExt(2) < 0) {
    }

    SceCtrlPortInfo info = {0};
    sceCtrlGetControllerPortInfo(&info);

    printf("Port Info: ");
    for (int i = 0; i < 5; i++) {
        printf("PORT%d-", i);
        switch(info.port[i]) {
            case SCE_CTRL_TYPE_PHY:
                printf("VITA    ");
                break;
            case SCE_CTRL_TYPE_VIRT:
                printf("PSTV    ");
                break;
            case SCE_CTRL_TYPE_DS3:
                printf("DS2     ");
                break;
            case SCE_CTRL_TYPE_DS4:
                printf("DS4     ");
                break;
            case SCE_CTRL_TYPE_UNPAIRED:
            default:
                printf("UNPAIR  ");
                break;
        }
    }
    printf("\n\n");

    SceCtrlData pad[5] = {0}, old[5] = {0}, none = {0};
    none.lx = 0x7f;
    none.ly = 0x7f;
    none.rx = 0x7f;
    none.ry = 0x7f;

    while (1) {

        for (int port = 0; port < 5; port++) {
            memset(&pad[port], 0, sizeof(SceCtrlData));
            if (sceCtrlReadBufferPositiveExt2(port, &pad[port], 64) < 0) {
                continue;
            };
            pad[port].timeStamp = 0;
            if (pad[port].lx != 0xff && pad[port].lx != 0) pad[port].lx = 0x7f;
            if (pad[port].ly != 0xff && pad[port].ly != 0) pad[port].ly = 0x7f;
            if (pad[port].rx != 0xff && pad[port].rx != 0) pad[port].rx = 0x7f;
            if (pad[port].ry != 0xff && pad[port].ry != 0) pad[port].ry = 0x7f;


            if (memcmp(&pad[port], &none, sizeof(SceCtrlData)) == 0) {
                continue;
            }
            if (memcmp(&pad[port], &old[port], sizeof(SceCtrlData)) == 0) {
                continue;
            }

            printf("PORT: %d    BTN: 0x%08X    ", port, pad[port].buttons);
            printf("ANL: 0x%02X 0x%02X 0x%02X 0x%02X\n", pad[port].lx, pad[port].ly, pad[port].rx, pad[port].ry);
            printf("RSV: ");
            for (int i = 0; i < 16; i++) {
                printf("0x%02X ", pad[port].reserved[i]);
            }
            printf("\n\n");
            memcpy(&old[port], &pad[port], sizeof(SceCtrlData));
        }
    }
	sceKernelExitProcess(0);
}
