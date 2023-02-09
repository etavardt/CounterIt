# CounterIt
An iterator that counts instead of iterating over objects.

## Purpous
One might ask, "Why would you do that?".
And I must answer because: There are cases where iterating over
objects themselves does not do the job and you need values to access
data that is in a range of positions and you need the value of that
position. The position that is an offset or offsets in the case that
prompted me to write this.

### The Problem:
You want to write a Raytracer, you write a couple of for loops
for the x and y values of the pixel you wish to render.  Now you wish to 
multi-thread this task.  Given that the best mean to acheive this
is by using the for_each function in the STL `<execution>` library.
But, it does not allow for iterating over values but requires an iterator's
begin/end functions.  So what do you iterate over? One could create a `<vector>`
containing the list of values but the construction cost time and resources.
And in our case we need to created 2 of them. The comes along the fact that 
we may want to change the size of the final rendered image thus causing
one to repopulate the vectors or shrink them and this can be time consuming
as well.

### A Solution:
CounterIt offers a solution to issues like this.  By allowing you to supply 
a bounds of the values you wish to iterate over.  One only needs to supply
them and the time of construction of the lightweight Counter class.  This 
option also allows for a dynamic solution to changing ranges.  There may
be other solutions but this one seems to be the easiest solution that I 
could come up with at the time.

## TODO's
~~1) Test and handle boundry conditions of the bounds passed in.~~
Now behaves like the vector class and only asserts during debug build.

## Usage:
    1. Place the header file in you project.
    2. Add the header file(Counter.hpp) where you wish to use it.
    3. View the implementation file(Counter.cpp) for example use cases.
    
    It offers 2 constructors one with 1 argument and another with 2.
        a. the one with 1 argument is the end boundry [0, arg]
        b. the one with 2 arguments are the start and end boundries [start, end]

    If you git this project then build and execute it you should see the following:

    Hello! Welcome to CounterIt.

    Kewl::Counter( 3, 6 );
    A standered for_each test.
     3 4 5 6

    A multi-threaded for_each test.
    May be out of order due to being proccessed in parallel!
     3 4 5 6

    Test the begin/end and rbegin/rend functions.
    begin():3
    end():7
    rbegin():6
    rend():2

    Postfix increment test.
    before it++:3
    after it++:4

    Prefix increment test.
    before ++it:4
    after ++it:5

    Standard for loop using begin/end functions test.
     3 4 5 6
    Standard for loop using rbegin/rend functions test.
     6 5 4 3

    Kewl::Counter( 10 );
    Count from 0 to 10 inclusive.
     0 1 2 3 4 5 6 7 8 9 10
    In reverse inclusive.
     10 9 8 7 6 5 4 3 2 1 0

    Kewl::Counter( -10 );
    Count from 0 to -10 in inclusive.
     0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10
    In reverse inclusive.
     -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0

    Kewl::Counter( -10, 0 );
    Count from -10 to 0 in inclusive.
     -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    In reverse inclusive.
     0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10

## Note

    The bounds are inclusive, so when dealing with a zero based range like
    the width of an image the width is always the value of the count of items
    and you need to pass (width - 1) as one of the bounds or you will have undefined
    results.  It is up to you to ensure that the resulting range is within your
    bound needs.

    For instance an icon with a width 15 would have a 0 to 14 bound range.