#include <gtest/gtest.h>
#include <vector>
#include <string>

typedef std::vector<std::string> Lines;

/*
TASK:

    Write a function, that is given a string and a length limit,
    splits provided string into sequence of string,
    where length of each string is not more, than provided limit.
    If there are spaces under provided limit - last space should be used to wrapp this line.
    If there are no spaces - wrapp it on provided length limit.

  Acceptance test:
        Input line:
            "When pos is specified, the search only includes sequences of characters that begin at or before position pos, ignoring any possible match beginning after pos."

        Expected Lines:
        {
            "When pos is specified, the",
            "search only includes sequences",
            "of characters that begin at or",
            "before position pos, ignoring",
            "any possible match beginning",
            "after pos."
        }
*/
