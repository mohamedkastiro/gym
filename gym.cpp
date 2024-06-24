#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void testDumbbell() {
    Dumbbell db1(15);
    assert(db1.getPrice() == 30.0); 
    assert(db1.getWeight() == 15); 

    
    try {
        Dumbbell db2(25); // gona put limits on the dumbell weights so this shouldnt work
        assert(false); 
    } catch (const invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "Dumbbell tests passed!" << endl;
}
void testBarbell() {
    Barbell bb1(30);
    assert(bb1.getPrice() == 60.0);  
    assert(bb1.getWeight() == 30);

    try {
        Barbell bb2(55); 
        assert(false); 
    } catch (const invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "Barbell tests passed!" << endl;
}

int main() {
testDumbbell();

return 0;
}
 