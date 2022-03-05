#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char **argv){

	int chosenId;
	int id = 0;

	int templateDescriptor;
	//getting the home folder path
	char *homeFolderName = getenv("HOME");
	
	char *TemplatesFolderName = "/Templates/";

	//allocating memory and appending the homeFolderName and TemplatesFolderName to the path
	char *path = malloc(strlen(homeFolderName) + strlen(TemplatesFolderName));
	strcat(path,homeFolderName);
	strcat(path,TemplatesFolderName);

	char *pathPlusName = { 0 };
	//folder and folder contents
	DIR *templateFolder = opendir(path);
	struct dirent *currentFile;
	

	int destinationDescriptor;
	char *destinationPathPlusName = { 0 };

	char *templateData = { 0 };
	struct stat *templateStats = { 0 };
	char *ptrToName;
	while((currentFile = readdir(templateFolder))){
		
		if(strcmp(currentFile->d_name,".") && strcmp(currentFile->d_name,"..") ){
			if(argc == 1){
				
				printf("%d --- %s\n",id,currentFile->d_name);
	
			}else{
				chosenId = atoi(argv[1]);
				if(id == chosenId) {
					printf("%s\n",currentFile->d_name);

					//get the size of the full file path and name
					pathPlusName = malloc(strlen(path) + strlen(currentFile->d_name));
					
					strcat(pathPlusName,path);
					strcat(pathPlusName,currentFile->d_name);
				
					//opening the template file fo reading
					templateDescriptor = open(pathPlusName,O_RDONLY);
					
					//allocating size for the file stats and reading the stats
					templateStats = malloc(sizeof(struct stat));
					fstat(templateDescriptor,templateStats);

						switch(argc){
							case 2:
								ptrToName = currentFile->d_name;
							break;
							case 3:
								ptrToName = argv[2];
							break;
						}
						
					destinationPathPlusName = malloc(strlen("./") + strlen(ptrToName));
					strcat(destinationPathPlusName,"./");
					strcat(destinationPathPlusName,ptrToName);

					//create new file if it dosent exist and write the template data
					destinationDescriptor = open(destinationPathPlusName,O_WRONLY | O_CREAT , S_IRUSR | O_EXCL);

					
					//previsouly i didnt minded making  system calls for every character, the speed of execution was practically instant anyway but my programmer brain did something better anyway
					//allocating size for the data
					templateData = malloc(templateStats->st_size);

					//reading and writing the data
					read(templateDescriptor,templateData,templateStats->st_size);
					write(destinationDescriptor,templateData,templateStats->st_size);
					
					
				}
			}
			id++;
		}
	}
	
	if(pathPlusName != NULL) free(pathPlusName);
	if(destinationPathPlusName != NULL) free(destinationPathPlusName);
	if(templateData != NULL) free(templateData);
	if(templateStats != NULL) free(templateStats);
	close(templateDescriptor);
	close(destinationDescriptor);
	closedir(templateFolder);
	return 0;
}
