/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only
what you need to new projects you will learn how to write code that doesn't leak
as well as how to refactor.

NOTE: there are 2 sets of instructions:
       One for if you completed project 3
       One for if you skipped project 3.

 Destructors

===============================================================
 If you completed Project 3:

 1) Copy 3 of your user-defined types (the ones with constructors and
for()/while() loops from Project 3) here Choose the classes that contained
nested classes.  Include the nested classes when you copy them over.

 2) move all of your implementations of all functions to OUTSIDE of the class.

 3) add destructors
        make the destructors do something like print out the name of the class.
===============================================================
If you skipped Project 3:
write 3 UDTs below that EACH have:
        5 member variables
            the member variable names and types should be relevant to the work
the UDT will perform. pick properties that can be represented with 'int float
double bool char std::string' 3 member functions with an arbitrary number of
parameters give some of those parameters default values. constructors that
initialize some of these member variables the remaining member variables should
be initialized in-class for() or while() loops that modify member variables 1) 2
of your 3 UDTs need to have a nested UDT. this nested UDT should fulfill the
same requirements as above: 5 member variables 3 member functions constructors
and loops.

 2) Define your implementations of all functions OUTSIDE of the class.
 NO IN-CLASS IMPLEMENTATION ALLOWED
 3) add destructors to all of your UDTs
        make the destructors do something like print out the name of the class.
===============================================================

 4) add 2 new UDTs that use only the types you copied above as member variables.

 5) add 2 member functions that use your member variables to each of these new
UDTs

 6) Add constructors and destructors to these 2 new types that do stuff.
        maybe print out the name of the class being destructed, or call a member
function of one of the members.  be creative

 7) copy over your main() from the end of Project3
        get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.

 8) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
       call their member functions.

 9) After you finish, click the [run] button.  Clear up any errors or warnings
as best you can.

 you can resolve any [-Wdeprecated] warnings by adding -Wno-deprecated to list
of compiler arguments in the .replit file. all of the "-Wno" in that file are
compiler arguments. You can resolve any [-Wpadded] warnings by adding
-Wno-padded to the list of compiler arguments in the .replit file. all of the
"-Wno" in that file are compiler arguments.

 Ignore the Atomic.h and LeakedObjectDetector.h files for now.
 You will use those in Part 3 of this project.

 */

/*
 copied UDT 1:
 */
#include <cmath>
#include <iostream>

struct Guitar
{
    Guitar();
    ~Guitar();
    std::string makeModel;
    int numberOfStrings;
    int numberOfPickups{2};
    std::string acousticElectricNylon;
    bool activePickups{false};
    int HP;
    int audienceMood;

    struct GuitarString
    {
        GuitarString();
        ~GuitarString();
        std::string brand;
        int gauge;
        std::string material = "Nickel wound";
        bool flatwound = false;
        bool coated;
        int tuningOpen;
        float stringAge;

        float bend(int whichString = 1, float distance = 0.0f); 
        void degrade(float time, std::string thisMaterial = "Nickel wound", bool coated = false); 
        void snap();
        void printMaterialCoated();
        void microwave(int time);
    };

    GuitarString stringPlaying;

    int emitNote(GuitarString string, int fret = 0);
    void feedback();
    void detachFromStrap();
    void printPickupsStrings();
    void polish();
};

Guitar::GuitarString::GuitarString() :
coated(false),
tuningOpen(64) //open high E midi number
{
    brand = "D'addario";
    gauge = 10;
    stringAge = 0;
    std::cout << "GuitarString has been constructed!" << std::endl;
}

Guitar::GuitarString::~GuitarString()
{
    std::cout << "This is GuitarString's destructor!" << std::endl;
}

float Guitar::GuitarString::bend(int whichString, float distance)
{
    float tension = 1 + static_cast<float>(whichString) * .2f;
    return distance * tension;
}

void Guitar::GuitarString::degrade(float time, std::string thisMaterial, bool isCoated)
{
    float multiplier;
    if(thisMaterial == "Nickel Wound")
    {
        multiplier = 1.f;
    }
    else if(thisMaterial == "Phospher Bronze")
    {
        multiplier = 1.5f;
    }
    else
    {
        multiplier = 2.0f;
    }
    if(isCoated == true)
    {
        multiplier *= .5f;
    }
    stringAge += time * multiplier;
}

void Guitar::GuitarString::snap()
{
    stringAge = 1;
    std::cout << "Time to change strings..." << std::endl;
}

