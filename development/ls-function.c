#include <stdio.h>
#include <string.h>
#include <dirent.h>
int main()
{
	while(1) {
	char str[256];
	fgets(str, 256, stdin);
	int files = 0;
	char check[] = "ls";
	if (strstr(str, check) != NULL) {
	
	char split[] = " ";
	char *arg = strtok(str, split);
    	char *arg2 = arg;
	//printf("\n%s", arg);
	arg2 = strtok(NULL, split);
	arg2 = strtok(arg2, "\n");
	if(arg2 != NULL) {
	printf("%s", arg2);
	
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
	}
   }

return 0;
}

