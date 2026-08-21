#include "Backend.h"
#include <iostream>
#include <QString>
#include <QDebug>

using namespace std;

vector<House> cityy;

Adresse::Adresse(string city, string street, string number)
    : city(move(city)), street(move(street)), number(move(number)) {}

string Adresse::getCity() const { return city; }
string Adresse::getStreet() const { return street; }
string Adresse::getNumber() const { return number; }
void Adresse::setCity(const string& c) { city = c; }
void Adresse::setStreet(const string& s) { street = s; }
void Adresse::setNumber(const string& n) { number = n; }


Human::Human() : age(0), sex(Gender::NONE) {}

Human::Human(string name, int age, Adresse adres, Gender sex)
    : name(move(name)), age(age), sex(sex) {
    adress.push_back(adres);
}

string Human::getName() const { return name; }
int Human::getAge() const { return age; }
Gender Human::getGender() const { return sex; }
Adresse Human::getAdress(int i) const { return adress[i]; }
vector<Adresse>& Human::getAdresse() { return adress; }
const vector<Adresse>& Human::getAdresse() const { return adress; }
void Human::setName(const string& n) { name = n; }
void Human::setAge(int a) { age = a; }
void Human::setGender(Gender g) { sex = g; }
void Human::setAdresse(const vector<Adresse>& a) { adress = a; }


House::House(Human h, Adresse a, int g, int w, int p)
    : adress(a), groesse(g), wert(w), preisquad(p) {
    humann.push_back(h);
    HouseId = a.getCity() + a.getStreet() + a.getNumber() + to_string(g) + to_string(w);
}

string House::getHouseId() const { return HouseId; }
Human House::getHuman(int i) const { return humann[i]; }
vector<Human> House::getHuman() const { return humann; }
Adresse House::getAdress() const { return adress; }
int House::getAnzahlPers() const { return humann.size(); }
int House::getGroesse() const { return groesse; }
int House::getWert() const { return wert; }
int House::getPreisquad() const { return preisquad; }

void House::setHuman(const vector<Human>& h) { humann = h; }
void House::setAdress(const Adresse& a) { adress = a; }
void House::setGroesse(int g) { groesse = g; }
void House::setWert(int w) { wert = w; }
void House::setPreisquad(int p) { preisquad = p; }


Gender chooseg(const string& choose) {
    if (QString::fromStdString(choose).compare("gay", Qt::CaseInsensitive) == 0) return Gender::GAY;
    if (QString::fromStdString(choose).compare("bi", Qt::CaseInsensitive) == 0) return Gender::BI;
    if (QString::fromStdString(choose).compare("trans", Qt::CaseInsensitive) == 0) return Gender::TRANS;
    if (QString::fromStdString(choose).compare("nonbinary", Qt::CaseInsensitive) == 0) return Gender::NONBINARY;
    if (QString::fromStdString(choose).compare("straight", Qt::CaseInsensitive) == 0) return Gender::STRAIGHT;
    return Gender::NONE;
}

string genderToString(Gender g) {
    switch (g) {
    case Gender::GAY: return "gay";
    case Gender::BI: return "bi";
    case Gender::TRANS: return "trans";
    case Gender::NONBINARY: return "nonbinary";
    case Gender::STRAIGHT: return "straight";
    default: return "none";
    }
}

void writefile(const House& house, ofstream& file) {
    // Left unimplemented as in your original file
}

vector<string> searchByName(const string& input) {
    vector<string> output;
    for (const auto& temp : cityy) {
        for (const auto& humantemp : temp.getHuman()) {
            if (humantemp.getName() == input) {
                output.push_back(temp.getHouseId());
                break;
            }
        }
    }
    return output;
}

vector<string> searchByCity(const string& input) {
    vector<string> output;
    for (const auto& temp : cityy) {
        if (temp.getAdress().getCity() == input) {
            output.push_back(temp.getHouseId());
        }
    }
    return output;
}

vector<string> searchByStreet(const string& input) {
    vector<string> output;
    for (const auto& temp : cityy) {
        if (temp.getAdress().getStreet() == input) {
            output.push_back(temp.getHouseId());
        }
    }
    return output;
}

vector<string> searchByGender(const string& input) {
    vector<string> output;
    for (const auto& temp : cityy) {
        for (const auto& humantemp : temp.getHuman()) {
            if (humantemp.getGender() == chooseg(input)) {
                output.push_back(temp.getHouseId());
                break;
            }
        }
    }
    return output;
}

vector<string> searchByNumber(const string& input) {
    vector<string> output;
    for (const auto& temp : cityy) {
        if (temp.getAdress().getNumber() == input) {
            output.push_back(temp.getHouseId());
        }
    }
    return output;
}

bool searchalreadyinPerson(const string& query) {
    for (const auto& temp : cityy) {
        for (const auto& humantemp : temp.getHuman()) {
            if (humantemp.getName() == query) {
                return true;
            }
        }
    }
    return false;
}

bool searchalreadyinAdress(const array<string, 3>& query) {
    for (const auto& temp : cityy) {
        if (temp.getAdress().getCity() == query[0] &&
            temp.getAdress().getStreet() == query[1] &&
            temp.getAdress().getNumber() == query[2]) {
            return true;
        }
    }
    return false;
}

bool searchPersonalreadyAdress(const array<string, 3>& query, const string& person) {
    for (const auto& temp : cityy) {
        if (temp.getAdress().getCity() == query[0] &&
            temp.getAdress().getStreet() == query[1] &&
            temp.getAdress().getNumber() == query[2]) {
            for (const auto& humantemp : temp.getHuman()) {
                if (humantemp.getName() == person) {
                    return true;
                }
            }
        }
    }
    return false;
}

void addEntry(string name, string city, string street, string number, string genderStr, int age, int price, int size) {
    Gender gender = chooseg(genderStr);
    Adresse newAdresse(city, street, number);
    Human newHuman(name, age, newAdresse, gender);
    bool houseFound = false;

    for (auto& house : cityy) {
        if (house.getAdress().getCity() == city &&
            house.getAdress().getStreet() == street &&
            house.getAdress().getNumber() == number) {

            vector<Human> currentHumans = house.getHuman();
            currentHumans.push_back(newHuman);
            house.setHuman(currentHumans);
            houseFound = true;
            break;
        }
    }

    if (!houseFound) {
        House newHouse(newHuman, newAdresse, size, price * size, price);
        cityy.push_back(newHouse);
    }
}

void setup() {
    addEntry("Lukas", "Berlin", "Hauptstrasse", "10", "straight", 25, 300, 50);
    addEntry("Anna", "München", "Bahnhofstraße", "5", "straight", 30, 450, 80);
    addEntry("Tom", "Hamburg", "Reeperbahn", "1", "bi", 22, 200, 40);
    addEntry("Julia", "Berlin", "Hauptstrasse", "10", "gay", 26, 300, 50);
    addEntry("Max", "Köln", "Domplatz", "3", "trans", 28, 500, 90);
    addEntry("Sophie", "München", "Bahnhofstraße", "5", "nonbinary", 24, 450, 80);
    addEntry("Leon", "Stuttgart", "Königstraße", "12", "straight", 35, 400, 70);
    addEntry("Mia", "Frankfurt", "Zeil", "8", "straight", 29, 600, 100);
    addEntry("Paul", "Hamburg", "Reeperbahn", "1", "gay", 23, 200, 40);
    addEntry("Lina", "Düsseldorf", "Königsallee", "15", "straight", 32, 700, 120);
}