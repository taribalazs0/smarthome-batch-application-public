#include "lock.h"
#include "memtrace.h"

// megjeleníti az eszkoz allapotat a kiválasztott stream-en
void Lock::printStatus(std::ostream& os) const
{
	os << "[LOCK] ID: " << this->getID();
	if (this->isClosed) os << ": LOCK IS ACTIVE";
	else os << ": LOCK IS INACTIVE";
}

// ellenőrzi a parameter nevet és értékét (0/1), majd frissít
void Lock::update(const std::string& param, double value)
{
	if (param == "STATE")
	{

		if (value != 1 && value != 0)
			throw InvalidParameterException("LOCK HAS TWO STATES (0/1)");
		else if (value == 1)
			this->isClosed = true;
		else if (value == 0)
			this->isClosed = false;
	}
	else
	{
		// invalid param esete 
		throw InvalidParameterException(param);
	}
}


// ezzel a parancssorral fajlbol betoltes utan az eszköz egyből visszaallithato
void Lock::save(std::ostream& os) const
{
	os << "ADD LOCK " << this->getID() << " ";
	if (isClosed == 1) os << "1";
	if (isClosed == 0) os << "0";
}