#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main()
{
	// hostname and username
	char hostname[100];
	gethostname(hostname, 100);
	char username[100];
	getlogin_r(username, 100);
	// command line, directories & checks
	char command[256];
	char lscheck[] = "ls";
	char split[] = " ";
	int files = 0;
	
	// commands
	while(1) {
	printf("\n%s@%s: ",username, hostname);
	fgets(command, 256, stdin);
	if(strstr(command, lscheck) != NULL) {
	char *arg = strtok(command, split);
	char *arg2 = arg;
	arg2 = strtok(NULL, split);
	arg2 = strtok(arg2, "\n");
	if(arg2 != NULL) {
	DIR *dir;
	struct dirent *contents;
	dir = opendir(arg2);
	while (contents = readdir(dir)) {
	files++;
	printf("%s\n",contents->d_name);
	}
	closedir(dir);
	continue;
	}
	else {
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
	}
	else if(strcmp(command,"whoami") == 0) {
	printf("%s",username);
	continue;
	}
	else if(strcmp(command,"exit") == 0) {
	printf("\nthank you for trying nOS\n");
	break;
	}
	else {
	printf("\ncommand '%s' not found\n", command);
	continue;
	} 
   } 
	
return 0;
}

