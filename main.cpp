#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>

#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

enum class Target { ONE, MULTIPLE };

enum class State { START, END };
struct Skill {
  string name;
  int every_x_turn;
  float multiplicater_damage;
  Target target;
};

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
  string name;
  Skill skill;
  int vie;
};

void presenter(Aventurier aventurier) {
  cout << "Force: " << aventurier.force << endl;
  cout << "Dex: " << aventurier.dex << endl;
  cout << "Tntel: " << aventurier.intell << endl;
  cout << "Charism: " << aventurier.charism << endl;
}


// Je peux faire template <typename... Ts>
// Mais ce n'est pas ce que je veux
// Ici,
// Je vérifie si mon type générique
// est un pack de paramètres std::vector<Aventurier>
template <typename... Ts,
typename = std::enable_if_t<std::conjunction_v<std::is_same<Ts, std::vector<Aventurier>>...>>>
void set_all_parties_pv(Ts&... aventuriers) {
  // Fold expressions ->
  // permet de gérer les parameter packs.

  // ... signifie qu'on applique à tous les éléments
  // [&aventurier = aventuriers]
  // -> spécifie une fonction générique qu'on va appliquer à chaque argument
  (..., [&aventurier = aventuriers] {
    for(Aventurier& elem : aventurier) {
      elem.vie += 5 * elem.force + 2 * elem.intell;
    }
  }());
};

int team_life(vector<Aventurier>& team) {
  int total_life = 0;

  for(const Aventurier& character : team) {
    total_life += character.vie;
  }
  return total_life;
}

int character_damage_normalize(Aventurier character) {
  return character.arme.degat + character.force / 2 + (character.dex * 1.5) +
  character.intell / (character.arme.degat + character.force);
}

// TODO (mais flemme)
// replace Aventurier& adverse by vector<Aventurier> &adverse
// to hit either one or many enemies
void player_attack(Aventurier character, Aventurier& adverse, float mutiplier = 1.0F) {
  float damage = (character_damage_normalize(character) * mutiplier);
  adverse.vie -= damage;
  cout << character.name << " inflige " << damage << " pts de dégats "
       << "à " << adverse.name << " !" << endl;
  if(adverse.vie <= 0) {
    adverse.vie = 0;
    cout << character.name << " a tué " << adverse.name << endl;
  }
};

void skill_attack(Aventurier character, Aventurier& bad_guys) {
  cout << character.name << " lance son attaque spécial, "
       << character.skill.name << " !! " << endl;

  // if  -> character.skill.target == Target::ONE
  player_attack(character, bad_guys, character.skill.multiplicater_damage);
  // else -> character.skill.target == Target::MULTIPLE
  // meh don't wanna
}

void team_attack(vector<Aventurier>& current_team,
vector<Aventurier>& adverse_team,
State& state,
int turn) {
  for(const Aventurier& c : current_team) {
    if(team_life(adverse_team) <= 0) {
      state = State::END;
      break;
    }
    if(c.vie > 0) {
      cout << "Tour [" << turn << "]: ";
      for(Aventurier& adverse : adverse_team) {
        if(adverse.vie > 0) {
          if(turn % c.skill.every_x_turn == 0) {
            skill_attack(c, adverse);
            break;
          }
          player_attack(c, adverse);
          break;
        }
      }
    };
  };
};

void fight(vector<Aventurier>& good_guys, vector<Aventurier>& bad_guys) {
  State state = State::START;

  int turn = 1;
  set_all_parties_pv(good_guys, bad_guys);

  while(true) {
    team_attack(good_guys, bad_guys, state, turn);
    if(state == State::END) {
      cout << "Good guys win";
      break;
    }
    team_attack(bad_guys, good_guys, state, turn);
    if(state == State::END) {
      cout << "Bad guys win";
      break;
    }
    ++turn;
  }
};

int main() {
  Arme dague{ "Dague", 7, 2.0F };
  Arme hache{ "Hache", 19, 10.9F };
  Arme baton{ "Baton", 10, 1.0F };

  Skill thunder{ "Thunder", 3, 1.2F, Target::MULTIPLE };

  Aventurier Leroy{ 50, 1, 0, 10, hache, "Leroy" };
  Aventurier Joker{ 25, 24, 15, 25, dague, "Joker" };
  Aventurier Zhoe{ 10, 14, 40, 17, baton, "Zhoe", thunder };

  Aventurier gobelin{ 5, 8, 5, 3, dague, "Gobelin" };

  vector<Aventurier> aventuriers = { Leroy, Joker, Zhoe };
  vector<Aventurier> gobelins = { gobelin, gobelin, gobelin, gobelin, gobelin,
    gobelin, gobelin, gobelin, gobelin };

  fight(aventuriers, gobelins);

  return 0;
}
