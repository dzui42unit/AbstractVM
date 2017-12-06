# AbstractVM


As for any assembly language, the language of AbstractVM is composed of a series of
instructions, with one instruction per line. However, AbstractVM’s assembly language
has a limited type system, which is a major difference from other real world assembly
languages.

# Description

• Comments: Comments start with a ’;’ and finish with a newline. A comment can
be either at the start of a line, or after an instruction.

• push v: Pushes the value v at the top of the stack. The value v must have one of
the following form:
  * int8(n) : Creates an 8-bit integer with value n.
  * int16(n) : Creates a 16-bit integer with value n.
  * int32(n) : Creates a 32-bit integer with value n.
  * float(z) : Creates a float with value z.
  * double(z) : Creates a double with value z.
  
• pop: Unstacks the value from the top of the stack. If the stack is empty, the
program execution must stop with an error.

• dump: Displays each value of the stack, from the most recent one to the oldest
one WITHOUT CHANGING the stack. Each value is separated from the next one
by a newline.

• assert v: Asserts that the value at the top of the stack is equal to the one passed
as parameter for this instruction. If it is not the case, the program execution must
stop with an error. The value v has the same form that those passed as parameters
to the instruction push.

• add: Unstacks the first two values on the stack, adds them together and stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

• sub: Unstacks the first two values on the stack, subtracts them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

• mul: Unstacks the first two values on the stack, multiplies them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

• div: Unstacks the first two values on the stack, divides them, then stacks the result.
If the number of values on the stack is strictly inferior to 2, the program execution
must stop with an error. Moreover, if the divisor is equal to 0, the program execution
must stop with an error too. Chatting about floating point values is relevant a this
point. If you don’t understand why, some will understand. The linked question is
an open one, there’s no definitive answer.

• mod: Unstacks the first two values on the stack, calculates the modulus, then
stacks the result. If the number of values on the stack is strictly inferior to 2, the
program execution must stop with an error. Moreover, if the divisor is equal to 0,
the program execution must stop with an error too. Same note as above about fp
values.

• print: Asserts that the value at the top of the stack is an 8-bit integer. (If not,
see the instruction assert), then interprets it as an ASCII value and displays the
corresponding character on the standard output.

• exit: Terminate the execution of the current program. If this instruction does not
appears while all others instruction has been processed, the execution must stop
with an error.

# Grammar

<img width="654" alt="screen shot 2017-12-06 at 7 49 41 pm" src="https://user-images.githubusercontent.com/28359156/33676583-c613526a-dabe-11e7-9d2e-75755f41e5d3.png">

# Errors

When one of the following cases is encountered, AbstractVM must raise an exception
and stop the execution of the program cleanly.

* The assembly program includes one or several lexical errors or syntactic errors.
* An instruction is unknown
* Overflow on a value or the result of an operation
* Underflow on a value or the result of an operation
* Instruction pop on an empty stack
* Division/modulo by 0
* The program doesn’t have an exit instruction
* An assert instruction is not true
* The stack is composed of strictly less that two values when an arithmetic instruction is executed.

# Execution

<img width="661" alt="screen shot 2017-12-06 at 7 52 10 pm" src="https://user-images.githubusercontent.com/28359156/33676657-00a8b492-dabf-11e7-8c4e-e74e6027abd9.png">

# IOoerand interface

AbstractVM uses 5 operand classes that you must declare and define:

* Int8 : Representation of a signed integer coded on 8bits.
* Int16 : Representation of a signed integer coded on 16bits.
* Int32 : Representation of a signed integer coded on 32bits.
* Float : Representation of a float.
* Double : Representation of a double.

# Precision

When an operation happens between two operands of the same type, there is no problem.
However, what about when the types are different ? The usual method is to order types 
using their precision. For this machine you should use the following order: Int8 < Int16 < Int32 < Float < Double.
This order may be represented as an enum, as enum values evaluate to integers.

The pure method getPrecision from the interface IOperand allows to get the precision
of an operand. When an operation uses two operands from two different types, the
comparison of theirs precisions allows to figure out the result type of the operation.

# Stack

AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack or
another container that behaves like a stack is up to you. Whatever the container, it MUST
only contain pointers to the abstract type IOperand.

