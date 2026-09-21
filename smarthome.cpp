
#include "memtrace.h"
#include "smarthome.h"
#include "light.h"
#include "lock.h"
#include "thermo.h"
#include "device.h"

void SmartHome::ADD(const std::string& type, const std::string& id, double value)
{	
	// id ellenorzese, egyediség garantálása
	for (size_t i = 0; i < devices.size(); i++)
		if (devices[i]->getID() == id) throw DuplicateIDException();


	// itt meg az objektum nincs a memoriaban, nem tudunk virtualis fuggvenyt hivni ra, (nincs heterogen kollekcioban)
	// ezert kell a csunya if-else ag, mivel itt jön létre az objektum
	// a tipust a type string alapjan dontjuk el
	if (type == "LAMP")
	{	
		devices.push_back(new Light(id, value));
	}
	else if (type == "THERMO")
	{
		devices.push_back(new Thermo(id, value));
	}
	else if (type == "LOCK")
	{
		devices.push_back(new Lock(id, value));
	}

	else throw SmartHomeException("UNKNOWN DEVICE TYPE");

}

// LIST : az osszes regisztrált eszköz adatainak kiirasa.
void SmartHome::LIST(std::ostream& os) const
{
	if (devices.size() == 0)
	{
		os << "NO DEVICES YET" << std::endl;
		return;
	}

	// polimorfizmus használata:
	// printStatus virtualis, igy minden eszkoz a sajat formatumaban irodik ki a heterogen kollekciobol
	for (size_t i = 0; i < devices.size(); i++)
	{
		devices[i]->printStatus(os);
		os << std::endl;
	}
}

// DEL <ID>: eszkoz eltávolítása. 
void SmartHome::DEL(const std::string& id)
{
	for (size_t i = 0; i < devices.size(); i++)
	{
		if (devices[i]->getID() == id)
		{
			// előszőr a dinamikusan foglalt memóriát kell felszabadítani
			delete devices[i];

			// torolt elem ne maradjon benne -> eltoljuk manuálisan a tömböt
			for (size_t j = i; j < devices.size() - 1; j++)
				devices[j] = devices[j + 1];

			// utolso elem nem kell már és így devices_size() is egyel kisebb lesz
			devices.pop_back();

			return;
		}
	}

	// ha vegigfutunk a cikluson. ekkor nincs benne a keresett eszkoz: hiba
	throw SmartHomeException("CAN NOT DELETE DEVICE : " + id + " NOT FOUND");

}

void SmartHome::SET(const std::string& id, const std::string& param, double value)
{
	for (size_t i = 0; i < devices.size(); i++)
	{
		if (devices[i]->getID() == id)
		{
			// az update hivas eldonti, hogy ez egy lakat, lampa vagy termosztat
			devices[i]->update(param, value);
			return;
		}
	}
	throw SmartHomeException("SET FAILED : " + id + " NOT FOUND");
}

void SmartHome::SAVE(const std::string& filename)
{
	std::ofstream file(filename); 

	if (file.is_open())
	{
		// minden eszkoz olyan formatumban menti magat, amit a runbatch kesobb ujra be tud tolteni
		for (size_t i = 0; i < devices.size(); i++)
		{
			devices[i]->save(file);
			file << std::endl;
		}
	}
	else throw SmartHomeException("CANNOT OPEN FILE FOR SAVE: " + filename);

}


void SmartHome::runBatch(std::istream& is)
{
	std::string command;
	
	// fő feldolgozó ciklus: olvasunk, amig van parancs
	while (is >> command) 
	{
		try 
		{
			// parancs azonosítása
			if (command == "ADD")
			{
				std::string type, id;
				double value;
				is >> type >> id >> value;
				this->ADD(type, id, value);
			}
			else if (command == "SET")
			{
				std::string id, param;
				double value;
				is >> id >> param >> value;
				this->SET(id, param, value);
			}
			else if (command == "DEL")
			{
				std::string id;
				is >> id;
				this->DEL(id);
			}
			else if (command == "LIST")
			{
				this->LIST(std::cout);
			}
			else if (command == "SAVE")
			{
				std::string filename;
				is >> filename;
				this->SAVE(filename);
			}

			// javítás: NINCS throw, helyben kezeljuk a hibát, nem allunk le
			else std::cerr << "BATCH ERROR: UNKNOWN COMMAND: " << command << std::endl;
		}
		catch (const SmartHomeException& e)
		{
			// kivetelkezeles: ha egy parans hiba dob, elkapjuk, kiirjuk a hibat.	
			// de itt a ciklus nem áll le
			std::cerr << "BATCH ERROR: " << e.what() << std::endl;
		}
	}

}
