#include <iostream>
#pragma once

struct token_info{
  // this holds information about the current token.
  int line_number; // line number token is on.
  int times_seen; // refrences
  std::string token_name;
  std::string general_type; // func or var
  std::string data_type; // int,string,etc
  std::string last_function; // last function
};

