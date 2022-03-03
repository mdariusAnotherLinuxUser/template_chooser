#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv){

	int chosenId;
	int id = 0;
	int templateDescriptor;
	DIR *folder;
	//getting the home folder path
	char *homeFolderName = getenv("HOME");
	
	char *TemplatesFolderName = "/Templates/";

	char *path = malloc(strlen(homeFolderName) + strlen(TemplatesFolderName));
	strcat(path,homeFolderName);
	strcat(path,TemplatesFolderName);

	char *pathPlusName = { 0 };
	struct dirent *dirent;
	folder = opendir(path);
	int destinationDescriptor;
	char *destinationPathPlusName = { 0 };
	char ch;
	int bytes;
	while((dirent = readdir(folder))){
		
		if(strcmp(dirent->d_name,".") && strcmp(dirent->d_name,"..") ){
			if(argc == 1){
				
				printf("%d --- %s\n",id,dirent->d_name);
	
			}else{
				chosenId = atoi(argv[1]);
				if(id == chosenId) {
					printf("%s\n",dirent->d_name);

					//get the size of the full file path and name
					pathPlusName = malloc(strlen(path) + strlen(dirent->d_name));
					
					strcat(pathPlusName,path);
					strcat(pathPlusName,dirent->d_name);
				
					
					templateDescriptor = open(pathPlusName,O_RDONLY);

					destinationPathPlusName = malloc(strlen("./") + strlen(dirent->d_name));
					strcat(destinationPathPlusName,"./");
					strcat(destinationPathPlusName,dirent->d_name);

					//create new file if it dosent exist and write the template data
					destinationDescriptor = open(destinationPathPlusName,O_WRONLY | O_CREAT , S_IRUSR | O_EXCL);
					//I dont mind making  system calls for every character, the speed of execution is practically instant anyway
					while((bytes = read(templateDescriptor,&ch,sizeof(ch))) > 0){
						write(destinationDescriptor,&ch,sizeof(ch));
					}
					
				}
			}
			id++;
		}
	}
	
	if(pathPlusName != NULL) free(pathPlusName);
	if(destinationPathPlusName != NULL) free(destinationPathPlusName);
	close(templateDescriptor);
	close(destinationDescriptor);
	closedir(folder);
	return 0;
}
