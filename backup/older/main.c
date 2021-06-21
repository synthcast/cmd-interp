#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>

int main()
{
	// hostname, username & prompt color
	char hostname[100];
	gethostname(hostname, 100);
	char username[100];
	getlogin_r(username, 100);
	/* neon */
	char color1[] = "\033[48;5;89;38;5;27m";
	/* white */
	char color2[] = "\033[00m";
	/* blue */
	char color3[] = "\033[01;34m";
	/* green */
	char color4[] = "\033[01;32m";

	// command line, directories & checks
	char command[256];
	char lscheck[] = "ls";
	char cdcheck[] = "cd";
	char split[] = " ";
	int files = 0;
	char directory[256];

	// directory and file color
	char *type_of(unsigned char type) {
	switch (type) {
	case DT_DIR:
	/* dir (blue) */
	return color3;
	case DT_REG:
	/* file (white) */
	return color2;
	}
	/* unknwn (green) */	
	return color4;
	}
	
	// directory contents
	DIR *dir;
        struct dirent *contents;
	/* list function for ls command (read, print, close) */
	char list() {
	while (contents = readdir(dir)) {
        printf("%s%s  ",type_of(contents->d_type), contents->d_name);
	}
	closedir(dir);
	}
	
	// commands
	while(1) {
	char *path = getcwd(directory, 256);
        char *bname = basename(path);
	printf("\n%s%s%s@%s%s: %s%s%s$ ",color2, color1, username, hostname, color2, color3, bname, color2);
	fgets(command, 256, stdin);
	/* removing trailing newline character from fgets */
	char *cmd = strtok(command, "\n");
	/* ls */
	if(strstr(command, lscheck) != NULL && strstr(command, " ") != NULL)  {
	char *arg = strtok(command, split);
	arg = strtok(NULL, split);
	if(arg != NULL) {
	dir = opendir(arg);
       	list();
	continue;
	}
	}	
	else if(strcmp(command,"ls") == 0){
	dir = opendir(".");
	list();	
	continue;
	}
	/* cd */
	else if(strstr(command, cdcheck) != NULL && strstr(command, " ") != NULL)  {
        char *arg = strtok(command, split);
        arg = strtok(NULL, split);
        if(arg != NULL) {
	chdir(arg);
	char *cmd = strtok(command, "\n");
	continue;
	}
	}
	else if(strcmp(command,"cd") == 0) {
	chdir("/home");
	continue;
	}
	/* whoami */
	else if(strcmp(command,"whoami") == 0) {
	printf("%s",username);
	continue;
	}
	/* pwd */
	else if(strcmp(command,"pwd") == 0) {
	char directory[256];
	getcwd(directory, 256);
	printf ("%s", directory);
	}
	/* exit */
	else if(strcmp(command,"exit") == 0) {
	printf("\nexiting...\n");
	break;
	}
	/* checking user input */
	else {
	printf("command '%s' not found", command);
	continue;
	} 
     } 
return 0;
}

