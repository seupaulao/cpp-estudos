#include <string>
#include <iostream>

using namespace std;

std::string convert(int n) {
        std::string ret = "";
        if (n % 3 == 0) { ret = ret + "Pling"; }
        if (n % 5 == 0) { ret = ret +  "Plang"; }
        if (n % 7 == 0) { ret = ret +  "Plong"; }
        if ((n % 3 != 0) && (n % 5 != 0) && (n % 7 != 0)) {
            return std::to_string(n);
        } else {
            return ret;
        }
    }

int main() {
    cout << "Saida: " << ((1 % 3) == 0) << endl;
    cout << convert(1) << endl;
    cout << convert(8) << endl;
    cout << convert(52) << endl;
}  // namespace raindrops
