/**
 * @file Lab2.cpp
 * @author your name (you@domain.com)
 * @brief Bridge and Torch
 * @version 0.1
 * @date 2020-04-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>

using namespace std;
enum Position { North, South };
int timeAccumulate = 0;
class Character {
public:
  char firstChar;
  string name;
  Position position;
  int timeConsume;
  Character(char firstChar, string name, int timeConsume)
      : firstChar(firstChar), name(name), position(South),
        timeConsume(timeConsume) {}
  void toggle() {
    if (this->position == North)
      this->position = South;
    else
      this->position = North;
  }
};
Character Adam('A', "Adam", 1);
Character Bob('B', "Bob", 2);
Character Chair('C', "Chair", 5);
Character Dave('D', "Dave", 10);
Character *characterList[4] = {&Adam, &Bob, &Chair, &Dave};
void outputCurrentState() {
  string north[4], south[4];
  cout << "North:";
  for (int i = 0; i < 4; i++) {
    if (characterList[i]->position == North)
      cout << " " << characterList[i]->name;
  }
  cout << "\n"
       << "South:  ";
  for (int i = 0; i < 4; i++) {
    if (characterList[i]->position == South)
      cout << " " << characterList[i]->name;
  }
  cout << endl;
}
void interact() {
  outputCurrentState();
  char char1, char2;

  cout << "Input first guy, A for Adam, B for Bob, and so on:\n";
  cin >> char1;
  cout << "Input second guy A for Adam, B for Bob, ... If nobody, input N:"
       << endl;
  cin >> char2;
  Character *character1;
  Character *character2;
  switch (char1) {
  case 'A':
    character1 = &Adam;
    break;
  case 'B':
    character1 = &Bob;
    break;
  case 'C':
    character1 = &Chair;
    break;
  case 'D':
    character1 = &Dave;
    break;
  }
  switch (char2) {
  case 'A':
    character2 = &Adam;
    break;
  case 'B':
    character2 = &Bob;
    break;
  case 'C':
    character2 = &Chair;
    break;
  case 'D':
    character2 = &Dave;
    break;
  }
  if (char2 == 'N') {
    character1->toggle();
    timeAccumulate += character1->timeConsume;
    cout << "\n"
         << character1->name << " is crossing the bridge with torch!\n\n";
    cout << character1->timeConsume << "mins passed...\n\n" << endl;

  } else {
    character1->toggle();
    character2->toggle();
    int timeMax = max(character1->timeConsume, character2->timeConsume);
    timeAccumulate += timeMax;
    cout << "\n"
         << character1->name << " and " << character2->name
         << " is crossing the bridge with torch!\n\n";
    cout << timeMax << "mins passed...\n\n" << endl;
  }
}

void outputIntroduction() {
  cout << "Adam, Bob, Clair and Dave want to cross the bridge.\n"
       << "The bridge is from south to north, and they are on south side at "
          "first\n"
       << "The bridge can take no more than two people at the same time.\n"
       << "Beside, it's very dark so the man who is"
       << "crossing the bridge has to use the only torch.\n"
       << "Characters Introduction:\n"
       << "     <Adam> and <Bob> each takes *1* and *2* mins to cross the "
          "bridge\n"
       << "     <Clair> needs *5* mins to cross the bridge\n"
       << "     <Dave> needs *10* mins to make it\n"
       << "You are a clever passer-by and come up with an idea that help them "
          "decide how to cross the bridge...\n"
       << "To control who should cross the bridge, input the first letter of "
          "only one person at a time.\n"
       << "if you input more than one, characters after the first one will be "
          "ignored.\n"
       << "\n\n"
       << "           !!!Get Start!!!\n\n"
       << endl;
}

void outputResult() {
  cout << "Congratulations!!!!!  They finally made it to the other side!\n"
       << "It takes " << timeAccumulate << " mins in all." << endl;
}
int main() {
  outputIntroduction();
  while (!(Adam.position == North && Bob.position == North &&
           Chair.position == North && Dave.position == North)) {
    interact();
  }
  outputResult();
  return 0;
}
