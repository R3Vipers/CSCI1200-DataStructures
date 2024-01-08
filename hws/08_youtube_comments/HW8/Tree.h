//
// Created by Ryan Ames on 11/7/2023.
//

#ifndef HW8_TREE_H
#define HW8_TREE_H

#include <iostream>
#include <vector>
#include "Comment.h"
using namespace std;

class TreeNode {
public:
    //constructor
    TreeNode(const Comment& value) : data(value) {}

    //fine desired node and return pointer to node
    TreeNode find(TreeNode node, const string& comment_id) {

        if (node.data.getCommentId() == comment_id) {
            return node;
        }
        //iterate through all children in a vector and recursively explore them
        if(!node.children.empty()) {
            for (TreeNode child: node.children) {
                TreeNode result = find(child, comment_id);
                    return result;
            }
        }
    }
    //find comment to add like to and increase the like count by one
    void like(TreeNode node, const string& comment_id) {
        if (node.data.getCommentId() == comment_id) {
            node.data.addlike();
            return;
        }
        //iterate through all children in a vector and recursively explore them
        if(!node.children.empty()) {
            for (TreeNode child: node.children) {
                TreeNode result = find(child, comment_id);

                    result.data.addlike();
                    return;

            }
        }
    }
    //uses the find function then inserts node into child vector
    bool insert(TreeNode root, const string& parent_comment_id, const Comment& newValue) {
        TreeNode nodeToInsert = find(root, parent_comment_id);
            TreeNode temp (newValue);
            nodeToInsert.children.push_back(temp);

            return true;
        return false;
    }
    //uses find function to find the element to remove then find the parent then erases the branch
    void erase(TreeNode root, const string& comment_id) {
        TreeNode nodeToDelete = find(root, comment_id);

        // Recursively delete the node to delete and its children
    }
    //print out eac element in the tree with spacing
    void print (TreeNode &node, int depth, const string& out_file) {
        node.data.setDepth(depth);
        std::ofstream fout(out_file, std::ios::app);
        fout << node.data;
        fout.close();
        if(node.children.empty()) return;
        for(TreeNode child : node.children){
            print(child, depth + 1, out_file);
        }
    }
private:
    //private variables
    Comment data;
    // Pointer to the parent node
    //vector of children for dynamic tree size
    std::vector<TreeNode> children;
};


#endif //HW8_TREE_H
