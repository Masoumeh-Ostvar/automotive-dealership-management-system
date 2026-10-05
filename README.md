# Automotive Dealership Management System

A C++ implementation of an automotive dealership management system using custom linked data structures and a manually implemented Max Heap-based priority queue.

## Overview

This project implements a management system for automotive dealerships, hierarchical vehicle services, and customer service orders.

The system models a company that manages multiple dealerships and the services they provide. Services can be organized into multiple levels of sub-services, while dealerships can offer different services to their customers.

Each dealership maintains its own collection of customer orders using a custom **Max Heap** based on service urgency.

The main focus of the project is the **implementation and integration of fundamental data structures from scratch** to solve a real-world management problem.

## Key Features

### Dealership Management

* Add a new dealership
* Search for a dealership
* Display the list of dealerships
* Maintain a separate priority queue for each dealership

### Service Management

* Add a new main service
* Add sub-services to existing services
* Support multiple levels of nested services
* Search services through the hierarchy
* Display all services and their sub-services
* Display sub-services of a specific service
* Associate services with dealerships

### Order Management

Customers can submit service orders to a specific dealership.

Each order contains:

* Service name
* Dealership name
* Customer name
* Immediacy level

Orders are maintained using a custom **Max Heap** for each dealership.

The current implementation prioritizes orders based on their **immediacy level**, with higher urgency receiving higher priority.

## Data Structures

A major goal of this project is to implement the required data structures manually rather than relying on ready-made implementations.

### Agency Linked List

Dealerships are stored in a custom singly linked list.

Each agency node contains:

```text
AgencyNode
├── name
├── PriorityQueue
└── next
```

This allows every dealership to maintain its own priority queue of customer orders.

### Hierarchical Service Structure

Services are represented using a custom linked structure with two relationships:

* `next` — connects services at the same hierarchy level
* `down` — points to the first sub-service

Conceptually:

```text
Service
├── Sub-service
│   ├── Sub-service
│   └── Sub-service
└── Sub-service
```

This representation supports multiple levels of nested services.

The core node is represented by:

```cpp
struct ServiceNode
{
    bool has_down;
    data_service_struct data;
    ServiceNode* next;
    ServiceNode* down;
};
```

### Max Heap

Each dealership owns a custom `PriorityQueue` implemented using a Max Heap.

The heap stores customer orders and provides the following operations:

* `push`
* `pop`
* `top`
* `empty`
* `size`

The heap uses `std::vector` as its underlying storage, while the heap operations are implemented manually.

The implementation includes:

* Parent calculation
* Left and right child calculation
* `heapify_up`
* `heapify_down`

The highest-immediacy order is maintained at the root of the heap.

## Service Information

Each service stores information such as:

```cpp
struct data_service_struct
{
    string service_name;
    string car_model;
    string customer_comments;
    string agent_comments;
    vector<string> agencies;
    int cost;
};
```

This includes:

* Service name
* Supported vehicle model
* Customer-facing description
* Technical description for dealership staff
* Associated dealerships
* Service cost

## Agency-Service Relationship

The system maintains relationships between dealerships and services using:

```cpp
struct AgencyServiceNode
{
    string service_name;
    string agency_name;
};
```

For example:

```text
Agency A ─── Service X
Agency A ─── Service Y
Agency B ─── Service X
Agency B ─── Service Z
```

This allows a service to be associated with multiple dealerships.

## Order Priority

Each dealership has its own Max Heap:

```text
Dealership
     │
     ▼
  Max Heap
     │
     ├── Order
     ├── Order
     └── Order
```

The order with the highest immediacy level is kept at the root of the heap.

When the order list is requested, orders are repeatedly removed from the heap and displayed until the priority queue becomes empty.

> **Note:** The current implementation prioritizes orders only by immediacy level. Timestamp-based tie-breaking for orders with equal urgency has not yet been implemented.

## Supported Commands

### Agency Commands

```text
add agency <Agency_Properties>
list agencies
```

