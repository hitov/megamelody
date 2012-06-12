extern unsigned char notes_tbl[];

void ToneGenInit (void);

void PlayTone(unsigned int freq,unsigned int len);
char ToneIsComplete(void);
void StopGen(void);
