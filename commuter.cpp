#include <random>

#include "commuter.h"

Commuter::Commuter(){
    id = -1;
    V = -1;
    Ta = -1;
    Tb = -1;
    tauAMax = -1;
    tauB = -1;
    Uap = -1;
    Ub = -1;

}


Commuter::Commuter(int inID, double inV, int inTa, int inTb, double inTauB){
    id = inID;
    V = inV;
    Ta = inTa;
    Tb = inTb;
    tauB = inTauB;
    
    Uap = -Ta;
    Ub = -Tb-(tauB/V);

    tauAMax = -1*V*(Ub+Ta);

}


bool Commuter::UapCheck(){
    if( Uap < Ub ){
        return false;
    }
    return true;
}


void Commuter::reroll(int i){

    // randomize V
    V = (20 + ( std::rand() % ( 80 - 20 + 1 ) ))/100.0;

    // randomize Tb
    Tb = 0;
    if(i != 37){
        Tb = 1 + ( std::rand() % ( 3*(37-i) - 1 + 1 ) );
    }
    
    // radomize Ta
    Ta = 37;
    if(i != 37){
        Ta = (i+1) + ( std::rand() % ( 37 - (i+1) + 1 ) );
    }
    Ta = 2*(Ta-i);

    // randomize tauB
    tauB = (0 + ( std::rand() % ( 500 - 0 + 1 ) ))/100.0;

    Uap = -Ta;
    Ub = -Tb-(tauB/V);

    tauAMax = -1*V*(Ub+Ta);
}

