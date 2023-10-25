//
//  data_process.cpp
//  testBench
//
//  Created by 킹민중 on 10/20/23.
//

#include "data_process.hpp"


void get_accel(uint8_t ax0, uint8_t ax1, uint8_t ay0, uint8_t ay1, uint8_t az0, uint8_t az1, float* accel_val) {
    float accel_bias[3] = {};
    float accel_sf[3] = {1.0f, 1.0f, 1.0f};
    
    int16_t val_x = ((uint16_t)ax0 << 8) | (uint16_t)ax1;
    int16_t val_y = ((uint16_t)ay0 << 8) | (uint16_t)ay1;
    int16_t val_z = ((uint16_t)az0 << 8) | (uint16_t)az1;
    
    *accel_val = ((val_x * A_FSR/32768.0) * gravity - accel_bias[0]) * accel_sf[0];
    *(accel_val+1) = ((val_y * A_FSR/32768.0) * gravity - accel_bias[1]) * accel_sf[1];
    *(accel_val+2) = ((val_z * A_FSR/32768.0) * gravity - accel_bias[2]) * accel_sf[2];

}

void get_gyro(uint8_t gx0, uint8_t gx1, uint8_t gy0, uint8_t gy1, uint8_t gz0, uint8_t gz1, float* gyro_val) {
    float gyro_bias[3] = {};
    int16_t val_x = ((uint16_t)gx0 << 8) | (uint16_t)gx1;
    int16_t val_y = ((uint16_t)gy0 << 8) | (uint16_t)gy1;
    int16_t val_z = ((uint16_t)gz0 << 8) | (uint16_t)gz1;
    float G_RANGE = G_FSR * (2/65535.0);
    *gyro_val = (val_x * G_RANGE) - gyro_bias[0];
    *(gyro_val+1) = (val_y * G_RANGE) - gyro_bias[1];
    *(gyro_val+2) = (val_z * G_RANGE) - gyro_bias[2];
}

void measure_orient (float gyro_x, float gyro_y, float gyro_z, float* gb, float ax, float ay, float az, float* roll, float* pitch, float* yaw, float P[2][2]) {
        float acc_r = 180 * atan2(ay, sqrt(ax*ax + az*az))/M_PI;
        float acc_p = 180 * atan2(ax, sqrt(ay*ay + az*az))/M_PI;
        float acc_y = atan2(ay, ax);
        // process noise covariance
        float Q = 0.001;
        float Q_bias = 0.003;
        // measurement noise variance
        float R = 0.02;
        float rate_x = gyro_x - (*gb);
        *roll += 0.01*rate_x;
        float rate_y = gyro_y - (*(gb+1));
        *pitch += 0.01*rate_y;
        float rate_z = gyro_z - (*(gb+2));
        *yaw += 0.01*rate_z;

        P[0][0] -= (P[1][0] + P[0][1] - P[1][1]*0.01 - Q)*0.01;
        P[0][1] -= P[1][1]*0.01;
        P[1][0] -= P[1][1]*0.01;
        P[1][1] += Q_bias*0.01;

        float y_r = acc_r - (*roll);
        float y_p = acc_p - (*pitch);
        float y_y = acc_y - (*yaw);

        float s = P[0][0] + R;
        float k[2] = {P[0][0]/s, P[1][0]/s};

        float temp = P[0][0];
        float temp1 = P[0][1];
        P[0][0] -= k[0]*temp;
        P[0][1] -= k[0]*temp1;
        P[1][0] -= k[1]*temp;
        P[1][1] -= k[1]*temp1;

        *roll += k[0]*y_r;
        *gb += k[1]*y_r;
        *pitch += k[0]*y_p;
        *(gb+1) += k[1]*y_p;
        *yaw += k[0]*y_y;
        *(gb+2) += k[1]*y_y;
}
