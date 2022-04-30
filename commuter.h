#ifndef commuter_h_
#define commuter_h_

class Commuter{
public:

    // default constructor
    Commuter();

    // constructor
    Commuter(int inID, double inV, int inTa, int inTb, double inTauB);

    // setters
    void reroll(int i);

    // getters
    int getID()                 {return id;}
    double getV()               {return V;}
    int getTa()                 {return Ta;}
    int getTb()                 {return Tb;}
    double getTauB()            {return tauB;}

    double getTauAMax()         {return tauAMax;}
    double getUap()             {return Uap;}
    double getUb()              {return Ub;}

    bool UapCheck();

private:
    int id;
    double V;
    int Ta;
    int Tb;
    double tauB;
    double tauAMax;
    double Uap;
    double Ub;
};


#endif