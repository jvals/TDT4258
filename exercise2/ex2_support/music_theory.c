#include "efm32gg.h"
#include "music_theory.h"
#include "timer.h"

Song* current_song = &TEST;
uint16_t counter = 0;
uint16_t current_note_length = 0x24FF;
uint16_t note_counter = 0;

void setCurrentSong(Song* song, uint16_t note_length) {
	current_song = song;
	current_note_length = note_length;
}

void setDACDATA(Note* n, int offset) {
	*DAC0_CH0DATA = (*n).buffer[offset];
	*DAC0_CH1DATA = (*n).buffer[offset];
}

void playSong(Song* song, uint16_t note_length) {
	setCurrentSong(song, note_length);
	startTimer();
}


Note A3 = { 200, { 127, 131, 135, 139, 143, 147, 151, 155, 159, 162, 166, 170, 174, 178, 181, 185, 188, 192, 195, 199, 202, 205, 208, 211, 214, 217, 220, 222, 225, 228, 230, 232, 234, 237, 239, 240, 242, 244, 245, 247, 248, 249, 250, 251, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 253, 252, 252, 251, 250, 248, 247, 246, 244, 243, 241, 239, 237, 235, 233, 231, 228, 226, 223, 220, 218, 215, 212, 209, 206, 203, 199, 196, 193, 189, 186, 182, 178, 175, 171, 167, 163, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 104, 100, 96, 92, 89, 85, 81, 77, 74, 70, 67, 63, 60, 56, 53, 50, 47, 44, 41, 38, 35, 32, 30, 27, 25, 22, 20, 18, 16, 14, 12, 10, 9, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 7, 8, 9, 11, 13, 15, 16, 19, 21, 23, 25, 28, 30, 33, 36, 39, 41, 44, 48, 51, 54, 57, 61, 64, 68, 71, 75, 78, 82, 86, 90, 94, 97, 101, 105, 109, 113, 117, 121 } };

Song TEST = {2, {&A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3}};