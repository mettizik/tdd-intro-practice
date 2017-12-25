# Homework

Homework is another core part of course activities. These are the tasks you should solve by yourself or with your pair-programming partner (whatever you like more) outside of a group sessions to fixup some practicies in your mind.

All homework tasks are bound to separate workshop sessions and should be solved in order they are provided, wishfully not earlier than the corresponding workshop occurs.

Solved homework tasks should be published into your public repo where mentor can review results you produced. Prefered way is to create your mainline branch and create pull requests from branches corresponding to the task solved.

All available tasks are listed below in corresponding order:

## Basic practicies training:

### Bob

Bob is a lackadaisical teenager. In conversation, his responses are very limited.

Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.

Implement Bob!

_from http://exercism.io/_

### Anagram

Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_

### Word Wrapp

Write a function, that is given a string and a length limit, splits provided string into sequence of string, where length of each string is not more, than provided limit. If there are spaces under provided limit - last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.

### Leap Year

Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.

_from http://exercism.io/_

### Trinary

Convert a trinary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid trinary as the value 0.

Trinary numbers contain three symbols: 0, 1, and 2.

The last place in a trinary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.
```
# "102012"
    1       0       2       0       1       2    # the number
1*3^5 + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243 +     0 +    54 +     0 +     3 +     2 =  302
```

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.

## Functionality decomposition training:

### TODO

## Mocking & Faking practicies

### TODO

