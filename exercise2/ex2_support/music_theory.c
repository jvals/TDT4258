#include "efm32gg.h"
#include "music_theory.h"
#include "timer.h"
#include "dac.h"

Song* current_song = &TEST;
uint16_t counter = 0;
uint16_t current_note_length = 0xFFF;
uint16_t note_counter = 0;
uint16_t i = 0;

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
	setupDAC();
}


Note A3 = { 200, { 127, 131, 135, 139, 143, 147, 151, 155, 159, 162, 166, 170, 174, 178, 181, 185, 188, 192, 195, 199, 202, 205, 208, 211, 214, 217, 220, 222, 225, 228, 230, 232, 234, 237, 239, 240, 242, 244, 245, 247, 248, 249, 250, 251, 252, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 253, 252, 252, 251, 250, 248, 247, 246, 244, 243, 241, 239, 237, 235, 233, 231, 228, 226, 223, 220, 218, 215, 212, 209, 206, 203, 199, 196, 193, 189, 186, 182, 178, 175, 171, 167, 163, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 104, 100, 96, 92, 89, 85, 81, 77, 74, 70, 67, 63, 60, 56, 53, 50, 47, 44, 41, 38, 35, 32, 30, 27, 25, 22, 20, 18, 16, 14, 12, 10, 9, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 7, 8, 9, 11, 13, 15, 16, 19, 21, 23, 25, 28, 30, 33, 36, 39, 41, 44, 48, 51, 54, 57, 61, 64, 68, 71, 75, 78, 82, 86, 90, 94, 97, 101, 105, 109, 113, 117, 121 } };

Note A32 = { 200, { 0,4,7,11,15,18,22,25,29,33,36,40,43,47,50,54,58,61,65,68,72,75,78,82,85,89,92,96,99,102,106,109,112,115,119,122,125,128,131,134,137,140,143,146,149,152,155,158,161,164,166,169,172,174,177,180,182,185,187,190,192,194,197,199,201,203,205,208,210,212,214,216,218,219,221,223,225,226,228,230,231,233,234,235,237,238,239,240,242,243,244,245,246,247,247,248,249,250,250,251,251,252,252,253,253,253,254,254,254,254,254,254,254,254,254,253,253,253,252,252,251,251,250,250,249,248,247,247,246,245,244,243,242,240,239,238,237,235,234,233,231,230,228,226,225,223,221,219,218,216,214,212,210,208,205,203,201,199,197,194,192,190,187,185,182,180,177,174,172,169,166,164,161,158,155,152,149,146,143,140,137,134,131,128,125,122,119,115,112,109,106,102,99,96,92,89,85,82,78,75} };

Note A4 = { 100, { 127, 135, 143, 151, 159, 166, 174, 181, 188, 195, 202, 208, 214, 220, 225, 230, 234, 239, 242, 245, 248, 250, 252, 253, 254, 254, 254, 254, 252, 251, 248, 246, 243, 239, 235, 231, 226, 220, 215, 209, 203, 196, 189, 182, 175, 167, 160, 152, 144, 136, 128, 120, 112, 104, 96, 89, 81, 74, 67, 60, 53, 47, 41, 35, 30, 25, 20, 16, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 2, 3, 5, 8, 11, 15, 19, 23, 28, 33, 39, 44, 51, 57, 64, 71, 78, 86, 94, 101, 109, 117 } };



Song TEST = {40, {&A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3 ,&A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3 ,&A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3 ,&A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3, &A3}};

Song TEST2 = {40, {&A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32 ,&A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32 ,&A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32 ,&A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32, &A32}};

Song TEST3 = {40, {&A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4 ,&A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4 ,&A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4 ,&A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4, &A4}};

Song TEST4 = {40, {&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3,&A32,&A4,&A3}};