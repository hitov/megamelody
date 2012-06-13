v 20110115 2
C 40000 40000 0 0 0 title-B.sym
C 47000 43100 1 0 0 ATmega8-SMD.sym
{
T 47100 47900 5 10 0 0 0 0 1
footprint=SO8
T 49300 47700 5 10 1 1 0 6 1
refdes=U1
T 47100 48700 5 10 0 0 0 0 1
device=ATmega8
}
C 46400 48700 1 90 0 connector6-2.sym
{
T 43600 49600 5 10 1 1 180 6 1
refdes=J1
T 43550 49000 5 10 0 0 90 0 1
device=CONNECTOR_6
T 43350 49000 5 10 0 0 90 0 1
footprint=SIP6N
}
N 44400 48700 44400 44100 4
N 44400 44100 47000 44100 4
N 44800 48700 44800 43900 4
N 44800 43900 47000 43900 4
N 45200 48700 45200 43700 4
N 45200 43700 47000 43700 4
N 45600 48700 45600 48000 4
N 50100 45200 49600 45200 4
C 46200 48600 1 180 0 generic-power.sym
{
T 46000 48350 5 10 1 1 180 3 1
net=Vcc
}
N 46000 48700 46000 48600 4
C 43900 48400 1 90 0 generic-power.sym
{
T 43650 48600 5 10 1 1 90 3 1
net=GND
}
N 43900 48600 44000 48600 4
N 44000 48600 44000 48700 4
C 45900 43200 1 0 0 crystal-1.sym
{
T 46100 43700 5 10 0 0 0 0 1
device=CRYSTAL
T 46100 43500 5 10 1 1 0 0 1
refdes=Q1
T 46100 43900 5 10 0 0 0 0 1
symversion=0.1
}
N 46600 43300 47000 43300 4
N 45900 43300 45900 43500 4
N 45900 43500 47000 43500 4
C 46100 42400 1 90 0 capacitor-1.sym
{
T 45400 42600 5 10 0 0 90 0 1
device=CAPACITOR
T 45600 42600 5 10 1 1 90 0 1
refdes=C1
T 45200 42600 5 10 0 0 90 0 1
symversion=0.1
}
C 46800 42400 1 90 0 capacitor-1.sym
{
T 46100 42600 5 10 0 0 90 0 1
device=CAPACITOR
T 46300 42600 5 10 1 1 90 0 1
refdes=C2
T 45900 42600 5 10 0 0 90 0 1
symversion=0.1
}
C 46100 42200 1 180 0 generic-power.sym
{
T 45900 41950 5 10 1 1 180 3 1
net=GND
}
C 46800 42200 1 180 0 generic-power.sym
{
T 46600 41950 5 10 1 1 180 3 1
net=GND
}
N 45900 42400 45900 42200 4
N 46600 42400 46600 42200 4
C 49800 48700 1 180 0 resistor-2.sym
{
T 49400 48350 5 10 0 0 180 0 1
device=RESISTOR
T 49500 49000 5 10 1 1 180 0 1
refdes=C3
}
N 48900 48600 46000 48600 4
N 49800 48600 50100 48600 4
N 50100 48600 50100 45200 4
C 50100 48400 1 0 0 capacitor-1.sym
{
T 50300 49100 5 10 0 0 0 0 1
device=CAPACITOR
T 50400 48900 5 10 1 1 0 0 1
refdes=C4
T 50300 49300 5 10 0 0 0 0 1
symversion=0.1
}
C 51100 48800 1 270 0 generic-power.sym
{
T 51350 48600 5 10 1 1 270 3 1
net=GND
}
N 51100 48600 51000 48600 4
C 50400 44200 1 270 0 generic-power.sym
{
T 50650 44000 5 10 1 1 270 3 1
net=Vcc
}
N 49600 44000 50400 44000 4
C 53300 47400 1 90 0 capacitor-1.sym
{
T 52600 47600 5 10 0 0 90 0 1
device=CAPACITOR
T 52800 47600 5 10 1 1 90 0 1
refdes=C5
T 52400 47600 5 10 0 0 90 0 1
symversion=0.1
}
C 54200 47400 1 90 0 capacitor-1.sym
{
T 53500 47600 5 10 0 0 90 0 1
device=CAPACITOR
T 53700 47600 5 10 1 1 90 0 1
refdes=C6
T 53300 47600 5 10 0 0 90 0 1
symversion=0.1
}
C 52900 48300 1 0 0 generic-power.sym
{
T 53100 48550 5 10 1 1 0 3 1
net=Vcc
}
C 53800 48300 1 0 0 generic-power.sym
{
T 54000 48550 5 10 1 1 0 3 1
net=Vcc
}
C 53300 47400 1 180 0 generic-power.sym
{
T 53100 47150 5 10 1 1 180 3 1
net=GND
}
C 54200 47400 1 180 0 generic-power.sym
{
T 54000 47150 5 10 1 1 180 3 1
net=GND
}
N 45600 48000 50100 48000 4
C 44100 44000 1 0 1 mosfet-with-diode-1.sym
{
T 43200 44500 5 10 0 0 0 6 1
device=NPN_TRANSISTOR
T 43200 44500 5 10 1 1 0 6 1
refdes=T1
}
C 45800 44400 1 0 0 resistor-2.sym
{
T 46200 44750 5 10 0 0 0 0 1
device=RESISTOR
T 46000 44700 5 10 1 1 0 0 1
refdes=R1
}
N 46700 44500 47000 44500 4
N 45800 44500 44100 44500 4
C 43500 47300 1 180 0 speaker-2.sym
{
T 41600 44400 5 10 0 0 180 0 1
device=SPEAKER
T 42900 45300 5 10 1 1 180 0 1
refdes=SPK1
}
N 43500 45400 43500 45000 4
C 43300 47600 1 0 0 generic-power.sym
{
T 43500 47850 5 10 1 1 0 3 1
net=+12V
}
C 43600 46700 1 90 0 resistor-2.sym
{
T 43250 47100 5 10 0 0 90 0 1
device=RESISTOR
T 43300 47100 5 10 1 1 90 0 1
refdes=R2
}
N 43500 46700 43500 46600 4
C 43700 43500 1 180 0 generic-power.sym
{
T 43500 43250 5 10 1 1 180 3 1
net=GND
}
N 43500 44000 43500 43500 4
C 54200 44300 1 0 1 lm7805-1.sym
{
T 52600 45600 5 10 0 0 0 6 1
device=7805
T 52800 45300 5 10 1 1 0 0 1
refdes=U2
}
C 56100 44600 1 0 1 pwrjack-1.sym
{
T 56000 45100 5 10 0 0 0 6 1
device=PWRJACK
T 56100 45100 5 10 1 1 0 6 1
refdes=J2
}
N 55200 44900 54200 44900 4
N 55200 43800 55200 44700 4
N 51800 43800 55200 43800 4
N 53400 44300 53400 43800 4
C 52200 44800 1 270 0 capacitor-4.sym
{
T 53300 44600 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 52700 44000 5 10 1 1 0 0 1
refdes=C7
T 52900 44600 5 10 0 0 270 0 1
symversion=0.1
}
C 54600 44800 1 270 0 capacitor-4.sym
{
T 55700 44600 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 54700 44100 5 10 1 1 180 0 1
refdes=C8
T 55300 44600 5 10 0 0 270 0 1
symversion=0.1
}
C 54500 43900 1 90 0 capacitor-1.sym
{
T 53800 44100 5 10 0 0 90 0 1
device=CAPACITOR
T 53900 44000 5 10 1 1 0 0 1
refdes=C9
T 53600 44100 5 10 0 0 90 0 1
symversion=0.1
}
C 52000 43900 1 90 0 capacitor-1.sym
{
T 51300 44100 5 10 0 0 90 0 1
device=CAPACITOR
T 51500 44100 5 10 1 1 180 0 1
refdes=C10
T 51100 44100 5 10 0 0 90 0 1
symversion=0.1
}
N 51800 43800 51800 43900 4
N 52400 43900 52400 43800 4
N 52600 44900 51800 44900 4
N 51800 44900 51800 44800 4
N 52400 44800 52400 44900 4
N 54300 44800 54300 44900 4
N 54800 44800 54800 44900 4
N 54300 43900 54300 43800 4
N 54800 43900 54800 43800 4
C 51600 44900 1 0 0 generic-power.sym
{
T 51800 45150 5 10 1 1 0 3 1
net=Vcc
}
C 54600 44900 1 0 0 generic-power.sym
{
T 54800 45150 5 10 1 1 0 3 1
net=+12V
}
