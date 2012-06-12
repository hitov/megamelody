#!/usr/bin/python

from math import *

N=256;
Fck=10000000;
print "#include <avr/pgmspace.h>"
print "#define	sine_N	",N
print "unsigned char sine_tbl [sine_N] PROGMEM = {"

for i in range(0,N-1):
	print int(round(127+127*sin(2*pi*i/N))), ",";
print int(round(127+127*sin(2*pi*(N-1)/N)));
print "};"

#	c,c#,d,d#,e,e#(f),f#,g,g#,a,a#,b,b#
notes = [261,277,294,311,330,349,370,392,415,440,466, 494, 523];
print "unsigned char notes_tbl[] = {"
#8*N_samples*f*510/Fck
for freq in notes:
	print 8*N*freq*510/Fck, ",";
print "};"
