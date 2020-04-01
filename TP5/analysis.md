**6. a)** The writer program waits for reader to open a FIFO and writes three
strings, separated by 3 second intervals. The reader reads the strings until
the FIFO is closed.

**6. b)** When the FIFO is closed by the writer process, the `read` call
returns zero, therefore no more characters are read and the `readLine` call
also returns zero, which breaks the loop in `main`.

If we open the FIFO with the `O_RDWR` flag in the reader process, it will never
terminate since the write end of the FIFO is never closed.
