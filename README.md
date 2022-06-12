# Advanced BrainF**k

Brainf**k interpreter with some additional features.

### Installation

I still have no installation, so just fork the project and add to your PATH the **abf/bin/** directory

### Usage

```
  $ abf [file].abf [-opt]
```

> *The extension is can be .abf or .bf, both can be used*

#### Options

##### -mem

Using the **-mem** option allows you to change the size of the memory array.

By default, the array contains 1000 8-bit unsigned integers.

```
  $ abf file.abf -mem X
```
> Where X is the amount of uints that you want to start your program with

### Features

When an execution starts, a **pointer** gets placed in the position 0 of the array.

##### >
Moves the pointer 1 position to the right

> Throws Error:
> Pointer can't be greater than the array size

##### <
Moves the pointer 1 position to the left

> Throws Error:
> Pointer can't point to a negative position

##### +
Adds 1 to the value in the position pointed

> Note: Since the data type is an 8-bit uint, adding from 255, will result in 0.

##### -
Subtracts 1 to the value in the position pointed

> Note: Since the data type is an 8-bit uint, subtracting from 0, will result in 255.

##### .
Outputs the ASCII charachter associated with the value in the pointed position

##### ,
Waits for user Input of a ASCII character to set the pointed position to it's value

##### [ ]
Loops through the code inside while the value of the pointed position != 0.

#### Added Features

##### :
Outputs the actual int value of the pointed position

##### ;
Waits for user Input of an integer to set the pointed position to.

### Contributions

Feel free to fork the repository, make changes and pull requests. 
My code is probably not the best, *(It's my first time making an interpreter)*.

Just, please, make sure to explain the changes you make and the reason why it's better, so I can understand.