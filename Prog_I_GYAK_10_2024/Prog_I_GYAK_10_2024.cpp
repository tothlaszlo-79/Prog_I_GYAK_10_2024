#include <string> // string k�nyvt�r beilleszt�se
#include <iostream> // iostream k�nyvt�r beilleszt�se
#include <ctime> // ctime k�nyvt�r beilleszt�se
#include <fstream> // fstream k�nyvt�r beilleszt�se
#include <iomanip> // iomanip k�nyvt�r beilleszt�se

using namespace std; // n�vt�r haszn�lata

struct indulo { // indulo strukt�ra defini�l�sa
    string nev; // n�v t�rol�sa
    float eddigi; // eddigi id� t�rol�sa
    int rajtszam; // rajtsz�m t�rol�sa
    float ido; // futott id� t�rol�sa
};

int main() // f� program
{
    indulo sik[19]; // indulo t�mb deklar�l�sa
    int i, jobb = 0, rosszabb = 0, letszam = 0; // v�ltoz�k inicializ�l�sa
    float elmaradt = 0, ossz = 0; // v�ltoz�k inicializ�l�sa

    srand((unsigned)time(NULL)); // v�letlen sz�m gener�l�s miatt

    ifstream verseny("indulok.txt"); // f�jl megnyit�sa olvas�sra

    for (i = 0; i < 19 && !verseny.eof(); i++) // ciklus a f�jl beolvas�s�ra
    {
        verseny >> sik[i].nev; // n�v beolvas�sa
        verseny >> sik[i].eddigi; // eddigi id� beolvas�sa
        sik[i].rajtszam = rand() % 100 + 100; // v�letlen rajtsz�m gener�l�sa
        do {
            cout << "\nAdja meg az " << sik[i].nev << " futo eredmenyet: "; // fut� eredm�ny�nek bek�r�se
            cin >> sik[i].ido; // futott id� beolvas�sa
            cin.ignore(); // bemeneti puffer �r�t�se
            if (sik[i].ido < 10 || sik[i].ido > 20) // id� ellen�rz�se
                cout << "\nHibas adat az ido 10-20 mp kozott lehet!" << endl; // hiba�zenet
        } while (sik[i].ido < 10 || sik[i].ido > 20); // ism�tl�s, ha az id� nem megfelel�
        letszam++; // l�tsz�m n�vel�se
    }
    verseny.close(); // f�jl bez�r�sa

    system("cls"); // k�perny� t�rl�se
    cout << "\nOsszesen " << letszam << " futo indult a versenyen!" << endl; // l�tsz�m ki�r�sa
    cout.setf(ios::right); // jobbra igaz�t�s be�ll�t�sa

    for (i = 0; i < letszam; i++) // ciklus a fut�k adatainak ki�r�s�ra
    {
        cout << setw(20) << sik[i].nev << "\t" << // n�v ki�r�sa
            sik[i].rajtszam << "\t" << // rajtsz�m ki�r�sa
            sik[i].eddigi << " mp\t" << // eddigi id� ki�r�sa
            sik[i].ido << "mp" << endl; // futott id� ki�r�sa
        ossz += sik[i].ido; // �sszes futott id� kisz�mol�sa
    }
    cout << "\nA futok osszesen " << ossz << " masotpercet futottak" << endl; // �sszes futott id� ki�r�sa

    for (i = 0; i < letszam; i++) // ciklus az id�k �sszehasonl�t�s�ra
    {
        if (sik[i].eddigi > sik[i].ido) // ha az �j id� jobb, mint az eddigi
        {
            jobb++; // jobb id� sz�ml�l� n�vel�se
            cout << sik[i].nev << " uj legjobbja: " // �j legjobb id� ki�r�sa
                << sik[i].ido << " mp" << endl;
        }
        else {
            rosszabb++; // rosszabb id� sz�ml�l� n�vel�se
            elmaradt += sik[i].ido; // elmaradt id� �sszegz�se
        }
    }
    cout << endl << jobb << " futo dontotte meg az eddigi legjobbjat " << endl; // jobb id�k sz�ma ki�r�sa
    cout << "\nAz eddigi legjobbtol elmaradt futok atlagideje: " // elmaradt id�k �tlaga ki�r�sa
        << elmaradt / rosszabb << " mp." << endl;
    cout << "\n Az elsokent nevezett futo adatai: \n\t" // els� fut� adatai ki�r�sa
        << sik[0].nev << " \trajtszama: " <<
        sik[0].rajtszam << " \tideje" <<
        sik[0].ido << " \t elteres: " <<
        sik[0].ido - sik[0].eddigi << " mp." << endl;

    ofstream kesz("eredmeny.txt"); // f�jl megnyit�sa �r�sra
    if (kesz.is_open()) { // ha a f�jl megny�lt
        for (i = 0; i < letszam; i++) // ciklus az adatok f�jlba �r�s�ra
        {
            kesz << sik[i].nev << "\t"; // n�v �r�sa
            kesz << sik[i].eddigi << "\t"; // eddigi id� �r�sa
            kesz << sik[i].rajtszam << "\t"; // rajtsz�m �r�sa
            kesz << sik[i].ido << endl; // futott id� �r�sa
        }
        kesz.close(); // f�jl bez�r�sa
        cout << "\nA lista sikeresen elkeszult" << endl; // sikeres �r�s �zenet
    }
    else
    {
        cout << "\nA lista letrehozasa sikertelen" << endl; // sikertelen �r�s �zenet
    }
}
