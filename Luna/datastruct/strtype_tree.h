//
//  strtype_tree.h
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef strtype_tree_h
#define strtype_tree_h

#include <string.h>
#include <dirent.h>

#include "../common.h"
#include "../datastruct/stringbuilder/stringbuilder.h"
#include "../arraylist/arraylist.h"
#include "../common/struct_common.h"
#include "../file/file_util.h"
#include "../utils/util.h"
#include "../utils/json/cJSON.h"

#define MAX_CHILDREN_NUMBER 65536

#define ROOT_DIR_NAME "__ROOT__"

typedef struct TreeNode {
    
    ArrayList* children;
    
    char* name;
    
    // 0-file 1-dir
    int dir;
    
    
} TreeNode; 
 

// 初始化一个node
TreeNode* initTreeNode(void);


// 为一个node append另一个node
int appendNode(TreeNode* origin, const TreeNode* child);

// 销毁一个节点及其子节点
void destoryTreeNode(TreeNode * node);

// 序列化TreeNode
char* treeNode2Json(const TreeNode* node);

// 反序列化json
TreeNode* json2TreeNode(const char* json);

// 生成完整文件tree
TreeNode* getFullDirTree(const char* path);


// 得到交互json并释放所有中间变量
char* getJson(const char* path);

#endif /* strtype_tree_h */
