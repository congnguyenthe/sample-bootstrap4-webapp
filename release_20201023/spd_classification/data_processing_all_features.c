#include "data_processing_all_features.h"

/*
 * --------------------------------
 * DO NOT NEEDED IN MICROCONTROLLER
 * --------------------------------
 * Name:  get_file_data
 * Purpose: read the spd values into an array from the input file
 * Params: 
 *  - filename: Name of the input file
 *  - spds: An array at which the spd values read from the input will be
 *  wrote.
 *  - file_type_str: An char array which will contains the type of the input
 *  file, which are normal, quick or not_move
 * Return: void
 */
void get_file_data(char *filename, uint8_t *spds, char *file_type_str)
{
#ifdef DSIMULATOR
    uint8_t spds_array[MAX_FILE_ROW] = {135, 136, 136, 137, 138, 139, 139, 139, 140, 141, 141, 141, 142, 143, 144, 144, 144, 146, 146, 146, 147, 148, 148, 149, 149, 150, 151, 152, 151, 152, 153, 154, 154, 155, 156, 156, 157, 157, 157, 158, 159, 159, 160, 160, 161, 161, 163, 163, 163, 164, 164, 165, 165, 166, 166, 168, 167, 168, 169, 169, 168, 168, 169, 168, 168, 167, 166, 165, 164, 163, 163, 161, 160, 159, 158, 157, 156, 155, 154, 154, 154, 153, 154, 154, 155, 156, 156, 157, 158, 159, 160, 162, 164, 166, 167, 168, 169, 171, 172, 173, 176, 177, 178, 179, 180, 181, 184, 183, 183, 184, 185, 186, 186, 186, 186, 186, 184, 183, 182, 181, 179, 177, 174, 173, 170, 167, 165, 162, 159, 158, 156, 155, 154, 154, 153, 152, 151, 151, 151, 151, 153, 152, 152, 152, 154, 154, 155, 155, 155, 156, 156, 157, 158, 158, 158, 160, 162, 162, 162, 163, 164, 163, 165, 165, 165, 164, 164, 165, 164, 165, 164, 165, 165, 166, 165, 166, 165, 165, 167, 167, 166, 167, 168, 168, 170, 170, 171, 171, 172, 173, 174, 175, 175, 178, 179, 180, 180, 182, 182, 183, 184, 186, 188, 188, 188, 190, 191, 191, 194, 194, 196, 197, 196, 196, 197, 197, 198, 198, 198, 199, 199, 199, 200, 200, 198, 198, 199, 199, 199, 200, 201, 202, 203, 203, 204, 205, 206, 207, 207, 207, 203, 208, 209, 209, 208, 208, 209, 211, 211, 209, 208, 208, 210, 209, 207, 208, 206, 205, 205, 206, 206, 204, 203, 203, 204, 203, 203, 203, 203, 201, 201, 201, 202, 200, 200, 201, 200, 200, 201, 200, 200, 202, 202, 202, 203, 202, 204, 207, 205, 206, 206, 207, 208, 207, 207, 209, 209, 210, 210, 211, 211, 211, 209, 209, 210, 210, 212, 210, 210, 209, 209, 209, 208, 208, 208, 208, 207, 204, 210, 210, 210, 209, 207, 208, 209, 207, 208, 209, 205, 208, 210, 204, 204, 209, 208, 207, 207, 211, 208, 207, 206, 206, 206, 206, 203, 202, 201, 200, 199, 200, 199, 198, 198, 197, 196, 195, 195, 195, 194, 195, 196, 196, 195, 196, 196, 195, 196, 196, 196, 196, 195, 196, 197, 195, 196, 197, 197, 198, 198, 199, 201, 200, 200, 201, 202, 203, 203, 204, 203, 201, 203, 203, 204, 204, 203, 203, 204, 204, 204, 204, 203, 204, 205, 205, 204, 205, 208, 207, 205, 206, 205, 204, 204, 204, 206, 207, 205, 206, 204, 205, 205, 207, 206, 207, 206, 205, 208, 208, 209, 208, 206, 204, 201, 201, 200, 199, 199, 199, 198, 196, 196, 197, 195, 195, 193, 194, 196, 196, 196, 197, 196, 197, 197, 198, 199, 199, 200, 200, 200, 200, 201, 202, 202, 203, 203, 203, 204, 203, 203, 204, 206, 205, 207, 206, 205, 206, 207, 206, 208, 211, 210, 211, 211, 211, 212, 214, 216, 217, 219, 221, 219, 221, 221, 224, 220, 223, 224, 225, 227, 227, 227, 228, 228, 227, 223, 229, 227, 228, 228, 227, 227, 224, 225, 225, 225, 223, 224, 226, 225};
    for (uint16_t i = 0; i < MAX_FILE_ROW; i++)
    {
        *(spds + i) = spds_array[i];
    }
#else
    // Get file data
    FILE *inputFile;
    inputFile = fopen(filename, "r");
    uint8_t u_temp_value = 0;
    if (NULL != inputFile)
    {
        uint16_t loop = 0;
        while (fscanf(inputFile, "%" SCNu8, &u_temp_value) == 1)
        {
            if (loop < MAX_FILE_ROW)
            {
                *(spds + loop) = u_temp_value;
                ++loop;
            }
        }
    }
    else
    {
        printf("read file error\n");
    }
    fclose(inputFile);

    // Get file name to int
    u_temp_value = 0;
    char *file_type_str_cpy = (char *)malloc(sizeof(char) * 10);
    strcpy(file_type_str_cpy, filename);
    file_type_str_cpy = strtok(file_type_str_cpy, "_");
    file_type_str_cpy = strtok(NULL, "_");
    if (file_type_str_cpy)
    {
        u_temp_value = atoi(file_type_str_cpy);
        if (u_temp_value % 4 == 0)
        {
            strcpy(file_type_str, "quick");
        }
        else if (u_temp_value % 4 == 1)
        {
            strcpy(file_type_str, "normal");
        }
        else if (u_temp_value % 4 == 2)
        {
            strcpy(file_type_str, "not_move");
        }
        else if (u_temp_value % 4 == 3)
        {
            strcpy(file_type_str, "strong");
        }
    }
    else
    {
        printf("file name to int error\n");
    }
#endif
}


