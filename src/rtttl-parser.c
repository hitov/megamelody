#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtttl-parser.h"

#define DEFAULT_OCTAVE   (6)
#define DEFAULT_TEMPO    (63)
#define DEFAULT_DURATION (4)

#ifdef notes_tbl

unsigned char *notes = notes_tbl;

#else

unsigned int notes[] =     {
                //c,sc#,d,d#,e,e#(f),f#,g,g#,a,a#,b,b#
                261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523
            };

#endif

//kopira str2 v str1 do zadadeniq terminator (term) ili \0 
//i vrushta ukazatel kum simvola sled zapetaqta ili \0
char *strcpy_term(char *str1, char *str2, char term)
{
    while( *str2 && (*str2 != term) ) *str1 ++= *str2++;
    *str1 = 0;
    return (*str2) ? ++str2 : str2;
}

char *str_chr(char *str, char chr)
{
    while( *str && (*str != chr) ) str++;
    return str;
}

char *str_chr_term(char *str, char chr, char term)
{
    while( *str && (*str != chr) ) 
    {
        str++;
	if (*str == term) return NULL;
    }
    if (*str == '\0') return NULL;
    return str;
}

char *str_pbrk(char *str, char *brks)
{
    int i;
    while( *str )
    {
        for(i = 0; brks[i]; i++)
	{
	    if(*str == brks[i]) return str;
	}
        str++;
    }
    return NULL;
}

int atoi10_term(char *ptr, char *terms)
{
    int  val = 0, mul = 1;
    char *rev;
    rev = str_pbrk(ptr, terms);
    
    if(rev == ptr) return 0;
    
    rev--;
    
    while(rev >= ptr)
    {
        val += (*rev-- - '0') * mul;
        mul *= 10;
    }
    return val;
}

int atoi10_digits(char *ptr)
{
    int  val = 0, mul = 1;
    char *rev = ptr;
    
    while( *rev && ( *rev >= '0' && *rev <= '9' ) ) rev++;
    
    if(rev == ptr) return 0; 
    
    rev--;
    
    while(rev >= ptr)
    {
        val += (*rev-- - '0') * mul;
        mul *= 10;
    }
    return val;
}

int getattrib(char *str, char atr)
{
    char *ptr = str;
    do {
        ptr = str_chr(ptr, atr);
    }while( *ptr && (*(ptr + 1) != '=') );
    
    if(*ptr) ptr += 2;
    return atoi10_term(ptr, " ,:\t");
}

char is_note_char(char c)
{
    if( (( c >= 'a') && ( c <= 'g')) || (c == 'p') ) return 1;
    return 0;
}

char validoctave(int oct)
{
    if( (oct >= 4) && (oct <= 8) ) return 1;
    return 0;
}

char *find_note(char *ptr, char term)
{
    while(*ptr)
    {
        if(is_note_char(*ptr)) return ptr;
	if(*ptr == term) return ptr + 1;
        ptr++;
    }
}

void rtttl_parser_init(rtttl_handle_t *rtttl_hdl, char *str)
{
    int i;
    rtttl_hdl->DefaultTempo    = DEFAULT_TEMPO;
    rtttl_hdl->DefaultOctave   = DEFAULT_OCTAVE;
    rtttl_hdl->DefaultDuration = DEFAULT_DURATION;
 
    if((i = getattrib(str,'o'))) rtttl_hdl->DefaultOctave   = i;
    if((i = getattrib(str,'b'))) rtttl_hdl->DefaultTempo    = i;
    if((i = getattrib(str,'d'))) rtttl_hdl->DefaultDuration = i;
    
    rtttl_hdl->buffer = str_chr(str, ':');
    if(rtttl_hdl->buffer) rtttl_hdl->buffer++;
}

char *rtttl_get_next_note(rtttl_handle_t *rtttl_hdl, play_note_t *note)
{
    char dotflag = 0, diezflag = 0;
    char *ptr;   
    int  tmoct; 
    
    rtttl_hdl->DefaultOctave   = DEFAULT_OCTAVE;
    rtttl_hdl->DefaultDuration = DEFAULT_DURATION;
    
    if(str_chr_term(rtttl_hdl->buffer, '.', ',')) dotflag = 1;
    if(str_chr_term(rtttl_hdl->buffer, '#', ',')) diezflag = 1;
    
    ptr = rtttl_hdl->buffer;
    
    rtttl_hdl->buffer = find_note(rtttl_hdl->buffer, ',');
    
    if(ptr < rtttl_hdl->buffer)
    {
        rtttl_hdl->DefaultDuration = atoi10_digits(ptr);
    }
    
    if( dotflag && diezflag )
    {    
        tmoct = atoi10_digits(rtttl_hdl->buffer + 3);
    } 
    else if( dotflag || diezflag ) 
    {    
        tmoct = atoi10_digits(rtttl_hdl->buffer + 2);
    } 
    else
    {
        tmoct = atoi10_digits(rtttl_hdl->buffer + 1);
    }
    
    if(validoctave(tmoct)) rtttl_hdl->DefaultOctave = tmoct;
    
    note->freq = 0;

    if( !diezflag )
    {    
        switch( *rtttl_hdl->buffer )
        {
            case 'c':       
	        note->freq = notes[0];
                break;
		
            case 'd':
	        note->freq = notes[2];
                break;
	      
            case 'e':
	        note->freq = notes[4];
                break;
		  
            case 'f':
	        note->freq = notes[5];
                break;
		  
            case 'g':       
	        note->freq = notes[7];
                break;
		  
            case 'a':
	        note->freq = notes[9];
                break;
		  
            case 'b':
	        note->freq = notes[11];
                break;
        }
    } else {
            switch(*rtttl_hdl->buffer)
            {
            case 'c':
	        note->freq = notes[1];
                break;
            case 'd':       
	        note->freq = notes[3];
                break;
            case 'e':
	        note->freq = notes[5];
                break;
            case 'f':
	        note->freq = notes[6];
                break;
            case 'g':
	        note->freq = notes[8];
                break;
            case 'a':
	        note->freq = notes[10];
                break;
            case 'b':
	        note->freq = notes[12];
                break;
            }  
    }
    
    note->freq <<= rtttl_hdl->DefaultOctave - 4;
    note->len = ( 60000 / rtttl_hdl->DefaultTempo / rtttl_hdl->DefaultDuration) * 4;
    if(dotflag) note->len = note->len + note->len / 2;
    
    printf("octave = %d\n", rtttl_hdl->DefaultOctave);
    
    rtttl_hdl->buffer = str_pbrk(rtttl_hdl->buffer, ",");
    if(rtttl_hdl->buffer) rtttl_hdl->buffer++;
    
    return rtttl_hdl->buffer;
}

#define str     "d=4,o=6,b=140:8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e,8c,8e4,8c7"

int main()
{
    rtttl_handle_t rtttl_hdl;
    play_note_t note;
    
    printf("o = %d\n", getattrib(str, 'o'));
    printf("d = %d\n", getattrib(str, 'd'));
    printf("b = %d\n", getattrib(str, 'b'));
    
    rtttl_parser_init(&rtttl_hdl, str);
    
    while(rtttl_get_next_note(&rtttl_hdl, &note))
    {
        printf("%d %d \n", note.freq, note.len);
    }
    
    return 0;
}

#if 0
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

#endif
