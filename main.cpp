#include <iostream>
#include <fstream>
#include <string.h>
#include "sneaker.h"
#include <stdio.h>
#include <vector>

using namespace std;


int main()
{



    fstream sneakersammlungXML; // XML wird eingelesen

    sneakersammlungXML.open("sneakersammlung.xml"); //Datei wird geöffnet

    if(!sneakersammlungXML){
        cout << "XML - Datei kann nicht gelesen werden." << endl;
    }


    char zeichen_XML; // geht im Folgenden jedes Zeichen in der XML Datei durch
    enum zustand_XML {anfang, oeffne_id, erwarte_id, verarbeite_id, erwarte_marke, verarbeite_marke, erwarte_groesse, verarbeite_groesse, erwarte_farbe, verarbeite_farbe, erwarte_name, verarbeite_name, oeffne_preis, erwarte_preis, verarbeite_preis, oeffne_datum, erwarte_datum, verarbeite_datum };
    enum zustand_XML zustand_XML= anfang;


    sneaker sn; //erstelle Sneaker-Objekt
    string str = "";
    vector<sneaker> liste; //Liste mit den Sneaker-Objekten

     while(sneakersammlungXML.get(zeichen_XML)) { // solange eof (end of file) nicht erreicht, geht jedes Zeichen durch


         switch (zeichen_XML) {

             case ':':
                 zustand_XML = oeffne_id;

                 break;

             case '"':
                 if(zustand_XML == oeffne_id){
                     zustand_XML = erwarte_id;
                     str = ""; //Wert wird zurückgesetzt
                 }else if (zustand_XML == erwarte_id){
                     zustand_XML = verarbeite_id;
                     sn.id = str; // Kopiert string (ID) in sneaker_id
                 }else if (zustand_XML== verarbeite_id){
                     zustand_XML = erwarte_marke;
                     str = "";
                 }else if(zustand_XML==erwarte_marke){
                     zustand_XML = verarbeite_marke;
                     sn.marke = str; // Kopiert string marke in sneaker_marke
                 }else if (zustand_XML == verarbeite_marke){
                     zustand_XML = erwarte_farbe;
                     str = "";
                 }else if(zustand_XML == erwarte_farbe){
                     zustand_XML = verarbeite_farbe;
                     sn.farbe = str; // Kopiert string farbe in sneaker_farbe
                 }else if(zustand_XML== verarbeite_farbe){
                     zustand_XML = erwarte_groesse;
                     str = "";
                 }else if (zustand_XML == erwarte_groesse){
                     zustand_XML = verarbeite_groesse;
                     sn.groesse = str; // Kopiert string groesse in sneaker_groesse
                 }
                 break;
             case '>':

                 if(zustand_XML==verarbeite_groesse){
                     zustand_XML=erwarte_name;
                     str = "";
                 }else if(zustand_XML==verarbeite_name){
                     zustand_XML=oeffne_preis;
                 }else if(zustand_XML==oeffne_preis){
                     zustand_XML=erwarte_preis;
                     str = "";
                 }else if(zustand_XML==verarbeite_preis){
                     zustand_XML=oeffne_datum;
                 }else if(zustand_XML==oeffne_datum){
                     zustand_XML=erwarte_datum;
                     str = "";
                 }
                 break;

             case'<':
                 if (zustand_XML==erwarte_name){
                     zustand_XML=verarbeite_name;
                     sn.name = str;
                 }else if(zustand_XML==erwarte_preis){
                     zustand_XML=verarbeite_preis;
                     sn.preis = str;
                 }else if(zustand_XML==erwarte_datum){
                     zustand_XML=verarbeite_datum;
                     sn.datum = str;
                     liste.push_back(sn); //Fügt Sneaker-Objekt zur Sneakerliste hinzu
                 }
                 break;

             default:
                 break;

             }//switch

         if(zustand_XML == erwarte_id){
             if(zeichen_XML ==  '\"'){  // beim Anführungszeichen leer string
             } else{
                 str += zeichen_XML; //fügt alle Zahlen zum string hinzu
             }
         }
         if(zustand_XML == erwarte_marke){
             if(zeichen_XML ==  '\"'){
             } else{
                 str += zeichen_XML;
            }
         }
         if(zustand_XML == erwarte_farbe){
             if(zeichen_XML ==  '\"'){
             } else{
                 str += zeichen_XML;
             }
         }
         if(zustand_XML == erwarte_groesse){
             if(zeichen_XML ==  '\"'){
             } else{
                 str += zeichen_XML;
             }
         }
         if(zustand_XML == erwarte_name){
             if(zeichen_XML ==  '>'){  // beim > zeichen leer string
             } else{
                 str += zeichen_XML;
             }
         }
         if(zustand_XML == erwarte_preis){
             if(zeichen_XML ==  '>'){
             } else{
                 str += zeichen_XML; //fügt alle Zahlen zum string hinzu
             }
         }
         if(zustand_XML == erwarte_datum){
             if(zeichen_XML ==  '>'){
             } else{
                 str += zeichen_XML; //fügt alle Zahlen zum string hinzu
             }
         }

  }  // while




sneakersammlungXML.close();

    fstream datenTXT;
    datenTXT.open("daten.txt");
    int liste_id;
    if(!datenTXT){
        cout << "TXT - Datei kann nicht gelesen werden." << endl;
    }

    char zeichen_TXT;
    string str_TXT = "";


    while(datenTXT.get(zeichen_TXT)) { // s.o.

        switch (zeichen_TXT) {
            case ':':


                for (unsigned i=0; i < liste.size(); i++) { //geht listenlänge durch
                    if(!liste[i].id.compare(str_TXT)){ // vergleicht id mit id vom Sneaker
                        liste_id = i;               // speichert Sneakerposition mit gleicher ID
                    }
                }


                str_TXT = "";
                break;
            case ';': // im Puffer steht Schrank
                liste[liste_id].schrank = str_TXT; //speichert Schrank in Sneaker
                str_TXT = "";
                break;
            case '\n': // im Puffer steht Bewertung
                liste[liste_id].bewertung = str_TXT; // speichert Bewertung in Sneaker
                str_TXT = "";
                break;
            case ' ':
                str_TXT = "";
                break;
            default:
                str_TXT += zeichen_TXT;
                break;
        }

    }
    cout<< "*************************Herzlich Willkommen!***************************" << endl;
    while (true){



       cout << "*************Wollen Sie suchen[s], konvertieren[k] oder schliessen [x]**********"<< endl;

        char aktion;
        cin >> aktion;

        switch (aktion) {
            case'x': { // case schliessen
                return 0;
                break;
            }
            case'k': { // Fuegt alle Daten in eine Neue Datei
                cout << "*********Wie soll die neue Datei heissen? Bitte mit .xml am Schluss*********" << endl
                     << " ";
                string dateiname;
                cin >> dateiname;

                fstream konvertierte_datei(dateiname);
                konvertierte_datei.open(dateiname, ios::in | ios::out | ios::trunc);

                konvertierte_datei << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
                konvertierte_datei << "<!DOCTYPE sneakers SYSTEM \"sneakersammlung.dtd\">\n";
                konvertierte_datei << "<sneakersammlung>\n";


                for (unsigned i = 0; i < liste.size(); i++) {
                    konvertierte_datei << "    <sneaker xml:id=\"" << liste[i].id << "\"" << ">\n";
                    konvertierte_datei << "        <schuh marke=\"" << liste[i].marke << "\" ";
                    konvertierte_datei << "farbe=\"" << liste[i].farbe << "\" ";
                    konvertierte_datei << "groesse=\"" << liste[i].groesse << "\">";
                    konvertierte_datei << liste[i].name << "</schuh>\n";
                    konvertierte_datei << "        <preis>" << liste[i].preis << "</preis>\n";
                    konvertierte_datei << "        <datum>" << liste[i].datum << "</datum>\n";
                    konvertierte_datei << "        <schrank>" << liste[i].schrank << "</schrank>\n";
                    konvertierte_datei << "        <bewertung>" << liste[i].bewertung << "</bewertung>\n";
                    konvertierte_datei << "    </sneaker>" << "\n";
                    konvertierte_datei << endl;
                }

                konvertierte_datei << "</sneakersammlung>\n";

                konvertierte_datei.close();
                break;
            }
            case's': { // Suche nach Kategorie
                cout << "*********Nach welcher Kategorie wollen Sie suchen*********" << endl;
                cout << "[id] [marke] [farbe] [groesse] [name] [preis] [datum] [schrank] [bewertung]" << endl;
                string kategorie;
                cin >> kategorie;

                transform(kategorie.begin(), kategorie.end(), kategorie.begin(), ::tolower); // Kategorie eingabe wird umgeformt in Kleinbuchstaben

                if (kategorie.compare("id") && kategorie.compare("marke") && kategorie.compare("farbe") &&
                    kategorie.compare("groesse") && kategorie.compare("name") && kategorie.compare("preis") &&
                    kategorie.compare("datum") && kategorie.compare("schrank") && kategorie.compare("bewertung")) {
                    cout << "ungueltige Eingabe" << endl;
                    continue;
                }

                cout << "**********Bitte geben Sie den Suchbegriff ein:**********" << endl;
                string suchbegriff;
                cin >> suchbegriff;

                int ergebnis_zaehler = 0;
                if (!kategorie.compare("id")) { // Wenn Eingabe "ID"
                    for (unsigned i=0; i < liste.size(); i++) { //Gehe länge der List durch
                        if(liste[i].id.find(suchbegriff) != string::npos){ // Vergleiche mit Suchbegriff
                            liste[i].werte_ausgeben(); // Gebe alle dazugehörigen Werte aus
                            ergebnis_zaehler++; // Setze Zaehler hoch, für Meldung, wenn kein Ergebnis gefunden wird
                        }
                    }

                } else if (!kategorie.compare("marke")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].marke.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("farbe")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].farbe.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("groesse")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].groesse.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("name")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].name.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("preis")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].preis.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("datum")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].datum.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("schrank")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].schrank.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }

                } else if (!kategorie.compare("bewertung")) {
                    for (unsigned i=0; i < liste.size(); i++) {
                        if(liste[i].bewertung.find(suchbegriff) != string::npos){
                            liste[i].werte_ausgeben();
                            ergebnis_zaehler++;
                        }
                    }
                }

                if(ergebnis_zaehler == 0) {
                    cout << "keine Ergebnisse gefunden" << endl;
                }
                break;
            }
            default: {
            cout << "aktion nicht verfügbar"<< endl;
                break;
            }

        }
    }


    datenTXT.close();
    return 0;

}// main



