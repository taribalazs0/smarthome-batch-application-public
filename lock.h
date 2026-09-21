#pragma once

#include "exception.h"
#include "device.h"
#include <iostream>
#include "memtrace.h"


// intelligens zár osztály, device leszarmazottja
class Lock : public Device
{
private:
	// zár állapota (zárva/nyitva) -> 0 vagy 1
	bool isClosed;
public:

	// konstruktor ID-ból és állapotból
	// @param id - eszköz ID-ja
	// @param b - kezdeti állapot (0: inaktiv(nyitva), 1: aktiv(zarva))
	Lock(const std::string& id, bool b) : Device(id), isClosed(b)
	{
		if (b != 0 && b != 1) throw InvalidParameterException("INVALID LOCK STATE");
	}

	// zár állapotának kiírása
	// @param os - output stream
	void printStatus(std::ostream& os) const override;

	// zár állapotának frissítése
	// @param param - paraméter neve (csak STATE-re engedelmeskedik)
	// @param value - új állapot (0 vagy 1)
	void update(const std::string& param, double value) override;

	// eszköz adatainak mentése
	// @param os - ostream
	void save(std::ostream& os) const override;

};
