// wyls.c
// Lexus Fermelia
// COSC 3750, SP 2025
// Homework 5
// February 28, 2025
//
// This files contains the source code
//   to my implementation of homework 5.


#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>


// void printPermissions(mode_t fileMode)
// Parameters:
//   fileMode - the given file's modes
// Return Value: void
//
// Prints off the permissions for the given file in
//   the "drwxrwxrwx" format.
void printPermissions(mode_t fileMode) {
  printf("%c", S_ISDIR(fileMode) ? 'd' : S_ISLNK(fileMode) ? 'l' : '-');

  // User Permissions
  printf("%c", (fileMode & S_IRUSR) ? 'r' : '-');
  printf("%c", (fileMode & S_IWUSR) ? 'w' : '-');
  printf("%c", (fileMode & S_IXUSR) ? 'x' : '-');

  // Group Permissions
  printf("%c", (fileMode & S_IRGRP) ? 'r' : '-');
  printf("%c", (fileMode & S_IWGRP) ? 'w' : '-');
  printf("%c", (fileMode & S_IXGRP) ? 'x' : '-');

  // Other Permissions
  printf("%c", (fileMode & S_IROTH) ? 'r' : '-');
  printf("%c", (fileMode & S_IWOTH) ? 'w' : '-');
  printf("%c", (fileMode & S_IXGRP) ? 'x' : '-');
}


// void printFileSize(int sizeBytes, bool hOption)
// Parameters:
//   sizeBytes - size of a file in bytes
//   hOption - boolean to keep track whether "-h" was enabled
// Return Value: void
//
// Prints off the size of a file in byte. If hOption is enabled,
//   then it will be printed off as "human-readable" value, in
//   Kilobytes (K), Megabytes (M), or Gigabytes (G).
void printFileSize(int sizeBytes, bool hOption) {
  if (!hOption) {
    printf("%9d ", sizeBytes);
  }
  else {
    double formattedSize = (double)sizeBytes;
    char unit = ' ';

    if (formattedSize >= 1024) {
      formattedSize /= 1024; unit = 'K';
    }
    if (formattedSize >= 1024) {
      formattedSize /= 1024; unit = 'M';
    }
    if (formattedSize >= 1024) {
      formattedSize /= 1024; unit = 'G';
    }

    // Get rid of unnecessary .0 if there is one
    if (formattedSize == (int)formattedSize) {
      printf("%4d%c ", (int)formattedSize, unit);
    }
    else {
      printf("%4.1f%c ", formattedSize, unit);
    }
  }
}


// void printTime(time_t mTime)
// Parameters:
//   mTime - the time in which a file was last modified
// Return Value: void
//
// Prints out the date/time based on the value passed in.
//   If the time was more than 180 days ago it will print
//   the year, but not the time it was modified. If it
//   was before 180 days ago, it will not print the year,
//   but it will print the time.
void printTime(time_t mTime) {
  char timeStr[20];
  struct tm *timeInfo = localtime(&mTime);
  time_t currentTime = time(NULL);

  // If file was modified more than 180 days go
  if (difftime(currentTime, mTime) > 180 * 24 * 3600) {
    strftime(timeStr, sizeof(timeStr), "%b %d  %Y", timeInfo);
  }
  else {
    strftime(timeStr, sizeof(timeStr), "%b %d %H:%M", timeInfo);
  }

  printf("%.20s ", timeStr);
}


// void listDir(const char *path, bool nOption, bool hOption)
// Parameters:
//   *path - the given path to the file/directory
//   nOption - boolean to keep track whether "-n" was enabled
//   hOption - boolean to keep track whether "-h" was enabled
// Return Value: void
//
// Lists the directory and all relevant information about the
//   given file like permissions, user, group, file size, time
//   last modified, and the file path itself.
//
// Will behave differently if -n or -h were passed as options.
void listDir(const char *path, bool nOption, bool hOption) {
  FILE *file = fopen(path, "r");
  if (!file) {
    perror(path);
    return;
  }

  struct stat fileStats;
  if (lstat(path, &fileStats) == -1) {
    perror(path);
    fclose(file);
    return;
  }


  // Print info:

  printPermissions(fileStats.st_mode);

  struct passwd *user = getpwuid(fileStats.st_uid);
  struct group *grp = getgrgid(fileStats.st_gid);

  if (nOption) { // ID numbers
    printf(" %d %d ", user->pw_uid, grp->gr_gid);
  }
  else { // Names
    printf(" %s %s ", user->pw_name, grp->gr_name);
  }

  printFileSize(fileStats.st_size, hOption);
  printTime(fileStats.st_mtime);
  printf("%s\n", path);

  fclose(file);
}


// void parseOption(char *arg, bool *nOption, bool *hOption)
// Parameters:
//   *arg - argument to be analyzed
//   *nOption - boolean to keep track whether "-n" was enabled
//   *hOption - boolean to keep track whether "-h" was enabled
// Return Value: void
//
// Parses through a give argument and checks for valid options,
//   if invalid option is given, an error message is printed and
//   the program ignores it.
void parseOption(char *arg, bool *nOption, bool *hOption) {

  for (int i = 1; arg[i] != '\0'; i++) {
    if (arg[i] == 'n') {
      *nOption = true;
    }
    else if (arg[i] == 'h') {
      *hOption = true;
    }
    else {
      errno = EINVAL;
      perror("Unsupported Option");
      continue;
    }
  }
}


// int main(int argc, char *argv[])
// Parameters:
//   argc - argument counter
//   *argv[] - argument vector
// Return Value: int
//
// Main Driver for the Program
int main(int argc, char *argv[]) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd error");
    return 1;
  }

  char *targetDir = NULL;
  if (argc == 1) { // No args passed
    targetDir = cwd;
  }


  // Parse Arguments
  bool nOption = false, hOption = false;
  bool isExpectingFiles = false;
  for (int i = 1; i < argc; i++) {

    // Handles case where an option is passed without a file after
    if (i == argc - 1 && !isExpectingFiles) {
      targetDir = cwd;
    }

    if (argv[i][0] == '-' && !isExpectingFiles) {
      parseOption(argv[i], &nOption, &hOption);
      continue;
    }

    isExpectingFiles = true;
    targetDir = argv[i];
  }


  DIR *dir = opendir(targetDir);
  if (dir == NULL) {
    perror(targetDir);
    return 1;
  }

  struct dirent *d;
  while ((d = readdir(dir)) != NULL) {
    if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
      continue; // skip listing "." and ".." directories
    }

    // Construct Full Path
    char fullPath[PATH_MAX];
    strcpy(fullPath, targetDir);
    strcat(fullPath, "/");
    strcat(fullPath, d->d_name);

    listDir(fullPath, nOption, hOption);
  }

  printf("\n");
  closedir(dir);

  return 0;
}
