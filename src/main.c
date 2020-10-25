//SPDX-License-Identifier: BSD-3-Clause
//SPDX-FileCopyrightText: 2020 Lorenzo Cauli (lorecast162)

#include <genesis.h>
#include "resources.h"
#include "sfx.h"
#include "bg.h"

int main() {

    int posX = 144;
    int posY = 104;

    int xInc = 4;
    
    u8 curPalette = 0;
    u8 prevPalette = 0;

    VDP_setScreenWidth320();
    SPR_init();
    JOY_init();

    VDP_drawImage(PLAN_A, &bg, 0, 0);

    Sprite* sphereSprite = SPR_addSprite(&sphere, posX, posY, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    while (1) {
        SPR_update();
        VDP_waitVSync();

        SPR_setPosition(sphereSprite, posX, posY);

        u16 joy0State = JOY_readJoypad(JOY_1);

        if (joy0State) {
            if (joy0State & BUTTON_DOWN)
                curPalette = 1;
            else if (joy0State & BUTTON_UP)
                curPalette = 2;
            else curPalette = 0;

            if (joy0State & BUTTON_LEFT)
                if (posX - xInc >0)
                    posX-=xInc;
                else
                    SND_startPlay_PCM(hitSfx, 5632, SOUND_RATE_8000, SOUND_PAN_CENTER, 0);
            else if (joy0State & BUTTON_RIGHT) 
                if (( posX + 32 ) + xInc < 320)
                    posX+=xInc;
                else 
                    SND_startPlay_PCM(hitSfx, 5632, SOUND_RATE_8000, SOUND_PAN_CENTER, 0);
        }
        else curPalette = 0;

        if (curPalette != prevPalette)
        switch (curPalette) {
            case 0:
                SPR_setPalette(sphereSprite, PAL1);
                break;
            case 1:
                SPR_setPalette(sphereSprite, PAL2);
                break;
            case 2:
                SPR_setPalette(sphereSprite, PAL3);
                break;
        }

        prevPalette = curPalette;
    }
    return (0);
}
