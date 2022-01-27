/* (1) minishell.c          */
/* (2) Patel Aryan ( 201901021 ) */

/* (3) appropriate includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

pid_t pid; // global variable for the child process ID

int main()
{

  printf("$ minishell\n");
  while (1)
  {
    /* ==== DO NOT MODIFY ANY OF THESE DECLARATIONS ============ */
    char cmdline[1024];  // the entire minishell command line
    int num_tokens = 0;  // number of tokens on the minishell command line
    char tokens[3][256]; // an array of the tokens
    int i = 0;           // just a counter
    char *p;             // pointer for stepping thru tokens
                         /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

    /* (4) Print the minishell prompt: */
    printf("IE411> ");

    /* ==== DO NOT MODIFY THIS NEXT SECTION OF CODE ============ */
    /* This reads an entire line from stdin: */
    if (fgets(cmdline, 1024, stdin) == NULL)
    {
      printf("\n");
      break;
    }

    // This replaces the newline at the end of the string with a NULL
    *strrchr(cmdline, '\n') = '\0';

    // extract the individual tokens from the minishell command line
    p = cmdline;
    while (1 == sscanf(p, " %s", tokens[i]))
    {
      p = strstr(p, tokens[i]) + strlen(tokens[i]);
      // printf("%s",tokens[i]);
      ++i;
    }
    num_tokens = i;
    /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    // printf("%d", num_tokens);

    /* (5) Handle the case where there were no tokens on the
     * minishell command line, i.e., maybe the user just
     * hit the ENTER key:
     */
    if (num_tokens == 0)
    {
      continue;
    }

    /* (6) Handle the case where something OTHER than "mmame" */
    /*     was entered on the minishell command line:         */

    /* (7) Something valid entered on the command line, gotta fork */

    pid = fork();

    /* (8) Handle the case where the fork failed: */
    if (-1 == pid)
    {
      printf("Process Failed ..,\n");
      exit(1);
    }

    /* (9) Code that the parent executes: */
    else if (0 != pid)
    {
      //printf("hello from parent\n");
      // wait for the command to finish if "&" is not present
      waitpid(pid, NULL, 0);
    }

    /* (10) Code that the child executes: */
    else
    {
      /*      Part 1: mmame     */
      char buff[FILENAME_MAX]; //create string buffer to hold path
      getcwd(buff, FILENAME_MAX);

      strcat(buff, "/");
      strcat(buff, tokens[0]);

      execl(buff, buff, NULL);
      printf("minishell : %s : command not found\n", tokens[0]);
    }
    continue;
  }
  return 0;
}