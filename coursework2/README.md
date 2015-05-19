# G52OSC coursework 2
* Grade: 93 / 100
* Comments:
> Username: bxf03u  
> Code compiles: OK  
> Code working: OK  
>
> ## Requirement 1 (fork):
>
> ### Implementation:  
> Configurable #childprocesses: OK  
> Correct #processes: OK  
> Process indexes: OK  
> Fork return value (pid < 0): OK  
> Child return/break/exit: OK  
> Return/exit used: OK  
> Efficiency of code: OK  
> Additional remarks/feedback: "The number of processes is configurable through a constant in the code or specifiable on the command line. The number of child processes that is generated is equal to the configured number. I.e., the child processes are prevented from continuing the loop of the parent process by using a return/break/exit statement. Indexes have been allocated to the individual child processes and are used for logging their times. The return value of the fork call is correctly validated (pid < 0) A return/break/exit statement was added at the end of the child processes to prevent the child process from continuing execution of the parent code. A return/exit statement was used to terminate the child processes.The code for the process creation is generally well written. "  
>
> ## Requirement 2 (wait):
>
> ### Implementation:  
> Wait call syntax: OK  
> Wait call location: OK  
> Wait for every child: OK  
> Additional remarks/feedback: "The syntax used for the wait call is correct. The wait calls are located outside the main process creation loop, and only carried out by the parent process. I.e., only the parent process waits for the termination of the child processes.The wait method is called for every child process. I.e., the parent process will only terminate if all child processes have finished, as requested."  
>
> ## Requirement 3 (time):
>
> ### Implementation:  
> Base time: OK  
> Child time calculation: OK  
> Stopping criterion: OK  
> Time logging data structure: OK  
> Time logging: NOK  
> Additional remarks/feedback: "The base time is set with the parent process and the same timestamp is shared between the different child processes. I.e., all child processes log their times relative against the same base time.The calculation of the child timings is correct. The stopping criterion is implemented and works as expected. I.e., all processes finish after the pre-specified amount of time. An appropriate data structure was used to keep track of the process times. The logging of the CPU times is not functioning as expected. This often means that the time value may exceed the bounds of the array before the loop is terminated."  
>
> ### Output:  
> CSV provided: OK  
> CSV correctness: OK  
> Graph provided: OK  
> Graph correctness: OK  
>
> ## Requirement 4 (Affinity):
>
> ### Implementation:  
> Correct affinity call made: OK  
> Correct location for affinity call: OK  
> Additional remarks/feedback: "The syntax used for setting the CPU affinity is correct. The CPU affinity is correctly set in the parent process. I.e. the CPU affinity is set once for the parent process, and hence all child processes inherit it. "  
>
> ### Output:  
> CSV provided: OK  
> CSV correctness: OK  
> Graph provided: OK  
> Graph correctness: OK  
>
> ## Requirement 5 (Priority):
>
> ### Implementation:  
> Correct priotity call made: OK  
> Correct location for priority call: OK  
> Priority set for every child: OK  
> Additional remarks/feedback: "The syntax used for setting the process priority is correct. The process priority is set within the code for the child process only. Hence, the priority of the parent process remains unaffected. The process priority is correctly set for each of the individual child processes. "  
>
> ### Output:  
> CSV provided : OK  
> CSV correctness: OK  
> Graph provided: OK  
> Graph correctness: OK  
>
> ## Requirement 6 (exec):
>
> ### Implementation:  
> Correct exec call made: OK  
> Correct location for exec call: NOK  
> Exec call only for one child: OK  
> Additional remarks/feedback: "The syntax used for over-writing the parent code is correct. The exec/system call may be located in a place where it is executed by both the parent and the child processes, or by multiple child processes. It may overwrite the parent process, or the exec call may be located in a place where it only gets executed after all child processes have finished. The correct location for the exec call is after the creation of the child processes and before the wait calls are executed. Only then will al the child processes be listed in the output. The exec call is carried out only once. "  
>
> ### Output:  
> TXT provided: OK  
> TXT correctness: OK  
>
> ## Requirement 7 (SVG):
>
> ### Implementation:
> SVG file in correct format: OK  
> SVG code efficient: OK  
>
> ## Requirement 8 (SVG):
>
> ### Output:  
> TIMINGS 1 provided: OK  
> TIMINGS 1 correctness: OK  
> TIMINGS 2 provided: OK  
> TIMINGS 2 correctness: OK  
> TIMINGS 3 provided: OK  
> TIMINGS 3 correctness: OK  
> TIMINGS 4 provided: OK  
> TIMINGS 4 correctness: OK  
> TIMINGS 5 provided: OK  
> TIMINGS 5 correctness: OK  
> TIMINGS 6 provided: OK  
> TIMINGS 6 correctness: OK  
>
> General remarks:
> Mark: 9.3
