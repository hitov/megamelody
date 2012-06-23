all: megamelody
	echo "all"
megamelody: board.pcb
	echo "make $@"

board.pcb: footprints
	gsch2pcb project

footprints:
	footgen/footgen.py footgen/footprint-atmega8gfp.des
	footgen/footgen.py footgen/footprint-sip.des

#clean:
#	rm -f pcb/*.net
#	rm  pcb/*.pcb
#	rm -f pcb/*.cmd