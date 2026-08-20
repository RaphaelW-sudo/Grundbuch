
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <QString>
#include <QApplication>
#include <QWidget>
#include <vector>
#include <QMessageBox>
#include <string>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QStackedWidget>
#include <QLabel>
#include <QShortcut>
#include <QKeySequence>
#include <array>

using namespace std;

enum class Gender {
    STRAIGHT,
    GAY,
    BI,
    TRANS,
    NONBINARY,
    NONE
};

class Adresse {
private:
    string city;
    string street;
    string number;

public:
    Adresse(string city, string street, string number)
        : city(move(city)), street(move(street)), number(move(number)) {}

    string getCity() const { return city; }
    string getStreet() const { return street; }
    string getNumber() const { return number; }

    void setCity(const string& c) { city = c; }
    void setStreet(const string& s) { street = s; }
    void setNumber(const string& n) { number = n; }
};

class Human {
private:
    string name;
    int age;
    Gender sex;
    vector<Adresse> adress;

public:
    Human(string name, int age, Adresse adres, Gender sex)
        : name(move(name)), age(age), sex(sex){
        adress.push_back(adres);
    }
    Human(){}
    string getName() const { return name; }
    int getAge() const { return age; }
    Gender getGender() const { return sex; }
    Adresse getAdress(int i) const { return adress[i]; }
    vector<Adresse>& getAdresse() { return adress; }
};

class House {
private:
    vector<Human> humann;
    Adresse adress;
    int groesse;
    int wert;
    int preisquad;

public:
    House(Human h, Adresse a, int g, int w, int p)
        : groesse(g), wert(w), preisquad(p),adress(a) {
        humann.push_back(h);
    }

    Human getHuman(int i) const { return humann[i]; }
    vector<Human>& getHuman() { return humann; }
    Adresse getAdress()const {return adress;}
    int getAnzahlPers() const{return humann.size();}
    int getGroesse() const { return groesse; }
    int getWert() const { return wert; }
    int getPreisquad() const { return preisquad; }
};

vector<House> cityy;

// Hilfsfunktionen
Gender chooseg(const string& choose) {
    if (QString::fromStdString(choose).compare(QString::fromStdString("gay"), Qt::CaseInsensitive) == 0) return Gender::GAY;
    if (QString::fromStdString(choose).compare(QString::fromStdString("bi"), Qt::CaseInsensitive) == 0) return Gender::BI;
    if (QString::fromStdString(choose).compare(QString::fromStdString("trans"), Qt::CaseInsensitive) == 0) return Gender::TRANS;
    if (QString::fromStdString(choose).compare(QString::fromStdString("nonbinary"), Qt::CaseInsensitive) == 0) return Gender::NONBINARY;
    if (QString::fromStdString(choose).compare(QString::fromStdString("straight"), Qt::CaseInsensitive) == 0) return Gender::STRAIGHT;
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
/*    if (!file.is_open()) return;

    file << house.getHuman().getName() << "\n,\n"
         << house.getHuman().getAge() << "\n,\n"
         << house.getHuman().getAdress().getCity() << "\n,\n"
         << house.getHuman().getAdress().getStreet() << "\n,\n"
         << house.getHuman().getAdress().getNumber() << "\n,\n"
         << genderToString(house.getHuman().getGender()) << "\n.\n";
*/
}

void searchByName(const string& input, const vector<House>& cityy) {
    int foundIndex = -1;
    for (size_t i = 0; i < cityy.size(); ++i) {
        for(int j = 0; j<cityy[i].getAnzahlPers();++j){
            if (cityy[i].getHuman(j).getName() == input) {
                foundIndex = static_cast<int>(i);
                break;
            }
        }
    }
}

void searchByStreet(const string& input, const vector<House>& cityy) {
    vector<House> containing;
    for (const auto& house : cityy) {
        if (house.getHuman(1).getAdress(1).getStreet() == input) {
            containing.push_back(house);
        }
    }

    if (containing.empty()) {
        cout << "Gibts net\n";
        return;
    }

    if (containing.size() == 1) cout << "Do wuhnt der ";
    else cout << "Do wuhne die folgende Leit: ";

    for (const auto& house : containing) {
        cout << house.getHuman(1).getName() << " ";
    }
    cout << "\nWas jetzt?\nZeig die Hausnummer von denen (1)\nexit (2)\n";

    string opt;
    cin >> opt;
    if (opt == "1") {
        for (const auto& house : containing) {
            cout << house.getHuman(1).getAdress(1).getNumber() << " ";
        }
        cout << "\n";
    }
}

bool searchalreadyinPerson(const string& query) {
    for (auto& house : cityy) {
        for (auto& human : house.getHuman()) {
            if (human.getName() == query) return true;
        }
    }
    return false;
}

bool searchalreadyinAdress(const array<string, 3>& query) {
    for (const auto& house : cityy) {
        if (house.getAdress().getCity() == query[0] &&
            house.getAdress().getStreet() == query[1] &&
            house.getAdress().getNumber() == query[2]) {
            return true;
        }
    }
    return false;
}

bool searchPersonalreadyAdress(const array<string, 3>& query, const string& person) {
    for (auto& house : cityy) {
        for (auto& human : house.getHuman()) {
            if (human.getName() == person) {
                for (const auto& addr : human.getAdresse()) {
                    if (addr.getCity() == query[0] &&
                        addr.getStreet() == query[1] &&
                        addr.getNumber() == query[2]) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void addEntry(string name, string city, string street, string number, string genderStr, int age, int price, int size) {
    if (searchalreadyinPerson(name)) {
        if (searchPersonalreadyAdress({city, street, number}, name)) {
            qDebug() << "Already in System";
        } else {
            for (auto& house : cityy) {
                for (auto& human : house.getHuman()) {
                    if (human.getName() == name) {
                        human.getAdresse().push_back(Adresse(city, street, number));
                        qDebug() << "Person gefunden, neue Adresse hinzugefügt";
                    }
                }
            }
        }
    } else if (searchalreadyinAdress({city, street, number})) {
        Adresse temp(city, street, number);
        for (auto& house : cityy) {
            if (house.getAdress().getCity() == city &&
                house.getAdress().getStreet() == street &&
                house.getAdress().getNumber() == number) {

                house.getHuman().push_back(Human(name, age, temp, chooseg(genderStr)));
                qDebug() << "Person zu existierendem Haus hinzugefügt";
                break;
            }
        }
    } else {
        int preisquad = (price > 0) ? size / price : 0;
        cityy.push_back(House(Human(name, age, Adresse(city, street, number), chooseg(genderStr)),
                              Adresse(city, street, number), price, size, preisquad));
        qDebug() << "Neues Haus geadded";
    }
}

void setup() {
    ofstream grundbuchFile("Grundbuch.txt", ios::app);
}