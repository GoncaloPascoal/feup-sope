**2. a)** If more than one CTRL-C is sent during the SIGINT handler, only one of them will be processed. 
**b)** The program terminates after receiving the SIGTERM signal, even if inside the SIGINT handler (since the sleep function is interrupted).
**c)** After receiving a SIGTERM signal, the corresponding handler runs and the sigint handler finishes execution (since, once again, the sleep function is interrupted).

**4. a)** Since the `wait` call only frees one of the child processes from its zombie state, if the tasks executed by the parent are longer than the tasks executed by the children, as is the case, some children can remain in a zombie state for a large amount of time before they are freed by the parent. Also, the parent process will hang on the `wait` call until a child exits if none of its children have finished execution.  
**c)** When we type CTRL-C in the shell, the SIGINT signal is sent to all processes in the active process group, so both the parent and its children terminate. When we send SIGINT to the parent process from another terminal window, only the parent will receive the signal and finish execution. The children will then become orphan processes until the init process becomes their parent.

**5. b)** Since signals received while the program is inside the signal handler aren't processed, if multiple child processes exit at around the same time, only calling `wait` once might mean that some of them remain in a zombie state. It is therefore better to call `waitpid` with `WNOHANG` until there are no changes to the state of the child processes.

**6.** The `SIGKILL` signal is used to terminate the process because it is impossible to install a handler for it, so we know for sure that the process will terminate when it is received.