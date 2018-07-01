
// EC440 OPERATING SYSTEMS PROJECT1 <BASH SHELL>
// BYOUNGSUL LEE 2017.09.27
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>



void execute();
void piping();
void redirect1();
void redirect2();

int main(){

	

	int index = 0; // token index variable
	int count = 0; // keeps track of where the counter is in the string 
	char word[32]; // char array to save the tokens
    int tokindex = 0;
	char cmd[1024]; 
	char current; //current charater
    char* tokens[100] = {NULL};
    int pipeindex[5];
    int pindex = 0;
    char file[32];
    
    //BOOLEAN VARIABLES FOR STATES
	
    int command = 0;
    int first = 1; // first command
	int argument = 0;
    int prevDeli = 0;
    
    int pipeE = 0;
    int redirect1E,re1 = 0;
    int redirect2E,re2 = 0;
    int backgroundE = 0;
    

	while(1) //while loop untill Ctrl-D is pressed (not yet)
	{
        
		//printf("my_shell:");

		if(fgets(cmd, 512 , stdin)== NULL) // CTRL + D : terminates the program EOF
        {
            
            break;
        }
        
        
		current = cmd[count]; 

		while(current != '\0') //loops untill current reaches the end of the string 
    	{
        	
        	if( (current != '|') && (current != '&') && (current != '<') && (current != '>') && (current != ' ') && (cmd[count+1] != '\0' )  )
        	{
        		word[index] = current;
        		index++;
                prevDeli = 0;
        	}

			

			else

			{	
                
                
                if(first == 1 && word[0] == '\0')
                    break;
                
                
                if(prevDeli == 0) // detects if the prev character was a delimeter (fix to an error)
                {
				
                    if (cmd[count+1] == '\0') // stores the last ch (fix to a error)
                    {
                        word[index] = current;

                    }

                    if ((first == 1 && command ==0 && argument != 1 ) || command ==1  )
                    {
                        
                        char temp[32];
                        
                        int a = 0;
                        
                        //for (a = 0; a < index  ; a++)
                            //printf("%c" ,word[a]);
                        
                        int b = 0;
                        for (b = 0; b < index  ; b++)//bug fix (filters out the \n at the end)
                            temp[b]=word[b];
                        
                        
                        //tokens[tokindex] = word;
                        tokens[tokindex] = malloc(sizeof(char) * 512);
                        strcpy(tokens[tokindex], temp);
                        tokindex++;
                        memset(temp,0,32);
                        //printf(" - command\n");
                        
                        argument = 1;
                        command = 0;
                        
                        
                    }
				
                    else if ( argument == 1 && first != 1 && command != 1)
                    {
                        
                        
                        char temp2[32];
                        int c =0;
                        //for (c = 0; c < index ; c++)
                            //printf("%c",word[c]);
                        
                        int d = 0;
                        for (d = 0; d < index  ; d++) //bug fix (Filters out the \n at the end
                            temp2[d]=word[d];

                        if(redirect1E ==1)
                        {
                            int f = 0;
                            for ( f; f < index  ; f++) //bug fix (Filters out the \n at the end
                                file[f]=word[f];
                            
                            redirect1E =0;
                            redirect2E =0;
                        }
                        
                        if(redirect1E == 0)
                        {
                        
                            tokens[tokindex] = malloc(sizeof(char) * 512); // allocate memory for the token
                            strcpy(tokens[tokindex], temp2); //copy the token string into the string array
                            tokindex++;// increment the index of the
                        }
                        //printf(" - argument\n" );
                        memset(temp2,0,32);
                        argument = 0;
                        
                        
                     
                    }
                }
                
                int d =0;
                for (d =0 ;d<32;d++)// clears the word array for the next paramemter (memsei)
					word[d]=0;
                
                if(current == '|')
				{
					//printf("| - pipe\n" );

					command = 1;
                    argument = 0;
                    
                    tokens[tokindex] = NULL;
                    pipeindex[pindex] = tokindex;
                    
                    pindex++;
                    
                    tokindex++;
                    
                    pipeE = 1;
					
				}

				if (current == '&')
				{
					//printf("& - background\n" );
                    
				}
				
				if (current == '<')
				{
					//printf("< - input redirect\n" );
					argument = 1;
                    command = 0;
                    
                    redirect1E =1;
                    re1 =1;
                    
				}

				if (current == '>')
				{
					//printf("> - output redirect\n" );
					argument = 1;
                    command = 0;
                    
                    redirect1E =1;
                    redirect2E =1;
                    re2=1;
				}



				
                prevDeli = 1;
				index = 0 ; // word index to 0
				first = 0; // not the first parameter anymore
                
                

			}
            
            
            count++; // increment position

        	current = cmd[count];
            
            
		}//done with string
        
        //printf("check pipeE is = %d", pipeE);
        
        if(pipeE == 0 && backgroundE == 0 && re1 == 0 && re2 ==0)
            execute(tokens);
        if(pipeE == 1)
            piping(tokens,pipeindex);
        if(re1 == 1 && re2== 0)
            redirect1(tokens,file);
        if(re2 == 1 && re1 ==0)
            redirect2(tokens,file);


        memset(pipeindex,0,5);
        memset(tokens, 0, 100);
        memset(cmd,0,1024);
        
        
        
		// setting all the states to initial state
        first = 1;
        command = 0;
        argument = 0;
        count = 0;
        prevDeli = 0;
        tokindex = 0;
        pindex = 0;
        redirect2E =0;
        redirect1E =0;
        re1=0;
        re2=0;
        pipeE =0;
        
    	
        
        }
	
	
}




