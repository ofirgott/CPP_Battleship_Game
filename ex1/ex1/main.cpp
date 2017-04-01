
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static void list_directory(const char *dirname);


int main(
	int argc, char *argv[])
{
	int i;

	/* For each directory in command line */
	i = 1;
	while (i < argc) {
		list_directory(argv[i]);
		i++;
	}

	/* List current working directory if no arguments on command line */
	if (argc == 1) {
		list_directory(".");
	}
	getchar();
	return EXIT_SUCCESS;
}

/*
* List files and directories within a directory.
*/
static void
list_directory(
	const char *dirname)
{
	DIR *dir;
	struct dirent *ent;

	/* Open directory stream */
	dir = opendir(dirname);
	if (dir != NULL) {

		/* Print all files and directories within the directory */
		while ((ent = readdir(dir)) != NULL) {
			switch (ent->d_type) {
			case DT_REG:
				printf("%s\n", ent->d_name);
				break;

			case DT_DIR:
				printf("%s/\n", ent->d_name);
				break;

			case DT_LNK:
				printf("%s@\n", ent->d_name);
				break;

			default:
				printf("%s*\n", ent->d_name);
			}
		}

		closedir(dir);

	}
	else {
		/* Could not open directory */
		printf("Cannot open directory %s\n", dirname);
		exit(EXIT_FAILURE);
	}
}