### Service Commands

```text
add service <Service_Properties>

add subservice <Subservice_Name> to <Service_Name>

add offer <Service_Name> to <Agency_Name>
```

### Query Commands

```text
list services

list services from <Service_Name>
```

### Order Commands

```text
order <Service_Name> to <Agency_Name> by <Customer_Name> with <Immediacy_Level>

list orders <Agency_Name>
```

> **Note:** The current source code does not yet contain a complete command-line parser. The listed commands describe the intended system operations and corresponding functionality.

## Example Service Hierarchy

A possible service hierarchy is:

```text
Automotive Services
├── Body Repair
│   ├── Bumper Replacement
│   └── Bodywork
│
└── Tire Services
    ├── Tire Replacement
    └── Tire Repair
```

The hierarchy is not restricted to a fixed number of levels.

## Example Workflow

A typical workflow can look like:

```text
> add agency Tehran_Agency

> add service Tire_Services

> add subservice Tire_Replacement to Tire_Services

> add subservice Tire_Repair to Tire_Services

> add offer Tire_Services to Tehran_Agency

> order Tire_Repair to Tehran_Agency by Ali with 3

> order Tire_Replacement to Tehran_Agency by Sara with 1

> list orders Tehran_Agency
```

Orders are processed according to their immediacy levels using the Max Heap.

## Design Goals

The project was developed with the following goals:

* Implement fundamental data structures manually
* Combine multiple data structures to solve a larger problem
* Represent hierarchical relationships between services
* Maintain relationships between dealerships and services
* Implement priority-based order processing
* Practice insertion, searching, and traversal
* Practice command-oriented system design

## Complexity

The core Max Heap operations have the following time complexities:

| Operation | Complexity |
| --------- | ---------- |
| `top()`   | O(1)       |
| `push()`  | O(log n)   |
| `pop()`   | O(log n)   |
| `empty()` | O(1)       |
| `size()`  | O(1)       |

Additional operations:

* Agency lookup: **O(n)** in the worst case
* Service search: **O(n)** in the worst case, where `n` is the number of service nodes

## Implementation Constraints

The project was designed around the requirement to implement the core data structures manually rather than relying on ready-made data structure implementations.

For example, instead of using:

```cpp
std::priority_queue
```

the project implements its own priority queue using a Max Heap.

`std::vector` is used as supporting dynamic storage where permitted by the project requirements.

## Technologies

* **C++**
* Data Structures & Algorithms
* Singly Linked Lists
* Hierarchical Linked Structures
* Max Heap
* Priority Queues
* Dynamic Memory Allocation
* Pointers
* STL `vector`

## Project Structure

```text
automotive-dealership-management-system/
│
├── S4.cpp
├── maxheap.cpp
└── README.md
```

`maxheap.cpp` contains the custom Max Heap and priority queue implementation, while `S4.cpp` contains the dealership, service, and order management logic.

## Running the Project

Clone the repository:

```bash
git clone https://github.com/Masoumeh-Ostvar/automotive-dealership-management-system.git
cd automotive-dealership-management-system
```

Compile:

```bash
g++ S4.cpp -o main
```

Run:

```bash
./main
```

## Future Improvements

Possible improvements include:

* Add order submission timestamps
* Implement timestamp-based tie-breaking for orders with equal urgency
* Complete service deletion and cleanup logic
* Strengthen validation of agency-service relationships
* Prevent orders for services not offered by a dealership
* Improve memory management using destructors and RAII
* Add automated unit and integration tests
* Separate declarations and implementations into `.h` and `.cpp` files
* Implement complete command parsing
* Improve error handling
* Add performance benchmarking

## Motivation

This project was developed as a practical exercise in **Data Structures and Algorithms**, with an emphasis on understanding how fundamental data structures can be implemented and combined to solve a larger problem.

Rather than relying on high-level implementations from the C++ Standard Library, the project focuses on understanding the underlying mechanisms of linked structures and heap-based priority queues.
