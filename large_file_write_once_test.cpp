/*
 * @Author: LIUZHENYU0609 1329004166@qq.com
 * @Date: 2023-02-24 16:13:05
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-24 17:06:14
 * @FilePath: /test_c/large_file_write_once_test.cpp
 * @Description: 大文件一次性写入文件系统测试脚本
 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<unistd.h>
#include<memory>
#include<string.h>
#include<errno.h>

int main(int argc, char **argv){
    if (argc <= 1){
        printf("lack of rumtime parameters, running failure\n");
        exit(0);
    }
    int opt;
    const char *opt_str = "p:s:";
    /* 解析命令行参数，设置为运行时环境变量
        -s 文件大小
        -p 文件所在路径
    */
   int file_size;
   char* file_path;
   while ((opt = getopt(argc, argv, opt_str)) != -1){
        switch (opt){
            case 'p' :
                printf("load param file path:%s\n", optarg);
                file_path = optarg;
                break;
            case 's':
                printf("load param file size:%s\n", optarg);
                file_size = atoi(optarg) * 1024 * 1024; // 写入数据量单位：MB
                break;
            case '?':
                printf("error optopt:%s\n", (char)optopt);
                if (optopt == 's' ||  optopt == 'p'){
                    exit(0);
                }
                break;    
        }
    }

    char *buf = (char*)malloc(file_size);
    memset(buf, 'a', file_size);
    
    int ret, fd;
    struct stat st;
    ret = stat(file_path, &st);
    if(ret != 0){
        fd = creat(file_path, 7777);
    }else{
        fd = open(file_path, O_RDWR);
    }
    if(fd == -1){
        printf("create/open file fail, because:%s\n", strerror(errno));
        exit(0);
    }
    ret =  write(fd, buf, file_size);
    if(ret == -1){
        printf("write file fail, beacause:%s. filename:%s, file_size:%d.\n", strerror(errno) ,file_path, file_size);
    }else{
        printf("write file success. filename:%s, file_size:%d.\n", file_path, file_size);
    }
    return 0;
}

