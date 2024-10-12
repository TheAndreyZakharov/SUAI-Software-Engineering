#include <iostream>
using namespace std;

class Range{
  public:
    void rangedraw();
    void rangeset(double set_left, double set_right);
    bool rangecheck(double num);
    
  private:
    double left = 0;
    double right = 0;

};

void Range::rangedraw() {
  cout << "Левая граница: " << left << endl;
  cout << "Правая граница: " << right << endl;
}

void Range::rangeset(double set_left, double set_right) {
  left = set_left;
  right = set_right;
}

bool Range::rangecheck(double num) {
  return (left <= num) && (num < right);
}
