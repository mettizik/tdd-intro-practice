#include <gtest/gtest.h>

/**
 * User Story 1
The following format is created by the machine:

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

/////////////////////////////////////
///
///
  {
      {" _ "},
      {"| |"},
      {"|_|"}
  },
  {
      {"   "},
      {"  |"},
      {"  |"}
  },
  {
      {" _ "},
      {" _|"},
      {"|_ "}
  },
  {
      {" _ "},
      {" _|"},
      {" _|"}
  },
  {
      {"   "},
      {"|_|"},
      {"  |"}
  },
  {
      {" _ "},
      {"|_ "},
      {" _|"}
  },
  {
      {" _ "},
      {"|_ "},
      {"|_|"}
  },
  {
      {" _ "},
      {"  |"},
      {"  |"}
  },
  {
      {" _ "},
      {"|_|"},
      {"|_|"}
  },
  {
      {" _ "},
      {"|_|"},
      {" _|"}
  }
///
/////////////////////////////////////

 * /
