#include <string>
#pragma once

std::string getHexcode(int r, int g, int b);
std::string toHex(int decVal);

void copyToClipboard(const std::string& text);