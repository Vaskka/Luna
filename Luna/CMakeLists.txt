PROJECT(datastruct_learn)

# add_executable(可执行文件的名字 main函数源文件路径))
add_executable(main ./main.c linkedlist/linkedlist arraylist/arraylist common/struct_common ./common.h datastruct/strtype_tree datastruct/stringbuilder/stringbuilder file/file_util net/net_server_util net/net_constant utils/json/cJSON utils/util)
