#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>

#include "debugScreen.h"
#define printf psvDebugScreenPrintf

int main() {
	psvDebugScreenInit();

    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);

    SceCtrlData pad = {0}, old = {0}, none = {0};
    printf("app start. please input any button\n");

    while (1) {
        memset(&pad, 0, sizeof(SceCtrlData));
        sceCtrlPeekBufferPositive(0, &pad, 1);
        pad.timeStamp = 0;
        pad.lx = 0;
        pad.ly = 0;
        pad.rx = 0;
        pad.ry = 0;

        if (memcmp(&pad, &none, sizeof(SceCtrlData)) == 0) {
            continue;
        }
        if (memcmp(&pad, &old, sizeof(SceCtrlData)) == 0) {
            continue;
        }

        //printf("BTN: 0x%08X\n L: (0x%02X,0x%02X) R: (0x%02X, 0x%02X)\n",
        //        pad.buttons, pad.lx, pad.ly, pad.rx, pad.ry);
        printf("BTN: 0x%08X\n", pad.buttons);
        printf("RSV: ");
        for (int i = 0; i < 16; i++) {
            printf("0x%02X ", pad.reserved[i]);
        }
        printf("\n\n");
        memcpy(&old, &pad, sizeof(SceCtrlData));
    }
	sceKernelExitProcess(0);
}
