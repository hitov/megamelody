#include <string.h>
#include <stdlib.h>
#include "tonegen.h"
#include "notestbl.h"

#define TRUE  -1
#define FALSE  0

unsigned char DefaultDuration; //1-32 means 1/1, 1/2, 1/4, 1/8, 1/16, 1/32 ...
unsigned char DefaultOctave;
unsigned char DefaultTempo;

extern unsigned char notes_tbbl[];

unsigned char *notes = notes_tbl;
//unsigned int notes[] =     {
//                //c,c#,d,d#,e,e#(f),f#,g,g#,a,a#,b,b#
//                261,277,294,311,330,349,370,392,415,440,466, 494, 523
//            };

char NoteChar(char c)
{
    if( (( c >= 'a') && ( c <= 'g')) || (c == 'p') ) return 1;
    return 0;
}

int getoctave(char *str)
{
    char tmps[10];
    strcpy(tmps, str);
    return atoi(tmps);
}

char validoctave(int oct)
{
    if( (oct >= 4) && (oct <= 8) ) return 1;
    return 0;
}

//kopira str2 v str1 do zadadeniq terminator (term) ili \0 
//i vrushta ukazatel kum simvola sled zapetaqta ili \0
char *strcpy_term(char *str1, char *str2, char term)
{
    while( *str2 && (*str2!=term) ) *str1 ++= *str2++;
    *str1 = 0;
    return (*str2) ? ++str2 : str2;
}

//vrushta stoinost na parametur sudurjasht se v str - 
//<atr>=xxx -> return atoi(xxx)
//pri lipsa na parametur vrushta 0
int getattrib(char *str, char atr)
{
    int i,j;
    char tmp[10], *p;
    for(i = 0; str[i]; i++)
    {
        if( (str[i] == atr) && ( str[i+1] == '=') )
        {
            for(j = i + 2; str[j] && (str[j] != ',') && (str[j] != ':'); j++)
            {
                tmp[j - i - 2] = str[j];
            }
            tmp[j - i - 2] = 0;
            return atoi(tmp);
        }
    }
    return 0;
}

void RTTTL_PlayNote(char *str)
{
    int i;
    unsigned int freq=0;
    unsigned int len;
    
    char tmps[10], dotflag = FALSE, diezflag = FALSE;
    int duration, octave, tmoct;
    
    duration    =    DefaultDuration;
    octave        =    DefaultOctave;    
    
    for(i = 0; str[i]; i++) if(str[i] == '.') dotflag = TRUE;
    for(i = 0; str[i]; i++) if(str[i] == '#') diezflag = TRUE;
    
    for(i = 0; str[i]; i++)    if( NoteChar(str[i]) ) break;
    
    if(i != 0)
    {
        strncpy(tmps, str, i);
        tmps[i] = 0;
        duration = atoi(tmps);
    }

    if( dotflag && diezflag )
    {    
            if(validoctave(tmoct = getoctave(str + i + 3))) octave = tmoct;
    } 
    else if( dotflag || diezflag ) 
    {    
            if(validoctave(tmoct = getoctave(str + i + 2))) octave = tmoct;
    } 
    else
    {
            if(validoctave(tmoct = getoctave(str + i + 1))) octave = tmoct;
    }
    
    freq = 0;
    if( !diezflag )
    {    
        switch( str[i] )
        {
            case 'c':       
	        freq = notes[0];
                break;
		
            case 'd':
	        freq = notes[2];
                break;
	      
            case 'e':
	        freq = notes[4];
                break;
		  
            case 'f':
	        freq = notes[5];
                break;
		  
            case 'g':       
	        freq = notes[7];
                break;
		  
            case 'a':
	        freq = notes[9];
                break;
		  
            case 'b':
	        freq = notes[11];
                break;
        }
    } else {
            switch(str[i])
            {
            case 'c':
	        freq = notes[1];
                break;
            case 'd':       
	        freq = notes[3];
                break;
            case 'e':
	        freq = notes[5];
                break;
            case 'f':
	        freq = notes[6];
                break;
            case 'g':
	        freq = notes[8];
                break;
            case 'a':
	        freq = notes[10];
                break;
            case 'b':
	        freq = notes[12];
                break;

            }  
    }
    freq <<= octave - 4;
    len = (60000 / DefaultTempo / duration) * 4;
    if(dotflag) len = len + len / 2;
    PlayTone(freq, len);
    while( !ToneIsComplete() );
}


void RTTTL_Play(char *str)
{
    int i;
    char tmps[20], *p;
    DefaultOctave = 6;
    DefaultTempo = 63;
    DefaultDuration = 4;
    
    if((i = getattrib(str,'o'))) DefaultOctave   = i;
    if((i = getattrib(str,'b'))) DefaultTempo    = i;
    if((i = getattrib(str,'d'))) DefaultDuration = i;
    
    p=strcpy_term(tmps,str, ':');
    while(*p)
    {
        p = strcpy_term(tmps,p,',');
        RTTTL_PlayNote(tmps);
    }
}


