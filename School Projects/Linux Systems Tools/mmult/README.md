# mmult

A tool that will multiple two compatible matrices together.

###### Note: The make_mat script is not my work, it was a file provided to us to assist in creating random matrices to run our tests with - it would be helpful for your own testing

<br>




## Usage

After having compiled with "make":

```
./make_mat <File Name> <Rows> <Columns>

./mmult <Left Matrix File Name> <Right Matrix File Name> [NUM THREADS]
```

- Rows & Columns must be an integer
- NUM THREADS is the number of threads the program will run with




<br>


## Example Usage

make_mat example:
```
lexus/mmult>./make_mat 2x4.matrix 2 4
lexus/mmult>./make_mat 4x6.matrix 4 6
lexus/mmult>
```

Single-Thread mmult example:
```
lexus/mmult>./mmult 2x4.matrix 4x6.matrix result.matrix
Matrix sizes:
  M: 2
  N: 4
  P: 6

Worker threads: 0

Total time: 0 seconds.
lexus/mmult>
```

Mutli-Thread mmult example:
```
lexus/mmult>./mmult 2x4.matrix 4x6.matrix result.matrix 5
Matrix sizes:
  M: 2
  N: 4
  P: 6

Worker threads: 5

Total time: 0 seconds.
lexus/mmult>
```

result.matrix will contain the correct multiplied matrix of the two input matrices. If dimensions are not compatible, you see something like this:
```
lexus/mmult>./mmult 4x6.matrix 2x4.matrix result.matrix
Error: Passed invalid matrices (incompatible sizes)
lexus/mmult>
```
