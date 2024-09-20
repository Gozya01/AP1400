#!/bin/bash


# 测试脚本
#!/bin/bash
# 解析命令行参数
options=$(getopt -o c: --long compression:,print -- "$@")
eval set -- "$options"

compression=1
# 提取选项和参数
while true; do
  case $1 in 
  	-c | --compression) shift; compression=$1 ; shift ;;
    --) shift ; break ;;
    *) echo "Invalid option: $1" exit 1 ;;
  esac
done

if [ -z "$compression" ]; then
    echo "Error: compression is required"
    exit 1
fi

if [ $# -l 2 ];then
    echo "缺少参数"
    exit 1
fi
source_path=$1
destination_path=$2
# 判断开关选项
echo "compressionVal: $compression";
# echo "脚本名称:$0"
# options =$(getopt -o c: --long compression:,print --"$@")
# eval set -- "$options"

# # 默认值
# compression=""
# print=false

# # 处理选项
# while true; do
#   case "$1" in
#     -c | --compression)
#       compression="$2"
#       shift 2
#       ;;
#     --print)
#       print=true
#       shift
#       ;;
#     --)
#       shift
#       break
#       ;;
#     *)
#       echo "无效的选项"
#       exit 1
#       ;;
#   esac
# done

# # 使用解析后的选项
# if $print; then
#   echo "Compression: $compression"
# fi