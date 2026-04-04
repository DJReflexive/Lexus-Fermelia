# Compiler Project


This class was an interesting one. The whole premise of the class was to build
a real working compiler for the Decaf programming language (a subset language 
of Java) over the span of the semester. 
You'll see six different versions of the compiler as it develops over time. 
Each iteration was to achieve a specific goal, the next step in the process 
to get to a working compiler.

Each program version use "make" to compile and run the compiler.

Here are the versions and their corresponding milestones:


- [Program 1](./program1/):  
    - When the command is run, it will take any input given through stdin and parse it for decaf keywords, symbols, identifiers, white spaces, etc... 
    - Unfortunately I do not have the original documentation that explains exactly what each "Type" is. 
    - However, it will detect every token within the input and classify into a meaningful way. 
    - At this stage the decaf language is not yet enforced since there is no semantical analysis.
- [Program 2](./program2/)
    - Much like Program 1, it will take any input given through stdin and parse for decaf keywords, symbols, identifiers, white spaces, etc... 
    - This version is more advanced due to its precision in specific character detection. Things like parenthesis, brackets, plus, minus, and (&&), or (||), spaces, etc...
    - There is also the first layer of error detection for unrecognized symbols and words using regex expressions.
    - While still not enforced through error handling, the decaf language is now being more and more encouraged
- [Program 3](./program3/)
    - Now that we have token parsing down, this version aims to start using a grammar for decaf's structure with the new .ypp file. This is a simplified version of it, so only very basic statements will pass without some sort of error from the compiler. 
    - Error handling will try to be helpful in describing what the problem is to the user, but is often wrong at this stage of development.
    - It's a step in the right direction, but at this point the compiler is too strict, so the next version aims to fix some of that.
- [Program 4](./program4/)
    - Lorem ipsum
- [Program 5](./program5/)
    - Lorem ipsum
- [Program 6](./program6/) 
    - The final working compiler for the Decaf Programming Language
    - Not a perfect compiler, but it's pretty close considering how large this project was considering the small time frame I had to complete it.
    - 



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
