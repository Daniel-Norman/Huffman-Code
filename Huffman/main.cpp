#include <iostream>
#include <vector>
#include <string>
#include "BuilderNode.h"
using namespace std;

void buildTree();
string encodeMessage(string);
string decodeMessage(string);

vector<BuilderNode*> builderNodes;

double spaceFrequency = 19.182;
double frequencyList[26] = {
	8.167, 1.492, 2.782, 4.253, 12.702,
	2.228, 2.015, 6.094, 6.966, 0.153,
	0.772, 4.025, 2.406, 6.749, 7.507,
	1.929, 0.095, 5.987, 6.427, 9.056,
	2.758, 0.978, 2.360, 0.150, 1.974,
	0.074 };
string encodingArray[27];

int main() {
	buildTree();
	string message = "what is in a name   that which we call a rose by any other name would smell as sweet";
	string encodedMessage = encodeMessage(message);
	cout << decodeMessage(encodedMessage) << endl;
	cout << "Saved bits: " << message.size() * 5 - encodedMessage.size();
	
	cout << endl;
	system("PAUSE");
	return 0;
}

int smallestNodeIndex(int ignore_index = -1) {
	double smallestFrequency = 1000000;
	int smallestIndex = -1;
	BuilderNode* temp = NULL;
	for (size_t i = 0; i < builderNodes.size(); ++i) {
		if (i == ignore_index) continue;
		if (builderNodes[i]->frequency < smallestFrequency) {
			smallestIndex = i;
			smallestFrequency = builderNodes[i]->frequency;
		}
	}
	return smallestIndex;
}

void saveSubtree(BuilderNode* node, string pathSoFar) {
	if (node->data != 0) {
		encodingArray[node->data == ' ' ? 26 : node->data - 'a'] = pathSoFar;
	}
	else {
		saveSubtree(node->leftChild, pathSoFar + "1");
		saveSubtree(node->rightChild, pathSoFar + "0");
	}
}

string encodeMessage(string message) {
	string result = "";
	for (char c : message) {
		result += encodingArray[c == ' ' ? 26 : c - 'a'];
	}
	return result;
}

string decodeMessage(string message) {
	string result = "";
	BuilderNode* node = NULL;
	for (char c : message) {
		if (node == NULL) {
			node = builderNodes[c == '1' ? 0 : 1];
			continue;
		}
		if (node->data != 0) {
			result += node->data;
			node = builderNodes[c == '1' ? 0 : 1];
		}
		else {
			if (c == '1') node = node->leftChild;
			else node = node->rightChild;
		}
	}
	if (node->data != 0) result += node->data;
	return result;
}

void buildTree() {
	for (int i = 0; i < 26; ++i) {
		BuilderNode* node = new BuilderNode((char)(i + 'a'), frequencyList[i]);
		builderNodes.push_back(node);
	}
	builderNodes.push_back(new BuilderNode(' ', spaceFrequency));

	while (builderNodes.size() > 2) {
		int indexA = smallestNodeIndex();
		int indexB = smallestNodeIndex(indexA);

		BuilderNode* comboNode = new BuilderNode(builderNodes[indexA], builderNodes[indexB]);
		builderNodes.erase(builderNodes.begin() + indexA);
		builderNodes.erase(builderNodes.begin() + indexB + (indexA < indexB ? -1 : 0));
		builderNodes.push_back(comboNode);
	}
	saveSubtree(builderNodes[0], "1");
	saveSubtree(builderNodes[1], "0");
	for (int i = 0; i < 26; ++i) {
		cout << (char)(i + 'a') << ": " << encodingArray[i] << endl;
	}
	cout << "space: " << encodingArray[26] << endl;
}

