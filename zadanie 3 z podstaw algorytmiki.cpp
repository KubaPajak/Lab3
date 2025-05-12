#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <cmath>
#include <fstream>
#include <sstream>

struct student{
    std::string imie;
    std::string nazwisko;
    int liczba_punktow;

};


void wczytajStudentow(student *&tab, int &n){
    tab = new student[n];
    std::ifstream plik;
    std::string nazwa_pliku = "studenci.csv";
    plik.open(nazwa_pliku);
    char sredniki;
    std::string pomoc;
    std::string linia;
    if(!plik.is_open()){
        std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        return;
    }

    for(int i=0; i<2; i++){
        plik >> sredniki;
    }

    for(int i=0; i<n; i++){
        plik>> linia;
        std::stringstream ss(linia);
        std::getline(ss, tab[i].imie, ';');
        std::getline(ss, tab[i].nazwisko, ';');
        std::getline(ss, pomoc);
        tab[i].liczba_punktow = std::atoi(pomoc.c_str());


    }
    plik.close();


}

void usunStudentow(student *&tab, int n){
    delete [] tab;
}

void wyswietlStudentow(student *tab, int n){
    std::cout << "Imie, Nazwisko, Liczba punktow" << std::endl;
    for(int i=0; i<n; i++){
        std::cout << tab[i].imie << ", " << tab[i].nazwisko << ", " << tab[i].liczba_punktow << std::endl; // /t generuje tabulacje w wypowadzonym tekscie na ekranie
    }
}

void sortowanieQuickSort(student *tab, int n, int a, int b, int tryb){
    int i = a;
    int j = b;
    student x = tab[(a + b) / 2];
    do{
        if(tryb == 1){
            while(tab[i].liczba_punktow < x.liczba_punktow) i++;
            while(tab[j].liczba_punktow > x.liczba_punktow) j--;
        }else{
            while(tab[i].liczba_punktow > x.liczba_punktow) i++;
            while(tab[j].liczba_punktow < x.liczba_punktow) j--;
        }
        if(i <= j){
            std::swap(tab[i], tab[j]);
            i++;
            j--;
        }
    }while(i <= j);
    if(a < j) sortowanieQuickSort(tab, n, a, j, tryb);
    if(i < b) sortowanieQuickSort(tab, n, i, b, tryb);
}

int main(){
    setlocale(LC_ALL, "");
    std::string nazwa_pliku;
    int liczba_studentow;
    std::ifstream plik;
    student *tab = nullptr;
    nazwa_pliku = "studenci.csv";
    plik.open(nazwa_pliku);
    if(!plik.is_open()){
        std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
        return 1;
    }
    plik >> liczba_studentow;
    wczytajStudentow(tab, liczba_studentow);
    if(tab == nullptr){
        std::cout << "Nie udalo sie wczytac studentow" << std::endl;
        return 1;
    }
    std::cout << "Wczytani studenci przed sortowaniem:" << std::endl;
    wyswietlStudentow(tab, liczba_studentow);
    int a,b;
    std::cout << "Podaj zakres indeksów do posortowania (a,b): ";
    std::cin >> a >> b;
    if(a < 0 || b >= liczba_studentow || a > b){
        std::cout << "Niepoprawny zakres indeksów" << std::endl;
        usunStudentow(tab, liczba_studentow);
        return 1;
    }
    int tryb;
    std::cout << "Podaj tryb sortowania (1-rosnąco, 2-malejąco): ";
    std::cin >> tryb;
    if(tryb != 1 && tryb != 2){
        std::cout << "Niepoprawny tryb sortowania" << std::endl;
        usunStudentow(tab, liczba_studentow);
        return 1;
    }
    sortowanieQuickSort(tab, liczba_studentow,a,b,tryb);
    std::cout << "Posortowani studenci:" << std::endl;

    wyswietlStudentow(tab, liczba_studentow);
    usunStudentow(tab, liczba_studentow);




return 0;}