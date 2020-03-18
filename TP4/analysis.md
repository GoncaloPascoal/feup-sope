**2. a)** If more than one CTRL-C is sent during the SIGINT handler, only one of them will be processed. 
**b)** The program terminates after receiving the SIGTERM signal, even if inside the SIGINT handler (since the sleep function is interrupted).
**c)** After receiving a SIGTERM signal, the corresponding handler runs and the sigint handler finishes execution (since, once again, the sleep function is interrupted).
