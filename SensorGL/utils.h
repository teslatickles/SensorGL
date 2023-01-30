#include <string>
#include <iostream>

#ifdef UTILS_H
#endif // UTILS_H

enum class SystemType {
	ADC,
	DISPLAY
};

void print_ok(SystemType stype, std::string msg = "ok!");
void print_err(SystemType stype, std::string msg = "error!");
