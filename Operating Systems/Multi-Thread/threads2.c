#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <setjmp.h>
#include <sys/time.h>
#include <stdint.h>
#include <alloca.h>
#include <semaphore.h>




void schedule();
static int ptr_mangle(int p);
void signal_handler();
void lock();
void unlock();
void pthread_exit_wrapper();
int pthread_join();
int sem_init();

// Thread Control Block 
struct TCB{

	jmp_buf BUFFER;

	pthread_t TID; // Thread ID

	int state; // 0 = dead 1 = ready 2 = running 3= blocked

	int RegPC; // pointer for program counter
	int RegStack; //pointer for stack pointer

	unsigned long int* stack;
	void* exitreturn;
	int initial;
	pthread_t jointhread;
	

};

struct sema
{
	int value;

	void* semaptr;

	int semainitial ;

	int semacount ;
	int semafront ;
	int semaback ;


};

struct sema sem1;

//CREATE THREAD

//struct sema sema_storage[128];

int semaQ[128];





int isFull() {
   return sem1.semacount == 128;
}

void insert(int data) {

   if(!isFull()) {
	
      if(sem1.semaback == 127) {
         sem1.semaback = -1;            
      }       

      semaQ[++sem1.semaback] = data;
      sem1.semacount++;
   }
}

int removeData() {
   int data = semaQ[sem1.semafront++];
	
   if(sem1.semafront == 128) {
      sem1.semafront = 0;
   }
	
   sem1.semacount--;
   return data;  
}


struct TCB tcb_storage[128]; 

const int THREADLIMIT = 128; // MAX THREADS

int threadtracker = 0; // CRURRENT RUNNING THREAD

int threadIDcounter = 1;// How many did the user make?

int first = 1; //for main thread creation

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
{

	

	if(threadIDcounter == THREADLIMIT ) //EXCEEDS thread limit returns -1
	{
		return -1;
	}

	attr = NULL;

	// Setting thread ID
	
    *thread =  threadIDcounter; 

    tcb_storage[threadIDcounter].TID = threadIDcounter;
    
	//tcb_storage[threadIDcounter].joincount =0;
	// Setting Stack 

	tcb_storage[threadIDcounter].stack = malloc(32767); // allocate memory

	tcb_storage[threadIDcounter].stack[8190] = (unsigned long int) arg; // Increment stack pointer and store arg

	tcb_storage[threadIDcounter].stack[8189] = (unsigned long int) pthread_exit_wrapper; //same (Decrement)

	//PTR mangle ( into tcb )
	//setjmp(tcb_storage[threadIDcounter].BUFFER);

	tcb_storage[threadIDcounter].RegPC = ptr_mangle((int) start_routine);		
	tcb_storage[threadIDcounter].RegStack = ptr_mangle((int) (tcb_storage[threadIDcounter].stack + 8189)); //Point to pthread exit

	//tcb_storage[threadtracker].BUFFER[0].__jmpbuf[4] = tcb_storage[threadtracker].RegStack;
    //tcb_storage[threadtracker].BUFFER[0].__jmpbuf[5] = tcb_storage[threadtracker].RegPC;

	//END of setting stack

	tcb_storage[threadIDcounter].initial  = 1; // When the thread is made we need to modify jmp buffers
	tcb_storage[threadIDcounter].state = 1; // THREAD READY

	threadIDcounter++; 
	
	if(first)
     {
     	if(!setjmp(tcb_storage[0].BUFFER)) // For main thread creation
     	{	
     		first = 0;

     		tcb_storage[0].TID = 0;  //MAIN thread will always be 0
     		tcb_storage[0].state = 1; // Ready
     		tcb_storage[0].stack = NULL; // Main has its own stack

     		schedule(); // 50ms timer and sig_handle
     		//signal_handler();

     	}
     }
     
			

     
	return 0;


}

