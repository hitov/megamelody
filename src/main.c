/*
 * Copyright (C) 2013 Angel Hitov
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "rtttl.h"
#include "tonegen.h"


#define adams       "d=4,o=5,b=160:8c,f,8a,f,8c,b4,2g,8f,e,8g,e,8e4,a4,2f,8c,f,8a,f,8c,b4,2g,8f,e,8c,d,8e,1f,8c,8d,8e,8f,1p,8d,8e,8f#,8g,1p,8d,8e,8f#,8g,p,8d,8e,8f#,8g,p,8c,8d,8e,8f"
#define bolero      "d=4,o=5,b=60:c6,8c6,16b,16c6,16d6,16c6,16b,16a,8c6,16c6,16a,c6,8c6,16b,16c6,16a,16g,16e,16f,2g,16g,16f,16e,16d,16e,16f,16g,16a,g,g,16g,16a,16b,16a,16g,16f,16e,16d,16e,16d,8c,8c,16c,16d,8e,8f,d,2g"
#define CocaCola    "d=4,o=5,b=125:8f#6,8f#6,8f#6,8f#6,g6,8f#6,e6,8e6,8a6,f#6,d6,2p"
#define Looney      "d=4,o=5,b=140:c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f"
#define PinkPanther "d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e"
#define YMCA        "d=4,o=5,b=160:8c#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8b,2p,8b,8a#,8g#,8a#,8b,d#6,8f#6,d#6,f.6,d#.6,c#.6,b.,a#,g#"
#define Xfiles      "d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b."
#define Friends     "d=8,o=5,b=100:16d,g,a,c6,b,a,g.,16g,d,g,a,2a,p,16p,16d,g,a,c.6,16b,16a,g.,16c6,b,a,g,2d6,p,16p,16c6,c6,c6,c6,c6,c6,c.6,16c6,b,2b,p,16a,16a,16b,16c6,c6,c6,c6,c.6,16b,a.,16g,g.,16d,16g,16a,b,4a,4g,p"
#define WeWish      "d=4,o=5,b=140:d,g,8g,8a,8g,8f#,e,c,e,a,8a,8b,8a,8g,f#,d,f#,b,8b,8c6,8b,8a,g,e,8d,8d,e,a,f#,2g."
#define PoliceP     "d=4,o=6,b=140:8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c"
#define addams1     "d=4,o=5,b=180:8c,f,8a,f,8c,b4,g.,8f,e,8g,e,8g4,a4,f.,8c,f,8a,f,8c,b4,g.,8f,e,8c,d,8e,f.,8c,8d,8e,8f,1p,8d,8e,8f#,8g,1p,8d,8e,8f#,8g,p,8d,8e,8f#,8g,p,8c,8d,8e,8f"

#define BUTTON0_IN()    ( PINC & (1 << PC3) )
#define MELODYCOUNT     6

char melodyes_tbl[MELODYCOUNT][256] PROGMEM = {
    //addams
    "d=4,o=5,b=180:8c,f,8a,f,8c,b4,g.,8f,e,8g,e,8g4,a4,f.,8c,f,8a,f,8c,b4,g.,8f,e,8c,d,8e,f.,8c,8d,8e,8f,1p,8d,8e,8f#,8g,1p,8d,8e,8f#,8g,p,8d,8e,8f#,8g,p,8c,8d,8e,8f",
    //police
    "d=4,o=6,b=140:8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c",
    //we wish you
    "d=4,o=5,b=140:d,g,8g,8a,8g,8f#,e,c,e,a,8a,8b,8a,8g,f#,d,f#,b,8b,8c6,8b,8a,g,e,8d,8d,e,a,f#,2g.",
    //bolero
    "d=4,o=5,b=60:c6,8c6,16b,16c6,16d6,16c6,16b,16a,8c6,16c6,16a,c6,8c6,16b,16c6,16a,16g,16e,16f,2g,16g,16f,16e,16d,16e,16f,16g,16a,g,g,16g,16a,16b,16a,16g,16f,16e,16d,16e,16d,8c,8c,16c,16d,8e,8f,d,2g",
    //pink panter
    "d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e",
    //x-files
    "d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b."
};

typedef enum ButtonState {
    PRESSED, 
    RELEASED
};

int scanbutton()
{
    int i, bsum = 0;
    for(i = 0; i < 100; i++)
    {
        if(BUTTON0_IN()) bsum++;
        _delay_ms(1);
    }
    if(bsum < 50) return PRESSED;
        else return RELEASED;

    return 0;
}

int main()
{
    char buffer[256];
    ToneGenInit();
    while(1)
    {
        static int MelodyIndex = 0;
        if(scanbutton() == PRESSED)
        {
            strcpy_P(buffer, &melodyes_tbl[MelodyIndex]);
            RTTTL_Play(buffer);
            MelodyIndex++;
            MelodyIndex %= MELODYCOUNT;
        }
    }
    return 0;
}
