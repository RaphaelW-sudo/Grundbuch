
#include "mainwindow.h"
#include "Backend.h"
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

using namespace std;

vector<string> mergeCommonUnsortedStrings(const vector<vector<string>>& vectors) {
    if (vectors.empty()) return {};

    unordered_set<string> common(vectors[0].begin(), vectors[0].end());

    for (size_t i = 1; i < vectors.size(); ++i) {
        unordered_set<string> current(vectors[i].begin(), vectors[i].end());
        unordered_set<string> nextCommon;

        for (const auto& str : common) {
            if (current.count(str)) {
                nextCommon.insert(str);
            }
        }
        common = std::move(nextCommon);
    }

    return vector<string>(common.begin(), common.end());
}

void registerPerson(string stadt, string strasse, string hausnummer, int preis, int groesse, int PersonNr, QWidget* parent = nullptr) {
    QDialog dialog(parent);
    dialog.setWindowTitle("Bestätigung");
    dialog.setFixedSize(500, 500);

    QGridLayout *dialogLayout = new QGridLayout(&dialog);
    string titel = "Bitte Daten zu Person Nr." + to_string(PersonNr) + " angeben";
    dialogLayout->addWidget(new QLabel(QString::fromStdString(titel)), 0, 0, Qt::AlignCenter);

    QLineEdit *ageinput = new QLineEdit();
    ageinput->setPlaceholderText("Alter");
    ageinput->setFixedSize(300, 50);
    dialogLayout->addWidget(ageinput, 1, 0, Qt::AlignCenter);

    QLineEdit *genderinput = new QLineEdit();
    genderinput->setPlaceholderText("Sexuelle Ausrichtung");
    genderinput->setFixedSize(300, 50);
    dialogLayout->addWidget(genderinput, 2, 0, Qt::AlignCenter);

    QLineEdit *nameinput = new QLineEdit();
    nameinput->setPlaceholderText("Name");
    nameinput->setFixedSize(300, 50);
    dialogLayout->addWidget(nameinput, 3, 0, Qt::AlignCenter);

    QPushButton *btnSave = new QPushButton("Ja, Speichern");
    QPushButton *btnCancel = new QPushButton("Abbrechen");

    dialogLayout->addWidget(btnSave, 4, 0, Qt::AlignLeft);
    dialogLayout->addWidget(btnCancel, 4, 0, Qt::AlignRight);

    QObject::connect(btnSave, &QPushButton::clicked, [&dialog, genderinput, ageinput, nameinput]() {
        if (!nameinput->text().trimmed().isEmpty() &&
            !genderinput->text().trimmed().isEmpty() &&
            !ageinput->text().trimmed().isEmpty()) {

            bool okAge;
            int age = ageinput->text().toInt(&okAge);

            if (okAge && chooseg(genderinput->text().toStdString()) != Gender::NONE) {
                dialog.accept();
            }
        }
    });

    QObject::connect(btnCancel, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        addEntry(nameinput->text().toStdString(), stadt, strasse, hausnummer,
                 genderinput->text().toStdString(), ageinput->text().trimmed().toInt(), preis, groesse);
    }
}

