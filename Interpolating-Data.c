#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct points_record {
    double x_value;
    double y_value;
};


double interpolate(double x1,double y1,double x_interpolate,double x2,double y2) {
    double y_interpolate;
    y_interpolate = y2 + ((y1 - y2) / (x1 - x2)) * (x_interpolate - x2);
    return y_interpolate;
}


int main(){

    int times=0;
    size_t count = 0;
    size_t output_size = 57;
    struct points_record records[100];
    double x_output[output_size];
    double y_output[output_size];
    double interpleted_time;
    double oversized_time=0;

    FILE *data_file = fopen("Data/raw_data.csv","r");
    FILE *interpolated_file;
    if (data_file==NULL){
        perror("Unable to open the file.");
        exit(1);
    }

    for(;count<sizeof(records)/sizeof(records[0]);++count){
        int got = fscanf(data_file,"%lf,%lf",&records[count].x_value,&records[count].y_value);
        if (got != 2) break;
    }

    fclose(data_file);
    interpleted_time= (double)output_size/(double)(count);
    printf("interpolating time between each coordinates: %lf \n",interpleted_time);
    printf("==============================\n\n");
    printf("X values from the input are: ");

    for (int i=0;i<count;i++){
        printf("%.2lf ",records[i].x_value);
    }


    printf("\nY values from the input are: ");
    for (int i=0;i<count;i++){
        printf("%.2lf ",records[i].y_value);}
    printf("\n\n==============================");

    printf("\n\nAll the coordinates from the input are: ");
    for (int i=0;i<count;i++) {
        printf("(%.2lf,%.2lf) ", records[i].x_value, records[i].y_value);}


    printf("\n\n==============================");
    for (int i = 0; i<count-1;i++){
        double gap = ((records[i+1].x_value-records[i].x_value)/interpleted_time);
    for (int j = 0; j < interpleted_time+1; j++) {
        if (oversized_time>(int)output_size-1){
            break;
        }
        x_output[times]=records[i].x_value+gap;
        y_output[times]=interpolate(records[i].x_value, records[i].y_value, x_output[times], records[i+1].x_value, records[i+1].y_value);
        times+=1;
        gap+=((records[i+1].x_value-records[i].x_value)/interpleted_time)*(0.5);
        oversized_time+=1;
    }
    }

    printf("\nexpected output size: %d\n==============================\n\ninterpolated x output: ",(int)output_size);
    for (int i = 0; i < output_size; i++) {
        printf("%.2lf ", x_output[i]);
    }

    printf("\n\n==============================\n\ninterpolated y output: ");
    for (int i = 0; i < output_size; i++) {
        printf("%.2lf ", y_output[i]);
    }

    printf("\n\n==============================\n\nAll %d expected coordinates after the interpolation are: ",(int)output_size);
    for (int i=0;i<output_size;i++) {
        printf("(%.2lf,%.2lf) ", x_output[i], y_output[i]);}
    printf("\n\n==============================");


    interpolated_file= fopen("data/interpolated_data.csv", "w");
    if(interpolated_file == NULL)
    {
        perror("Unable to open the file.");
        exit(1);
    }

    printf("\n....creating a file and dumping all the data into Data/interpolated_data.csv\n");
    fprintf(interpolated_file, "%s,%s", "x_values", "y_values" );
    for (int i=0;i<(int)output_size;i++) {
            fprintf(interpolated_file, "\n%.2lf,%.2lf", x_output[i], y_output[i]);
    }

    fclose(interpolated_file);
    printf("...File created and saved successfully. \n");

}
