# automotive-dealership-management-system
C++ implementation of an automotive service management system using custom Linked Lists, Trees, and Max Heaps.

# Automotive Dealership Management System

A command-line management system for organizing automotive dealerships, hierarchical vehicle services, and customer service orders.

The main focus of this project is the **implementation and integration of fundamental data structures from scratch** to model a real-world service management problem.

## Overview

The system is designed for an automotive company that manages multiple dealerships and the services they provide to customers.

The company can define services and organize them into an arbitrary hierarchy of sub-services. Dealerships can offer different services, while customers can submit service orders to specific dealerships.

Each dealership maintains its pending orders according to their urgency and submission time using a **Max Heap-based priority queue**.

### Example Service Hierarchy

```text
Body Repair
├── Bumper Replacement
├── Bodywork
├── Tire Services
│   ├── Tire Replacement
│   └── Tire Repair
└── Interior Services
```

Services are not restricted to a fixed number of hierarchical levels.

## Key Features

### Agency Management

* Add a new dealership
* Display the list of dealerships

### Service Management

* Add a new main service
* Add a sub-service to an existing service
* Display all services and their complete hierarchy
* Display the sub-services of a specific service
* Associate services with dealerships
* Remove services from dealerships
* Automatically remove services and their descendants when they are no longer offered by any dealership

### Order Management

Customers can submit an order for a service offered by a specific dealership.

Each order has an urgency level:

* **Immediate / Necessary**
* **Required**
* **Normal**

Orders are prioritized according to:

1. Urgency level
2. Submission time

If two orders have the same urgency, the order submitted earlier receives higher priority.

Each dealership maintains its orders using a **Max Heap**, so the highest-priority order is always available at the root.

## Data Structures

One of the main requirements of the project was to implement the required data structures rather than relying on library implementations.

### Linked Lists

Linked lists are used to manage dynamic collections such as:

* Dealerships
* Services
* Services associated with dealerships

### Hierarchical Service Structure

Services can contain sub-services recursively, allowing an arbitrary number of hierarchy levels.

Conceptually, the structure can be represented as:

```text
Service
├── Sub-service
│   ├── Sub-service
│   └── Sub-service
└── Sub-service
```

This structure supports operations such as adding sub-services, traversing the hierarchy, and removing unused services.

### Max Heap

Each dealership has a priority queue implemented using a **Max Heap**.

The heap determines the next order to be processed based on:

```text
Higher urgency
      ↓
Earlier submission time
      ↓
Higher priority
```

When orders are listed and processed, they are removed from the heap in priority order until the queue becomes empty.

## Service Removal Logic

A service can be offered by more than one dealership.

Therefore, removing a service from one dealership does not necessarily remove the service from the global service hierarchy.

For example:

```text
Dealership A ──┐
               ├── Tire Services
Dealership B ──┘
```

If Dealership A stops offering `Tire Services`, the service remains available because Dealership B still provides it.

Only when no dealership offers the relevant service anymore can the service and its dependent sub-services be removed when appropriate.

This requirement makes service deletion more than a simple linked-list removal operation and requires maintaining relationships between dealerships and the service hierarchy.

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

delete <Service_Name> from <Agency_Name>
```

### Query Commands

```text
list services

list services from <Service_Name>
```

### Order Commands

```text
order <Service_Name> to <Agency_Name>
      by <Customer_Name>
      with <Immediacy_Level>

list orders <Agency_Name>
```

## Example

A possible service hierarchy:

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

Suppose a dealership receives the following orders:

```text
Order 1 → Normal    → 10:05
Order 2 → Necessary → 10:10
Order 3 → Necessary → 10:02
Order 4 → Required  → 10:01
```

The Max Heap processes them in:

```text
Order 3
Order 2
Order 4
Order 1
```

The two `Necessary` orders are ordered by their submission time.

## Design Goals

The project was developed with the following goals:

* Implement core data structures manually
* Combine multiple data structures to solve a larger problem
* Model hierarchical relationships between services
* Maintain relationships between dealerships and services
* Implement priority-based scheduling
* Handle insertion, deletion, traversal, and searching operations
* Provide a simple command-line interface for interacting with the system

## Constraints

The project was intentionally implemented without relying on ready-made implementations of the required data structures.

The core structures, including linked lists, trees, queues, stacks, and heaps where required, are implemented manually.

Arrays and basic array-based structures can be used as supporting structures.

## Technical Concepts

This project demonstrates practical experience with:

* Data Structures
* Algorithms
* Linked Lists
* Trees and hierarchical data
* Max Heap
* Priority Queues
* Recursive traversal
* Searching
* Dynamic insertion and deletion
* Object-oriented design
* Command-line interfaces
* Problem decomposition

## Project Structure

```text
automotive-dealership-management-system/
│
├── src/
│   ├── ...
│
├── README.md
└── ...
```

The source code is organized around the entities, data structures, and operations required by the system.

## Running the Project

Clone the repository:

```bash
git clone https://github.com/YOUR_USERNAME/automotive-dealership-management-system.git
cd automotive-dealership-management-system
```

Build and run the project according to the language and build system used in this repository.

## Example Workflow

A typical interaction with the system may look like:

```text
> add agency Tehran_Agency

> add service Tire_Services

> add subservice Tire_Replacement to Tire_Services

> add subservice Tire_Repair to Tire_Services

> add offer Tire_Services to Tehran_Agency

> order Tire_Replacement to Tehran_Agency by Ali with Necessary

> order Tire_Repair to Tehran_Agency by Sara with Normal

> list orders Tehran_Agency
```

The orders are then processed according to the priority rules implemented by the Max Heap.

## Possible Future Improvements

Potential extensions include:

* Persistent storage
* Database integration
* REST API
* Graphical or web-based interface
* Automated unit and integration tests
* Authentication and role-based access control
* Performance benchmarking
* Additional scheduling policies
