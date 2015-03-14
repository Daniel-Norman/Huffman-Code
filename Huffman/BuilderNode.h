#pragma once
#include <cstdlib>
using namespace std;

class BuilderNode {
public:
	BuilderNode(char, double);
	BuilderNode(BuilderNode*, BuilderNode*);
	double frequency;
	char data;
	BuilderNode* leftChild;
	BuilderNode* rightChild;
};

BuilderNode::BuilderNode(char d, double f) {
	this->frequency = f;
	this->data = d;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

BuilderNode::BuilderNode(BuilderNode* lc, BuilderNode* rc) {
	this->leftChild = lc;
	this->rightChild = rc;
	this->frequency = lc->frequency + rc->frequency;
	this->data = 0;
}
