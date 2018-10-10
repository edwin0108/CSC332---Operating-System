javac *.java &&
jar -cmf Scheduler.mf Scheduler.jar process.class Scheduler.class &&
jar -cmf CPU_Emulator.mf CPU_Emulator.jar process.class CPU_Emulator.class &&
gcc -o init init.c