void Guitar::GuitarString::microwave(int time)
{
    if(stringAge == 0.f)
    {
        stringAge = 0.0003f;
    }
    while(time > 0)
    {
        std::cout << "He's cooking now!" << std::endl;
        stringAge *= 3.0f;
        --time;
    }
    std::cout << "That string is cooked! String age: " << stringAge << std::endl;
}

void Guitar::GuitarString::printMaterialCoated()
{
    std::cout << "Guitar::GuitarString::printMaterialCoated() material:" << material << " coated: " << coated << std::endl; 
}

Guitar::Guitar() : 
numberOfStrings(6),
acousticElectricNylon("electric")
{
    makeModel = "Fender Telecaster";
    HP = 10;
    audienceMood = 10;
    std::cout << "Guitar has been constructed!" << std::endl;
}

Guitar::~Guitar()
{
    std::cout << "This is Guitar's destructor!" << std::endl;
}

int Guitar::emitNote(GuitarString thisString, int fret)
{
    stringPlaying = thisString;
    int note = stringPlaying.tuningOpen + fret;
    return note;
}

void Guitar::feedback()
{
    audienceMood -= 3;
}

void Guitar::detachFromStrap()
{
    HP -= 2;
    std::cout << "Clunk!" << std::endl;
}

void Guitar::printPickupsStrings()
{
    std::cout << "Guitar::printPickupsStrings() pickups:" << numberOfPickups << " strings: " << numberOfStrings << std::endl; 
}

void Guitar::polish()
{
    while(HP < 10)
    {
        std::cout << "Polishing the guitar..." << std::endl;
        ++HP;
    }
    std::cout << "Your guitar is good as new!" << std::endl;
}

/*
 copied UDT 2:
 */
struct Bird
{
    Bird();
    ~Bird();
    float height;
    float altitude;
    double wingspan;
    std::string type;
    bool isMale = true;
    double distance = 0.;

    struct Progeny
    {
        Progeny();
        ~Progeny();
        bool stillEgg;
        float percentToMaturity;
        float satedLevel{0.f};
        bool canFly = false;
        bool canForage;

        void flyTheNest();
        void eat(float maturePercent, std::string target);
        int chirp(bool parentPresent, float location, int timeOfDay);
        void printSatedEgg();
        void hatch();
    };

    Progeny fledgling;
    void fly(double x, double y);
    void sing();
    void eat(std::string target);
    void forage(Progeny progeny);
    void printMaleWingspan();
    int howManyFlaps();
};

Bird::Progeny::Progeny() :
stillEgg(true),
percentToMaturity{0.f}
{
    canForage = false;
    std::cout << "Progeny has been constructed!" << std::endl;
}

Bird::Progeny::~Progeny()
{
    std::cout << "This is Progenys destructor!" << std::endl;
}

void Bird::Progeny::flyTheNest()
{
    float growUp = percentToMaturity + satedLevel;
    if(.80f < percentToMaturity || 1.f <= growUp)
    {
        std::cout << "Your Fledgling grew up!" << std::endl;
    }
    else if(.60f <= percentToMaturity)
    {
        std::cout << "Your Fledgling survived the attempt, but isn't ready to grow up." << std::endl;
    }
    else
    {
        std::cout << "Your Fledgling didn't survive the attempt..." << std::endl;
    }

}

void Bird::Progeny::eat(float maturePercent, std::string target)
{
    std::cout << "Your Fledgling ate a " << target << std::endl;
    percentToMaturity += maturePercent;
}

int Bird::Progeny::chirp(bool parentPresent, float location, int timeOfDay)
{
    int safety = 0;
    if (parentPresent == true)
    {
        safety += 45;
    }
    if(location >= 40.f)
    {
        safety += 20;
    }
    if(7 < timeOfDay && timeOfDay < 18)
    {
        safety += 35;
    }
    std::cout << "Chirp !!" << std::endl;
    return safety;
}

void Bird::Progeny::printSatedEgg()
{
    std::cout << "Bird::Progeny::printSatedEgg() satedLevel:" << satedLevel << " stillEgg: " << stillEgg << std::endl; 
}

void Bird::Progeny::hatch()
{
    if(stillEgg)
    {
        for(int i = 1; i < 20; ++i)
        {
            std::cout << "Embryo is growing..." << std::endl;
        }
        std::cout << "Fledgling has hatched!" << std::endl;
        stillEgg = false;
    }
}

