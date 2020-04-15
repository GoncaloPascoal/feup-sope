**1. b)** Since the memory location of the variable is passed as the argument of `thrfunc`, using the same variable for both threads means that both of them will print 2 (the second value of the variable). 

**2.** The number of characters printed is usually larger than N, possibly due to synchronization problems with the two threads (one of the threads reads the value of the global variable before it is updated by the other thread).

**3. a)** Since the address of the variable t is passed, a thread may print their hello message after the value of t is altered, which leads to the observed output.  
**b)** Allocate memory for a copy of the t variable and pass that to the thread instead.  
**c)** If `exit` is used in the main function instead of `pthread_exit`, the hello message of the last thread isn't printed since the program finishes execution.
