
#include <stdint.h>

typedef struct Note{
	uint16_t number;
	uint16_t buffer[];	
} Note;

typedef struct Song{
	uint16_t length;
	Note* notes[];
} Song;

void setDACDATA(Note*, int);
void playSong(Song* song, uint16_t note_length);


extern Song* current_song;
extern uint16_t current_note_length;
extern uint16_t counter;
extern uint16_t note_counter;
extern uint16_t i;


extern Song LisaWentToSchoolSchool;
extern Song MarioAttempt;
extern Song Winner1;
extern Song Melody;
extern Song Winner2;
extern Song WellDone;
extern Song Loser;