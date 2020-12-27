/*
  Name: Inara Rupani
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 12     // Mav shell only supports ten arguments

int main()
{
    char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
    int i;
    
    //array that stores the past history commands
    char *history[15];
    
    //array that stores pids from the processors
    //used when user enter showpids
    int arrayPids[15];
    int arraycount=0;
    
    //listing all the commands into the history array  and initializing the showpids array
    //reopulating the elements in the history array if the counter exceed 15 elements
    for(i=0; i<15; i++)
    {
        history[i]=(char*)malloc(1024);
        memset(history[i],0,1024);
        arrayPids[i]=0;
    }
    
    while (1)
    {
        printf("msh> ");
        static int count = 0;
        while(!fgets(cmd_str,MAX_COMMAND_SIZE,stdin));
        strncpy(history[count++],cmd_str,strlen(cmd_str));
        
        //prompts msh input line again if user enters empty input
        if(strcmp(cmd_str, "\n") == 0)
        {
            continue;
        }
        
        //setting the counter to 0 if user commands exceeds 15
        else if(count==15)
        {
            count=0;
        }
        
        else if(count>=15)
        {
            count=0;
        }
        
        //re-run the nth command (history) that user entered
        else if(cmd_str[0]=='!')
        {
            int index=atoi(&cmd_str[1]);
            //fill the block if memory with particluar value (0)
            //till number of bytes to be filled starting from cmd_str to be filled
            memset(cmd_str,0,255);
            //reading the command from history array
            strncpy(cmd_str, history[index], strlen(history[index]));
        }
        
        char *token[MAX_NUM_ARGUMENTS];
        int token_count = 0;
        
        // Pointer to point to the token
        // parsed by strsep
        char *arg_ptr;
        char *working_str  = strdup( cmd_str );
        
        // we are going to move the working_str pointer so
        // keep track of its original value so we can deallocate
        // the correct amount at the end
        char *working_root = working_str;
        
        // Tokenize the input stringswith whitespace used as the delimiter
        while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&
               (token_count<MAX_NUM_ARGUMENTS))
        {
            token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
            if( strlen( token[token_count] ) == 0 )
            {
                token[token_count] = NULL;
            }
            token_count++;
        }
        
        //exits with 0
        if((strcmp(token[0], "exit"))==0 || (strcmp(token[0], "quit"))==0)
        {
            exit(0);
        }
        
        //changes directory
        else if(strcmp(token[0], "cd") == 0)
        {
            chdir(token[1]);
        }
        
        //prints the last 15 commads entered by user
        else if(strcmp(token[0], "history")==0)
        {
            int i;
            for(i=0;i<15;i++)
            {
                printf("%d: %s\n",i,history[i]);
            }
        }
        
        //printing 15 processors spawed by the shell
        else if(strcmp(token[0],"showpids")==0)
        {
            int i;
            for(i=0;i<15;i++)
            {
                printf("%d: %d\n",i,arrayPids[i]);
            }
        }
        
        else
        {
            //creating a child from the parent
            pid_t pid = fork();
            
            //storing the child in arraypids
            arrayPids[arraycount++]=pid;
            
            //rewrites the showpids array if exceed 14
            if(arraycount>14)
            {
                arraycount=0;
            }
            
            //if the pid is child then it executes all the basic commands
            //if the user inputs invalid command it notifies user and goes to next line
            if(pid==0)
            {
                int ret=execvp(token[0],token);
                if(ret==-1)
                {
                    printf("%s: Command not found\n\n",token[0]);
                }
                exit(EXIT_SUCCESS);
            }
            
            else
            {
                int status;
                wait(&status);
            }
        }
        free (working_root);
    }
}
