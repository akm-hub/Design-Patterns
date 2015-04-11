/**
  * @purpose A simple object pool example
  *
  * @author  Ashish
  * @license MIT license
  * @version 1.0, Doxygen compatible comments
  */

#include<iostream>
#include<string>
#include<list>
using namespace std;

class Car {
 private:
    bool in_use_;
    string rentee_;
    string last_rentee_;

 public:
    Car()
    : in_use_(false),
    last_rentee_("NONE"),
    rentee_("NONE") {
    }

    void set_in_use(bool status) {
        in_use_ = true;
    }

    bool in_use(void) {
        return in_use_;
    }

    void set_rentee(const string& given_rentee) {
        rentee_ = given_rentee;
    }

    string rentee(void) {
        return rentee_;
    }

    void set_last_rentee(const string& given_rentee) {
        last_rentee_ = given_rentee;
    }

    string last_rentee(void) {
        return last_rentee_;
    }
};

class CarPool : public Car {
 private:
    list <Car*> car_list;  /// list STL to store object pointers

 public:
    static CarPool& get_instance() {  /// singleton objectpool instance
        static CarPool instance;
        return instance;
    }

    Car* get_car() {
        Car* car = NULL;

        if (car_list.empty()) {  /// case 1: Henry gets a brand new car for the first customer
            car = new Car;
        } else {
            car = car_list.front();  /// case 2: Henry allots an already existing car to the customer
            car_list.pop_front();
        }

        car->set_in_use(true);
        return car;
    }

    Car* return_car(Car *given_car) {
        if (given_car != NULL) {
            given_car->set_in_use(false);
            given_car->set_last_rentee(given_car->rentee());  /// Henry notes the previous customer name
            given_car->set_rentee("NONE");

            car_list.push_back(given_car);  /// The car has been returned to Henry's car lot
            return NULL;
        }
    }

 protected:
    CarPool() {
    }
};

int main() {
    CarPool henrys_car_rental = CarPool::get_instance();  /// henry starts a car rental service

    /// usecase 1 - alice is the first customer, she gets a brand new car
    Car* alices = henrys_car_rental.get_car();  /// alice gets a car from henry's rental service
    cout << "Alice's car was last rented to = " << alices->last_rentee() << endl;
    alices->set_rentee("ALICE");  /// alice is now registered as the rentee and can drive the car
    cout << "Alice's car is now rented to = " << alices->rentee() << endl;

    /// usecase 2 - bob is the next customer, he also gets a new car
    Car* bobs = henrys_car_rental.get_car();  /// bob also gets a car from henry's rental service
    cout << "Bob's car was last rented to = " << bobs->last_rentee() << endl;
    bobs->set_rentee("BOB");  /// the car is now resitered to BOB as rentee
    cout << "Bob's car is now rented to = " << alices->rentee() << endl;
    bobs = henrys_car_rental.return_car(bobs);  /// bob returns the car to henry's rental service

    /// usecase 3 - fred is a customer, who gets the car bob has returned
    Car* freds = henrys_car_rental.get_car();  /// fred gets bob's returned car from henry's rental service
    cout << "Fred's car was last rented to = " << freds->last_rentee() << endl;
    freds->set_rentee("FRED");  /// the car is now resitered to FRED as rentee
    cout << "Fred's car is now rented to = " << freds->rentee() << endl;
    freds = henrys_car_rental.return_car(freds);  /// fred returns the car to henry's rental service

    return 0;
}

