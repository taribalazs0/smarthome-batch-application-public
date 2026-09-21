#pragma once
#include "memtrace.h"
#include <stdexcept>
#include <string>

// sajat kivetelkezelo osztalyok
// alap hibak
class SmartHomeException : public std::runtime_error
{
public:
	SmartHomeException(const std::string msg) : std::runtime_error(msg) {}
};
// "specialisabb" hibak
class InvalidParameterException : public SmartHomeException
{
public:
	InvalidParameterException(const std::string msg) : SmartHomeException("INVALID PARAMETER: " + msg) {}
};
class DuplicateIDException : public SmartHomeException
{
public:
	DuplicateIDException() : SmartHomeException("ID ALREADY EXISTS!") {}
};