void  execute(char **arguments)
{
    
    pid_t  pid;
    int status;
    pid = fork(); // fork a child process
    

    
    if(pid < 0)
   {
       fprintf(stderr, "Fork Process Failed!");
        return;
   }
    if(pid == 0) //child
    
    {
        execvp(arguments[0], arguments);
        perror("ERROR: execvp");
        //memset(&arguments,0,sizeof(arguments));
    }
    
    else
    {
        while(wait(&status)!= pid);
            
    }
    
}



void piping(char** argument1, int* index)
{
    int fds[2]; // input and ouput of a pipe
    
    pipe(fds); // make a pipe
    
    pid_t pid;
    


    
    if (fork() == 0) // Child 1
    {
        
        dup2(fds[0], 0);
        
        close(fds[1]);
        
        
        execvp(argument1[*index+1], argument1+(*index+1));
        perror("ERROR: execvp");
        
    }
    
    else if ((pid = fork()) == 0) // Child 2
    {
        dup2(fds[1], 1);
        
        close(fds[0]);
        
        execvp(argument1[0], argument1);
        perror("ERROR: execvp");

    }
    else // parent Process 
    {
        
        waitpid(pid, NULL, 0);
       
    
    }
    close(fds[0]);
    close(fds[1]);
    
    
}

void redirect1(char ** command, char* filename)
{
    int in;
    
    
    pid_t  pid;
    int status;
    pid = fork();
    
    //printf("In R1 function\n");
    if(pid < 0)
    {
        fprintf(stderr, "Fork Process Failed!");
        return;
    }
    
    else if(pid == 0) //child
    {
        in = open(filename, O_RDONLY);
        
        dup2(in,0);
        close(in);
        
        execvp(command[0], command);

    }
    
    else
    {
        while(wait(&status)!= -1);

        
    }
    
    
    
    
}

void redirect2(char** command , char*  filename)
{
    int out;
    int status;
    pid_t  pid;
    pid = fork();
    
    if(filename != 0)
        out = open(filename, O_WRONLY | O_TRUNC | O_CREAT,0644);
    
    if(pid < 0)
    {
        fprintf(stderr, "Fork Process Failed!");
        return;
    }
    
    if(pid == 0) //child
    {
        
        
        dup2(out,1);
       
        close(out);
        
        execvp(command[0], command);
        perror("ERROR: execvp");
        
        
    }
    
    else if(pid > 0)
    {
        while(wait(&status)!= pid);
        
    }
    
    
    
}
