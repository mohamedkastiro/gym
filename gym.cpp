#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>

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

class Treadmill : public GymEquipment {
private:
    double price;

public:
    Treadmill() {
        price = 1000.0;
    }

    double getPrice() const override {
        return price;
    }

    double getWeight() const override {
        return 0.0; // Treadmill does not have weight
    }
};

class ExerciseBike : public GymEquipment {
private:
    double price;

public:
    ExerciseBike(int resistanceLevel) {
        if (resistanceLevel < 1 || resistanceLevel > 3) {
            throw invalid_argument("Invalid resistance level for Exercise Bike");
        }
        price = resistanceLevel * 500.0;
    }

    double getPrice() const override {
        return price;
    }

    double getWeight() const override {
        return 0.0; // Exercise Bike does not have weight
    }
};

class GymPlan {
protected:
    vector<GymEquipment*> equipment;
public:
    virtual ~GymPlan() {
        for (GymEquipment* eq : equipment) {
            delete eq;
        }
    }

    double getTotalPrice() const {
        double total = 0.0;
        for (const GymEquipment* eq : equipment) {
            total += eq->getPrice();
        }
        return total;
    }

    virtual GymPlan* makePlan() = 0;
};

class BasicPlan : public GymPlan {
public:
    BasicPlan* makePlan() override {
        equipment.push_back(new Dumbbell(10));
        equipment.push_back(new Dumbbell(10));
        equipment.push_back(new ExerciseBike(1));
        return this;
    }
};

class AdvancedPlan : public GymPlan {
public:
    AdvancedPlan* makePlan() override {
        equipment.push_back(new Dumbbell(15));
        equipment.push_back(new Dumbbell(15));
        equipment.push_back(new Barbell(40));
        equipment.push_back(new Treadmill());
        equipment.push_back(new ExerciseBike(3));
        return this;
    }
};

void testDumbbell() {
    GymEquipment* db1 = nullptr;
    try {
        GymEquipment* db1 = new Dumbbell(15);
        assert(db1->getPrice() == 30.0);
        assert(db1->getWeight() == 15);
    } catch (const invalid_argument& e) {
        cerr << "Exception caught: " << e.what() << endl;
        if (db1) delete db1;
        return;
    }

    try {
        GymEquipment* db2 = new Dumbbell(25);
        assert(false);
        delete db2;
    } catch (const invalid_argument& e) {
    }

    delete db1;
    cout << "Dumbbell tests passed!" << endl;
}

void testBarbell() {
    try {
        GymEquipment* bb1 = new Barbell(30);
        assert(bb1->getPrice() == 60.0);
        assert(bb1->getWeight() == 30);
        delete bb1;
    } catch (const invalid_argument& e) {
        cerr << "Exception caught: " << e.what() << endl;
        assert(false);
    }

    try {
        GymEquipment* bb2 = new Barbell(55);
        assert(false);
        delete bb2;
    } catch (const invalid_argument& e) {
    }

    cout << "Barbell tests passed!" << endl;
}

void testTreadmill() {
    try {
        GymEquipment* tm = new Treadmill();
        assert(tm->getPrice() == 1000.0);
        delete tm;
    } catch (const invalid_argument& e) {
        cerr << "Exception caught: " << e.what() << endl;
        assert(false);
    }

    cout << "Treadmill tests passed!" << endl;
}

void testExerciseBike() {
    try {
        GymEquipment* eb1 = new ExerciseBike(2);
        assert(eb1->getPrice() == 1000.0);
        delete eb1;
    } catch (const invalid_argument& e) {
        cerr << "Exception caught: " << e.what() << endl;
        assert(false);
    }

    try {
        GymEquipment* eb2 = new ExerciseBike(4);
        assert(false);
        delete eb2;
    } catch (const invalid_argument& e) {
    }

    cout << "Exercise Bike tests passed!" << endl;
}



void testBasicPlan() {
    GymPlan* plan = new BasicPlan();
    plan = plan->makePlan();
    assert(plan->getTotalPrice() == 540.0);
    delete plan;
    cout << "BasicPlan tests passed!" << endl;
}

void testAdvancedPlan() {
    GymPlan* plan = new AdvancedPlan();
    plan = plan->makePlan();
    assert(plan->getTotalPrice() == 2640.0);
    delete plan;
    cout << "AdvancedPlan tests passed!" << endl;
}

int main() {
    testDumbbell();
    testBarbell();
    testTreadmill();
    testExerciseBike();
    testBasicPlan();
    testAdvancedPlan();

    cout << "All tests passed!" << endl;
    return 0;
}
