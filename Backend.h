#pragma once

#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <QString>
#include <QDebug>

// Enum für Geschlechtsidentität / Orientierung
enum class Gender {
    STRAIGHT,
    GAY,
    BI,
    TRANS,
    NONBINARY,
    NONE
};

// --- Klassen-Deklarationen ---

class Adresse {
private:
    std::string city;
    std::string street;
    std::string number;

public:
    Adresse(std::string city, std::string street, std::string number);

    std::string getCity() const;
    std::string getStreet() const;
    std::string getNumber() const;

    void setCity(const std::string& c);
    void setStreet(const std::string& s);
    void setNumber(const std::string& n);
};

class Human {
private:
    std::string name;
    int age = 0;
    Gender sex = Gender::NONE;
    std::vector<Adresse> adress;

public:
    Human();
    Human(std::string name, int age, Adresse adres, Gender sex);

    std::string getName() const;
    int getAge() const;
    Gender getGender() const;
    Adresse getAdress(int i) const;
    std::vector<Adresse>& getAdresse();
    const std::vector<Adresse>& getAdresse() const;
};

class House {
private:
    std::vector<Human> humann;
    Adresse adress;
    int groesse = 0;
    int wert = 0;
    int preisquad = 0;

public:
    House(Human h, Adresse a, int g, int w, int p);

    Human getHuman(int i) const;
    std::vector<Human>& getHuman();
    const std::vector<Human>& getHuman() const;
    Adresse getAdress() const;
    int getAnzahlPers() const;
    int getGroesse() const;
    int getWert() const;
    int getPreisquad() const;
};

// --- Globale Variable ---
extern std::vector<House> cityy;

// --- Hilfsfunktionen ---
Gender chooseg(const std::string& choose);
std::string genderToString(Gender g);
void writefile(const House& house, std::ofstream& file);

// --- Such- und Logikfunktionen ---
void searchByName(const std::string& input, const std::vector<House>& cityy);
void searchByStreet(const std::string& input, const std::vector<House>& cityy);

bool searchalreadyinPerson(const std::string& query);
bool searchalreadyinAdress(const std::array<std::string, 3>& query);
bool searchPersonalreadyAdress(const std::array<std::string, 3>& query, const std::string& person);

void addEntry(std::string name, std::string city, std::string street, std::string number,
              std::string genderStr, int age, int price, int size);
void setup();