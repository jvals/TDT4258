
#include <stdint.h>

typedef struct Note{
	uint16_t number;
	uint8_t buffer[];	
} Note;

typedef struct Song{
	uint8_t length;
	Note* notes[];
} Song;


void playSong(Song* song, uint16_t note_length);

extern Note A4;