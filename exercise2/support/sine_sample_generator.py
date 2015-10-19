'''
This script uses python version 3
'''

from math import sin,pi

'''
Frequencies for equal-tempered scale, A4 = 440 Hz
http://www.phy.mtu.edu/~suits/notefreq438.html
'''
notes = dict(
C0	= 16.35,
CS0	= 17.32,
Db0	= 17.32,
D0	= 18.35,
DS0	= 19.45,
Eb0	= 19.45,
E0	= 20.60,
F0	= 21.83,
FS0	= 23.12,
Gb0	= 23.12,
G0	= 24.50,
GS0	= 25.96,
Ab0	= 25.96,
A0	= 27.50,
AS0	= 29.14,
Bb0	= 29.14,
B0	= 30.87,
C1	= 32.70,
CS1	= 34.65,
Db1	= 34.65,
D1	= 36.71,
DS1	= 38.89,
Eb1	= 38.89,
E1	= 41.20,
F1	= 43.65,
FS1	= 46.25,
Gb1	= 46.25,
G1	= 49.00,
GS1	= 51.91,
Ab1	= 51.91,
A1	= 55.00,
AS1	= 58.27,
Bb1	= 58.27,
B1	= 61.74,
C2	= 65.41,
CS2	= 69.30,
Db2	= 69.30,
D2	= 73.42,
DS2	= 77.78,
Eb2	= 77.78,
E2	= 82.41,
F2	= 87.31,
FS2	= 92.50,
Gb2	= 92.50,
G2	= 98.00,
GS2	= 103.83,
Ab2	= 103.83,
A2	= 110.00,
AS2	= 116.54,
Bb2	= 116.54,
B2	= 123.47,
C3	= 130.81,
CS3	= 138.59,
Db3	= 138.59,
D3	= 146.83,
DS3	= 155.56,
Eb3	= 155.56,
E3	= 164.81,
F3	= 174.61,
FS3	= 185.00,
Gb3	= 185.00,
G3	= 196.00,
GS3	= 207.65,
Ab3	= 207.65,
A3	= 220.00,
AS3	= 233.08,
Bb3	= 233.08,
B3	= 246.94,
C4	= 261.63,
CS4	= 277.18,
Db4	= 277.18,
D4	= 293.66,
DS4	= 311.13,
Eb4	= 311.13,
E4	= 329.63,
F4	= 349.23,
FS4	= 369.99,
Gb4	= 369.99,
G4	= 392.00,
GS4	= 415.30,
Ab4	= 415.30,
A4	= 440.00,
AS4	= 466.16,
Bb4	= 466.16,
B4	= 493.88,
C5	= 523.25,
CS5	= 554.37,
Db5	= 554.37,
D5	= 587.33,
DS5	= 622.25,
Eb5	= 622.25,
E5	= 659.25,
F5	= 698.46,
FS5	= 739.99,
Gb5	= 739.99,
G5	= 783.99,
GS5	= 830.61,
Ab5	= 830.61,
A5	= 880.00,
AS5	= 932.33,
Bb5	= 932.33,
B5	= 987.77,
C6	= 1046.50,
CS6	= 1108.73,
Db6	= 1108.73,
D6	= 1174.66,
DS6	= 1244.51,
Eb6	= 1244.51,
E6	= 1318.51,
F6	= 1396.91,
FS6	= 1479.98,
Gb6	= 1479.98,
G6	= 1567.98,
GS6	= 1661.22,
Ab6	= 1661.22,
A6	= 1760.00,
AS6	= 1864.66,
Bb6	= 1864.66,
B6	= 1975.53,
C7	= 2093.00,
CS7	= 2217.46,
Db7	= 2217.46,
D7	= 2349.32,
DS7	= 2489.02,
Eb7	= 2489.02,
E7	= 2637.02,
F7	= 2793.83,
FS7	= 2959.96,
Gb7	= 2959.96,
G7	= 3135.96,
GS7	= 3322.44,
Ab7	= 3322.44,
A7	= 3520.00,
AS7	= 3729.31,
Bb7	= 3729.31,
B7	= 3951.07,
C8	= 4186.01,
CS8	= 4434.92,
Db8	= 4434.92,
D8	= 4698.63,
DS8	= 4978.03,
Eb8	= 4978.03,
E8	= 5274.04,
F8	= 5587.65,
FS8	= 5919.91,
Gb8	= 5919.91,
G8	= 6271.93,
GS8	= 6644.88,
Ab8	= 6644.88,
A8	= 7040.00,
AS8	= 7458.62,
Bb8	= 7458.62,
B8	= 7902.13
)

def sine_sample_generator(frequency, sample_rate, amplitude, offset):
	period = sample_rate/frequency
	for i in range(int(period)):
		sample = amplitude * sin( (2.0 * pi * frequency * i) / sample_rate ) + offset
		sample *= 0xff # Scaling to 8 bits?
		yield (int(sample))


def main():
	# Create an empty file
	with open('notes.txt', 'w') as doc:
		print('',file=doc)

	sample_rate = 44100

	for key,value in notes.items():
		frequency = value
		period = sample_rate/frequency

		# h is the string which we will build and later write to file
		h = 'Note ' + key + ' = { ' + str(int(period)) + ', { '

		for sample in sine_sample_generator(frequency, sample_rate, 0.5, 0.5):
			h += str(sample) + ', '

		h = h[:-2] # Remove the last space and comma
		h += '}};'

		# Append the note to the text file we created
		with open('notes.txt', 'a') as doc:
			print(h, file=doc)
			print("", file=doc)

# run
main()