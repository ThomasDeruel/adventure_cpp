#include <iostream>
#include <string>

using namespace std;

struct Arme {
  string nom;
  int degat;
  float poids;
};

struct Aventurier {
  int force;
  int dex;
  int intell;
  int charism;
  Arme arme;
};

void presenter(Aventurier aventurier) {
  cout << "Force: " << aventurier.force << endl;
  cout << "Dex: " << aventurier.dex << endl;
  cout << "Tntel: " << aventurier.intell << endl;
  cout << "Charism: " << aventurier.charism << endl;
}

int get_party_initiative(vector<Aventurier> aventuriers) {
  int initiative = 0;
  for(const Aventurier aventurier : aventuriers) {
    initiative += aventurier.dex + aventurier.intell;
  }
  return initiative / aventuriers.size();
};
int main() {
  Arme dague{ "Dague", 7, 2.0F };
  Arme hache{ "Hache", 19, 10.9F };

  Aventurier Leroy{ 50, 1, 0, 10, hache };
  Aventurier Joker{ 25, 24, 25, 25, dague };

  vector<Aventurier> aventuriers{ Leroy, Joker };

  cout << "Initiative groupe: " << get_party_initiative(aventuriers) << endl;

  return 0;
}
