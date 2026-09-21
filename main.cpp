#include <iostream>
#include <sstream>
#include "smarthome.h"
#include "gtest_lite.h"
#include "memtrace.h"

#include "light.h"
#include "lock.h"
#include "thermo.h"
#include "device.h"

// ennek a makronak az allitasaval tudjuk beallitani hogy milyen modban fusson a program
// testmode 1 == tesztek futnak
// testmode 0 == interaktiv mod
#define TESTMODE 0


int main() 
{
        
    if (TESTMODE)
    {
        TEST(SmartHome, FullTest)
        {
            SmartHome sh;
            TEST(Device, Validation)
            {
                // érvénytelen fenyero
                EXPECT_THROW(Light("L1", 110), const InvalidParameterException&);
                EXPECT_THROW(Light("L2", -10), const InvalidParameterException&);

                // érvénytelen hő (15-35 kozott ok)
                EXPECT_THROW(Thermo("T1", 14), const InvalidParameterException&);
                EXPECT_THROW(Thermo("T2", 36), const InvalidParameterException&);

                // ezek érvényesek
                EXPECT_NO_THROW(Light("L3", 50));
                EXPECT_NO_THROW(Thermo("T3", 22));
                EXPECT_NO_THROW(Lock("Z1", 1));
            } END

                // SmartHome menedzsment
                TEST(SmartHome, Registration)
            {
                SmartHome sh;
                sh.ADD("LAMP", "L1", 50);
                sh.ADD("THERMO", "T1", 20);
                sh.ADD("LOCK", "DOOR", 1);
                sh.DEL("DOOR");

                // DuplicateID ellenorzese
                EXPECT_THROW(sh.ADD("LOCK", "L1", 1), const DuplicateIDException&);

                // ismeretlen típus
                EXPECT_THROW(sh.ADD("KAVEFOZO", "K1", 1), const SmartHomeException&);
            } END

                TEST(SmartHome, ModificationAndDeletion)
            {
                SmartHome sh;
                sh.ADD("LAMP", "L1", 10);
                sh.ADD("THERMO", "T1", 20);
                sh.ADD("LOCK", "DOOR", 1);

                // sikeres modositas
                EXPECT_NO_THROW(sh.SET("L1", "BRIGHTNESS", 90));
                EXPECT_NO_THROW(sh.SET("T1", "TEMPERATURE", 24));

                // rossz paraméter név
                EXPECT_THROW(sh.SET("L1", "COLOR", 255), const InvalidParameterException&);
                EXPECT_THROW(sh.SET("DOOR", "LOCK", 0), const InvalidParameterException&);

                // nemlétező eszkozt akarunk modositani
                EXPECT_THROW(sh.SET("X99", "ANY", 0), const SmartHomeException&);

                // rossz parameter (lakatnak 20)
                EXPECT_THROW(sh.SET("DOOR", "STATE", 20), const InvalidParameterException&);

                // törlés teszt
                EXPECT_NO_THROW(sh.DEL("L1"));
                // törlés után már nem szabad megtalálnia
                EXPECT_THROW(sh.SET("L1", "BRIGHTNESS", 50), const SmartHomeException&);
                // ismételt törlés (mar nem letezik)
                EXPECT_THROW(sh.DEL("L1"), const SmartHomeException&);
            } END

                // I/O es Batch tesztek
                TEST(SmartHome, BatchAndIO)
            {
                SmartHome sh;
                std::stringstream input;
                input << "ADD LAMP L1 20\n"
                    << "ADD THERMO T1 22\n"
                    << "SET L1 BRIGHTNESS 100\n"
                    << "DEL T1\n";

                // batch futtatás stringből
                EXPECT_NO_THROW(sh.runBatch(input));


                // listazas ellenorzese
                sh.ADD("LAMP", "L3", 10);
                sh.ADD("THERMO", "T1", 20);
                sh.ADD("LOCK", "DOOR", 1);
                sh.LIST(std::cout);

                // mentes ellenorzese (fajlmuvelet)
                EXPECT_NO_THROW(sh.SAVE("test_output.dat"));
            } END

                // memoriaszivargasok elleni teszt
                TEST(SmartHome, MemoryLeakCheck) 
            {
                SmartHome* sh = new SmartHome();
                sh->ADD("LAMP", "M1", 50);
                sh->ADD("THERMO", "M2", 20);
                sh->ADD("LOCK", "M3", 1);
                sh->SET("M1", "BRIGHTNESS", 10);
                sh->DEL("M2");

                delete sh;
            } ENDM
        } END
        return 0;
    }

 
        // alapertelmezett manualis / batch mod
        std::cout << "--- SmartHome Interaktiv Mod ---" << std::endl;
        std::cout << "Adjon meg parancsokat (ADD, SET, LIST, DEL, SAVE) vagy Ctrl+Z a kilepeshez:" << std::endl;
        SmartHome myHome;

        myHome.runBatch(std::cin);

        return 0;

}