#pragma once

#include "exception.h"
#include "device.h"
#include <iostream>
#include "memtrace.h"

// intelligens lámpa osztály, device leszarmazott
class Light : public Device
{
private:
	// lámpa fényereje (%)
	double brightness;
public:
	// konstruktor ID-ból és fényerőből
	// @param id - eszköz ID-ja
	// @param b - kezdeti fényerő (0-100)
	Light(const std::string& id, double b) : Device(id), brightness(b)
	{
		if (b > 100 || b < 0) throw InvalidParameterException("INVALID BRIGHTNESS %!");
	}

	// fényerő állapotának kiírása
	// @param os - output stream
	void printStatus(std::ostream& os) const override;

	// fényerő frissítése
	// @param param - paraméter neve (csak BRIGTHNESS-t fogadja el)
	// @param value - új fényerő értéke
	void update(const std::string& param, double value) override;

	// eszköz adatainak mentése
	// @param os - ostream
	void save(std::ostream& os) const override;

};

