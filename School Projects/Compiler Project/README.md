# Compiler Project

This class project walked us through building a real compiler for Decaf, a subset programming language similar to Java, over the course of a semester. The repository contains six compiler versions, each representing a new milestone toward a working compiler.

Here are the versions and their milestones:

- [Program 1](./program1/): Tokenizes stdin input into Decaf keywords, symbols, identifiers, and whitespaces. The compiler detects tokens, but it does not enforce Decaf grammar yet.
- [Program 2](./program2/): Improves token detection with finer character handling (parentheses, brackets, operators, whitespace) and adds initial error detection for unrecognized symbols.
- [Program 3](./program3/): Introduces grammar parsing with a `.ypp` file. This version accepts simple Decaf statements and adds early error reporting, though the parser remains strict.
- [Program 4](./program4/): Makes major grammar improvements, adds C-style comments, and supports more complex function and class structures. Pressing **Ctrl+D** outputs a parsed tree of the Decaf input.
- [Program 5](./program5/): Adds scope enforcement and more consistent error handling for unknown variables, functions, and classes.
- [Program 6](./program6/): The final working compiler. It supports class declarations, constructors, and function declarations. It’s not perfect, but it’s a strong result for a semester-long compiler project.

<br>


## Usage

After having compiled with "make":

```
lexus/compiler>./programX   (X being the program version you are on)
    /* Your decaf file input from stdin */
Ctrl+D
    /* Output, if any */
lexus/compiler>
```

To exit the compiler, you can either input **Ctrl+D** when you are done with your
current stdin input, or input **Ctrl+C** to panic exit the tool entirely right where 
you're at without any input.


## Table of Contents

<!-- Two directories deep -->
<pre>
Lexus-Fermelia
├── <a href="../.././Personal%20Works">Personal Works</a>
│   └── <a href="../.././Personal%20Works/README.md">README.md</a>
│
├── <a href="../.././Professional%20Works">Professional Works</a>
│   └── <a href="../.././Professional%20Works/University%20of%20Wyoming%20IT">University of Wyoming IT</a>
│
└── <a href="../.././School%20Projects/">School Works</a>
    ├── <a href="../.././School%20Projects/Algorithms">Algorithms</a>
    ├── <a href="../.././School%20Projects/Android%20Mobile%20Apps">Android Mobile Apps</a>
    ├── <a href="../.././School%20Projects/Compiler%20Project">Compiler Project</a> (You are Here!)
    ├── <a href="../.././School%20Projects/Cyber%20Security%20Malware%20Project">Cyber Security Malware Project</a>
    ├── <a href="../.././School%20Projects/Linux%20Systems%20Tools">Linux Systems Tools</a>
    ├── <a href="../.././School%20Projects/Primetime%20Paradox">Primetime Paradox</a>
    └── <a href="../.././School%20Projects/VR%20%26%20AR%20Unity%20Projects">VR & AR Unity Projects</a>
</pre>

<br>



# Links & Contact Info

### [Personal Website](https://lexusfermelia.com) | [LinkedIn](https://www.linkedin.com/in/lexus-fermelia/) | [Handshake](https://wyoming.joinhandshake.com/profiles/lexus-fermelia) 

### Get in Touch: lexusfermelia@gmail.com
