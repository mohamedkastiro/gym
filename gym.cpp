#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class GymEquipment {
public:
    virtual ~GymEquipment() {}
    virtual double getPrice() const = 0;
    virtual double getWeight() const = 0;
};

class Dumbbell : public GymEquipment {
private:
    double weight;
    double price;

public:
    Dumbbell(double _weight) {
        if (_weight > 20) {
            throw invalid_argument("Dumbbell weight cannot exceed 20 kg");
        }
        weight = _weight;
        price = (_weight / 5) * 10.0;
    }

    double getPrice() const override {
        return price;
    }

    double getWeight() const override {
        return weight;
    }
};

class Barbell : public GymEquipment {
private:
    double weight;
    double price;

public:
    Barbell(double _weight) {
        if (_weight > 50) {
            throw invalid_argument("Barbell weight cannot exceed 50 kg");
        }
        weight = _weight;
        price = (_weight / 5) * 10.0;
    }

    double getPrice() const override {
        return price;
    }

    double getWeight() const override {
        return weight;
    }
};

void testDumbbell() {
    GymEquipment* db1 = nullptr;
    try {
        db1 = new Dumbbell(15);
        assert(db1->getPrice() == 30.0);
        assert(db1->getWeight() == 15);
    } catch (const invalid_argument& e) {
        cerr << "Exception caught: " << e.what() << endl;
        if (db1) delete db1;
        return;
    }

    GymEquipment* db2 = nullptr;
    try {
        db2 = new Dumbbell(25);
        assert(false);
    } catch (const invalid_argument& e) {
        delete db2;
    }

    delete db1;
    cout << "Dumbbell tests passed!" << endl;
}

void testBarbell() {
    GymEquipment* bb1 = nullptr;
    try {
        bb1 = new Barbell(30);
        assert(bb1->getPrice() == 60.0);
        assert(bb1->getWeight() == 30);
    } catch (const invalid_argument& e) {
        cerr << "Exception caught: " << e.what() << endl;
        if (bb1) delete bb1;
        return;
    }

    GymEquipment* bb2 = nullptr;
    try {
        bb2 = new Barbell(55);
        assert(false);
    } catch (const invalid_argument& e) {
        delete bb2;
    }

    delete bb1;
    cout << "Barbell tests passed!" << endl;
}

int main() {
    testDumbbell();
    testBarbell();

    cout << "All tests passed!" << endl;
    return 0;
}
