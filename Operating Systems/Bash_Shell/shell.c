// Creating my own shell. At the most, it just parses out the input line.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //fork
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFF 512
#define MAXARGS 100
#define READ  0
#define WRITE 1

void readline();
void run_command();
void execute();
void execute_pipe();
void execute_redirect();


int main(int argc, char* argv[]){
  char *c;
  char* line = malloc(sizeof(char) * BUFF);

  int index = 0;
  int continueLoop = 1;

  while(1){
    // printf("\nmy_shell");

    //check if CTRL D is pressed i.e EOL
    if( continueLoop == 1){
      int index_pipe = -1;
      char* tokens[MAXARGS] = {NULL};

      //used to check if there is a pipe
      int pipe = 0;
      int in_redirect = 0;
      int out_redirect = 0;
      char *in_redirect_arr[MAXARGS] = {NULL};
      char *out_redirect_arr[MAXARGS] = {NULL};

      readline(line, tokens, &continueLoop, &pipe, &index_pipe, &in_redirect, &out_redirect, in_redirect_arr, out_redirect_arr);

      //no pipe so just execute normally
      if(pipe == 0 && in_redirect == 0 && out_redirect == 0){
        execute(tokens);
      }
      else{
        if(in_redirect || out_redirect){
          // printf("redirection\n");
          execute_redirect(tokens,&in_redirect, &out_redirect, in_redirect_arr, out_redirect_arr);
          // printf("\n");
        }
        else{
          // printf("pipe\n");
          execute_pipe(tokens, &pipe, &index_pipe);
        }
      }
    }

    else{
      break;
    }
  }

  return 0;
}

void readline(char *line, char **tokens, int *continueLoop, int *pipe, 
  int *index_pipe, int *in_redirect, int* out_redirect,
  char **in_redirect_arr, char **out_redirect_arr){

  if(fgets(line, BUFF, stdin) != NULL){

      //parseing the line into input
      char* input = malloc(sizeof(char) * BUFF);
      char* word = malloc(sizeof(char) * BUFF);
      int i = 0;
      int j = 0;
      int cmd = 1;
      int location = 0;
      int index_tokens = 0;
      int index_in_redirect = 0;
      int index_out_redirect = 0;
      int in_redir = 0;
      int out_redir = 0;
      // iterate through buffer SIZE
      for(; i < BUFF; i++){

        //check for delimiters
        //took out line[i] == ' '
        if( line[i] == '\n'  || line[i]==' ' || line[i] == '|' || line[i] == '>' || line[i] =='<' || line[i] == '&') {

            // if(line[i] == ' '){
            //   tokens[i] = ' ';
            // }
          //check if input is NOT whitespace
            if(input[0] != 0){

              //check if it is a command
              if(cmd) {
                //turn command off for arguments
                cmd = 0;
                // printf("%s - command\n", input);
                tokens[index_tokens] = malloc(sizeof(char) * BUFF);
                strcpy(tokens[index_tokens], input);
                // printf("inside function: %s\n", tokens[index_tokens]);
                index_tokens++;

                memset(input,0,BUFF);
              }

              //check if argument
              else if(!cmd){
                //turn command on
                cmd = 1;
                // printf("%s - argument\n", input);

                //input redirect
                if(in_redir == 1){ 
                  // printf("in redir\n");

                  in_redirect_arr[index_in_redirect] = malloc(sizeof(char) * BUFF);
                  strcpy(in_redirect_arr[index_in_redirect], input);
                  index_in_redirect++;
                  in_redir = 0;
                }
                //output redirect
                else if(out_redir == 1){
                  // printf("out redir\n");
                  out_redirect_arr[index_out_redirect] = malloc(sizeof(char) * BUFF);
                  strcpy(out_redirect_arr[index_out_redirect], input);
                  index_out_redirect++;
                  out_redir = 0;
                }
                else{
                  // printf("ELSEEEE\n");
                  tokens[index_tokens] = malloc(sizeof(char) * BUFF);
                  strcpy(tokens[index_tokens], input);
                  // printf("inside function: %s\n", tokens[index_tokens]);
                  index_tokens++;
                }
                                //empty string
                memset(input,0,BUFF);
              }
            }

            if(line[i] == '\n'){
              // *tokens = malloc(sizeof(char) * BUFF);
              // strcpy(*tokens, input);
              // // printf("inside function: %s", tokens[0]);
              // *tokens++;
              memset(input,0,BUFF);
              return;
            }
            //print out delimiters
            else if(line[i] == '|'){
              // printf("%c - pipe\n", line[i]);
              cmd = 1;
              (*pipe)++;
              tokens[index_tokens] = 0;
              index_tokens++;
              *index_pipe = index_tokens;
              // printf("%i", *index_pipe);

              // if(*pipe == 1) printf("pipe = 1");
              memset(input,0,BUFF);
            }

            else if(line[i] == '<'){
              // printf("%c - input redirect\n", line[i]);
              cmd = 0;
              in_redir = 1;
              (*in_redirect)++;
              // *index_in_redirect = index_tokens;

            }
            else if(line[i] == '>'){
              // printf("%c - output redirect\n", line[i]);
              cmd = 0;
              out_redir = 1;
              (*out_redirect)++;
            }
            else if(line[i] == '&'){
              // printf("%c -  background\n", line[i]);
            }

          j = 0;
          
          //empty cmd/arg
          memset(input,0,BUFF);
        }

        else{
          // append tokens of the line into the input
          input[j] = line[i];
          j++;
        }
      }
      memset(line, 0, BUFF);
    }

  else {
    *continueLoop = 0;
    printf("%c",'\n');
  }
}

