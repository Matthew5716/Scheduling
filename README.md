Lab 2 - Matthew Martinez, Wei Zhong Tee, Simon Arneberg

# Compiling and Running Program
To compile make sure you are in the directory with all the source code files.
Then run "make schedule". Then to run use command ./schedule. Once the Process 
is running follow command line prompts and enter input as desired.

# Real Time Details
For the real time scheduler the algorithm we used was to always put the 
process with the earliest deadline first on the CPU. If there was multiple processes that
had this deadline then the process with Minimum slack would obtain the cpu first. For real time
the statistics printed are only for completed processes.

#MFQS Details
The MFQS algorithms was implemented as specified. However our scheduler still takes in I/O
offset from user rather than just doing I/0 on last clock tick before burst.