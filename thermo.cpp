#include "thermo.h"
#include "memtrace.h"
#include <string>


// megjeleníti az eszkoz allapotat a kiválasztott stream-en
void Thermo::printStatus(std::ostream& os) const
{
	os << "[THERMO] ID: " << this->getID() << ", TEMPERATURE: " << this->temp << "C";
}

// ellenőrzi a parameter nevet és tartományát, majd frissít
void Thermo::update(const std::string& param, double value)
{
	if (param == "TEMPERATURE")
	{
		if (value > MAXIMUM_TEMP || value < MINIMUM_TEMP)
			throw InvalidParameterException("TEMPERATURE OUT OF RANGE! : (" + std::to_string(MINIMUM_TEMP) + "-" + std::to_string(MAXIMUM_TEMP) + ")");
		else
			this->temp = value;
	}
	else
	{
		// invalid param esete
		throw InvalidParameterException(param);		
	}
}

// ezzel a parancssorral fajlbol betoltes utan az eszköz egyből visszaallithato
void Thermo::save(std::ostream& os) const
{
	os << "ADD THERMO " << this->getID() << " " << temp;
}