Bird::Bird() :
wingspan{15.0},
type("pigeon")
{
    height = 7.0f;
    altitude = 4800.0f;
    std::cout << "Bird has been constructed!" << std::endl;
}

Bird::~Bird()
{
    std::cout << "This is Bird's destructor!" << std::endl;
}

void Bird::fly(double x, double y)
{
    distance += sqrt(pow(x, 2.) + pow(y, 2.));
}

void Bird::sing()
{
    std::cout << "Tweet !!" << std::endl;
}

void Bird::eat(std::string target)
{
    std::cout << "Your Bird ate a " << target << std::endl;
}

void Bird::forage(Progeny progeny)
{
    fledgling = progeny;
    if(fledgling.percentToMaturity <= .2f)
    {
        std::cout << "Your Fledgling needs some seed!" << std::endl;
    }
    else if(.2f < fledgling.percentToMaturity && fledgling.percentToMaturity <= .6f)
    {
        std::cout << "Your Fledgling needs a worm!" << std::endl;
    }
    else
    {
        std::cout << "Your Fledgling needs a beetle!" << std::endl;
    }
}

void Bird::printMaleWingspan()
{
    std::cout << "Bird::printMaleWingspan() male?:" << isMale << " wingspan: " << wingspan << std::endl; 
}

int Bird::howManyFlaps()
{
    double i = distance;
    int j = 0;
    while(i > 0)
    {
        ++j;
        i -= wingspan;
    }
    std::cout << "Your bird has flappped " << j << " times so far!" << std::endl;
    return j;
}
  /*
   copied UDT 3:
   */
struct CPU
{
    CPU();
    ~CPU();
    std::string manufacturer;
    float temperature;
    float clockSpeed;
    int cores;
    std::string socket = "AM4";

    float storeData(); 
    float outputResults(); 
    float compute(float x, float y);
    void printClockSpeedAndSocket();
    void overheat();
};

CPU::CPU() :
clockSpeed{3.5f},
cores(6)
{
    manufacturer = "AMD";
    temperature = 55.5f;
    std::cout << "CPU has been constructed!" << std::endl;
}

CPU::~CPU()
{
    std::cout << "This is CPU's destructor!" << std::endl;
}

float CPU::storeData()
{
    return 1.43667f * 2.44435f * temperature;
}

float CPU::outputResults()
{
    return 89.667f * .30741f * temperature;
}

float CPU::compute(float x, float y)
{
    return x * y * temperature;
}

void CPU::printClockSpeedAndSocket()
{
    std::cout << "CPU::printClockSpeedAndSocket() clock speed:" << clockSpeed << " socket: " << socket << std::endl; 
}

void CPU::overheat()
{
    if(temperature > 1000)
    {
        std::cout << "Overheated! Shutting down..." << std::endl;
        temperature = 55;
    }   
}

struct Motherboard
{
    Motherboard();
    ~Motherboard();
    std::string manufacturer;
    bool wirelessLAN;
    int m2Slots;
    int expansionSlots;
    int maxRAM = 64;
    int AVSignals;

    void dataToRAM();
    void generateAVSignals();
    void autoSuspend();
    void printMaxRAMAndManufacturer();
    void badSectors();
};

Motherboard::Motherboard() :
manufacturer("Gigabyte"),
m2Slots(2)
{
    wirelessLAN = false;
    expansionSlots = 4;
    AVSignals = 0;
    std::cout << "Motherboard has been constructed!" << std::endl;
}

Motherboard::~Motherboard()
{
    std::cout << "This is Motherboard's destructor!" << std::endl;
}

void Motherboard::dataToRAM()
{
    maxRAM += 5;
}

void Motherboard::generateAVSignals()
{
    ++AVSignals;
}

void Motherboard::autoSuspend()
{
    maxRAM = 0;
    AVSignals = 0;
}

void Motherboard::printMaxRAMAndManufacturer()
{
    std::cout << "Motherboard::printMaxRAMAndManufacturer() max RAM:" << maxRAM << " manufacturer: " << manufacturer << std::endl; 
}

void Motherboard::badSectors()
{
    while(maxRAM > 0)
    {
        std::cout << "RAM corrupted!" << std::endl; 
        --maxRAM;
    }
}


struct KeyboardAndMouse
{
    KeyboardAndMouse();
    ~KeyboardAndMouse();
    int numberOfMouseButtons;
    bool mechanicalStyle;
    bool wireless;
    std::string language;
    bool numpad = false;

