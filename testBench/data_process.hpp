//
//  data_process.hpp
//  testBench
//
//  Created by 킹민중 on 10/20/23.
//

#ifndef data_process_hpp
#define data_process_hpp

#include <stdio.h>
#include <cstdint>
#include <math.h>

#define A_FSR 16
#define G_FSR 2000
#define gravity 9.81

void get_accel(uint8_t ax0, uint8_t ax1, uint8_t ay0, uint8_t ay1, uint8_t az0, uint8_t az1, float* accel_val);
void get_gyro(uint8_t gx0, uint8_t gx1, uint8_t gy0, uint8_t gy1, uint8_t gz0, uint8_t gz1, float* gyro_val);
void measure_orient (float gyro_x, float gyro_y, float gyro_z, float* gb, float ax, float ay, float az, float* roll, float* pitch, float* yaw, float P[2][2]);



#endif /* data_process_hpp */
