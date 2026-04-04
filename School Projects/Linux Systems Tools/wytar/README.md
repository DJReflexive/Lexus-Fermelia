# wytar

My own simplified implementation of the "tar" tool.

A tool that can create/extract .tar formatted archive files.

<br>


## Usage

After having compiled with "make":

```
./wytar -c -f [ARCHIVE NAME] [FILES]...
./wytar -cf [ARCHIVE NAME] [FILES]...

OR

./wytar -x -f [ARCHIVE NAME]
./wytar -xf [ARCHIVE NAME]

```

- -c: Create Archive
- -x: Extract Archive
- -f: The archive name (the next argument must be the file name)
- -cf: Create Archive with file name (the next argument must be the file name)
- -xf: Extract Archive from file name (the next argument must be the file name)

###### The -f flag is a non-optional flag, and one of -c or -x must be used

<br>


## Example Usage


Creating an archive:
```
lexus/wytar>./wytar -c -f myArchive.tar file1 file2 file3

lexus/wytar>vim myArchive.tar
------------------------------------------------
" tar.vim version v29
" Browsing tarfile lexus/wytar/myArchive.tar
" Select a file with cursor and press ENTER

file1
file2
file3
~
~
:q
------------------------------------------------
lexus/wytar>
```

Extracting an archive:
```
lexus/wytar>ls
myArchive.tar   wytar

lexus/wytar>./wytar -x -f myArchive.tar

lexus/wytar>ls
file1   file2   file3   myArchive.tar   wytar

lexus/wytar>
```