    int transmitKeystrokeData();
    double transmitXYChange(double x, double y);
    bool toggleStatus(bool status);
    void printNumpadAndLanguage();
    void typing(int words);
};

KeyboardAndMouse::KeyboardAndMouse() :
wireless(true),
language("English")
{
    numberOfMouseButtons = 3;
    mechanicalStyle = false;
    std::cout << "KeyboardAndMouse has been constructed!" << std::endl;
}

KeyboardAndMouse::~KeyboardAndMouse()
{
    std::cout << "This is KeyboardAndMouse's destructor!" << std::endl;
}

int KeyboardAndMouse::transmitKeystrokeData()
{
    return 103;
}

double KeyboardAndMouse::transmitXYChange(double x, double y)
{
    return sqrt(pow(x, 2.) + pow(y, 2.));
}

bool KeyboardAndMouse::toggleStatus(bool status)
{
    if(status == true)
    {
        return false;
    }
    return true;
}

void KeyboardAndMouse::printNumpadAndLanguage()
{
    std::cout << " KeyboardAndMouse::printNumpadAndLanguage() numpad:" << numpad << " language: " << language << std::endl; 
}

void KeyboardAndMouse::typing(int words)
{
    int check = 1;
    for(int i = words * 6; i > 0; --i)
    {
        if(check == 1)
        {
            std::cout << "Click!" << std::endl;
            check = 0;      
        }
        else
        {
            std::cout << "Clack!" << std::endl;
            check = 1;
        }
    }
}

struct CoolingSystem
{

    CoolingSystem();
    ~CoolingSystem();
    bool liquid;
    int numberOfRGB;
    int numberOfFans = 3;
    int fanSetting;
    bool molex;
    std::string lightColor;

    void setFanSpeed(int speed);   
    void setLightColor(std::string color);
    void springALeak();
    void printFansRGB();
    void powerStatus(int hours);

};

CoolingSystem::CoolingSystem() :
liquid(false),
numberOfRGB(5)
{
    fanSetting = 2;
    molex = false;
    lightColor = "red";
    std::cout << "CoolingSystem has been constructed!" << std::endl;
}

CoolingSystem::~CoolingSystem()
{
    std::cout << "This is CoolingSystem's destructor!" << std::endl;
}

void CoolingSystem::setFanSpeed(int speed)
{
    if(0 <= speed && speed >= 5)
    {
        fanSetting = speed;
    }
    else
    {
        std::cout << "Invalid Selection" << std::endl;//the if and else are both executed ???
    }
    std::cout << "Speed is " << fanSetting << std::endl;
}

void CoolingSystem::setLightColor(std::string color)
{
    if(color == "red" || color == "orange" || color == "blue" || color == "green")
    {
        lightColor = color;
    }
    else
    {
        std::cout << "Please Pick a Color" << std::endl;
    }

}

void CoolingSystem::springALeak()
{
    liquid = true;
}

void CoolingSystem::printFansRGB()
{
    std::cout << "CoolingSystem::printFansRGB() number of fans:" << numberOfFans << " number of RGB: " << numberOfRGB << std::endl; 
}

void CoolingSystem::powerStatus(int hours)
{
    int jigawatts = 8;
    for(int i = hours* 60; i > 0; --i)
    {
        std::cout << "Cooling has consumed " << jigawatts << " jigawatts!" << std::endl; 
        jigawatts += 8;
    }
}

struct GPU
{
    GPU();
    ~GPU();
    bool intel;
    int ram;
    float clockSpeed;
    int numberOfFans;
    int numberOfOutputs;
    int AVSignals;
    int currentRGB;
    int fanSpeed = 3;
    int model = 1;

    void outputAVSignal();
    void cycleRGBDisplay(); 
    void adjustFanSpeed(int speed);
    void printFanSpeedRGBCycle();
    void upgrade();
};

GPU::GPU() :
AVSignals(0),
currentRGB(0)
{
    intel = false;
    ram = 8;
    clockSpeed = 1525.f;
    numberOfFans = 3;
    numberOfOutputs = 4;
    std::cout << "GPU has been constructed!" << std::endl;
}

GPU::~GPU()
{
    std::cout << "This is GPU's destructor!" << std::endl;
}

void GPU::outputAVSignal()
{
    ++AVSignals;
}

