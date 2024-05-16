#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

class TransportService
{
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip);

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

    vector<Trip *> getTrips()
    {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

class Location
{
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {
        for (int i = 0; i < serviceptrs.size(); i++)
        {
            if (serviceptrs[i]->getName() == droplocation)
            {
                return serviceptrs[i];
                break;
            }
        }
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }

    TransportService *setServicePtr(std::string droplocation)
    {
        return nullptr;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

    void add_service(TransportService *ser)
    {
        serviceptrs.push_back(ser);
    }

    vector<Trip *> getTrips()
    {
        return trips;
    }

private:
    std::string name;
    std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int height_help(BinaryTreeNode *root)
    {

        // base case for empty tree
        if (root == NULL)
        {

            return 0;
        }

        int leftHeight = height_help(root->getLeftPtr());
        int rightHeight = height_help(root->getRightPtr());

        return 1 + max(leftHeight, rightHeight);
    }

    int getHeight()
    {


        return height_help(this->root);
    }

    int No_of_nodes_help(BinaryTreeNode *root)
    {

        if (root == NULL)
        {
            return 0;
        }

        int leftCount = No_of_nodes_help(root->getLeftPtr());
        int rightCount = No_of_nodes_help(root->getRightPtr());

        return 1 + leftCount + rightCount;
    }
    int getNumberOfNodes()
    {

        return No_of_nodes_help(this->root);
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        // Implement getting the element with the minimum key
        BinaryTreeNode *node = root;

        while (node->getLeftPtr() != nullptr)
        {
            node = node->getLeftPtr();
        }
        // now node has element with min key

        return node;
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement getting the element with the maximum key
        BinaryTreeNode *node = root;

        while (node->getRightPtr() != nullptr)
        {
            node = node->getRightPtr();
        }
        // now node has element with min key

        return node;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // Implement searching for a node with the given key
        BinaryTreeNode *node = root;
        while (node != nullptr && node->getDepartureTime() != key)
        {
            if (key > node->getDepartureTime())
            {
                node = node->getRightPtr();
            }
            else
            { // key>node->key
                node = node->getLeftPtr();
            }
        }

        return node;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement getting the successor node of the given node

        int key = node->getDepartureTime();

        // if node->right doesnt exist
        BinaryTreeNode *parent = node->getParentPtr();
        BinaryTreeNode *child = node;
        while (parent->getRightPtr() == child)
        {
            child = parent;
            parent = parent->getParentPtr();
        }
        if (parent->getLeftPtr() == child)
        {
            // parent node becomes successor here
            return parent;
        }

        // if node->right exists
        if (node->getRightPtr() != nullptr)
        {

            node = node->getRightPtr();
            while (node->getLeftPtr() != nullptr)
            {
                node = node->getLeftPtr();
            }

            return node;
        }

        return nullptr;
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        // Implement getting the successor node by key
        BinaryTreeNode *node = root;

        node = searchNodeWithKey(key);
        node = getSuccessorNode(node);

        return node;
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        // Implement getting the predecessor node of the given node

        int key = node->getDepartureTime();

        // if node->left doesnt exist
        BinaryTreeNode *parent = node->getParentPtr();
        BinaryTreeNode *child = node;
        while (parent->getLeftPtr() == child)
        {
            child = parent;
            parent = parent->getParentPtr();
        }
        if (parent->getRightPtr() == child)
        {
            // parent node becomes successor here
            return parent;
        }

        // if node->left exists
        if (node->getLeftPtr() != nullptr)
        {

            node = node->getLeftPtr();
            while (node->getRightPtr() != nullptr)
            {
                node = node->getRightPtr();
            }

            return node;
        }

        return nullptr;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        // Implement getting the predecessor node by key
        BinaryTreeNode *node = root;

        node = searchNodeWithKey(key);
        node = getPredecessorNode(node);

        return node;
    }
};
class TravelDesk
{
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        // Implement this function to add a trip

        // for vechical object
        int check = 1, i = 0;
        // Vehicle*v=nullptr;
        for (i = 0; i < vehicles.size(); i++)
        {
            if (vehicle_number == vehicles[i]->getVehicleNumber())
            {
                vehicles[i];
                check = 0;
                break; // dont add this vech obj
            }
        }
        if (check == 1)
        { // this means this vechicle wasnt present in vector previously so
            Vehicle *v = new Vehicle(vehicle_number, seating_capacity);
            vehicles.push_back(v);
            i = vehicles.size() - 1;
        }

        // now creating trip obj
        Trip *tr = new Trip(vehicles[i], pick_up_location, drop_location, departure_time);
        // cout<< tr->getVehicle()->getVehicleNumber()<<endl;
        vehicles[i]->addTrip(tr);
        // added trip to vech obj

        // creating a loc obj and adding it to vector
        check = 1;
        for (i = 0; i < locations.size(); i++)
        {
            if (pick_up_location == locations[i]->getName())
            {
                check = 0;
                locations[i]->addTrip(tr);
                // service obj
                TransportService *ser = new TransportService(drop_location);
                // now adding elements in BST for this service
                ser->setBSTHead(insert(ser->getBSTHead(), departure_time, tr));
                // cout<<ser->getBSTHead()->getDepartureTime()<<endl;
                locations[i]->add_service(ser);
            }
        }
        if (check == 1)
        {
            Location *loc = new Location(pick_up_location);
            loc->addTrip(tr);
            locations.push_back(loc);
            // service obj

            TransportService *ser = new TransportService(drop_location);
            ser->setBSTHead(insert(ser->getBSTHead(), departure_time, tr));
            locations.back()->add_service(ser);
            // cout<<ser->getBSTHead()->getDepartureTime()<<endl;
        }

        // cout<<locations.back()->getName()<<endl;
    }

    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range
        Location *loc = nullptr;
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
            {
                loc = locations[i];
                break;
            }
        }
        // loc is the location for which we need to show trips
        vector<Trip *> trips = loc->getTrips();
        vector<Trip *> desiredTrips;

        for (int i = 0; i < trips.size(); i++)
        {

            // cout<<"lol";
            if (trips[i]->getDepartureTime() < before_time && trips[i]->getDepartureTime() >= after_time)
            {
                // cout<<trips[i]->getDepartureTime()<<endl;
                desiredTrips.push_back(trips[i]);
            }
        }
        // desired trips as name suggests bruh

        return desiredTrips;
    }

    vector<Trip *> showTripsbydestination(string pick_up_location, string destination, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        Location *loc = nullptr;
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
            {
                loc = locations[i];
                break;
            }
        }

        TransportService *ser = loc->getServicePtr(destination);
        BinaryTreeNode *root = ser->getBSTHead();
        vector<Trip *> desired_trips;
        inOrderTraversal(root, desired_trips);

        return desired_trips;
    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        // Implement this function to book a trip
        int i = 0, j = 0;
        Vehicle *v = nullptr;

        for (i = 0; i < vehicles.size(); i++)
        {

            if (vehicles[i]->getVehicleNumber() == vehicle_number)
            {
                v = vehicles[i];
                break;
            }
        }

        // incorrect vechical condition
        if (i == vehicles.size())
        {
            return nullptr;
        }

        // v is the vechical for which im booking the trip
        // trip details are in argument
        // cout<<i<<endl;
        // cout<<v->getVehicleNumber()<<endl;
        // cout<<vehicles[i]->getVehicleNumber()<<endl;
        vector<Trip *> trips = v->getTrips();
        Trip *tr = nullptr;
        for (j = 0; j < trips.size(); j++)
        {
            if (trips[j]->getPickUpLocation() == pick_up_location && trips[j]->getDropLocation() == drop_location && trips[j]->getDepartureTime() == departure_time)
            {
                tr = trips[j];
                break;
            }
        }

        if (tr == nullptr)
        {
            return nullptr;
        }

        int bookedTrips = 0;
        bookedTrips = trips[j]->getBookedSeats();
        bookedTrips++;

        trips[j]->setBookedSeats(bookedTrips);

        return trips[j]; // Placeholder
    }
    Location *getLocation(std::string location)
    {
        for (int i = 0; i < locations.size(); i++)
        {
            if (location == locations[i]->getName())
            {
                return locations[i];
            }
        }
        return nullptr;
    }

    BinaryTreeNode *insert(BinaryTreeNode *root, int key, Trip *tr)
    {

        if (root == nullptr)
        {
            return new BinaryTreeNode(key, tr);
        }

        // Otherwise, recur down the tree
        if (key < root->getDepartureTime())
        {
            root->setLeftPtr(insert(root->getLeftPtr(), key, tr));
        }
        else if (key > root->getDepartureTime())
        {
            root->setRightPtr(insert(root->getRightPtr(), key, tr));
        }

        // Return the (unchanged) node pointer
        return root;
    }

    void inOrderTraversal(BinaryTreeNode *root, vector<Trip *> trips)
    {
        if (root == nullptr)
        {
            // cout<<"kuch nahi hai anadar"<<endl;
            return;
        }
        inOrderTraversal(root->getLeftPtr(), trips);
        // cout << root->getDepartureTime() << " ";
        trips.push_back(root->getTripNodePtr());
        inOrderTraversal(root->getRightPtr(), trips);
    }

    void printlol()
    {
        BinaryTreeNode *bt = locations[0]->getServicePtr("droploc2")->getBSTHead();
        // inOrderTraversal(bt);
        // cout<<"mu lalalala";
        cout << bt->getDepartureTime();
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
};

// int main(){

//     // TravelDesk td;
//     // td.add_trip("MH013",2,"pickup","droploc1",4);
//     // td.add_trip("MH014",3,"pickup","droploc2",6);
//     // td.add_trip("MH015",3,"pickup","droploc2",2);
//     // td.book_trip("pickup","droploc2","MH015",12);
//     // td.add_trip("MH013  ",3,"pickup","droploc2",3);
//     // td.add_trip("MH013  ",3,"pickup","droploc2",7);
//     // td.add_trip("MH013  ",3,"pickup","droploc3",3);
//     // td.add_trip("MH013  ",3,"pickup2","droploc4",7);

//     // td.printlol();

//     return 0;
// }
