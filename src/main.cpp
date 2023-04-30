
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <vector>


struct tiuring {
    std::string dabartine_busena;
    char dabartinis_simbolis;
    char naujas_simbolis;
    char kryptis;
    std::string nauja_busena;
};

void meniu();
void skaitymas_is_failo(std::string);
void programos_vykdymas(std::string, int, std::vector<tiuring>, std::string);
void juostos_rodymas(std::string, int, std::vector<tiuring>, std::string);

unsigned int greitis = 50;
int programos_ilgis = 0;

void meniu() {
    std::cout << "Sveiki atvykę į tiuringo mašinos simuliatorių!\n\n";
    std::cout << "Kad tęstumėte, įveskite failo pavadinimą:\n";
    std::string failo_pav;
    std::cin >> failo_pav;
    failo_pav += ".txt";
    skaitymas_is_failo(failo_pav);
}

void skaitymas_is_failo(std::string failo_pav) {
    std::ifstream failas(failo_pav);
    std::string juosta; int galvute;
    std::vector<tiuring> instrukcijos;
    std::string dabartine_busena; char dabartinis_simbolis; char naujas_simbolis; char kryptis; std::string nauja_busena;
    if (failas.good()) {
        failas >> juosta >> galvute;
        while (failas >> dabartine_busena >> dabartinis_simbolis >> naujas_simbolis >> kryptis >> nauja_busena) {
            tiuring tr {
                dabartine_busena, dabartinis_simbolis, naujas_simbolis, kryptis, nauja_busena
            };
            programos_ilgis++;
            instrukcijos.push_back(tr);
        }
        programos_vykdymas(juosta, galvute, instrukcijos, "0");
    } else {
        std::cerr << "Failas pavadinimu " << failo_pav << " neegzistuoja, pabandykite įvesti pavadinimą iš naujo\n";
        std::cerr << "Grįžti į pradžią galite su 'Enter' mygtuku\n";
        std::cin.get();
        std::cin.get();
        system("CLS");
        meniu();
    }
}

void programos_vykdymas(std::string juosta, int galvute, std::vector<tiuring> instrukcijos, std::string busena) {
    int i = 0;
    while (i <= programos_ilgis) {
        
        if (instrukcijos[i].dabartine_busena == busena) {
            if (instrukcijos[i].dabartinis_simbolis == juosta[galvute - 1]) {
                juosta[galvute - 1] = instrukcijos[i].naujas_simbolis;
                busena = instrukcijos[i].nauja_busena;
                
                if (instrukcijos[i].kryptis == 'L') {
                    galvute--;
                } 
                else if (instrukcijos[i].kryptis == 'R') {
                    galvute++;
                }
                juostos_rodymas(juosta, galvute, instrukcijos, busena);
            } else {
                ++i;
            } 
        } else {
            
            while (instrukcijos[i].dabartine_busena != busena) {
                ++i;
                if (i > programos_ilgis) {
                    i = 0;
                }
            }
        }
    }
    meniu();
}

void juostos_rodymas(std::string juosta, int galvute, std::vector<tiuring> instrukcijos, std::string busena) {
    system("CLS");
    std::string s("");
    std::string tarpai(s.insert(0, galvute - 1, ' '));
    std::cout << tarpai << "|\n" << tarpai << "V\n" << juosta << "\n\n";
    std::cout << "Būsena: " << busena << "\n";  
    std::this_thread::sleep_for(std::chrono::milliseconds(greitis));
}

int main() {
    meniu();
    return 0;
}