#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int stringToInt(const std::string &str)
{
    int result = 0;
    bool isNegative = false;
    int startIndex = 0;

    // Check for negative sign
    if (str[0] == '-')
    {
        isNegative = true;
        startIndex = 1;
    }

    for (int i = startIndex; i < str.length(); ++i)
    {
        if (isdigit(str[i]))
        {
            result = result * 10 + (str[i] - '0');
        }
    }

    if (isNegative)
    {
        result = -result;
    }

    return result;
}

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop
{
private:
    string stopName;
    MetroStop *nextStop;
    MetroStop *prevStop;
    MetroLine *line;
    int fare;

public:
    MetroStop(string name, MetroLine *metroLine, int fare);

    // Getter methods
    string getStopName() const;
    MetroStop *getNextStop() const;
    MetroStop *getPrevStop() const;
    MetroLine *getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop *next);
    void setPrevStop(MetroStop *prev);
};

MetroStop::MetroStop(string name, MetroLine *metroLine, int fare)
{
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

string MetroStop::getStopName() const
{
    return stopName;
}

MetroStop *MetroStop::getNextStop() const
{
    return nextStop;
}

MetroStop *MetroStop::getPrevStop() const
{
    return prevStop;
}

MetroLine *MetroStop::getLine() const
{
    return line;
}

int MetroStop::getFare() const
{
    return fare;
}

void MetroStop::setNextStop(MetroStop *next)
{
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop *prev)
{
    prevStop = prev;
}

// MetroLine class
class MetroLine
{
private:
    string lineName;
    MetroStop *node = nullptr;

public:
    MetroLine(string name);

    // Getter methods
    string getLineName() const;
    MetroStop *getNode() const;

    // Setter methods
    void setNode(MetroStop *node);

    void populateLine(string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(string name)
{
    lineName = name;
    node = nullptr;
}

string MetroLine::getLineName() const
{
    return lineName;
}

MetroStop *MetroLine::getNode() const
{
    return node;
}

void MetroLine::setNode(MetroStop *node)
{
    this->node = node;
}

void MetroLine::printLine() const
{
    MetroStop *stop = node;
    while (stop != nullptr)
    {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    int total_stops = 0;
    MetroStop *ptr = node;
    while (ptr != nullptr)
    {
        total_stops++;
        ptr = ptr->getNextStop();
    }

    return total_stops;
}

void MetroLine::populateLine(string filename)
{
    vector<string> entries;
    //    cout<<"bruh";

    // Open the CSV file for reading
    ifstream file(filename);

    string line;
    while (getline(file, line))
    {
        // Remove commas from the CSV entry
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        // Store the modified CSV entry as a string
        entries.push_back(line);
    }

    for (int i = 0; i < entries.size(); ++i)
    {
        // cout<< entries[i] << endl;
        string num_str;
        string name;
        for (int j = entries[i].size() - 1; j >= 0; j--)
        {
            string str = entries[i];

            if (str[j] == ' ')
            {
                name = str.substr(0, j);
                break;
            }

            num_str.insert(num_str.begin(), str[j]);
        }

        // cout<<num_str<<" "<<endl;
        // cout<<name<<endl;
        int num = stringToInt(num_str);

        // num contains fare price and name contains stop name
        // now creating the node of MetroStop
        MetroStop *msnode = new MetroStop(name, this, num);
        // cout<<msnode->getFare()<<" "<<msnode->getStopName()<<endl;
        MetroStop *ptr = node;
        if (node == nullptr)
        {
            node = msnode;
        }
        else
        {

            while (ptr->getNextStop() != nullptr)
            {
                ptr = ptr->getNextStop();
            }
            ptr->setNextStop(msnode);
            msnode->setPrevStop(ptr);
            msnode->setNextStop(nullptr);
        }

        // created dll successfully

        // ptr=node;
        // while(ptr->getNextStop()!=nullptr){
        //     cout<<ptr->getStopName()<<" fare"<<ptr->getFare()<<endl;
        //     ptr=ptr->getNextStop();
        // }

        num_str.clear();
    }
}

// AVLNode class
class AVLNode
{
private:
    string stopName;
    vector<MetroStop *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    AVLNode(string name);

    // Getter methods
    string getStopName() const;
    const vector<MetroStop *> &getStops() const;
    AVLNode *getLeft() const;
    AVLNode *getRight() const;
    AVLNode *getParent() const;

    // Setter methods
    void addMetroStop(MetroStop *metroStop);
    void setLeft(AVLNode *left);
    void setRight(AVLNode *right);
    void setParent(AVLNode *parent);
};

AVLNode::AVLNode(string name)
{
    stopName = name;
    left = nullptr;
    right = nullptr;
}

string AVLNode::getStopName() const
{
    return stopName;
}

const vector<MetroStop *> &AVLNode::getStops() const
{
    return stops;
}

AVLNode *AVLNode::getLeft() const
{
    return left;
}

AVLNode *AVLNode::getRight() const
{
    return right;
}

AVLNode *AVLNode::getParent() const
{
    return parent;
}

void AVLNode::setLeft(AVLNode *left)
{
    this->left = left;
}

void AVLNode::setRight(AVLNode *right)
{
    this->right = right;
}

void AVLNode::setParent(AVLNode *parent)
{
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop *metroStop)
{
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree
{
    // Define your AVLTree implementation here.
private:
    AVLNode *root = nullptr;

public:
    // getter methods
    AVLNode *getRoot() const;

    // setter methods
    void setRoot(AVLNode *root);

    // helper functions
    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    AVLNode *rotateLeft(AVLNode *node);
    AVLNode *rotateRight(AVLNode *node);
    AVLNode *balance(AVLNode *node);
    int stringCompare(string s1, string s2);
    AVLNode *insert(AVLNode *node, MetroStop *metroStop);
    void populateTree(MetroLine *metroLine);
    void inOrderTraversal(AVLNode *node);
    int getTotalNodes(AVLNode *node);
    AVLNode *searchStop(string stopName);
};

AVLNode *AVLTree::getRoot() const
{
    return root;
}

void AVLTree::setRoot(AVLNode *root)
{
    this->root = root;
}

int AVLTree::height(AVLNode *node)
{
    if (node == nullptr)
    {

        return 0;
    }

    else
    {
        short int leftHeight = height(node->getLeft());
        short int rightHeight = height(node->getRight());
        return max(leftHeight, rightHeight) + 1;
    }
}

int AVLTree::stringCompare(string s1, string s2)
{
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

AVLNode *AVLTree ::rotateLeft(AVLNode *x)
{
    if (x == nullptr || x->getRight() == nullptr)
    {
        return x;
    }

    AVLNode *y = x->getRight();
    AVLNode *T2 = y->getLeft();

    // Perform rotation
    y->setLeft(x);
    x->setRight(T2);

    return y;
}

AVLNode *AVLTree::rotateRight(AVLNode *y)
{
    if (y == nullptr || y->getLeft() == nullptr)
    {

        return y;
    }

    AVLNode *x = y->getLeft();
    AVLNode *T2 = x->getRight();

    // Perform rotation
    x->setRight(y);
    y->setLeft(T2);

    return x;
}

AVLNode *AVLTree::balance(AVLNode *node)
{

    if (node == nullptr)
    {
        return nullptr;
    }

    int balance = height(node->getLeft()) - height(node->getRight());
    // int balance = 0;
    balanceFactor(node);
    // balanceFactor(node);

    if (balance > 1)
    {
        if (height(node->getLeft()->getLeft()) >= height(node->getLeft()->getRight()))
        {

            return rotateRight(node);
        }
        else
        {

            node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }
    }
    if (balance < -1)
    {
        if (height(node->getRight()->getRight()) >= height(node->getRight()->getLeft()))
        {

            return rotateLeft(node);
        }
        else
        {

            node->setRight(rotateRight(node->getRight()));
            return rotateLeft(node);
        }
    }

    return node;
}

AVLNode *AVLTree::insert(AVLNode *root, MetroStop *metroStop)
{

    if (root == nullptr)
    {
        AVLNode *newnode = new AVLNode(metroStop->getStopName());
        newnode->addMetroStop(metroStop);

        return newnode;
    }

    int val = stringCompare(metroStop->getStopName(), root->getStopName());

    if (val < 0)
    {

        root->setLeft(insert(root->getLeft(), metroStop));
    }
    else if (val > 0)
    {

        root->setRight(insert(root->getRight(), metroStop));
    }
    else if (val == 0)
    {

        root->addMetroStop(metroStop);
        return root;
    }

    // return root;
    // Balancing the tree after insertion
    return balance(root);
}

void AVLTree::populateTree(MetroLine *metroLine)
{
    MetroStop *msnode = metroLine->getNode();
    // AVLTree* avl_tree = new AVLTree;
    // cout<<"inside populate tree"<<endl;

    while (msnode != nullptr)
    {
        // avl_tree->insert(avl_tree->getRoot(),msnode);
        // cout<<msnode->getStopName()<<" ";
        // cout<<"bruh"<<" ";
        this->setRoot(this->insert(this->getRoot(), msnode));
        // inOrderTraversal(root);
        msnode = msnode->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode *node)
{
    if (node == nullptr)
    {

        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode *AVLTree::searchStop(string stopName)
{

    AVLNode *node = root;
    short int val = stringCompare(stopName, node->getStopName());
    while (node != nullptr && stringCompare(stopName, node->getStopName()) != 0)
    {
        if (stringCompare(stopName, node->getStopName()) > 0)
        {
            node = node->getRight();
        }
        else
        { // key>node->key
            node = node->getLeft();
        }
    }

    return node;
}

// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    int flag = 0; // 1 means forward and 0 means backward trip
    Trip(MetroStop *metroStop, Trip *previousTrip);
    Trip(MetroStop *metroStop, Trip *previousTrip, int flag);

    // Getter methods
    MetroStop *getNode() const;
    Trip *getPrev() const;
};

Trip::Trip(MetroStop *metroStop, Trip *previousTrip)
{
    node = metroStop;
    prev = previousTrip;
}

Trip::Trip(MetroStop *metroStop, Trip *previousTrip, int flag)
{
    node = metroStop;
    prev = previousTrip;
    this->flag = flag;
}

MetroStop *Trip::getNode() const
{
    return node;
}

Trip *Trip::getPrev() const
{
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration
{
private:
    queue<Trip *> trips;

public:
    Exploration();

    // Getter methods
    queue<Trip *> getTrips() const;

    // Setter methods
    void enqueue(Trip *trip);
    Trip *dequeue();
    bool isEmpty() const;
};

Exploration::Exploration()
{
}

queue<Trip *> Exploration::getTrips() const
{
    return trips;
}

void Exploration::enqueue(Trip *trip)
{
    trips.push(trip);
}

Trip *Exploration::dequeue()
{
    if (trips.empty())
    {
        return nullptr;
    }
    Trip *trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const
{
    return trips.empty();
}

class Path
{
private:
    vector<MetroStop *> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    vector<MetroStop *> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop *stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path()
{
    totalFare = 0;
}

vector<MetroStop *> Path::getStops() const
{
    return stops;
}

int Path::getTotalFare() const
{
    return totalFare;
}

void Path::addStop(MetroStop *stop)
{
    stops.push_back(stop);
}

void Path::setTotalFare(int fare)
{
    totalFare = fare;
}

void Path::printPath() const
{
    for (auto stop : stops)
    {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    vector<MetroLine *> lines;

public:
    PathFinder(AVLTree *avlTree, const vector<MetroLine *> &metroLines);
    void createAVLTree();
    Path *findPath(string origin, string destination);

    // Getter methods
    AVLTree *getTree() const;
    const vector<MetroLine *> &getLines() const;
};

PathFinder::PathFinder(AVLTree *avlTree, const vector<MetroLine *> &metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree *PathFinder::getTree() const
{
    return tree;
}

const vector<MetroLine *> &PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    for (int i = 0; i < lines.size(); i++)
    {
        tree->populateTree(lines[i]);
    }
}

long int computefare(vector<MetroStop *> stops)
{
    long int totalfare = 0;
    int temp = 0;
    for (int i = 0; i < stops.size(); i++)
    {
        // cout<<"hug kyu raha hai bsdk"<<endl;
        temp = stops[i + 1]->getFare() - stops[i]->getFare();
        // cout<<temp<<endl;
        totalfare = totalfare + (stops[i + 1]->getFare() - stops[i]->getFare());
        // cout<<totalfare<<endl;
    }
    return totalfare;
}

Path *PathFinder::findPath(string origin, string destination)
{
    AVLNode *onode = tree->searchStop(origin);
    // AVLNode* dnode = tree->searchStop(destination);
    Path *finalPath = new Path();

    // o node is orgin destination node ab usme there would be vector of metrostops pointers so usme se you can access metrostop node and usse you can access the line corresponding to that metrostop
    // considering origin is not a junction

    vector<MetroStop *> stops_of_o = onode->getStops();

    // considring origin isnt a junction , if it was a junction ye sab loop mein dal dena till vector.size(); replacing stops_of_o[i]
    for (int i = 0; i < stops_of_o.size(); i++)
    {

        MetroStop *msnode = stops_of_o[i];
        MetroLine *currentline = msnode->getLine();

        // creating inital trip objects for origin
        Trip *forward = new Trip(msnode, nullptr, 1);
        Trip *backward = new Trip(msnode, nullptr, 0);

        // inserting trip objects into exploration queue
        Exploration *exp = new Exploration();
        exp->enqueue(forward);
        exp->enqueue(backward);

        ////scrap
        // Trip* trip = exp->dequeue();
        // while(trip->getNode()->getNextStop()->getStopName()!=destination || trip->getNode()->getNextStop()!=nullptr){

        // }

        while (!exp->isEmpty())
        {
            Trip *currentTrip = exp->dequeue();
            // MetroStop* currentStop = currentTrip->getNode();

            while (currentTrip->getNode() != nullptr)
            {
                // cout<<"inside currentTrip->getNode()!=nullptr while loop"<<endl;
                if (currentTrip->getNode()->getStopName() == destination)
                {
                    // destination found , ab path bana ke return kar de
                    //  cout<<"inside..."<<endl;
                    while (currentTrip != nullptr)
                    {
                        // cout<<"adding trip..."<<endl;
                        finalPath->addStop(currentTrip->getNode());
                        currentTrip = currentTrip->getPrev();
                    }

                    vector<MetroStop *> stopsforfare = finalPath->getStops();
                    reverse(stopsforfare.begin(), stopsforfare.end());
                    long int finalfare = 0;
                    // long int finalfare = computefare(stopsforfare);
                    // cout<<computefare(stopsforfare)<<endl;
                    // finalPath->setTotalFare(finalfare);

                    for (int l = 0; i < stopsforfare.size(); i++)
                    {
                        // cout<<"hug kyu raha hai bsdk"<<endl;
                        int temp = stopsforfare[l + 1]->getFare() - stopsforfare[l]->getFare();
                        // cout<<temp<<endl;
                        finalfare = finalfare + abs(temp);
                        // cout<<totalfare<<endl;
                    }
                    finalPath->setTotalFare(finalfare);
                    return finalPath;
                }

                else
                {
                    // new node is getting created and my current node is getting updated to new node
                    if (currentTrip->flag == 1)
                    {
                        // forward traversal

                        Trip *tempTrip = new Trip(currentTrip->getNode()->getNextStop(), currentTrip, 1);
                        currentTrip = tempTrip;
                    }
                    if (currentTrip->flag == 0)
                    {
                        // backward traversal
                        Trip *tempTrip = new Trip(currentTrip->getNode()->getPrevStop(), currentTrip, 0);
                        currentTrip = tempTrip;
                    }

                    // checking if currentTrip pointer has more than one stops in its avl node
                    AVLNode *avnode = tree->searchStop(currentTrip->getNode()->getStopName());
                    // here you will get avl node which has name of current stop;

                    // condition for checking if current stop is a junction or not
                    vector<MetroStop *> avstops = avnode->getStops();
                    if (avnode->getStops().size() > 1)
                    {
                        // then av node is a junction
                        for (int k = 0; k < avstops.size(); k++)
                        {
                            Trip *forwardwala = new Trip(avstops[i], currentTrip, 1);
                            Trip *backwardwala = new Trip(avstops[i], currentTrip, 0);
                            exp->enqueue(forwardwala);
                            exp->enqueue(backwardwala);
                        }
                    }
                }
            }
        }
    }
}

vector<MetroLine *> lines;

// int main(){
//     cout<<"welcome to project"<<endl;
//     MetroLine* ml1 = new MetroLine("blue");
//     MetroLine* ml2 = new MetroLine("green");
//     MetroLine* ml3 = new MetroLine("magenta");
//     MetroLine* ml4 = new MetroLine("orange");
//     MetroLine* ml5 = new MetroLine("red");
//     MetroLine* ml6 = new MetroLine("violet");
//     MetroLine* ml7 = new MetroLine("yellow");

//     // MetroStop ms("pune",ml,100);
//     // cout<<ms.getFare();
//     ml1->populateLine("blue.txt");
//     ml2->populateLine("green.txt");
//     ml3->populateLine("magenta.txt");
//     ml4->populateLine("orange.txt");
//     ml5->populateLine("red.txt");
//     ml6->populateLine("violet.txt");
//     ml7->populateLine("yellow.txt");

//     AVLTree* tree = new AVLTree();
//     tree->populateTree(ml1);
//     tree->populateTree(ml2);
//     tree->populateTree(ml3);
//     tree->populateTree(ml4);
//     tree->populateTree(ml5);
//     tree->populateTree(ml6);
//     tree->populateTree(ml7);
//     // tree->inOrderTraversal(tree->getRoot());
//     // cout<<tree->height(tree->getRoot())<<endl;
//     // cout<<tree->getTotalNodes(tree->getRoot());

//     AVLNode* node = tree->searchStop("Janakpuri West");
//     cout<<node->getStopName()<<endl;
//     vector<MetroStop*> stops = node->getStops();
//     cout<<stops[0]->getStopName()<<endl;
//     cout<<stops[0]->getLine()->getLineName()<<endl;
//     cout<<stops[1]->getLine()->getLineName()<<endl;
//     return 0;

//  }