void GPU::cycleRGBDisplay()
{
    if(currentRGB < 8)
    {
        currentRGB += 1;
    }
    else
    {
        currentRGB = 0;
    }
}

void GPU::adjustFanSpeed(int speed)
{
    if(0 <= speed && speed >= 5)
    {
        fanSpeed = speed;
    }
    else
    {
        std::cout << "Invalid Selection" << std::endl;
    }
    std::cout << "Speed is " << fanSpeed << std::endl;
}

void GPU::printFanSpeedRGBCycle()
{
    std::cout << "GPU::printFanSpeedRGBCycle() fan speed:" << fanSpeed << " RGB cycle: " << currentRGB << std::endl; 
}

void GPU::upgrade()
{
    while(model < 5)
    {
        if(model == 1)
        {
            std::cout << "You got a GTX 1660!" << std::endl;
            ++model;
        }
        if(model == 2)
        {
            std::cout << "You got a RTX 2070!"<< std::endl;
            ++model;
        }
        if(model == 3)
        {
            std::cout << "You got a RTX 3070!"<< std::endl;
            ++model;
        }
        if(model == 4)
        {
            std::cout << "You got a RTX 4090!"<< std::endl;
            ++model;
        }
    }
    model = 1;
}


struct Computer
{
    Computer();
    ~Computer();
    CPU myCPU;
    Motherboard myMotherboard;
    KeyboardAndMouse myKeyboardAndMouse;
    CoolingSystem myCoolingSystem;
    GPU myGPU;

    void runProgram(float complexity);
    void allocateRAM();
    void refreshDisplay();
    void printStats();
    void typingAndPowerStatus(int a, int b);
};

Computer::Computer()
{
    std::cout << "Computer has been constructed!" << std::endl;
}

Computer::~Computer()
{
    std::cout << "This is Computer's destructor!" << std::endl;
}

void Computer::runProgram(float complexity)
{
    std::cout << "You are running my program..." << std::endl;
    myCPU.temperature += complexity;
}

void Computer::allocateRAM()
{
    myMotherboard.dataToRAM();
    std::cout << "You can always download more..." << std::endl;
    std::cout << "Total RAM is " << myMotherboard.maxRAM << std::endl;
}

void Computer::refreshDisplay()
{
    myMotherboard.generateAVSignals();
    myGPU.outputAVSignal();
}

void Computer::printStats()
{
    myMotherboard.printMaxRAMAndManufacturer();
    myGPU.printFanSpeedRGBCycle();
}

void Computer::typingAndPowerStatus(int a, int b)
{
    myKeyboardAndMouse.typing(a);
    myCoolingSystem.powerStatus(b);
}
  /*
   new UDT 4:
   with 2 member functions
   */
struct Flock
{
    Flock();
    ~Flock();

    Bird flockLeader;
    Bird flockMember1;
    Bird flockMember2;
    Bird flockMember3;

    void fly(double x, double y);
    void feast();
};

Flock::Flock()
{
    flockLeader.wingspan = 19.0;
    flockMember1.wingspan = 17.5;
    flockMember2.wingspan = 13.6;
    flockMember3.wingspan = 14;
}

Flock::~Flock()
{
    std::cout << "Flock Leader flew " << flockLeader.distance << ", flock member 1 flew " << flockMember1.distance << ", flock member 2 flew " << flockMember2.distance << ", flock member 3 flew " << flockMember3.distance << ", for a total of " << flockLeader.distance + flockMember1.distance + flockMember1.distance + flockMember1.distance << "!" << std::endl; // i have no idea why flock member 2 has a different distance than the others
}

void Flock::fly(double x, double y)
{
    int totalFlaps;
    flockLeader.fly(x, y);
    flockMember1.fly(x, y);
    flockMember2.fly(x, x);
    flockMember3.fly(x, y);

    totalFlaps = flockLeader.howManyFlaps() + flockMember1.howManyFlaps() + flockMember2.howManyFlaps() + flockMember3.howManyFlaps();
    std::cout << "The flock members flapped their wings " << totalFlaps << " times!" << std::endl; //flockMember2 seems to have less than everybody else, for some reason
}

void Flock::feast()
{
    flockLeader.eat("worm");
    flockMember1.eat("worm");
    flockMember2.eat("worm");
    flockMember3.eat("worm");
    flockLeader.forage(flockLeader.fledgling);
    flockMember1.forage(flockMember1.fledgling);
    flockMember2.forage(flockMember2.fledgling);
    flockMember2.forage(flockMember2.fledgling);
}
  /*
   new UDT 5:
   with 2 member functions
   */
