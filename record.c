

#include "record.h"

int read_record(){
    FILE *fp;
    int record;
    fp = fopen("record.bin", "rb+");
    if(fp == NULL){
        fp = fopen("record.bin", "w+b");
        if(fp == NULL){
            printf("Error: cannot open record.bin");
            return 0;
        }
        else{
            record = 0;
            fwrite(&record, sizeof(int), 1, fp);
            fclose(fp);
            return record;
        }
    }
    fread(&record, sizeof(int), 1, fp);
    fclose(fp);

    return record;
}

void write_record(int score){
    FILE *fp;
    fp = fopen("record.bin", "w+b");
    if(fp == NULL){
        printf("Error: cannot open record.bin");
        return;
    }
    fwrite(&score, sizeof(int), 1, fp);
    fclose(fp);
}
