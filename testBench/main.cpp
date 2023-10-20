//
//  main.cpp
//  testBench
//
//  Created by 킹민중 on 10/20/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "data_process.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream test;
    size_t temp;
    size_t temp1;
    string test_case[12] = {"Ax1", "Ax0", "Ay1", "Ay0", "Az1", "Az0", "Gx1", "Gx0", "Gy1", "Gy0", "Gz1", "Gz0"};
    test.open("/Users/kimminjoong/Desktop/Project/HSMS/cpp/testBench/testBench/testbench.txt");
    int data[5066][12] = {};
    // Ax1, Ax0, Ay1, Ay0, Az1, Az0, Gx1, Gx0, Gy1, Gy0, Gz1, Gz0
    
    if(!test.fail()) {
        string line;
        cout << "file open" << endl;
        int i = 0;
        while(!test.eof()) {
            getline(test, line);
            if(line.find(test_case[0]) != string::npos) {
                    for(int j = 0; j < 12; j++) {
                        if(j < 11) {
                            temp = line.find(test_case[j]);
                            temp1 = line.find(test_case[j+1]);
                            data[i][j] = (uint8_t)stoi(line.substr(temp+5, temp1-temp-6));
                        }
                        else {
                            temp = line.find(test_case[11]);
                            temp1 = line.find('\r');
                            data[i][j] = (uint8_t)stoi(line.substr(temp+5, temp1-temp-6));
                        }
                    }
            }
            i++;
        }
    }
    
    float accel_val[3] = {};
    float gyro_val[3] = {};
    float gb[3] = {};
    float roll = 0.0;
    float pitch = 0.0;
    float yaw = 0.0;
    float P[2][2] = {};
    
    
    for(int i = 0; i < 5066; i++) {
        get_accel(data[i][0], data[i][1], data[i][2], data[i][3], data[i][4], data[i][5], accel_val);
        get_gyro(data[i][6], data[i][7], data[i][8], data[i][9], data[i][10], data[i][11], gyro_val);
        cout << "Ax: " << accel_val[0] << " Ay: " << accel_val[1] << " Az: " << accel_val[2];
        cout << " Gx: " << gyro_val[0] << " Gy: " << gyro_val[1] << " Gz: " << gyro_val[2] << endl;
        
        measure_orient (gyro_val[0], gyro_val[1], gyro_val[2], gb, accel_val[0], accel_val[1], accel_val[2], &roll, &pitch, &yaw, P);
        cout << "roll: " << roll << " pitch: " << pitch << " yaw: " << yaw << endl;
    }
    
    return 0;
}