void signal_handler()
{	

	if (!setjmp(tcb_storage[threadtracker].BUFFER))  //setjump called directly 
	{	
		// Look for a ready thread (Round Robin)
		do
		{
			threadtracker++;
			if(threadtracker >= threadIDcounter) // If the tracker reaches 128 , resets
			{
				threadtracker =0;
			}

		}while(tcb_storage[threadtracker].state != 1 );
         
        
        if(tcb_storage[threadtracker].initial == 1) // Only done first time
        {
        	// MODIFY JUMP BUFFERS 

         	tcb_storage[threadtracker].BUFFER[0].__jmpbuf[4] = tcb_storage[threadtracker].RegStack;
         	tcb_storage[threadtracker].BUFFER[0].__jmpbuf[5] = tcb_storage[threadtracker].RegPC;

         	tcb_storage[threadtracker].initial = 0;
        }
        

       
        longjmp(tcb_storage[threadtracker].BUFFER, 1); //LONG JUMP to nxt thread 
    	
    }

    else // called by longjump
    {

    }

    return;

}

void schedule()
{
	struct sigaction signal;
    signal.sa_handler = signal_handler; //SIG HANDLE FOR TIMER
    signal.sa_flags = SA_NODEFER;
    sigaction(SIGALRM, &signal, 0);
    

    ualarm(50000, 50000); //50ms

    return;
}




void pthread_exit(void *value_ptr)
{

	tcb_storage[threadtracker].state = 0; //Thread killed 



	tcb_storage[tcb_storage[threadtracker].jointhread].state  = 1;
	tcb_storage[threadtracker].exitreturn = value_ptr;

	free(tcb_storage[threadtracker].stack); 
	
	
	//threadIDcounter--;
	
	//Proceed to next thread
	signal_handler(); // next thread
	return;

}


pthread_t pthread_self(void)
{
	return tcb_storage[threadtracker].TID;
}


void lock()
{
    sigset_t block;
    sigemptyset(&block);
	sigaddset(&block, SIGALRM);
	//sigaddset(&block, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &block, NULL);
    
}

void unlock()
{
    sigset_t block;
    sigemptyset(&block);
	sigaddset(&block, SIGALRM);
	//sigaddset(&block, SIGRTMIN);
	sigprocmask(SIG_UNBLOCK, &block, NULL);
}

int pthread_join(pthread_t thread, void **value_ptr) 
{
	if(tcb_storage[thread].state != 0)
	{
	
		tcb_storage[threadtracker].state = 3;
	
		tcb_storage[thread].jointhread = threadtracker;

	
		signal_handler();

		if(value_ptr != NULL)
			*value_ptr = tcb_storage[thread].exitreturn;
	}
	//schedule();

	return 0;

}

void pthread_exit_wrapper()
{
          unsigned int res;
          asm("movl %%eax, %0\n":"=r"(res));
          pthread_exit((void *) res);
}




int sem_init(sem_t *sem, int pshared, unsigned value)
{	


	pshared = 0;

	sem1.value =value;

	sem->__align = &sem1;

	sem1.semainitial = 1;

	sem1.semacount = 0;
	sem1.semafront  = 0;
	sem1.semaback = -1;

	
	return 0;
}

int sem_wait(sem_t *sem)
{
	if(sem1.value > 0 )
	{
	  sem1.value--;
	}
	else
	{
	  insert(threadtracker);
	  tcb_storage[threadtracker].state = 3;
	}
	
}

int sem_post(sem_t *sem)
{
	sem1.value++;

	int popthread = removeData();

	//tcb_storage[popthread].state=1;
	
}

int sem_destroy(sem_t *sem)
{
	sem1.semainitial = 0;
}

static int ptr_mangle(int p) {
           unsigned int ret;
           asm(" movl %1, %%eax;\n"
               " xorl %%gs:0x18, %%eax;"
               " roll $0x9, %%eax;"
               " movl %%eax, %0;"
           : "=r"(ret)
           : "r"(p)
           : "%eax"
           );
return ret; 
}


