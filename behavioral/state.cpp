/**
  * @purpose     Demonstrate state design pattern using fsm and pointers
  *
  * @description The State pattern allows an object to change its behavior
  *              when its internal state changes. This example shows, a Vending
  *              machine that vends one item and depends on one state variable
  *              inventory
  *
  * @author      Ashish
  * @license     MIT license
  * @version     1.0, Doxygen compatible comments
  */

#include<iostream>
#include<exception>
#include<stdexcept>

class VendingMachine;
class InventoryState {  /// state abstract base class
 public:
    virtual void sell(VendingMachine&, int) = 0;
    virtual void restock(VendingMachine&, int) = 0;
    virtual ~InventoryState();
};

class InStock : public InventoryState {  /// Individual state derived class
 public:
    virtual void sell(VendingMachine&, int);
    virtual void restock(VendingMachine&, int);
    virtual ~InStock();
};

class OutOfStock : public InventoryState {  /// Individual state derived class
 public:
    virtual void sell(VendingMachine&, int);
    virtual void restock(VendingMachine&, int);
    virtual ~OutOfStock();
};

class VendingMachine {  /// Context class - presents a single interface to the outside world
 private:
    InventoryState* state_;  /// Maintain a pointer to the current "state"
    int stock_units_;

 public:
    explicit VendingMachine(int);
    ~VendingMachine();

    void set_state(InventoryState*);

    int stock_units(void);
    int set_stock_units(int);

    void sell(int);
    void restock(int);
};

VendingMachine::VendingMachine(int given_stock_units)
    : stock_units_(given_stock_units), state_(new InStock()) {
}

VendingMachine::~VendingMachine() {
    delete state_;
}

void VendingMachine::sell(int asked_units) {
    state_->sell(*this, asked_units);
}

void VendingMachine::restock(int given_units) {
    state_->restock(*this, given_units);
}

int VendingMachine::stock_units() {
    return stock_units_;
}

void VendingMachine::set_state(InventoryState* state) {
    delete state_;
    state_ = state;
}

int VendingMachine::set_stock_units(int given_stock_units) {
    stock_units_ = given_stock_units;
}

InventoryState::~InventoryState() {
}

InStock::~InStock() {
}

void InStock::sell(VendingMachine &machine, int asked_units) {
    int cur_stock_units = machine.stock_units();
    if (cur_stock_units < asked_units) {
        throw std::runtime_error("Insufficient inventory");
    }

    machine.set_stock_units(cur_stock_units - asked_units);

    if (machine.stock_units() == 0) {
        machine.set_state(new OutOfStock());
    }
}

void InStock::restock(VendingMachine &machine, int given_units) {
    machine.set_stock_units(machine.stock_units() + given_units);
}

OutOfStock::~OutOfStock() {
}

void OutOfStock::sell(VendingMachine &machine, int asked_units) {
    throw std::runtime_error("Sold out");
}

void OutOfStock::restock(VendingMachine &machine, int given_units) {
    machine.set_stock_units(given_units);
    machine.set_state(new InStock());
}

int main() {
    VendingMachine vending_machine(10);

    try {
    std::cout << "Selling 10 items" << std::endl;
    vending_machine.sell(10);
    std::cout << "Sold 10 items" << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout  << "Selling 1 item" << std::endl;
        vending_machine.sell(1);
        std::cout << "Sold 1 item" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Can't sell : " << e.what() << std::endl;
    }

    std::cout << "Refilling 20 items" << std::endl;
    vending_machine.restock(20);

    try {
        std::cout << "Selling 10 items" << std::endl;
        vending_machine.sell(10);
        std::cout << "Sold 10 items" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Can't Sell : " << e.what() << std::endl;
    }

    try {
        std::cout << "Selling another 20 items" << std::endl;
        vending_machine.sell(20);
    } catch (std::exception& e) {
        std::cerr << "Can't Sell : " << e.what() << std::endl;
    }
    return 0;
}
