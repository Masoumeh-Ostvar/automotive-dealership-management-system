#include <iostream>
#include <string>
#include "maxheap.cpp"
using namespace std;

struct AgencyNode
{
    string name;
    PriorityQueue pq;
    AgencyNode *next;
};

struct AgencyServiceNode
{
    string service_name;
    string agency_name;
};

struct data_service_struct
{
    string service_name;
    string car_model;
    string customer_comments;
    string agent_comments;
    vector<string> agencies;
    int cost;
};

struct ServiceNode
{
    bool has_down = false;
    data_service_struct data;
    ServiceNode *next = NULL;
    ServiceNode *down = NULL;
};

class ServiceLinkedList
{
    ServiceNode *head;

public:
    // default constructor. Initializing head pointer
    ServiceLinkedList()
    {
        head = NULL;
    }

    // inserting elements (At start of the list)
    void insert(data_service_struct val)
    {
        // make a new node
        ServiceNode *new_node = new ServiceNode;
        new_node->data = val;
        new_node->next = NULL;

        // If list is empty, make the new node, the head
        if (head == NULL)
            head = new_node;
        // else, make the new_node the head and its next, the previous
        // head
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }

    // loop over the list. return true if element found
    vector<ServiceNode *> search_node(string val)
    {
        vector<ServiceNode *> res;
        vector<ServiceNode *> q;
        ServiceNode *temp;
        ServiceNode *prev = head;
        q.push_back(head);
        while (!q.empty())
        {
            temp = q.back();
            q.pop_back();
            while (temp != NULL)
            {
                if (temp->data.service_name == val)
                {
                    res.push_back(prev);
                    res.push_back(temp);
                    return res;
                }
                if (temp->has_down)
                {
                    q.push_back(temp->down);
                }
                prev = temp;
                temp = temp->next;
            }
        }
        res.push_back(NULL);
        res.push_back(NULL);
        return res;
    }

    void list_services()
    {
        vector<ServiceNode *> q;
        ServiceNode *temp = head;
        q.push_back(head);
        while (!q.empty())
        {
            temp = q.back();
            q.pop_back();
            while (temp != NULL)
            {
                cout << temp->data.service_name << endl;
                if (temp->has_down)
                {
                    q.push_back(temp->down);
                }
                temp = temp->next;
            }
        }
    }

    void list_services_from(string Service_Name)
    {
        ServiceNode *temp = search_node(Service_Name)[1];
        cout << temp->data.service_name << endl;
        vector<ServiceNode *> q;
        if (temp->has_down)
            q.push_back(temp->down);
        else
            return;
        while (!q.empty())
        {
            temp = q.back();
            q.pop_back();
            while (temp != NULL)
            {
                cout << temp->data.service_name << endl;
                if (temp->has_down)
                {
                    q.push_back(temp->down);
                }
                temp = temp->next;
            }
        }
    }

    void add_subservice(data_service_struct subservice_data, string service_name)
    {
        ServiceNode *main_node = search_node(service_name)[1];
        ServiceNode *sub_node = new ServiceNode;
        sub_node->data = subservice_data;
        sub_node->next = NULL;
        if (!main_node->has_down)
        {
            main_node->has_down = true;
            main_node->down = sub_node;
        }
        else
        {
            ServiceNode *tmp = main_node->down;
            main_node->down = sub_node;
            sub_node->next = tmp;
        }
    }
};

class AgencyLinkedList
{
    // Head pointer
    AgencyNode *head;

public:
    // default constructor. Initializing head pointer
    AgencyLinkedList()
    {
        head = NULL;
    }

    // inserting elements (At start of the list)
    void insert(string val)
    {
        // make a new node
        AgencyNode *new_node = new AgencyNode;
        new_node->name = val;
        new_node->next = NULL;

        // If list is empty, make the new node, the head
        if (head == NULL)
            head = new_node;
        // else, make the new_node the head and its next, the previous
        // head
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }

    // loop over the list. return true if element found
    AgencyNode *search(string val)
    {
        AgencyNode *temp = head;
        while (temp != NULL)
        {
            if (temp->name == val)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void list_agencies()
    {
        AgencyNode *temp = head;
        while (temp != NULL)
        {
            cout << temp->name << "\n";
            temp = temp->next;
        }
        cout << endl;
    }
};

vector<AgencyServiceNode> asn;

AgencyLinkedList al;

void add_offer(string Service_Name, string Agency_Name)
{
    AgencyServiceNode tmp;
    tmp.agency_name = Agency_Name;
    tmp.service_name = Service_Name;
    asn.push_back(tmp);
}


void order(string service_name, string agency_name, string customer_name, int Immediacy_Level)
{
    struct order_struct o;
    o.Service_Name = service_name;
    o.Agency_Name = agency_name;
    o.Customer_Name = customer_name;
    o.Immediacy_Level = Immediacy_Level;
    AgencyNode *ag = al.search(agency_name);
    ag->pq.push(o);
}

void list_orders(string Agency_Name)
{
    AgencyNode *g = al.search(Agency_Name);
    while (!g->pq.empty())
    {
        cout << "processing service: " << g->pq.top().Service_Name << endl
             << "customer name: " << g->pq.top().Customer_Name << endl
             << "at agency: " << g->pq.top().Agency_Name << endl
             << "immediacy level: " << g->pq.top().Immediacy_Level << endl
             << "-------------------------------------" << endl;
        g->pq.pop();
    }
}

int main()
{
    al.insert("a1");
    al.insert("a2");

    ServiceLinkedList sl;
    data_service_struct ds1, ds3;
    ds1.service_name = "khadamate lastik";
    ds1.car_model = "peugeot";
    sl.insert(ds1);

    ds3.service_name = "tamire motor";
    ds3.car_model = "peugeot";
    sl.insert(ds3);

    data_service_struct ds2;
    ds2.service_name = "panchar giri";
    ds2.cost = 10000;
    sl.insert(ds2);
    sl.add_subservice(ds2, "khadamate lastik");
    sl.list_services();
}