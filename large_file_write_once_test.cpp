/*
 * @Author: LIUZHENYU0609 1329004166@qq.com
 * @Date: 2023-02-24 16:13:05
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-25 11:30:40
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
#include"include/libcfs.h"

void large_file_write(char *file_path, char *data_buf, int file_size, const char *write_mode){
    int fd;
    if(strcmp(write_mode, "SDK") == 0){
        int64_t cid = cfs_new_client();
        cfs_set_client(cid, "volName", "ltptest");
        cfs_set_client(cid, "masterAddr", "192.168.3.62:17010,192.168.3.63:17010,192.168.3.125:17010,192.168.3.126:17010");
        cfs_set_client(cid, "logDir", "/cfs/client/log");
        cfs_set_client(cid, "logLevel", "debug");
        cfs_set_client(cid, "accessKey", "ItfD1YZtAH6KEBYZ");
        cfs_set_client(cid, "secretKey", "oY40FnIpUwEV0kcNdAQpWiTb5Q3Q7n31");
        int ret = cfs_start_client(cid);

        fd = cfs_open(cid, file_path, O_RDWR | O_CREAT, 7777);
        if(fd < 0){
            printf("create/open file fail");
            return;
        }
        ssize_t res = cfs_write(cid, fd, data_buf, file_size, 0);
        if(res == 0){
            printf("write file fail by SDK.");
        }else{
            printf("write file success by SDK.");
        }
        cfs_close(cid, fd);
        cfs_close_client(cid);
    }else if(strcmp(write_mode, "FUSE") == 0){
        int ret;
        struct stat st;
        ret = stat(file_path, &st);
        if(ret != 0){
            fd = creat(file_path, 7777);
        }else{
            fd = open(file_path, O_RDWR);
        }
        if(fd < -1){
            printf("create/open file fail, because:%s\n", strerror(errno));
            return;
        }
        ret =  write(fd, data_buf, file_size);
        if(ret == -1){
            printf("write file fail by FUSE, beacause:%s. filename:%s, file_size:%d.\n", strerror(errno) ,file_path, file_size);
        }else{
            printf("write file success by FUSE. filename:%s, file_size:%d.\n", file_path, file_size);
        }
        close(fd);
    }else{
        printf("write fail, invalid write mode:%s", write_mode);
    }
}

int main(int argc, char **argv){
    if (argc <= 1){
        printf("lack of rumtime parameters, running failure\n");
        exit(0);
    }
    int opt;
    const char *opt_str = "p:s:t:";
    /* 解析命令行参数，设置为运行时环境变量
        -s 文件大小
        -p 文件所在路径
    */
   int file_size;
   char* file_path;
   char* write_mode;
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
            case 't':
                printf("Data Write Mode:%s\n", optarg);
                write_mode = optarg;
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

    large_file_write(file_path, buf, file_size, write_mode);
    
    return 0;
}

