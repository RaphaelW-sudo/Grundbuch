#pragma once

#ifndef BACKEND_H
#define BACKEND_H
#endif

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

    void setName(const std::string& n);
    void setAge(int a);
    void setGender(Gender g);
    void setAdresse(const std::vector<Adresse>& a);
};

class House {
private:
    std::string Houseid;
    std::vector<Human> humann;
    Adresse adress;
    int groesse = 0;
    int wert = 0;
    int preisquad = 0;

public:
    House(Human h, Adresse a, int g, int w, int p);

    std::string getHouseid() const;
    Human getHuman(int i) const;
    std::vector<Human>& getHuman();
    const std::vector<Human>& getHuman() const;
    Adresse getAdress() const;
    int getAnzahlPers() const;
    int getGroesse() const;
    int getWert() const;
    int getPreisquad() const;

    void setHuman(const std::vector<Human>& h);
    void setAdress(const Adresse& a);
    void setGroesse(int g);
    void setWert(int w);
    void setPreisquad(int p);
};

// --- Globale Variable ---
extern std::vector<House> cityy;

// --- Hilfsfunktionen ---
Gender chooseg(const std::string& choose);
std::string genderToString(Gender g);
void writefile(const House& house, std::ofstream& file);

// --- Such- und Logikfunktionen ---
std::vector<std::string> searchByName(const std::string& input);
std::vector<std::string> searchByStreet(const std::string& input);
std::vector<std::string> searchByCity(const std::string& input);
std::vector<std::string> searchByGender(const std::string& input);
std::vector<std::string> searchByNumber(const std::string& input);

bool searchalreadyinPerson(const std::string& query);
bool searchalreadyinAdress(const std::array<std::string, 3>& query);
bool searchPersonalreadyAdress(const std::array<std::string, 3>& query, const std::string& person);

void addEntry(std::string name, std::string city, std::string street, std::string number,
              std::string genderStr, int age, int price, int size);
void setup();