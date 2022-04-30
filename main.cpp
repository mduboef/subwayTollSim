#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <random>
#include <algorithm>

#include "commuter.h"


bool compare(Commuter & c1, Commuter & c2){
    return c1.getTauAMax() > c2.getTauAMax();
}


int main(){


    std::vector<int> stationPop(38, 0);

    int goal = 336;
    double goalOcc = 0.8;
    int stops = 416;

    // read in station populations 
    std::ifstream file("data.txt");
    std::string str;
    int lineCount = 0;
    int count = 0;
    while(std::getline(file, str)){
        lineCount++;
        if(lineCount%2 == 0){
            // divide daily number of commuters at station by num of trains stopping
            stationPop[count] = std::stoi(str)/416;
            count++;
        }
    }


    std::vector<std::vector<Commuter>> stations;

    std::vector<std::vector<double>> tauVec;

    // construct commuters from each station
    for(int i = 0; i != stationPop.size(); i++){

        std::cout << i << " : " << stationPop[i];

        std::vector<Commuter> s;

        std::vector<double> t;

        // double tauArr[stationPop[i].size()];

        for(int j = 0; j != stationPop[i]; j++){

            // randomize V
            double V = (20 + ( std::rand() % ( 80 - 20 + 1 ) ))/100.0;

            // randomize Tb
            int Tb = 0;
            if(i != 37){
                Tb = 1 + ( std::rand() % ( 3*(37-i) - 1 + 1 ) );
            }
            
            // radomize Ta
            int Ta = 37;
            if(i != 37){
                Ta = (i+1) + ( std::rand() % ( 37 - (i+1) + 1 ) );
            }
            Ta = 2*(Ta-i);

            // randomize tauB
            double tauB = (0 + ( std::rand() % ( 500 - 0 + 1 ) ))/100.0;

            Commuter newCommuter (j, V, Ta, Tb, tauB);
            while ( newCommuter.UapCheck() == false ){
                newCommuter.reroll(i);
            }

            s.push_back(newCommuter);

            t.push_back(newCommuter.getTauAMax());

        }
        std::cout << std::endl;

        stations.push_back(s);

        std::sort(t.begin(), t.end());
        tauVec.push_back(t);

        // std::sort(stationPop[i][0], stationPop[i][stationPop[i].size()], compare);

    }

    std::cout << std::endl << std::endl;


    // for(int i = 0; i != tauVec[1].size(); i++){
    //     std::cout << tauVec[1][i] << std::endl;
    // }


    //                                  traversal

    std::vector<int> boardedNum;

    int o = 0;
    for (int i = 0; i != tauVec.size(); i++){

        // seats = num of commuter unless cant fit all
        int seats = stationPop[i];
        if(o+seats > goal){seats = goal - o;}

        if(seats > 0){
            double toll = tauVec[i][tauVec[i].size()-seats];
            std::cout << "Station " << i << " : " << seats << "/" << stationPop[i] << " : $" << toll << std::endl;
        }else{
            std::cout << "Station " << i << " : " << seats << " : $" << 35 << std::endl;
        }

        o += seats;

        boardedNum.push_back(seats);

        // deboard old passengers
        if(i >= 5){
            o -= boardedNum[i-5];
        }
    }

    std::cout << std::endl << std::endl;



    

    return 0;
}