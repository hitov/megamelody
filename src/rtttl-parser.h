#ifndef RTTTL_PARSER_H
#define RTTTL_PARSER_H

typedef struct {
    unsigned int freq;
    unsigned int len;
}play_note_t;

typedef struct {
    char          *buffer;  //rtttl melody buffer
    int           duration;
    int           octave;
    unsigned char DefaultTempo;
    unsigned char DefaultOctave;
    unsigned char DefaultDuration;
}rtttl_handle_t;

#endif