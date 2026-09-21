#pragma once
#include "memtrace.h"
#include <string>

// absztrakt Device osztaly
class Device
{
private:
	// device ID-ja
	std::string ID;				  
public:

	// konstruktor ID-ból
	// @param id - eszköz ID-ja
	Device(const std::string& id) : ID(id) {}

	// jelenlegi állapotot kiiro metódus
	// @param os - output stream (file, konzol stb...)
	virtual void printStatus(std::ostream& os) const = 0;

	// frissitjuk (ha SET hivodik, illetve kezdetben inicializal)
	// @param param - paramétere (eszkoz specifikus)
	// @param value - parameter beállitasa erre az értékre
	virtual void update(const std::string& param, double value) = 0;

	// elmentjük (file-ba)
	// @param os - ostream
	virtual void save(std::ostream& os) const = 0;

	// ID getter
	std::string getID() const { return ID; }

	virtual ~Device() {}
};