int main(int argc, char *argv[])
{
    äsetup();
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Monnema Grundbuch");
    window.resize(1000, 1000);

    QGridLayout *layout = new QGridLayout(&window);

    QStackedWidget *stackedWidget = new QStackedWidget();
    layout->addWidget(stackedWidget,0,0);

    //hier Zeug fuer start
    QWidget *start = new QWidget();
    QGridLayout *gridstart = new QGridLayout(start);

    QLabel *welcome = new QLabel("Willkommen im Monnema Grundbuch!");
    welcome->setStyleSheet("font-size: 36px; font-weight: bold;");
    gridstart->addWidget(welcome,0,0,Qt::AlignCenter|Qt::AlignTop);

    QLabel *wasmachen = new QLabel("Was willsch machen?:");
    wasmachen->setStyleSheet("font-size: 24px;");
    gridstart->addWidget(wasmachen,1,0,Qt::AlignCenter|Qt::AlignTop);

    QShortcut *shortcutEsc = new QShortcut(QKeySequence(Qt::Key_Escape),&window);
    QObject::connect(shortcutEsc, &QShortcut::activated, &window, [&stackedWidget, &window](){
        if(stackedWidget->currentIndex()==0){
            QMessageBox::StandardButton reply = QMessageBox::question(
                &window,
                "Schliessen",
                "Möchtest du dieses Fenster schliessen?",
                QMessageBox::Yes | QMessageBox::No
                );
            if(reply==QMessageBox::Yes){
                &QWidget::close;
                window.close();
            }
        }else{
            stackedWidget->setCurrentIndex(0);
        }
    });

    QPushButton *hinzuf = new QPushButton("Was hinzufuegen");
    hinzuf->setCheckable(true);
    gridstart->addWidget(hinzuf,2,0,Qt::AlignCenter|Qt::AlignTop);
    hinzuf->setStyleSheet(
        "QPushButton{"
        "font-size: 20px; "
        "padding: 40px 200px; "
        "border-radius: 8px;"
        "color: white;"
        "background-color: black;"
        "}"
        "QPushButton:pressed{"
        "background-color:white;"
        "}"
        );
    hinzuf->setFixedWidth(700);

    QPushButton *suchen = new QPushButton("Was suchen");
    suchen->setCheckable(true);
    gridstart->addWidget(suchen,3,0,Qt::AlignCenter|Qt::AlignTop);
    suchen->setStyleSheet(
        "QPushButton{"
        "font-size: 20px; "
        "padding: 40px 200px; "
        "border-radius: 8px;"
        "color: white;"
        "background-color: black;"
        "}"
        "QPushButton:pressed{"
        "background-color:white;"
        "}"
        );
    suchen->setFixedWidth(700);

    QPushButton *show = new QPushButton("Alle Daten anzeigen");
    show->setCheckable(true);
    gridstart->addWidget(show,4,0,Qt::AlignCenter|Qt::AlignTop);
    show->setStyleSheet(
        "QPushButton{"
        "font-size: 20px; "
        "padding: 40px 200px; "
        "border-radius: 8px;"
        "color: white;"
        "background-color: black;"
        "}"
        "QPushButton:pressed{"
        "background-color:white;"
        "}"
        );
    show->setFixedWidth(700);

    QObject::connect(hinzuf,&QPushButton::clicked,[stackedWidget](){
        stackedWidget->setCurrentIndex(1);
    });

    QObject::connect(suchen,&QPushButton::clicked,[stackedWidget](){
        stackedWidget->setCurrentIndex(2);
    });

    QObject::connect(show,&QPushButton::clicked,[stackedWidget](){
        stackedWidget->setCurrentIndex(3);
    });
    stackedWidget->addWidget(start);
    //Ende start
    //----------------------------------------------
    //hier Zeug fuer hinzufscreen
    QWidget *hinzufscreen = new QWidget();

    QGridLayout *gridhinzufscreen = new QGridLayout(hinzufscreen);

    QLabel *Titelh = new QLabel("Daten Hinzufuegen");
    Titelh->setStyleSheet("font-size: 24px;");
    gridhinzufscreen->addWidget(Titelh,0,0,Qt::AlignCenter);

    QPushButton *auslesen = new QPushButton("eingeben");
    auslesen->setStyleSheet("padding: 30px 200px");
    gridhinzufscreen->addWidget(auslesen,7,0,Qt::AlignCenter);

    vector<QLineEdit*> ersterinput;
    vector<string*> ersterinputstring;

    for(int i=0;i<6;i++){
        QLineEdit *Line = new QLineEdit();
        Line->setStyleSheet("font-size: 22px; padding: 8px 12px;");
        Line->setMinimumWidth(450);
        gridhinzufscreen->addWidget(Line,i+1,0,Qt::AlignCenter);
        ersterinput.push_back(Line);
    }

    ersterinput[0]->setPlaceholderText("In welchem Stadtteil?");
    ersterinput[1]->setPlaceholderText("In welcher Strasse?");
    ersterinput[2]->setPlaceholderText("Welche Hausnummer?");
    ersterinput[3]->setPlaceholderText("Wie gross(in qm)?");
    ersterinput[4]->setPlaceholderText("Welcher Preis");
    ersterinput[5]->setPlaceholderText("Wie viele Personen?");

    QObject::connect(auslesen,&QPushButton::clicked,[&window,auslesen,ersterinput,ersterinputstring](){
        bool hatLeeresFeld = false;

        for (QLineEdit *line : ersterinput) {
            if (line->text().trimmed().isEmpty()) {
                hatLeeresFeld = true;
                break;
            }
        }

        if (hatLeeresFeld) {
            qDebug() << "Fehler: Bitte fülle erst alle Felder aus!";
            return;
        }
        bool okQm, okPreis, okPersonen;

        int qm       = ersterinput[3]->text().toInt(&okQm);
        int preis    = ersterinput[4]->text().toInt(&okPreis);
        int personen = ersterinput[5]->text().toInt(&okPersonen);

        if (!okQm || !okPreis || !okPersonen || qm<0 || preis<0 ||personen<0) {
            qDebug() << "Fehler: Preis, Quadratmeter und Personen müssen gültige Zahlen sein!";
            return;
        }

        string stadt   = ersterinput[0]->text().toStdString();
        string strasse = ersterinput[1]->text().toStdString();
        string hausnr  = ersterinput[2]->text().toStdString();
        for(int i = 0;i<personen;++i){
            registerPerson(stadt,strasse,hausnr,preis,qm,i+1,&window);
        }
    });

    stackedWidget->addWidget(hinzufscreen);
    //Ende hinzufscreen
    //----------------------------------------------
    //hier Zeug fuer suchscreen
    QWidget *suchscreen = new QWidget();

    QGridLayout *gridsuchscreen = new QGridLayout(suchscreen);

    vector<QLineEdit*> erstersuchinput;

    QLabel *titelsuch = new QLabel("Suchen nach Stadt, Strasse oder Name");
    titelsuch->setStyleSheet("font-size:24px");
    gridsuchscreen->addWidget(titelsuch,0,0,Qt::AlignCenter);

    for(int i=0;i<5;i++){
        QLineEdit *Line = new QLineEdit();
        Line->setStyleSheet("font-size: 22px; padding: 8px 12px;");
        Line->setMinimumWidth(450);
        gridsuchscreen->addWidget(Line,i+2,0,Qt::AlignCenter);
        erstersuchinput.push_back(Line);
    }

    erstersuchinput[0]->setPlaceholderText("Nach Stadt suchen:");
    erstersuchinput[1]->setPlaceholderText("Nach Strasse suchen:");
    erstersuchinput[2]->setPlaceholderText("Nach Hausnummer suchen:");
    erstersuchinput[3]->setPlaceholderText("Nach Name suchen:");
    erstersuchinput[4]->setPlaceholderText("Nach sex. Ausrichtung suchen:");

    QPushButton *suchenauslesen = new QPushButton("eingeben");
    suchenauslesen->setStyleSheet("padding: 30px 200px");
    gridsuchscreen->addWidget(suchenauslesen,7,0,Qt::AlignCenter);

    QObject::connect(suchenauslesen,&QPushButton::clicked,[erstersuchinput](){
        //Felder pruefen
        bool voll=false;
        for(QLineEdit *Line: erstersuchinput) {
            if(!Line->text().trimmed().isEmpty())voll=true;
        }
        if(!voll)return;

        QString genderText = erstersuchinput[4]->text().trimmed();
        if (!genderText.isEmpty() && chooseg(genderText.toStdString()) == Gender::NONE) {
            return;
        }
        //---------------------------------------
        //jetzt das suchen kolleg
        vector<vector<string>> uebergeben;

        for(QLineEdit *Line: erstersuchinput){
            if(!Line->text().isEmpty()){
                if (!erstersuchinput[0]->text().isEmpty())
                    uebergeben.push_back(searchByCity(erstersuchinput[0]->text().toStdString()));
                if (!erstersuchinput[1]->text().isEmpty())
                    uebergeben.push_back(searchByStreet(erstersuchinput[1]->text().toStdString()));
                if (!erstersuchinput[2]->text().isEmpty())
                    uebergeben.push_back(searchByNumber(erstersuchinput[2]->text().toStdString()));
                if (!erstersuchinput[3]->text().isEmpty())
                    uebergeben.push_back(searchByName(erstersuchinput[3]->text().toStdString()));
                if (!erstersuchinput[4]->text().isEmpty())
                    uebergeben.push_back(searchByGender(erstersuchinput[4]->text().toStdString()));
            }
        }

        vector<string> suchergebnisse=mergeCommonUnsortedStrings(uebergeben);

        /*for (const auto& temp : suchergebnisse) { // Debug
            qDebug() << QString::fromStdString(temp);
        }*/
        vector<House> showablehouses;
        long long showlaenge=0;
        for(string Id:suchergebnisse){
            for(House temp: cityy){
                if(temp.getHouseId()==Id){
                    showablehouses.push_back(temp);
                    showlaenge+=temp.getHuman().size();
                }
            }
        }
        
    QWidget *showzeigscreen[ceil(showlaenge/15)];
    vector<vector<House>> housesproseite;
    for(int i=0;i<ceil(showlaenge/15)){
    if(showablehouses.empty())break;
    for(int j=0;j<15;j++){
    vector<House> seite;
    if(showablehouses.empty())break;
    short available=15;
    seite.push_back(showablehouses[showablehouses.size()-1]);
    available-=showablehouses[showablehouses.size()-1].getHuman().size();
    if(available-showablehouses[showablehouses.size()-2]<0)break;
    showablehouses.pop_back();
   if(!seite.empty())housesproseite.push_back(seite);
    }
    }
    QGridLayout *gridshowzeigscreen = new QGridLayout(showzeigscreen);
    vector<QLabel*> showlabels;
    for(auto&&[i,h]: std::views::enumerate(showablehouses)){
    showlabels.pushback(h.getLabel());
    gridshowzeigscreen->addWidget(showlabels[showlabels.size()-1],static_cast<int>(i),0);
    }
    });

    stackedWidget->addWidget(suchscreen);
    //Ende suchscreen
    //--------------------------------------------
    //hier Zeug fuer showzeigscreen
    

    //Ende Showzeigscreen
    //--------------------------------------------
    //hier Zeug fuer showscreen
    QWidget *showscreen = new QWidget();
    QGridLayout *gridshowscreen = new QGridLayout(showscreen);

    stackedWidget->addWidget(showscreen);

    //Ende Showscreen

    window.show();

    return app.exec();
}