/*
 * -------------------------
 * NEEDED IN MICROCONTROLLER
 * -------------------------
 * Name:  calculate_sum_area 
 * Purpose: Calculate the sum area feature from an array of spd values
 * Params: 
 *  - spds: An array contains spd values which will be used to calculate the 
 *  sum area feature
 *  - sum_area: A float pointer which will be used to return the sum area value 
 * Return: void
 */
void calculate_sum_area(uint8_t *spds, float *sum_area, float *spds_diff_to_average)
{
    uint8_t divide_result_sumarea = 0;
    int8_t count = 0;
    float *f_temp_value = (float *)malloc(sizeof(float));
    float *normalize_list_sumarea = (float *)malloc(sizeof(float) * (MAX_FILE_ROW - TOTAL_CELL_NORMALIZE_SUM_AREA + 1));
    divide_result_sumarea = round_div(MAX_FILE_ROW - TOTAL_CELL_NORMALIZE_CROSSING_POINT + 1, TOTAL_CELL_AVERAGE_SUMAREA_POINT);    

    *f_temp_value = 0;
    for (uint16_t i = 0; i < MAX_FILE_ROW - TOTAL_CELL_NORMALIZE_SUM_AREA + 1; i++)
    {
        *f_temp_value = 0;
        for (uint8_t j = 0; j < TOTAL_CELL_NORMALIZE_SUM_AREA; j++)
        {
            *f_temp_value += *(spds_diff_to_average + i + j);
        }

        *(normalize_list_sumarea + i) = (float)*f_temp_value / TOTAL_CELL_NORMALIZE_SUM_AREA;
    }

    float *average_list_sumarea = (float *)malloc(sizeof(float) * divide_result_sumarea);
    *f_temp_value = 0;
    for (uint16_t i = 0; i <= divide_result_sumarea * TOTAL_CELL_AVERAGE_SUMAREA_POINT; i += TOTAL_CELL_AVERAGE_SUMAREA_POINT)
    {
        *f_temp_value = 0;
        for (uint16_t j = 0; j < TOTAL_CELL_AVERAGE_SUMAREA_POINT; j++)
        {
            *f_temp_value += *(normalize_list_sumarea + i + j);
        }
        *(average_list_sumarea + count) = (float)*f_temp_value / TOTAL_CELL_AVERAGE_SUMAREA_POINT;
        count += 1;
    }
    

    *sum_area = 0;
    for (uint16_t i = 0; i < divide_result_sumarea * TOTAL_CELL_AVERAGE_SUMAREA_POINT; i++)
    {
        *sum_area += fabs(*(normalize_list_sumarea + i) - *(average_list_sumarea + (int)(i / TOTAL_CELL_AVERAGE_SUMAREA_POINT)));
    }

    free(normalize_list_sumarea);
    free(average_list_sumarea);
    free(f_temp_value);
}


