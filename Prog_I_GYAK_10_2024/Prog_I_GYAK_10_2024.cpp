#include <string> // string könyvtár beillesztése
#include <iostream> // iostream könyvtár beillesztése
#include <ctime> // ctime könyvtár beillesztése
#include <fstream> // fstream könyvtár beillesztése
#include <iomanip> // iomanip könyvtár beillesztése

using namespace std; // névtér használata

struct indulo { // indulo struktúra definiálása
    string nev; // név tárolása
    float eddigi; // eddigi idõ tárolása
    int rajtszam; // rajtszám tárolása
    float ido; // futott idõ tárolása
};

int main() // fõ program
{
    indulo sik[19]; // indulo tömb deklarálása
    int i, jobb = 0, rosszabb = 0, letszam = 0; // változók inicializálása
    float elmaradt = 0, ossz = 0; // változók inicializálása

    srand((unsigned)time(NULL)); // véletlen szám generálás miatt

    ifstream verseny("indulok.txt"); // fájl megnyitása olvasásra

    for (i = 0; i < 19 && !verseny.eof(); i++) // ciklus a fájl beolvasására
    {
        verseny >> sik[i].nev; // név beolvasása
        verseny >> sik[i].eddigi; // eddigi idõ beolvasása
        sik[i].rajtszam = rand() % 100 + 100; // véletlen rajtszám generálása
        do {
            cout << "\nAdja meg az " << sik[i].nev << " futo eredmenyet: "; // futó eredményének bekérése
            cin >> sik[i].ido; // futott idõ beolvasása
            cin.ignore(); // bemeneti puffer ürítése
            if (sik[i].ido < 10 || sik[i].ido > 20) // idõ ellenõrzése
                cout << "\nHibas adat az ido 10-20 mp kozott lehet!" << endl; // hibaüzenet
        } while (sik[i].ido < 10 || sik[i].ido > 20); // ismétlés, ha az idõ nem megfelelõ
        letszam++; // létszám növelése
    }
    verseny.close(); // fájl bezárása

    system("cls"); // képernyõ törlése
    cout << "\nOsszesen " << letszam << " futo indult a versenyen!" << endl; // létszám kiírása
    cout.setf(ios::right); // jobbra igazítás beállítása

    for (i = 0; i < letszam; i++) // ciklus a futók adatainak kiírására
    {
        cout << setw(20) << sik[i].nev << "\t" << // név kiírása
            sik[i].rajtszam << "\t" << // rajtszám kiírása
            sik[i].eddigi << " mp\t" << // eddigi idõ kiírása
            sik[i].ido << "mp" << endl; // futott idõ kiírása
        ossz += sik[i].ido; // összes futott idõ kiszámolása
    }
    cout << "\nA futok osszesen " << ossz << " masotpercet futottak" << endl; // összes futott idõ kiírása

    for (i = 0; i < letszam; i++) // ciklus az idõk összehasonlítására
    {
        if (sik[i].eddigi > sik[i].ido) // ha az új idõ jobb, mint az eddigi
        {
            jobb++; // jobb idõ számláló növelése
            cout << sik[i].nev << " uj legjobbja: " // új legjobb idõ kiírása
                << sik[i].ido << " mp" << endl;
        }
        else {
            rosszabb++; // rosszabb idõ számláló növelése
            elmaradt += sik[i].ido; // elmaradt idõ összegzése
        }
    }
    cout << endl << jobb << " futo dontotte meg az eddigi legjobbjat " << endl; // jobb idõk száma kiírása
    cout << "\nAz eddigi legjobbtol elmaradt futok atlagideje: " // elmaradt idõk átlaga kiírása
        << elmaradt / rosszabb << " mp." << endl;
    cout << "\n Az elsokent nevezett futo adatai: \n\t" // elsõ futó adatai kiírása
        << sik[0].nev << " \trajtszama: " <<
        sik[0].rajtszam << " \tideje" <<
        sik[0].ido << " \t elteres: " <<
        sik[0].ido - sik[0].eddigi << " mp." << endl;

    ofstream kesz("eredmeny.txt"); // fájl megnyitása írásra
    if (kesz.is_open()) { // ha a fájl megnyílt
        for (i = 0; i < letszam; i++) // ciklus az adatok fájlba írására
        {
            kesz << sik[i].nev << "\t"; // név írása
            kesz << sik[i].eddigi << "\t"; // eddigi idõ írása
            kesz << sik[i].rajtszam << "\t"; // rajtszám írása
            kesz << sik[i].ido << endl; // futott idõ írása
        }
        kesz.close(); // fájl bezárása
        cout << "\nA lista sikeresen elkeszult" << endl; // sikeres írás üzenet
    }
    else
    {
        cout << "\nA lista letrehozasa sikertelen" << endl; // sikertelen írás üzenet
    }
}
