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
	// command line & directories
	char command[256];
	int files = 0;
	
	// commands
	while(1) {
	printf("\n%s@%s: ",username, hostname);
	scanf("%s",command);
	if(strcmp(command,"ls") == 0) {
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