/*
 * -------------------------
 * NEEDED IN MICROCONTROLLER
 * -------------------------
 * Name:  calculate_histogram
 * Purpose: Calculate the histogram feature from an array of spd values
 * Params:
 *  - spds: An array contains spd values which will be used to calculate the histogram feature
 *  - first_range: A float pointer which will be used to return the histogram value 
 * Return: void
 */
void calculate_histogram(uint8_t *spds, uint16_t *first_range, float *spds_diff_to_average)
{
    float *average_list_histogram = (float *)malloc(sizeof(float) * (MAX_FILE_ROW - TOTAL_CELL_AVERAGE + 1));
    float *f_temp_value = (float *)malloc(sizeof(float));

    *f_temp_value = 0;
    // cal average each 8 spd
    for (uint16_t i = 0; i < MAX_FILE_ROW - TOTAL_CELL_AVERAGE + 1; i++)
    {
        *f_temp_value = 0;
        for (int8_t j = 0; j < TOTAL_CELL_AVERAGE; j++)
        {
            *f_temp_value += *(spds_diff_to_average + i + j);
        }
        *(average_list_histogram + i) = (float)(*f_temp_value) / TOTAL_CELL_AVERAGE;
    }

    for (uint16_t i = 1; i < MAX_FILE_ROW - TOTAL_CELL_AVERAGE + 1; i++)
    {
        *f_temp_value = (float)(*(average_list_histogram + i) - *(average_list_histogram + (i - 1)));
        *f_temp_value = fabs(*f_temp_value);

        if (*f_temp_value == 0.0)
        {
            *first_range += 1;
        }
    }

    free(f_temp_value);
    free(average_list_histogram);
}


/*
 * -------------------------
 * NEEDED IN MICROCONTROLLER
 * -------------------------
 * Name:  round_div 
 * Purpose: An utility function which will be used to round up the float value
 * after divided
 * Params: 
 *  - numerator: An uint16_t number which will be acted as numerator
 *  - denominator: An uint16_t number which will be acted as denominator
 * Return: Round up value after divided
 */
uint8_t round_div(uint16_t numerator, uint16_t denominator)
{
    uint8_t div_result = (uint8_t)(numerator / denominator);
    float *f_temp_value = (float *)malloc(sizeof(float));
    *f_temp_value = (float)(numerator % denominator) / denominator;
    if (*f_temp_value >= 0.5)
    {
        div_result += 1;
    }
    free(f_temp_value);
    return div_result;
}

/*
 * -------------------------
 * NEEDED IN MICROCONTROLLER
 * -------------------------
 * Name:  data_evaluation 
 * Purpose: Evaluate the type of data with corresponding spd values
 * Params: 
 *  - sum_area: A float number which contains the sum area value
 *  - histogram_0: An uint16_t number which contains the histogram 0 value
 *  - result: An u_int8_t pointer which will be used to saved the result
 *  of the classification. The "result" value 1 means Normal, 2 means Quick and 3 means Not Move
 * Return: void
 */
