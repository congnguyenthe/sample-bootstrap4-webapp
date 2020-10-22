#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include "stdint.h" // for uint8_t, uint16_t...NEEDED in micro-controller
#include "stdlib.h" // for atoi. Might NOT NEEDED in micro-controller
#include "stdio.h" // for fopen, fclosed. Might NOT NEEDED in micro-controller
#include "string.h" // for strcpy, strtok. Might NOT NEEDED in microcontroller
#include "inttypes.h" // for SCNu8. Might NOT NEEDED in micro-controller
#include "math.h" // for fabs. NEEDED in micro-controller

#define MAX_FILE_ROW                            263
#define TOTAL_CELL_AVERAGE                      8
#define TOTAL_CELL_NORMALIZE_CROSSING_POINT     12
#define MULTIPLE_NUMBER                         5
#define TOTAL_CELL_AVERAGE_SUMAREA_POINT        128
#define TOTAL_CELL_NORMALIZE_SUM_AREA           8

#define HISTOGRAM_LOWER_THRESHOLD               85
#define HISTOGRAM_UPPER_THRESHOLD               195
#define SUM_AREA_LOWER_THRESHOLD                2000
#define SUM_AREA_UPPER_THRESHOLD                11000

void get_file_data(char* filename, uint8_t* spds, char* file_type_str);
void calculate_histogram(uint8_t* spds, uint16_t* first_range, float *spds_diff_to_average);
void calculate_sum_area(uint8_t* spds, float* sum_area, float *spds_diff_to_average);
void data_processing(char* filename);
void data_evaluation(float sum_area, uint16_t histogram_0, uint8_t* result);
uint8_t round_div(uint16_t numerator, uint16_t denominator);

#endif