void execute(char **argv)
{
  pid_t pid;
  int status;
  pid = fork(); // fork a new process

  if (pid < 0) // error
  {
    fprintf(stderr, "Fork Failed");
    return;
  }

  //child process
  else if (pid == 0)
  {
    execvp(argv[0], argv);
    perror("error");
    // memset(&argv,0,sizeof(argv));
  }

  //parent
  else{
    while(wait(&status) != pid)
      ;
  }
}

void execute_pipe(char **argv, int *pipes, int *index_pipe){

  // int fd[2*(*pipes)];
  int fd[2];

  pid_t pid;
  int status;
  int index = 0;
  /* create the pipe */
  pipe(fd);

  //initial fork
  if(fork() == 0){
    dup2(fd[READ], READ);
    close(fd[WRITE]);
    execvp(argv[*index_pipe], argv+(*index_pipe));
    perror("execvp error");
  } 
  else if ( (pid = fork()) == 0){
    dup2(fd[WRITE], WRITE);
    close(fd[READ]);
    execvp(argv[0], argv);
    perror("execvp error");
  }
  else{
    waitpid(pid, NULL, 0);

  }
  close(fd[0]);
  close(fd[1]);
  wait(0);
  wait(0);
}

void execute_redirect(char **argv, int *in_redirect, 
  int* out_redirect, char **in_redirect_arr, char **out_redirect_arr){

  pid_t pid;
  int status;
  int in, out;
  pid = fork();
  if(*in_redirect!=0){
    in = open(in_redirect_arr[0], O_RDONLY);
  }
  if(*out_redirect != 0){
    out = open(out_redirect_arr[0],  O_WRONLY|O_TRUNC|O_CREAT, 0644);
  }
  if(pid == 0){
    if(*in_redirect && !*out_redirect){
      dup2(in, 0);
      close(in);
    }
    else if(!*in_redirect && *out_redirect){
      dup2(out,1);
      close(out);
    }
    execvp(argv[0], argv);
    perror("execvp");
  }
  else if(pid > 0){
    while (wait(&status) != -1) ; /* pick up dead children */

  }
}
