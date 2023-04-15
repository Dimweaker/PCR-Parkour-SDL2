#include "record.h"

/**
 * 读取本地的记录
 * @return 记录的值
 */
int read_record(){
    FILE *fp;
    int record;

    fp = fopen("record.bin", "rb+"); /* 读取二进制文件 */

    /* 如果文件不存在，创建文件并写入0，并返回0 */
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

    /* 否则，直接从文件中读取记录 */
    fread(&record, sizeof(int), 1, fp);
    fclose(fp);

    return record;
}

/**
 * 写入记录
 * @param score 成绩
 */
void write_record(int score){
    FILE *fp;

    /* 打开文件 */
    fp = fopen("record.bin", "w+b");
    if(fp == NULL){
        printf("Error: cannot open record.bin");
        return;
    }

    /* 写入记录 */
    fwrite(&score, sizeof(int), 1, fp);
    fclose(fp);
}
