#include "efm32gg.h"
#include "music_theory.h"

Song* current_song;
uint16_t current_note_len;

void setCurrentSong(Song* song, uint16_t note_length) {
	current_song = song;
	current_note_len = note_length;
}

void setDACDATA(Note* n, int offset) {
	*DAC0_CH0DATA = (*n).buffer[offset];
	*DAC0_CH1DATA = (*n).buffer[offset];
}

void playSong(Song* song, uint16_t note_length) {
	setCurrentSong(song, note_length);
	startTimer();
}


