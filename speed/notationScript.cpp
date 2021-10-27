#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
  string letters[] = {"a","b","c","d","e","f","g","h"};
  string nums[] = {"1","2","3","4","5","6","7","8"};

  for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
          cout << "\"" << letters[i] << nums[j] << "\",";
      }
  }

  string filesWhite[] = {"a8","b8","c8","d8","e8","f8","g8","h8"};
    string promoWhite[] = {"Q","R","N","B"};
    string filesBlack[] = {"a1","b1","c1","d1","e1","f1","g1","h1"};
    string promoBlack[] = {"q","r","n","b",};

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            string temp = filesWhite[i] + promoWhite[j];
            cout << "\"" << temp << "\",";
        }
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            string temp = filesBlack[i] + promoBlack[j];
            cout << "\"" << temp << "\",";
        }
    }

    cout << endl;

  for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
          cout << letters[i] << nums[j] << ", ";
      }
  }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            string temp = filesWhite[i] + promoWhite[j];
            cout << temp << ", ";
        }
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            string temp = filesBlack[i] + promoBlack[j];
            cout << temp << ", ";
        }
    }

  for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        string temp = letters[i] + nums[j];
        cout <<  "if(s=="<< "\"" << temp << "\") " << "return " <<temp << ";" << endl;
      }
  }
  for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 4; j++) {
          string temp = filesWhite[i] + promoWhite[j];
          cout <<  "if(s=="<< "\"" << temp << "\") " << "return " <<temp << ";" << endl;
      }
  }

  for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 4; j++) {
          string temp = filesBlack[i] + promoBlack[j];
          cout <<  "if(s=="<< "\"" << temp << "\") " << "return " <<temp << ";" << endl;
      }
  }

    vector<string> letters = {"a", "b", "c", "d", "e", "f", "g", "h"};
    vector<string> promo = {"Q", "R", "B", "N"};
    for(int i = 0; i < letters.size(); i++) {
        for(int j =0; j < promo.size(); j++) {
        cout << "case ";
        cout << letters[i] << "8"<<promo[j]<<": ";
        cout << "x=" << i << "; y=0;";
        cout << "break;"<<endl;
        }
    }
    promo = {"q", "r", "b", "n"};
    for(int i = 0; i < letters.size(); i++) {
        for(int j =0; j < promo.size(); j++) {
        cout << "case ";
        cout << letters[i] << "1"<<promo[j]<<": ";
        cout << "x=" << i << "; y=7;";
        cout << "break;"<<endl;
        }
    }
}