#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <tar.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include "helperFuncs.h"
#include "tarHeader.h"



void processFile(char *filePath, FILE *archive) {
  if (!filePath) {
    fprintf(stderr, "Error: filePath is NULL before calling processFile()\n");
    return;
  }
  struct stat st;
  if (lstat(filePath, &st) == -1) {
    perror(filePath);
    return;
  }

  // Write the Header
  tarHeader header;
  memset(&header, 0, sizeof(header));
  strncpy(header.name, filePath, sizeof(header.name) - 1);
  snprintf(header.mode, sizeof(header.mode), "%07o", st.st_mode & 0777);
  snprintf(header.uid, sizeof(header.uid), "%07o", st.st_uid);
  snprintf(header.gid, sizeof(header.gid), "%07o", st.st_gid);
  snprintf(header.size, sizeof(header.size), "%011o", (unsigned int)st.st_size);
  snprintf(header.mtime, sizeof(header.mtime), "%011o", (unsigned int)st.st_mtime);
  memset(header.chksum, ' ', sizeof(header.chksum));
  strncpy(header.magic, TMAGIC, TMAGLEN);
  memcpy(header.version, TVERSION, TVERSLEN);

  // If a Directory
  if (S_ISDIR(st.st_mode)) {
    header.typeflag = DIRTYPE;
    snprintf(header.size, sizeof(header.size), "%011o", 0);
  }
  // If a Symbolic Link
  else if (S_ISLNK(st.st_mode)) {
    header.typeflag = SYMTYPE;
    ssize_t len = readlink(filePath, header.linkname, sizeof(header.linkname)-1);
    if (len != -1) {
      header.linkname[len] = '\0';
    }
    else {
      perror("Failed to read symbolic link target");
      exit(1);
    }
  }
  // If a Regular File
  else {
    header.typeflag = REGTYPE;
  }

  int checksum = 0;
  char *bytes = (char *)&header;
  for (int j = 0; j < sizeof(header); j++) {
    checksum += bytes[j];
  }
  snprintf(header.chksum, sizeof(header.chksum), "%06o", checksum);
  fwrite(&header, 1, BLOCK_SIZE, archive);


  if (REGTYPE == header.typeflag) {
    FILE *file = fopen(filePath, "rb");
    if (!file) {
      perror("Error opening file for archiving");
      exit(1);
    }


    char buffer[BLOCK_SIZE] = {0};
    while (fread(buffer, 1, BLOCK_SIZE, file) > 0) {
      fwrite(buffer, 1, BLOCK_SIZE, archive);
    }

    fclose(file);
  }

  // If a directory, recursively process contents
  if (DIRTYPE == header.typeflag) {
    DIR *dir = opendir(filePath);
    if (!dir) {
      perror("Failed to open directory");
      return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
      if (strcmp(entry->d_name, ".") == 0 ||
          strcmp(entry->d_name, "..") == 0) {
        continue;
      }

      char fullPath[BLOCK_SIZE*2];
      if (entry->d_name != NULL) {
        snprintf(fullPath, sizeof(fullPath), "%s/%s", filePath, entry->d_name);
        processFile(fullPath, archive);
      }
    }

    closedir(dir);
  }
}


void archiveFiles(char *archiveFile, char *files[]) {
  FILE *archive = fopen(archiveFile, "wb");
  if (archive == NULL) {
    perror("Failed to create archive file");
    exit(1);
  }

  for (int i = 0; files[i] != NULL; i++) {
    if (!files[i]) {
      perror("Error: files[] is NULL before calling processFile()");
      continue;
    }

    processFile(files[i], archive);
  }

  char end[BLOCK_SIZE*2] = {0}; // End block filled with 0's
  fwrite(end, 1, BLOCK_SIZE*2, archive);
  fclose(archive);
}




void extract(FILE *archive, tarHeader *header) {

  // if directory
  if (DIRTYPE == header->typeflag) {
    mkdir(header->name, 0755);
  }

  // if symbolic link
  if (SYMTYPE == header->typeflag) {
    symlink(header->linkname, header->name);
  }

  // if file is regular
  if (REGTYPE == header->typeflag) {
    FILE *file = fopen(header->name, "wb");

    if (!file) {
      perror("Failed to open file");
      return;
    }

    char buffer[BLOCK_SIZE] = {0};
    int remainingBytes = atoi(header->size);
    while (remainingBytes > 0) {

      size_t bytesToRead;
      if (remainingBytes > BLOCK_SIZE) {
        bytesToRead = BLOCK_SIZE;
      }
      else {
        bytesToRead = remainingBytes;
      }

      fread(buffer, 1, BLOCK_SIZE, archive);
      fwrite(buffer, 1, bytesToRead, file);

      remainingBytes -= bytesToRead;
    }

    fclose(file);
  }
}

void extractFiles(char *archiveFile) {
  FILE *archive = fopen(archiveFile, "rb");

  if (!archive) {
    perror("Failed to open archive");
    exit(1);
  }

  tarHeader header;

  while (fread(&header, 1, sizeof(header), archive) > 0 &&
         header.name[0] != '\0') {
    extract(archive, &header);
  }

  fclose(archive);
}
