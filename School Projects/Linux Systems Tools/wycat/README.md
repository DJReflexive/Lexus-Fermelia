# wycat

My own simplified implementation of the "cat" tool.

A tool that will print out provided contents either through stdin or provided files.

<br>




## Usage

After having compiled with "make":

```
./wycat [FILES]... 

```

- Passing "-" as an argument will take input from stdin when that argument 
is reached.

<br>


## Example Usage


The user can use it to open up a stdin input. You can type anything here and
press **Ctrl+D** to have it recite what you had input back to you:

```
lexus/wycat>./wycat
Hello wycat!
Hello wycat!
This is my first line of input,
and here is my second line of input!
This is my first line of input,
and here is my second line of input!
Here is

some more complex

usages with multiple lines
and blank lines


Here is

some more complex

usages with multiple lines
and blank lines


lexus/wycat>
```



The user can concatenate files provided file names:

```
lexus/wycat>./wycat test1.txt
This is


Test file 1!

It has multiple lines
lexus/wycat>
```
```
lexus/wycat>./wycat test1.txt test2.txt
This is


Test file 1!

It has multiple lines
This is test 2! It only has 1 line
lexus/wycat>
```

The user can also mix in stdin with the files by passing 
"-" as a parameter to the command:

```
lexus/wycat>./wycat test1.txt - test2.txt
This is


Test file 1!

It has multiple lines
THIS IS STDIN INPUT
THIS IS STDIN INPUT
This is test 2! It only has 1 line
lexus/wycat>
```


<br>

To exit the tool, you can either input **Ctrl+D** when your current stdin input
is empty, or input **Ctrl+C** to exit the tool entirely right where you're at!



