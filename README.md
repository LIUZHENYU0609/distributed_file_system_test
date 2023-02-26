# distributed_file_system_test
分布式文件系统测试脚本

# 现有测试脚本介绍
copy_file_range : 测试Linux的copy_file_range系统调用接口 \
large_file_write_once : 测试向cubefs中写入大文件，并且一次性将文件数据写入 

# 安装教程
mkdir build \
cd build \
cmake .. \
make

# 使用说明
cd build
1. copy_file_range接口调用测试 \
   `./copy_file_range`
2. cubefs文件系统大文件写入测试 \
   `./large_file_write_once -p {file_path} -s {file_size} -t {FUSE|SDK}` \
   其中-p指定文件路径，-s指定写入的文件大小，-t指定写入方式（FUSE表示利用用户态文件系统客户端写入，SDK表示利用libcfs库进行数据写入）