void data_evaluation(float sum_area, uint16_t histogram_0, uint8_t* result)
{
    // printf("sum_area: %f",sum_area);
    // printf("\nhistogram_0: %d",histogram_0);
    // Check histogram
    if (HISTOGRAM_LOWER_THRESHOLD <= histogram_0 && histogram_0 <= HISTOGRAM_UPPER_THRESHOLD)
    {
        *result = 1;
        return;
    }
    else if (histogram_0 < HISTOGRAM_LOWER_THRESHOLD)
    {
        // Check sum_area
        if (SUM_AREA_LOWER_THRESHOLD <= sum_area && sum_area <= SUM_AREA_UPPER_THRESHOLD)
        {
            // normal type
            *result = 1;
            return;
        }
        else if (sum_area > SUM_AREA_UPPER_THRESHOLD)
        {
            // quick type
            *result = 2;
            return;
        }
        else // sum_area < SUM_AREA_LOWER_THRESHOLD
        {
            // not move
            *result = 3;
            return;
        }
    }
    else // histogram_0 >= HISTOGRAM_UPPER_THRESHOLD
    {
        // Check sum_area
        if (SUM_AREA_LOWER_THRESHOLD <= sum_area && sum_area <= SUM_AREA_UPPER_THRESHOLD)
        {
            // normal type
            *result = 1;
            return;
        }
        else if (sum_area > SUM_AREA_UPPER_THRESHOLD)
        {
            // quick type
            *result = 2;
            return;
        }
        else // sum_area < SUM_AREA_LOWER_THRESHOLD
        {
            // not move type
            *result = 3;
            return;
        }
    }
}


void calculate_average(uint8_t *spds, float *spds_diff_to_average) {
    float *f_temp_value = (float *)malloc(sizeof(float));
    *f_temp_value = 0;

    for (uint16_t i = 0; i < MAX_FILE_ROW; i++)
    {
        *f_temp_value += *(spds + i);
    }

    *f_temp_value = (float)*f_temp_value / MAX_FILE_ROW;

    for (uint16_t i = 0; i < MAX_FILE_ROW; i++)
    {
        *(spds_diff_to_average + i) = ((float)*(spds + i) - *f_temp_value) * MULTIPLE_NUMBER;
    }
}
/*
 * --------------------------------
 * DO NOT NEEDED IN MICROCONTROLLER
 * --------------------------------
 * Name:  data_processing 
 * Purpose: Read and evalue data from an input file
 * Params: 
 *  - filename: A char array contains the name of file
 * Return: void
 */
void data_processing(char *filename)
{
    uint8_t *spds = (uint8_t *)malloc(sizeof(uint8_t) * MAX_FILE_ROW);
    char *file_type_str = (char *)malloc(sizeof(char) * 10);
    get_file_data(filename, spds, file_type_str);

    float *spds_diff_to_average = (float *)malloc(sizeof(float) * MAX_FILE_ROW);
    calculate_average(spds, spds_diff_to_average);

    float *sum_area = (float *)malloc(sizeof(float));
    calculate_sum_area(spds, sum_area, spds_diff_to_average);

    uint16_t first_range = 0;
    calculate_histogram(spds, &first_range, spds_diff_to_average);

    free(spds);

    uint8_t* result = (uint8_t *)malloc(sizeof(uint8_t));
    data_evaluation(*sum_area, first_range, result);

// #ifndef DSIMULATOR
    char *result_type_str = (char *)malloc(sizeof(char) * 10);
    if (*result == 1) {
        strcpy(result_type_str, "normal");
    } else if (*result == 2) {
        strcpy(result_type_str, "quick");
    } else if (*result == 3 ) {
        strcpy(result_type_str, "not_move");
    } else {
        strcpy(result_type_str, "undefined");
    }
    //Write to file, append data
    FILE *ouput_file = fopen("final_result.csv", "a");
    if (ouput_file == NULL)
    {
        printf("write to file error");
        free(file_type_str);
        free(result_type_str);
        free(sum_area);
        return;
    }
    else
    {
        fprintf(ouput_file, "%s, %s, %f, %d, %s \n",
                filename,
                file_type_str,
                *sum_area,
                first_range,
                result_type_str);
    }

    fclose(ouput_file);
// #endif

    free(file_type_str);
    free(sum_area);
}