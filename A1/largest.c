#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2048


int main(int argc, char **argv){
	char *line = NULL;
	size_t len = MAX;
	if(getline(&line, &len, stdin) == -1){
		fprintf(stderr, "Error : no input is inserted");
		return(1);
	}
	int max = 0;
	char name[31];
	if(argc == 1){
		while(getline(&line, &len, stdin) != -1){
			line[strlen(line) - 1] = '\0';
			char *pch;
			pch = strtok(line, " ");
			if(strncmp(&pch[0], "d",1)!=0 && strncmp(&pch[4], "r",1)==0){
				int i;
				for(i = 0; i < 4;i++){
					pch = strtok(NULL, " ");
				}
				if(atoi(pch) >= max){
					max = atoi(pch);
					for(i = 0; i < 4;i++){
						pch = strtok(NULL, " ");
					}
					strcpy(name, pch);
				}
			}
		}
		fprintf(stdout,"%d	%s\n",max, name);
	}
	else if(argc == 3){
		while(getline(&line, &len, stdin) != -1){
			line[strlen(line) - 1] = '\0';
			char *pch;
			pch = strtok(line, " ");
			if(strncmp(&pch[0], "d",1) != 0 && strncmp(&pch[4], "r",1) == 0){
				int i;
				for(i = 0; i < 3;i++){
					pch = strtok(NULL, " ");
				}
				if(strncmp(pch, argv[2],sizeof(argv[2])) == 0){
					pch = strtok(NULL, " ");
					if(atoi(pch) > max){
						max = atoi(pch);
						for(i = 0; i < 4;i++){
							pch = strtok(NULL, " ");
						}
						strcpy(name, pch);
					}
				}

			}
		}
		fprintf(stdout,"%d	%s\n",max, name);
	}
	return 0;
}