
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
    int redirect1E = 0;
    int backgroundE = 0;
    
    
    while(1) //while loop untill Ctrl-D is pressed (not yet)
    {
        memset(tokens, 0, 100);
        printf("my_shell>");
        
        if(fgets(cmd, 512 , stdin)== NULL) // CTRL + D : terminates the program
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
                        
                        
                        for (int i = 0; i < index  ; i++)
                            printf("%c" ,word[i]);
                        
                        for (int i = 0; i < index  ; i++)//bug fix (filters out the \n at the end)
                            temp[i]=word[i];
                        
                        
                        //tokens[tokindex] = word;
                        tokens[tokindex] = malloc(sizeof(char) * 512);
                        strcpy(tokens[tokindex], temp);
                        tokindex++;
                        
                        printf(" - command\n");
                        
                        argument = 1;
                        command = 0;
                        
                        memset(temp,0,32);
                        
                    }
                    
                    else if ( argument == 1 && first != 1 && command != 1)
                    {
                        
                        
                        /*char temp2[32];
                        
                        for (int i = 0; i < index ; i++)
                            printf("%c",word[i]);
                        for (int i = 0; i < index  ; i++) //bug fix (Filters out the \n at the end
                            temp2[i]=word[i];
                        
                        if(redirect1E ==1)
                        {
                            for (int i = 0; i < index  ; i++) //bug fix (Filters out the \n at the end
                                file[i]=word[i];
                            
                            redirect1E =0;
                        }
                        
                        if(redirect1E == 0)
                        {
                            
                            tokens[tokindex] = malloc(sizeof(char) * 512); // allocate memory for the token
                            strcpy(tokens[tokindex], temp2); //copy the token string into the string array
                            tokindex++;// increment the index of the
                        }
                        printf(" - argument\n" );
                        
                        argument = 0;*/
                        
                        
                        
                    }
                }
                
                
                
                
                if(current == '|')
                {
                    printf("| - pipe\n" );
                    
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
                    printf("& - background\n" );
                    
                }
                
                if (current == '<')
                {
                    printf("< - input redirect\n" );
                    argument = 1;
                    command = 0;
                    
                    redirect1E =1;
                    
                }
                
                if (current == '>')
                {
                    printf("> - output redirect\n" );
                    argument = 1;
                    command = 0;
                    
                }
                
                
                
                
                prevDeli = 1;
                index = 0 ; // word index to 0
                first = 0; // not the first parameter anymore
                
                
                
            }
            
            
            count++; // increment position
            
            current = cmd[count];
            
            
        }//done with string
        
        if(pipeE == 0 && backgroundE == 0 && redirect1E == 0)
            execute(&tokens);
        /*if(pipeE == 1)
            piping(tokens,pipeindex);
        if(redirect1E == 1)
            redirect1(tokens,file);*/
        
        memset(pipeindex,0,5);
        memset(tokens, 0, 100);
        memset(cmd,0,1024);
        
        for(int a =0; a < 100 ; a++)
        {
            tokens[a]=NULL;
            if( a== 99)
            {
                printf("done\n");
                printf("what the hell = %s\n",tokens[0]);
            }
        }
        
        // setting all the states to initial state
        first = 1;
        command = 0;
        argument = 0;
        count = 0;
        prevDeli = 0;
        tokindex = 0;
        pindex = 0;
        
        
        
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
    
    else if(pid == 0) //child
        
    {
        printf("token 1 is = %s and token 2 is = %s \n",arguments[0],arguments[1]);
        execvp(arguments[0], arguments);
        perror("error");
        
    }
    
    else
    {
        while(wait(&status)!= pid);
        
    }
    
}



/*void piping(char** argument1, int* index)
{
    int pipefd[2]; // input and ouput of a pipe
    int pid;
    char* tokens2[100] = {NULL};
    int yay = 0 ;
    
    for(int i = index[0] ; i < 50 ; i++) // Creates a new array for child
    {
        tokens2[yay]= argument1[i+1];
        yay++;
    }
    
    pipe(pipefd); // make a pipe
    
    pid = fork(); // fork the process
    
    
    if (pid == 0) // child gets the strings after the pipe
    {
        dup2(pipefd[0], 0);
        
        close(pipefd[1]);
        
        execvp(argument1[index[0]+1], tokens2);
    }
    else // parents gets the first command and the first argument
    {
        dup2(pipefd[1], 1);
        
        close(pipefd[0]);
        
        execvp(argument1[0], argument1);
        
    }
    
}

void redirect1(char ** command, char* filename)
{
    int in;
    
    
    pid_t  pid;
    int status;
    pid = fork();
    
    
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
        while(wait(&status)!= pid);
        
    }
    
    
    
    
}*/
