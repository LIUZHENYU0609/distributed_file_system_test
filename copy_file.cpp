/*
 * @Author: LIUZHENYU0609 1329004166@qq.com
 * @Date: 2022-10-19 18:43:07
 * @LastEditors: LIUZHENYU0609 1329004166@qq.com
 * @LastEditTime: 2023-02-24 16:12:57
 * @Description: linux copy_file_range 接口测试
 */
#include<fcntl.h>
#include<string>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc,  char **argv){
    std::string in_file_name = "/home/lzy/code/go/juicefs_oppo/jfs/base/.git/objects/pack/pack-a80619e3b32c77590e632520c1c9eb3983e6df4c.pack";
    std::string out_file_name = "/home/lzy/code/go/juicefs_oppo/jfs/pack-a80619e3b32c77590e632520c1c9eb3983e6df4c.pack";
    int fd_in = open(in_file_name.c_str(), O_RDWR);
    int fd_out = open(out_file_name.c_str(), O_RDWR | O_CREAT);
    struct stat in_stat;
    fstat(fd_in, &in_stat);
    off_t len = in_stat.st_size;
    ssize_t ret;
    do {
        ret = copy_file_range(fd_in, NULL, fd_out, NULL, len, 0);
        if (ret == -1) {
            perror("copy_file_range");
            exit(EXIT_FAILURE);
        }
        len -= ret;
    } while (len > 0 && ret > 0);
    return 0;
}
