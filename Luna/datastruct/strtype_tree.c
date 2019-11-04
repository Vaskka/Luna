//
//  strtype_tree.c
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include "strtype_tree.h"


// 初始化一个node
TreeNode* initTreeNode() {
    TreeNode* node = malloc(sizeof(TreeNode));

    node->children = alCreateList(0);
    node->name = ROOT_DIR_NAME;
    node->dir = 1;
    
    return node;
}


// 为一个node appendq另一个node
int appendNode(TreeNode* origin, const TreeNode* child) {
    
    // 超过一个最大w字节点数返回false
    if (alGetSize(origin->children) >= MAX_CHILDREN_NUMBER) {
        return 0;
    }
    
    alAdd(origin->children, (void*)child);
    return 1;
    
}

// 销毁一个节点及其子节点
void destoryTreeNode(TreeNode* node) {
    
    // 文件直接释放
    if (!node->dir) {
        
        // printf("destorying...%s\n", node->name);
        alDestory(node->children);
        free(node);
        return;
    }
    
    // 处理文件夹
    for (int i = 0 ; i < alGetSize(node->children); i++) {
        TreeNode* curr =(TreeNode*) alGet(node->children, i);
        destoryTreeNode(curr);
    }
    
}

// 生成完整文件tree
TreeNode* getFullDirTree(const char* path) {
    
    // init node
    TreeNode* original = initTreeNode();
    
    DIR *dp;
    struct dirent *dirp;

    // deal path not exist
    if (!pathExist(path)) {

        free(original);
        char res[256];
        strcat(res, path);
        strcat(res, "not exist.");
        raise_error(res);
        
        return NULL;
    }
    
    if((dp = opendir(path)) == NULL) {
        // 当前根路径是非文件夹
        original->name = path;
        original->dir = 0;
        
        return original;
    }
    
    // iterate dir 
    while((dirp = readdir(dp)) != NULL) {

        // 不考虑 . and ..
        if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, "..")) {
            continue;
        }
        
        TreeNode* childNode;
        if (dirp->d_type != DT_DIR) {
            childNode = initTreeNode();
            childNode->name = dirp->d_name;
            childNode->dir = 0;
        }
        else {
            // dir
            childNode = getFullDirTree(joinPath(path, dirp->d_name));
            childNode->dir = 1;
            childNode->name = dirp->d_name;
        }
        
        appendNode(original, childNode);

    }

    closedir(dp);
    return original;
}


// 序列化TreeNode
/*
 each item has below structure:
 
{"name": "%s", "dir": %d, "children": []}
 
 
 */
char* treeNode2Json(const TreeNode* node) {
    if (!node->dir) {
        char* result = (char*) malloc(sizeof(char) * (256));
        sprintf(result, "{\"name\": \"%s\", \"dir\": 0, \"children\": []}", node->name);
        return result;
    }
    
    // construct children list
    int childrenLength = alGetSize(node->children);
    StringBuilder* childset = initStringBuilder("");
    
    for (int i = 0 ; i < childrenLength; i++) {
        char* child = treeNode2Json((TreeNode*) alGet(node->children, i));
        appendString(childset, child);
        
        // append ", "
        if (i != childrenLength - 1) {
            appendString(childset, ", ");
        }
    }
    
    // construct result string
    char* result = (char*) malloc(sizeof(char) * (256 + length(childset)));
    sprintf(result, "{\"name\": \"%s\", \"dir\": %d, \"children\": [%s]}", node->name, node->dir, toString(childset));
    
    // free StringBuilder memory
    destoryStringBuilder(childset);
    return result;
    
}


// for debug
void debugViewAllNodeInfo(int deep, const TreeNode* _node) {
    

    if (_node->dir) {
        for (int i = 0; i < deep; i++) {
            printf("\t");
        }
        printf("current dir has %d file and dir\n", alGetSize(_node->children));
    }
    for (int i = 0 ; i < alGetSize(_node->children); i++) {
        
        TreeNode* curr =(TreeNode*) alGet(_node->children, i);
        
        for (int i = 0; i < deep; i++) {
            printf("\t");
        }
        printf("%s\n", curr->name);
        
        if (curr->dir) {
             debugViewAllNodeInfo(deep + 1, curr);
        }

    }
    
}

// 得到h文件json并释放全部中间变量
char* getJson(const char* path) {
    
    TreeNode* node = getFullDirTree(path);
    char* result = treeNode2Json(node);

    destoryTreeNode(node);
    return result;
}

// 反序列化json
TreeNode* json2TreeNode(const char* json) {
    
    
    cJSON* root = cJSON_Parse(json);
    TreeNode* node = initTreeNode();
    
    node->name = cJSON_GetObjectItem(root, "name")->valuestring;
    node->dir  = cJSON_GetObjectItem(root, "dir")->valueint;
    
    // deal with children
    cJSON* children = cJSON_GetObjectItem(root, "children");
    cJSON* child = children->child;
    
    // iterate chilren field for node
    while (child != NULL) {
        TreeNode* childNode = json2TreeNode(cJSON_Print(child));
        
        appendNode(node, childNode);
        child = child->next;
    }
    
    return node;
}
