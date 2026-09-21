#pragma once

#include "exception.h"
#include "device.h"
#include <iostream>
#include "memtrace.h"



// homersekletetk a termosztathoz
#define MINIMUM_TEMP 15
#define MAXIMUM_TEMP 35


// intelligens termosztát osztály, device leszarmazott
class Thermo : public Device
{
private:

	// beállított hőmérséklet
	double temp;
public:
	// konstruktor ID-ból és hőmérsékletből
	// @param id - eszköz ID-ja
	// @param t - kezdeti hőmérséklet
	Thermo(const std::string& id, double t) : Device(id), temp(t)
	{
		if (t < MINIMUM_TEMP || t > MAXIMUM_TEMP) throw InvalidParameterException("INVALID TEMPERATURE");
	}

	// termosztat állapotának kiírása
	// @param os - ostream
	void printStatus(std::ostream& os) const override;

	// termosztat/homerseklet frissítése
	// @param param - paraméter neve, csak TEMPERATURE-val mukodik
	// @param value - új hőmérséklet érték
	void update(const std::string& param, double value) override;

	// eszköz adatainak mentése
	// @param os - ostream
	void save(std::ostream& os) const override;

};