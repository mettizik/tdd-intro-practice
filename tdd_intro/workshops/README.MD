# WorkShops

Workshop sessions is one of the core parts of the "Practicing TDD" course. This kind of sessions is implemented in specific way:

Group of people sit in a room with PC and projector. Two men from group peek a task from provided list and implement it in _live_ mode using ping-pong technique. Rest of group observes this process and corrects their actions if they choose a wrong path, or avoiding TDD practicies.

Pairs of programmers switch from task to task.

All workshops sessions tasks are listed below in corresponding order

## FizzBuzz

Nothing but classics. FizzBuzz is a most common kata in the world.

### Task

Write a program that prints the numbers from 1 to 100. But for multiples of three print “Fizz” instead of the number and for the multiples of five print “Buzz”. For numbers which are multiples of both three and five print “FizzBuzz “.

## Words Count

### Task

Given a phrase -> count the occurrences of each word in that phrase.

For example for the input "olly olly in come free"

```
olly: 2
in: 1
come: 1
free: 1
```

Example declaration of function required can be something like this:

```
std::map<std::string, int> WordsCount(std::string)
```

### Word Wrapp

Write a function, that is given a string and a length limit, splits provided string into sequence of string, where length of each string is not more, than provided limit. If there are spaces under provided limit - last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.

As an acceptance test you can use this input:
```
When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos.
```
It should be wrapped by length of 30 into this sequence of lines (ommiting quotes):
```
"When pos is specified, the",
"search only includes sequences",
"of characters that begin at or",
"before position pos, ignoring",
"any possible match beginning",
"after pos."
```
