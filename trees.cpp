/*
 * Spring Assignment Project Part 2.
 * Module: Data Structures
 *
 * Konstantinos Barmpas Electrical and Electronic Engineering Year 2
 * CID: 01214454
 */


/*
 * I USE THE FOLLOWING C++11 STANDARD FEAUTURES:
 *
 * 1) std::to_string(int)
 * 2) std::stoi(string,nullptr,2);
 * 3) Vector constructor and comparison.
 *
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

struct bdnode {
    std::string val;
    bdnode *left;
    bdnode *right;

};

typedef bdnode *bdt;

bdt buildcompactbdt(const std::vector<std::string> &fvalues);

std::string evalcompactbdt(bdt t, const std::string& input);

bdt movePointer(bdt r, char c);

void setVectorLeafValuesTo1(std::vector<std::string> &input, std::vector<bool> &vectorLeafValues);

bdt newNode(std::string value);

bdt reduceTree (std::vector<bool>& values,unsigned int& maxDepth);


bdt buildcompactbdt(const std::vector<std::string> &fvalues) {
    if (fvalues.size() == 0) {
        return newNode("0");
    }
    unsigned int maxDepth = fvalues[0].length();
    unsigned int sizeOfLeafValuesVector = pow(2, maxDepth);
    std::vector<bool> vectorLeafValues(sizeOfLeafValuesVector);
    setVectorLeafValuesTo1(const_cast<std::vector<std::string> &>(fvalues), vectorLeafValues);
    bdt root = reduceTree(vectorLeafValues,maxDepth);
    return root;
}

bdt reduceTree (std::vector<bool>& values,unsigned int &maxDepth){
    int midValue = values.size() / 2;
    bdt node;
    //check if it is leaf
    if (midValue!=0) {
        std::vector<bool> values_half1(values.begin(), values.begin() + midValue);
        std::vector<bool> values_half2(values.begin() + midValue, values.end());
        if (values_half1 == values_half2) {
            //doesnt create X node - simplification
            node=reduceTree(values_half1, maxDepth);
        } else {
            node = newNode("X" + std::to_string(maxDepth - (int)log2(values.size()) + 1));
            node->left = reduceTree(values_half1, maxDepth);
            node->right = reduceTree(values_half2, maxDepth);
        }
    }else{
        //create the leaf node
        node=newNode(std::to_string(values[0]));
    }
    return node;
}

void setVectorLeafValuesTo1(std::vector<std::string> &input, std::vector<bool> &vectorLeafValues) {
    int index_set1_leaf;
    for (int i = 0; i < input.size(); i++) {
        //calculate the index to translating the bin string to int eg "010" = 2.
        //at this index set value of leaf to 1.
        index_set1_leaf = std::stoi(input[i], nullptr, 2);
        vectorLeafValues[index_set1_leaf] = 1;
    }
}

bdt newNode(std::string value) {
    bdt temp = new bdnode;
    temp->val = value;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

std::string evalcompactbdt(bdt t, const std::string& input) {
    const char* array_of_characters = input.c_str();
    bdt temp = t;
    while (temp->val != "0" && temp->val != "1") {
        //to calculate the right element from the array_of_characters and move the pointer accordingly.
        int arrayCharIndex = std::stoi(temp->val.substr(1), nullptr,10) - 1;
        temp = movePointer(temp, array_of_characters[arrayCharIndex]);
    }
    return temp->val;
}

bdt movePointer(bdt t, char c) {
    if (c == '0') {
        return t->left;
    } else {
        return t->right;
    }
}

