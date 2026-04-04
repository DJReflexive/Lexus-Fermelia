# wyshell


This project had three iterations, in which you can find the different stages
of development for this tool. This is essentially our own shell terminal with 
token parsing, command execution, and command control flow using pipes, 
semi colons, redirection, etc...

Depending on which version you select, you will see different outputs. 
By going through each version in order, you will the next iteration is an
improvement from the previous. This reflects in the code as well, you can see
how I refine and refactor code between versions. 

## Breakdown of versions

- [Version 1](./Version%201/): A simple token analyzer. It will take input 
                                and separate tokens for later interpretation.
                                Any semi colons, pipes, ampersands, redirections,
                                and control flow errors are also observed for 
                                later use.

- [Version 2](./Version%202/): This version can actually execute any basic command
                                your typical shell can execute, but it cannot
                                handle advanced control flows with pipes, semi
                                colons, ampersands, nor redirections yet.

- [Version 3](./Version%203/): This is the final version in which can handle
                                the advanced control flows mentioned above.
                                It has basic error catching and can execute 
                                most commands you throw its way.

<br>

###### Note: I did not write wyscanner.c nor wyscanner.h. These files were responsible for lexical parsing and token analysis. You'll see much of the parsing "magic" is done here, but I handle everything else around it.


## Usage

After having compiled with "make":

```
lexus/wyshell>./wyshell
$> <Any linux command can be input here>
/* Result of that command */
$>
lexus/wyshell>
```

###### To exit, press <b>Ctrl+C</b>, and it will bring you to your original command line.
