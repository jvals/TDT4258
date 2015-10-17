
#include <stdint.h>

typedef struct Note{
	uint16_t number;
	uint8_t buffer[];	
} Note;

typedef struct Song{
	uint8_t length;
	Note* notes[];
} Song;

void setDACDATA(Note*, int);
void playSong(Song* song, uint16_t note_length);


extern Song* current_song;
extern uint16_t current_note_length;
extern uint16_t counter;
extern uint16_t note_counter;
extern uint16_t i;

extern Note A3;
extern Note A32;
extern Note A4;
extern Song TEST;
extern Song TEST2;
extern Song TEST3;
extern Song TEST4;