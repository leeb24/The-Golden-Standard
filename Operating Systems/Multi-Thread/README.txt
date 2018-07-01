
First off, I created a TCB structure that will store the ID of the thread , state , jump buffer , storage for program counter and stack pointer. 

When the Pthread create is initially run, the function creates two diffrent threads. One of them being the main thread and the actual thread. When the thread is being made I set the ID as a integer and malloc the space for the stack.
After that, I access the stack space and store the arguments and pthread exit for automatic completion.
The process of making a main thread is a bit different beacause it will have its own stack space that we dont allocate.
When schedule is called , 50ms timer will activate to start the rotation of the threads. If the alarm goes off, it will automatically call the signal_handler function to setjump the current thread and find the next ready thread to jump to.
When the program long jumps to the next thread it will return to the the point where the thread setjumped before and resume its process. (If the process is done it will pthread exit)
One of the problem that I came across was the pthread exit portion.
When I tried to decrement the amount of thread that the user made, it fails multiple test cases.


// For Project3

For Pthread join, the purpose of the function was to make a target thread run without being interrupted to quit it’s process in the middle. So I created a new state in my TCB “BLOCKED” which is 3. The original thread which called the pthread join will be blocked until the target thread is done with it’s process. When the target thread is done, the original thread will be unblocked and resume it’s process.
For semaphore, I created a struct containing the value of the semaphore and a pointer for linking the sem_t __align with the custom semaphore structure. 
When the sem_wait happens, the value of the semaphore decrements as the resource is being used. When the value reaches 0, the thread ID is pushed into the queue since the resource is currently all occupied.
In sem_post, the thread is freeing up resource for other threads to use. The value of the semaphore is incremented and the queue pops off the head thread to indicate that resource is readily available. 

