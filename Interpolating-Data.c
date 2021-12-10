#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct points_record {
    double x_value;
    double y_value;
};
int main(){
    FILE *data_file = fopen("Data/data.csv","r");
    if (data_file==NULL){
        perror("Unable to open the file.");
        exit(1);
    }

    struct points_record records[100];
    size_t count = 0;
    for(;count<sizeof(records)/sizeof(records[0]);++count){
        int got = fscanf(data_file,"%lf,%lf",&records[count].x_value,&records[count].y_value);
        if (got != 2) break;
    }
    fclose(data_file);


    printf("X values are: ");
    for (int i=0;i<count;i++){
    printf("%.2lf ",records[i].x_value);}

    printf("\nY values are: ");
    for (int i=0;i<count;i++){
        printf("%.2lf ",records[i].y_value);}

    printf("\n\nAll the coordinates are: ");
    for (int i=0;i<count;i++) {
        printf("(%.2lf,%.2lf) ", records[i].x_value, records[i].y_value);
    }
    size_t output_size = 50;


}

