## cpp-sandbox
This repo contains some C++ codes to illustrate language concepts and examples. Some small APPs are also included.
Each code has to be compiled individually in order to be run once this is NOT a software project!

---

## FOLDER "language-concepts"
Contains some codes with examples of important concepts of the language. Most of code files also have lots of comments within where useful information of subject related by the sub folder can be found.
Notice that some concepts does not belong necessarily to the subject where they are explained, but were put there merely because they were needed while explaining the major concept of the file.
Follow the list of contents in alphabetical order.

### Containers
Knowledge of Containers:
* DEQUE (double ended queue)
* FORWARD_LIST (singly-linked list)
* LIST (double-linked list)
* SET, MAP, MULTISET, MULTIMAP (trees)
* UNORDERED_SET, UNORDERED_MAP, UNORDERED_MULTISET, UNORDERED_MULTIMAP (hash maps)
* Custom types using associative containers (examples)
* Nested maps (map of maps)
* QUEUE, PRIORITY_QUEUE (fifo)
* STACK (lifo)

### CopyMoveSemantics
Knowledge of where language performs copy operations and how they can be turned into move operations for performance:
* Where to find copy operations in traditional C++
* Copy elision optimization by compiler (return value / name returned value optimizations)
* LValues, RValues (PRValues/XValues)
* Move semantics and Rvalues References
* std:: move
* Reference collapsing (universal reference)
* Perfect forwarding and std::forward
* RAII (Resource Acquisition is Initialization) and move semantics
* Disabling copy operators in classes (a bit of unique_ptr also)

### ErrorHandling
Knowledge of Error Handling:
* Why not simply use error codes
* Exceptions
* Constructor/destructor during stack unwinding
* std::exception
* Exception safety (basic, strong, no-throw guarantees)
* Custom exception classes

### File-Stream
Examples of file handling and use of stream.

### Functor
Examples of these very simple classes which overload function call operator "()".

### GenericAlgorithms
Knowledge of generic algorithms (with standard and functor/lambda predicates):
* find, find_if
* sort
* count, count_if
* equal
* min, max, minmax, min_element, max_element, minmax_element
* upper_bound, lower_bound
* pair
* iota, accumulate, partial_sum, adjacent_difference, inner_product
* fill
* replace, replace_if
* for_each
* copy, copy_n, copy_if
* transform
* replace_copy, replace_copy_if
* reverse, reverse_copy
* remove, remove_if, erase
* unique
* set_intersection
* next_permutation

### Inheritance-Polymorphism
Knowledge in Inheritance and Polymorphism:
* Static type and dynamic binding
* Virtual class management
  * Virtual functions 
  * Compiler's structure to manage virtual functions (vtable)
  * Virtual destructors
* Multiple Inheritance
  * Independent multiple inheritance 
  * Virtual functions
  * Diamond inheritance problem

### Iterators
Examples of iterators:
* Read/write
* Read only
* Reverse
* Stream
* Insert

### LambdaFunctions
Knowledge of lambda functions:
* Structure
* Arguments
* Variable capturing
* Inline/declared

### OverloadedOstreamOperator
Examples of overload of ostream operator "<<".

### Pointers
Knowledge of:
* Traditional Pointers (C-standard)
* Smart Pointers
  * unique_ptr
  * shared_ptr
* Pointers in built in arrays
* Pointers in classes
* Pre/postfix operators

### RandomNumbers
Knowledge of random functions for number generation:
* rand
* srand
* random_device
* random engines/distributions (mt19937, uniform_int/real_distribution, bernoulli_distribution)
Examples of generic algorithms shuffle and generate_n with random functions.

### Vector-String-Array
Knowledge of:
* Vector
* Array
* Built-In Array (C-standard)
* String
* C-Style String (C-standard)

---

## FOLDER "minor-codes"
Contains some example of minor codes, very simple things!

---

## FOLDER "rest-api"
Simple REST API developed in C++ to return json responses. The API contains the structure to response to any HTTP method, but the only one really handling something in this demo is the method GET. Other methods are responding as "not implemented". See detailed [documentation](rest-api/README.md).
