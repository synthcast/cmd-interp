#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main()
{
	// hostname, username & prompt color
	char hostname[100];
	gethostname(hostname, 100);
	char username[100];
	getlogin_r(username, 100);
	char color1[] = "\033[48;5;89;38;5;27m";
	char color2[] = "\033[00m";

	// command line, directories & checks
	char command[256];
	char lscheck[] = "ls";
	char split[] = " ";
	int files = 0;

	// commands
	while(1) {
	printf("\n%s%s@%s%s: ",color1, username, hostname, color2);
	fgets(command, 256, stdin);
	/* command cleanup */
	char *cmd = strtok(command, "\n");
	/* ls */
	if(strstr(command, lscheck) != NULL && strstr(command, " ") != NULL)  {
	char *arg = strtok(command, split);
	arg = strtok(NULL, split);
	if(arg != NULL) {
	DIR *dir;
	struct dirent *contents;
	dir = opendir(arg);
	while (contents = readdir(dir)) {
	files++;
	printf("%s\n",contents->d_name);
	}
	closedir(dir);
	continue;
	}
	}
	else if(strcmp(command,"ls") == 0){
	DIR *dir;
	struct dirent *contents;
	dir = opendir(".");
	while (contents = readdir(dir)) {
	files++;
	printf("%s\n",contents->d_name);
	}
	closedir(dir);
	continue;
	}
	/* whoami */
	else if(strcmp(command,"whoami") == 0) {
	printf("%s",username);
	continue;
	}
	/* exit */
	else if(strcmp(command,"exit") == 0) {
	printf("\nexiting...\n");
	break;
	}
	/* checking user input */
	else {
	printf("\ncommand '%s' not found\n", command);
	continue;
	} 
   } 
	
return 0;
}

