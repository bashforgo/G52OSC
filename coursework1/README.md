# G52OSC coursework 1
* Grade: 100 / 100
* Comments:
> ## Marks Section
>
> Username: 'bxf03u'  
> Part 1a: 40 from 40  
> Part 1b: 25 from 25  
> Part 1c: 35 from 35  
>
> Total mark without late penalty: 100%  
> Days late: 0  
> Total mark WITH late penalty: 100%  
> Percentage contribution to module (out of 15% for coursework): 15%  
>
> ## Feedback Section
>
> ### Documentation:
> You submitted a documentation file which was useful
>
> #### Part 1a: 40 from 40
>
> ### Compilation:
> Part A compiled successfully
>
> ### Execution:
> Part A ran with no crashes
>
> ### Functionality:
> Your program appears to correctly output the resource counts at the end  
> Your program correctly waits for the user to press ENTER before ending  
> Well done, you correctly protected your resources using entry and exit protocols for your critical sections  
> You appear to have protected your resources correctly, well done  
> You explained well how you have protected your resources, well done.  
> Well done, a critical section was appropriate for use within a threaded client, since the resources are only used within the same process  
> Excellent work at making the locking efficient, well done  
> Your program appeared to run without deadlocking, even though you had correct locking code in there, well done  
> You explained well what you did to try to make the locking efficient  
> You correctly created volatile variables for your counts  
> You seem to have correctly incremented the counts before using each resource  
> You correctly sent windows messages to the server, one message per resource  
> You used PostMessage correctly and made a good case for it, well done  
>
> #### Part 1b: 25 from 25
>
> ### Compilation:
> Part B compiled successfully
>
> ### Execution:
> Part B ran with no crashes
>
> ### Functionality:
> You successfully created two windows  
> You successfully registered two window classes  
> You successfully created two window procedures  
> Each of your windows correctly uses a different window class  
> Your thread progress window appears and shows something  
> Your thread progress window seems to correctly show the progress  
> Your counts of thread activity seem to be correct  
> Your server correctly handles the windows message that the client sends with thread activity information, well done.  
> The thread activity counts are stored correctly.  
> Your resource usage window appears and shows something  
> Your resource usage window seems to correctly show the progress  
> Your counts of resource usage seem to be correct  
> Your server correctly handles the windows message that the client sends with resource usage information, well done.  
> The resource usage counts are stored correctly.  
> Well done, you ensured that your resource counts are always increasing, which fixes the concurrency problem here if messages arrive in the wrong order.  
> Your explanation about how the counts for the Part A client don't need to be protected because they are only ever accessed by the message loop thread was good and clear, well done  
>
> #### Part 1c: 35 from 35
>
> ### Compilation:
> Part C compiled successfully
>
> ### Execution:
> Part C ran with no crashes
>
> ### Functionality:
> You correctly changed the client program to use processes rather than threads, well done  
> Child client processess would not start from a location with spaces in the full path.  File names with spaces have to be quoted in command line.  
> You correctly changed the locking to work across processes  
> Your program correctly avoids deadlocks (as far as we can see)  
> Your resource counts are correctly shared between client processes  
> Your server correctly opens and listens on a socket  
> Your server correctly allows the client to create a connection  
> Your client programs correctly connect to the server  
> Your server correctly handles multiple connections, well done  
> You correctly create the data packets to send to the server side  
> You correctly take apart the packets received on the server side  
> Well done, it was a good idea to handle the sockets information by posting the message to the window within the server  
> Well done, your server can simultaneously handle windows messages and socket connections from clients  
> Your clients can correctly run concurrently  
> You correctly show 10 activity counts in your window  
> Your activity counts which are shown appear to be correct  
> You correctly show 10 resource usage counts  
> Your resource usage counts appear to be shown correctly  
