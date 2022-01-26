/* (1) filename          */
/* (2) last name, first name */

/* (3) appropriate includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

char *argv[16];
pid_t pid; // global variable for the child process ID

int main()
{
  while( 1 )
  {
/* ==== DO NOT MODIFY ANY OF THESE DECLARATIONS ============ */
    char cmdline[1024];  // the entire minishell command line
    int  num_tokens = 0; // number of tokens on the minishell command line
    char tokens[3][256]; // an array of the tokens
    int i = 0;           // just a counter
    char *p;             // pointer for stepping thru tokens
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

    /* (4) Print the minishell prompt: */
    printf("IE411> ");
    

/* ==== DO NOT MODIFY THIS NEXT SECTION OF CODE ============ */
    /* This reads an entire line from stdin: */
    if( fgets( cmdline, 1024, stdin ) == NULL ) { printf("\n"); break; }

    // This replaces the newline at the end of the string with a NULL
    *strrchr( cmdline, '\n') = '\0';

    // extract the individual tokens from the minishell command line
    p = cmdline;
    while( 1 == sscanf( p, " %s", tokens[i] ) )
    {
      p = strstr( p, tokens[i] ) + strlen( tokens[i] );
      // printf("%s",tokens[i]);
      ++i;
    }
    num_tokens = i;
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    printf("%d", num_tokens);
    
    /* (5) Handle the case where there were no tokens on the
     * minishell command line, i.e., maybe the user just
     * hit the ENTER key:
     */
    if(num_tokens == 0)
    {
      printf("\n");
      continue;
    }

    /* (6) Handle the case where something OTHER than "mmame" */
    /*     was entered on the minishell command line:         */
    if (num_tokens == 1)
    {
      // char *myinp = tokens[i];
      printf("%s\n",tokens[0]);

      // char buf[10];

      // while (read(0, buf, sizeof(buf)) > 0)
      // {
      //   // read() here read from stdin charachter by character
      //   // the buf[0] contains the character got by read()
      //   printf("%s ",buf);
      //   buf.free();
      // }

      char *ptr;
      i = 0;
      ptr = strtok(tokens[0], " ");
      while (ptr != NULL)
      {
        //printf("%s\n", ptr);
        argv[i] = ptr;
        i++;
        ptr = strtok(NULL, " ");
      }

      // // check for "&"
      if (!strcmp("&", argv[i - 1]))
      {
        argv[i - 1] = NULL;
        argv[i] = "&";
      }
      else
      {
        argv[i] = NULL;
      }

      pid = fork();
      if (-1 == pid)
      {
        printf("failed to create a child\n");
      }
      else if (0 == pid)
      {
        printf("hello from child\n");
        // execute a command
        execvp(argv[0], argv);
      }
      else
      {
        // printf("hello from parent\n");
        // wait for the command to finish if "&" is not present
        if (NULL == argv[i])        
          waitpid(pid, NULL, 0);
        break;
      }
      continue;
    }

    /* (7) Something valid entered on the command line, gotta fork */

    /* (8) Handle the case where the fork failed: */
    if( -1 == -1 )
    {
      exit( 1 );
    } 

    /* (9) Code that the parent executes: */ 
    if( 0 !=  0 )
    {
      int status;
      // parent waits for child (mmame) to terminate
    }

    /* (10) Code that the child executes: */
    else
    {
      /* (11) The child must handle these cases: */
      /*      Part 1: mmame                      */
      /*      Part 2: mmame   filename           */
      /*      Part 3: mmame < filename           */
      /*      Part 4: mmame > filename           */
    }

  }
  return 0;
}
