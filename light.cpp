#include "light.h"
#include "memtrace.h"


// megjeleníti az eszkoz allapotat a kiválasztott stream-en
void Light::printStatus(std::ostream& os) const
{
	os << "[LAMP] ID: " << this->getID() << ", BRIGHTNESS: " << this->brightness << "%";
}

// ellenőrzi a parameter nevet és tartományát, majd frissít
void Light::update(const std::string& param, double value)
{
	if (param == "BRIGHTNESS")
	{
		if (value > 100 || value < 0)
			throw InvalidParameterException("BRIGHTNESS OUT OF RANGE (0-100)");
		else
			this->brightness = value;
	}
	else
	{
		// invalid param
		throw InvalidParameterException(param);		
	}
}

// ezzel a parancssorral fajlbol betoltes utan az eszköz egyből visszaallithato
void Light::save(std::ostream& os) const
{
	os << "ADD LAMP " << this->getID() << " " << brightness;
}