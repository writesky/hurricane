
#ifndef HURRICANE_STRING_H
#define HURRICANE_STRING_H

#pragma once

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> SplitString(const std::string& value, char seperator);
std::string RandomString(const std::string& candidate, int length);
std::string itos(int number);
#endif //HURRICANE_STRING_H
