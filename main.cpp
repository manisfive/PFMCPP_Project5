/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 2) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 3) write the name of your class where it says "OwnerClass"
 
 4) write wrapper classes for each type similar to how it was shown in the video
 
 5) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

6) If you have a class that has a nested class in it, and an instantiation of that nested class as a member variable, 
    - you do not need to write a Wrapper for that nested class
    - you do not need to replace that nested instance with a wrapped instance.
    If you want an explanation, message me in Slack

7) If you were using any UDTs as function arguments like this:
*/
#if false
void someMemberFunction(Axe axe);
#endif
/*
  Pass those arguments by Reference now that you know what references are (Project 6 Part 2).
*/
#if false
void someMemberFunction(Axe& axe);
#endif
/*
If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
Additionally, you can mark class member functions as 'const'
If you do this, you are promising that the member function will not modify any member variables.

Mark every member function that is not modifying any member variables as 'const'
*/
#if false
//a function where the argument is passed by const-ref
void someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 Clear any warnings about exit-time-destructors.
 Suppress them by adding -Wno-exit-time-destructors to the .replit file with the other warning suppression flags
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
    void printModelGauge();
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

void Guitar::printModelGauge()
{
        std::cout << "Your guitar is a " << this->makeModel << " with " << this->stringPlaying.gauge << " guage strings on it." << std::endl;
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
        void printPercentToMaturity();
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

void Bird::Progeny::printPercentToMaturity()
{
    std::cout << "Progeny's percent to maturity is " << this->percentToMaturity << "." << std::endl;
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
    float temperature = 30.f;
    float totalBitcoinMined = 0;

    void outputAVSignal();
    void cycleRGBDisplay(); 
    void adjustFanSpeed(int speed);
    void printFanSpeedRGBCycle();
    void upgrade();
    float mineBitcoin(float x, float y);
    void overheat();
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

float GPU::mineBitcoin(float x, float y)
{
    totalBitcoinMined += x * y * temperature;
    temperature *= 1.8f;
    return x * y * temperature;
}

void GPU::overheat()
{
    if(temperature > 1500)
    {
        std::cout << "Overheated! Shutting down..." << std::endl;
        temperature = 55;
    }   
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
    void printMemberTwoAndThreeDistance();
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
    flockMember2.fly(x, y);
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

void Flock::printMemberTwoAndThreeDistance()
{
    std::cout << "Flock members 2 and 3 have flown " << this->flockMember2.distance + this->flockMember3.distance << "." << std::endl;
}
  /*
   new UDT 5:
   with 2 member functions
   */
struct BitcoinMiningOp
{
    BitcoinMiningOp();
    ~BitcoinMiningOp();

    GPU subGPU1;
    GPU subGPU2;
    GPU subGPU3;
    GPU subGPU4;
    GPU subGPU5;

    void mineBitcoin(float complexity);
    void mtGox();
};

BitcoinMiningOp::BitcoinMiningOp()
{
    mineBitcoin(5.5f);
}

BitcoinMiningOp::~BitcoinMiningOp()
{
    mineBitcoin(30.f);
    mineBitcoin(40.f);
    mineBitcoin(50.f);
    mtGox();
}

void BitcoinMiningOp::mineBitcoin(float amount)
{
    float subtotal = 0.f;
    subtotal += subGPU1.mineBitcoin(amount, amount / 3.f);
    amount *= 6.f;
    subtotal += subGPU2.mineBitcoin(amount / 3.66f, amount * 8.44444f);
    amount /= 2.99f;
    subtotal += subGPU3.mineBitcoin(amount + 70.f, amount * 90.f);
    amount += 33.33333333f;
    subtotal += subGPU4.mineBitcoin(amount * 10.f, amount * 1.11f);
    amount *= .02790f;
    subtotal += subGPU5.mineBitcoin(amount, amount / 2.f);

    subGPU1.overheat();
    subGPU2.overheat();
    subGPU3.overheat();
    subGPU4.overheat();
    subGPU5.overheat();
    std::cout << "You Mined " << subtotal << " Bitcoin this session!" << std::endl;
}

void BitcoinMiningOp::mtGox()
{
    float total = subGPU1.totalBitcoinMined + subGPU2.totalBitcoinMined + subGPU3.totalBitcoinMined + subGPU4.totalBitcoinMined + subGPU5.totalBitcoinMined;
    std::cout << "You mined " << total << " but it got stolen by the exchange!!" << std::endl;
    subGPU1.totalBitcoinMined = 0;
    subGPU2.totalBitcoinMined = 0;
    subGPU3.totalBitcoinMined = 0;
    subGPU4.totalBitcoinMined = 0;
    subGPU5.totalBitcoinMined = 0;
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
    GPU nvidia;
    Flock seagulls;
    BitcoinMiningOp botNet;

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
    nvidia.adjustFanSpeed(3);
    nvidia.cycleRGBDisplay();
    nvidia.outputAVSignal();

    std::cout << "Progeny's percent to maturity is " << progeny.percentToMaturity << "." << std::endl;
    progeny.printPercentToMaturity();
    std::cout << "Your guitar is a " << tele.makeModel << " with " << tele1.gauge << " guage strings on it." << std::endl;
    tele.printModelGauge();
    std::cout << "Flock members 2 and 3 have flown " << seagulls.flockMember2.distance + seagulls.flockMember3.distance << "." << std::endl;
    seagulls.printMemberTwoAndThreeDistance();
    
    tele.printPickupsStrings();
    tele1.printMaterialCoated();
    bird.printMaleWingspan();
    progeny.printSatedEgg();
    nvidia.printFanSpeedRGBCycle();

    tele.polish();
    tele1.microwave(4);
    bird.howManyFlaps();
    progeny.hatch();
    nvidia.upgrade();

    seagulls.feast();
    seagulls.fly(587.44, 30000.7);
    botNet.mtGox();
    std::cout << "good to go!" << std::endl;
  }
