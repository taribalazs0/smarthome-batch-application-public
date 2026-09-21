#pragma once

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "memtrace.h"
#include "device.h"


// std::string type -> eszkoz tipusa : lampa, thermo, lock
// std::string id -> konkret eszkoztipuson beluli konkret eszkoz : nappali_lampa, door_lock
// std::string param -> eszkoz parameterenek modositasa : thermo -> TEMP, lampa -> BRITGHNTESS, lock ->STATE
// double value -> az ertek ami jellemzi : thermo -> 22.5C, lampa -> 50% brightness, LOCK 0/1 (off/on)
// <TYPE> <ID> <PARAM> <VALUE> : LAMP L01 BRIGHTNESS 80 



// vezerlo osztaly, a kollekcio es a parancsoknak, eszközök gyujtemenyét kezeli
class SmartHome
{
private:

	// heterogén kollekció: az eszközöket mutatókon keresztül tároljuk a polimorfizmus miatt
	std::vector<Device*> devices;
public:

	// alapértelmezett konstruktor
	SmartHome() {}

	// új eszköz hozzáadása a rendszerhez
	// @param type - az eszköz típusa ("LAMP", "THERMO", "LOCK")
	// @param id - az eszköz egyedi azonosítója
	// @param value - az eszköz kezdeti értéke
	virtual void ADD(const std::string& type, const std::string& id, double value);

	// az összes regisztrált eszköz állapotának listázása
	// @param os - ostream
	virtual void LIST(std::ostream& os) const;

	// egy meglévő eszköz paraméterének módosítása/beallitasa
	// @param id - a keresett eszköz azonosítója
	// @param param - a módosítandó paraméter neve
	// @param value - az új érték
	virtual void SET(const std::string& id, const std::string& param, double value);

	// eszköz eltávolítása az azonosító alapján
	// @param id - az eltávolítandó eszköz azonosítója
	virtual void DEL(const std::string& id);

	// a teljes rendszerállapot mentése fájlba
	// @param filename - a mentéshez használt fájl neve
	virtual void SAVE(const std::string& filename);

	// kötegelt parancsfeldolgozás bemeneti folyamatból
	// @param is - bemeneti folyamat (file vagy konzol)
	void runBatch(std::istream& is);

	// virtuális destruktor, amely felszabadítja a dinamikusan foglalt eszközöket
	virtual ~SmartHome() { for (size_t i = 0; i < devices.size(); i++) delete devices[i]; }

};



