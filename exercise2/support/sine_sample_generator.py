'''
This script uses python version 3
'''

from math import sin,pi
from notes import notes

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