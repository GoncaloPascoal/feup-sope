**1. b)** Since the memory location of the variable is passed as the argument of `thrfunc`, using the same variable for both threads means that both of them will print 2 (the second value of the variable). 

**2.** The number of characters printed is usually larger than N, possibly due to synchronization problems with the two threads (one of the threads reads the value of the global variable before it is updated by the other thread).
