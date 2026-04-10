# wyls

My own simplified implementation of the `ls` tool.

This tool lists a directory (or the current working directory by default) and prints a detailed view like `ls -l`:

```
permissions user group file_size date path
```

<br>




## Usage

After having compiled with "make":

```
./wyls [OPTIONS]... <Directory>

```

- -n: replace user & group names with their ID numbers
- -h: put the file size into a human-readable format
- -nh/-hn: both together

<br>


## Example Usage

When the user doesn't pass anything:
```
lexus/wyls>./wyls
-rw-r--r-- lexus students       297 Feb 19  2025 lexus/wyls/Makefile
-rw-r--r-- lexus students      6397 Feb 28  2025 lexus/wyls/wyls.c
-rwxr-xr-x lexus students     32816 Mar 31 22:18 lexus/wyls/wyls

lexus/wyls>
```

When the user passes a directory:
```
lexus/wyls>./wyls .
-rw-r--r-- lexus students       297 Feb 19  2025 ./Makefile
-rw-r--r-- lexus students      6397 Feb 28  2025 ./wyls.c
-rwxr-xr-x lexus students     32816 Mar 31 22:18 ./wyls

lexus/wyls>
```

Using -n:
```
lexus/wyls>./wyls -n .
-rw-r--r-- 11094 200       297 Feb 19  2025 ./Makefile
-rw-r--r-- 11094 200      6397 Feb 28  2025 ./wyls.c
-rwxr-xr-x 11094 200     32816 Mar 31 22:18 ./wyls

lexus/wyls>
```

Using -h:
```
lexus/wyls>./wyls -h .      
-rw-r--r-- lexus students  297  Feb 19  2025 ./Makefile
-rw-r--r-- lexus students  6.2K Feb 28  2025 ./wyls.c
-rwxr-xr-x lexus students 32.0K Mar 31 22:18 ./wyls

lexus/wyls>
```