struct ServerFarm
{
    ServerFarm();
    ~ServerFarm();
    
    Computer lenovo;
    Computer asus;
    Computer IBM;
    Computer apple;
    Computer acer;

    void cloudHosting(float complexity);
    void howMuchRAM(int much);
};

ServerFarm::ServerFarm()
{
    ServerFarm::cloudHosting(30);    
}

ServerFarm::~ServerFarm()
{
    ServerFarm::howMuchRAM(10);
}

void ServerFarm::cloudHosting(float complexity)
{
    lenovo.runProgram(complexity);
    asus.runProgram(complexity);
    IBM.runProgram(complexity);
    apple.runProgram(complexity);
    acer.runProgram(complexity);

    lenovo.myCPU.overheat();
    asus.myCPU.overheat();
    IBM.myCPU.overheat();
    apple.myCPU.overheat();
    acer.myCPU.overheat();
}

void ServerFarm::howMuchRAM(int much)
{
    for(int i = much; i > 0; --i)
    {
        lenovo.allocateRAM();
        asus.allocateRAM();
        IBM.allocateRAM();
        apple.allocateRAM();
        acer.allocateRAM();
    }
}
  /*
   MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

   Commit your changes by clicking on the Source Control panel on the left,
   entering a message, and click [Commit and push].

   If you didn't already:
      Make a pull request after you make your first commit
      pin the pull request link and this repl.it link to our DM thread in a
   single message.

   send me a DM to review your pull request when the project is ready for
   review.

   Wait for my code review.
   */

#include <iostream>
  int main() 
{
    Guitar tele;
    Guitar::GuitarString tele1;
    Bird bird;
    Bird::Progeny progeny;
    CPU ryzen;
    Motherboard motherboard;
    KeyboardAndMouse logitech;
    CoolingSystem noctua;
    GPU nvidia;
    Computer dell;
    Flock seagulls;
    ServerFarm noVa;

    tele.emitNote(tele1, 7);
    tele.detachFromStrap();
    tele.feedback();
    tele1.bend(2, 0.3f);
    tele1.degrade(20.5f);
    tele1.snap();
    bird.eat("worm");
    bird.fly(6348.22, 81000.2);
    bird.sing();
    bird.forage(progeny);
    progeny.flyTheNest();
    progeny.eat(.67f, "worm");
    progeny.chirp(true, .788f, 12);
    ryzen.storeData();
    ryzen.compute(46.7866f, 30027.11111f);
    ryzen.outputResults();
    motherboard.autoSuspend();
    motherboard.dataToRAM();
    motherboard.generateAVSignals();
    logitech.toggleStatus(false);
    logitech.transmitKeystrokeData();
    logitech.transmitXYChange(753.22, 966.80);
    noctua.setFanSpeed(2);
    noctua.setLightColor("orange");
    noctua.springALeak();
    nvidia.adjustFanSpeed(3);
    nvidia.cycleRGBDisplay();
    nvidia.outputAVSignal();
    dell.allocateRAM();
    dell.refreshDisplay();
    dell.runProgram(600.);
    

    std::cout << "Progeny's percent to maturity is " << progeny.percentToMaturity << "." << std::endl;
    std::cout << "The Result of Ryzen's computation is " << ryzen.outputResults() << "." << std::endl;
    std::cout << "Noctua's RGB color is " << noctua.lightColor << "." << std::endl;

    tele.printPickupsStrings();
    tele1.printMaterialCoated();
    bird.printMaleWingspan();
    progeny.printSatedEgg();
    ryzen.printClockSpeedAndSocket();
    motherboard.printMaxRAMAndManufacturer();
    logitech.printNumpadAndLanguage();
    noctua.printFansRGB();
    nvidia.printFanSpeedRGBCycle();
    dell.printStats();

    tele.polish();
    tele1.microwave(4);
    bird.howManyFlaps();
    progeny.hatch();
    ryzen.overheat();
    motherboard.badSectors();
    logitech.typing(7);
    noctua.powerStatus(2);
    nvidia.upgrade();
    dell.typingAndPowerStatus(2, 3);

    seagulls.feast();
    seagulls.fly(587.44, 30000.7);
    noVa.cloudHosting(6000.4f);
    noVa.howMuchRAM(3);
    std::cout << "good to go!" << std::endl;
  }
