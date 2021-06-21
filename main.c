#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>

int main()
{
	printf("\n");
	/* hostname & username */
	char hostname[100];
	gethostname(hostname, 100);
	char username[100];
	getlogin_r(username, 100);

	/* colors */
	char color_neon[] = "\033[48;5;89;38;5;27m";
	char color_white[] = "\033[00m";
	char color_blue[] = "\033[01;34m";
	char color_green[] = "\033[01;32m";

	/* command, directory & checks */
	char command[256];
	char lscheck[] = "ls";
	char cdcheck[] = "cd";
	char split[] = " ";
	char directory[256];

	/* directory & file sorting*/
	char *type_of(unsigned char type) {
		switch (type) {
			case DT_DIR:
			/* dir color*/
			return color_blue;
			case DT_REG:
			/* file color */
			return color_white;
		}
		/* unknwn file color */
		return color_green;
	}

	/* directory contents */
	DIR *dir;
	struct dirent *contents;
	/* list function for ls command */
	char list() {
		while (contents = readdir(dir)) {
			printf("%s%s  ",type_of(contents->d_type), contents->d_name);
		}
		printf("\n");
		closedir(dir);
	}

	/* commands */
	while(1) {
		char *path = getcwd(directory, 256);
		/* prompt */
		printf("%s%s%s@%s%s:%s%s%s$ ",color_white, color_neon, username, hostname, color_white, color_blue, path, color_white);
		fgets(command, 256, stdin);
		/* removing trailing newline character from fgets */
		char *cmd = strtok(command, "\n");
		/* ls */
		if(strstr(command, lscheck) != NULL) {
			char *arg = strtok(command, split);
			arg = strtok(NULL, split);
			if(arg != NULL) {
				dir = opendir(arg);
				list();
				continue;
			}
			else {
				dir = opendir(".");
				list();
				continue;
			}
		}
		/* cd */
		else if(strstr(command, cdcheck) != NULL) {
			char *arg = strtok(command, split);
			arg = strtok(NULL, split);
			if(arg != NULL) {
				chdir(arg);
				char *cmd = strtok(command, "\n");
				continue;
			}
			else {
				chdir ("/home");
				continue;
			}
		}
		/* whoami */
		else if(strcmp(command,"whoami") == 0) {
			printf("%s\n",username);
			continue;
		}
		/* pwd */
		else if(strcmp(command,"pwd") == 0) {
			getcwd(directory, 256);
			printf ("%s\n", directory);
		}
		/* exit */
		else if(strcmp(command,"exit") == 0) {
			printf("\nexiting...\n");
			break;
		}
		/* checking user input */
		else {
			printf("command '%s' not found\n", command);
			continue;
		}
	}
	return 0;
}
