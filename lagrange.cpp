#include <iostream>
#include <math.h>

using namespace std;

void wczytanieDanych(float *& , float *&, int&, float &);
void wyswietlenieDanych(float *, float *, int );
void wyswietlenieWielomianu(float *, int );
float *obliczenieWielomianu(float*,int ,int);
float* interpolacja(float*, float*, int);
float interpolacjaWPunkcie(float*, float,int);

int main()
{

    int liczbaWezlow = 5;
    float punkt = 1;
    /*//przyklad 1
    float tabX[liczbaWezlow] = {-2,0,1,2,3};
    float tabY[liczbaWezlow] = {-240,24,18,-16,-60};
    */

    /* //przyklad 2
    float tabX[liczbaWezlow] = {-4,-2,0,3,5};
    float tabY[liczbaWezlow] = {1008,420,-240,-420,630};
    */

     //przyklad 3
    float tabX[liczbaWezlow] = {-5,-3,-1,2,5};
    float tabY[liczbaWezlow] = {1120,-160,-144,-630,2880};


    /*//wczytywanie z klawiatury
    float *tabX, *tabY;
    wczytanieDanych(tabX ,tabY, liczbaWezlow,punkt);
    */

    float *wynik ;
    wyswietlenieDanych(tabX,tabY,liczbaWezlow);
    wynik = interpolacja(tabX,tabY,liczbaWezlow);
    wyswietlenieWielomianu(wynik,liczbaWezlow);
    cout << "\n wartosc w punkcie : " << noshowpos << punkt << " to " << interpolacjaWPunkcie(wynik,punkt,liczbaWezlow);
    return 0;
}

// funkcja jako parametr pobiera indeks, którego nie liczmy z tablicy wprowadzonych X
float *obliczenieWielomianu(float * tabX,int indexBezKtoregoLiczymy,int liczbaWezlow)
{
    //obliczanie wielomianu 3 stopnia
    int poczatkowaWielkosc,flag = 0;
    if(liczbaWezlow < 4) poczatkowaWielkosc = liczbaWezlow ;
    else poczatkowaWielkosc = 4;

    float *tabKolejnychPoteg = new float[poczatkowaWielkosc];
    for(int i = 0; i < poczatkowaWielkosc ;i++)
    {
        if(i == 0 || i == poczatkowaWielkosc -1 ) tabKolejnychPoteg[i] = 1;
        else tabKolejnychPoteg[i] = 0;
    }

    if(indexBezKtoregoLiczymy > 3)
    {
        indexBezKtoregoLiczymy = 3;
        flag = 1; // ostatnia sytuacja w ktorej liczymy bez ostatniej wartosci w tabX np L(4) dla 5 wezlow
    }

    for(int i =0 ;i < poczatkowaWielkosc ;i++)// liczymy tylko pierwsze 3, bo zawsze na najw potega = 1
    {
        if(i != indexBezKtoregoLiczymy)
        {
            tabKolejnychPoteg[0] *= (-1 *tabX[i]);
            tabKolejnychPoteg[poczatkowaWielkosc-2] += (-1 * tabX[i]);
            for(int j = i ; j < 4  ;j++)
            {
                if(i != j && j !=indexBezKtoregoLiczymy  )
                {
                    tabKolejnychPoteg[poczatkowaWielkosc-3] += (tabX[i] * tabX[j]);
                }
            }
        }
    }
    if(liczbaWezlow <= 4) return tabKolejnychPoteg;
    else
    {
        int nowaWielkosc = poczatkowaWielkosc;
        float *nowaTabKolejnychPoteg = new float [liczbaWezlow];
        float * tablicaTymaczoswa = new float[liczbaWezlow];
        for(int i = 0 ;i < poczatkowaWielkosc ;i++)
        {
            nowaTabKolejnychPoteg[i] = tabKolejnychPoteg[i] ;
            tablicaTymaczoswa[i] = tabKolejnychPoteg[i];
        }
        while(nowaWielkosc != liczbaWezlow)
        {
        //dla liczby wezlow > 4
        nowaWielkosc++;
        nowaTabKolejnychPoteg[nowaWielkosc-1] = 1;
        tablicaTymaczoswa[nowaWielkosc-1] = 1;
        //wyswietlenieWielomianu(nowaTabKolejnychPoteg, nowaWielkosc);
        //wyswietlenieWielomianu(tablicaTymaczoswa,liczbaWezlow);

        //nowaTabKolejnychPoteg[nowaWielkosc-1]= 1;  //przepisujemy stare wartosci o jeden blizej robiac miejsce dla najwyzszej potegi
        for(int i = 0 ;i < nowaWielkosc - 1;i++)
        {
            if(i > 0 )
            {
                if(flag) nowaTabKolejnychPoteg[i] = tablicaTymaczoswa[i-1] +  (-1 * tablicaTymaczoswa[i] *tabX[nowaWielkosc - 2]) ;
                else nowaTabKolejnychPoteg[i] = tablicaTymaczoswa[i-1] +  (-1 * tablicaTymaczoswa[i] *tabX[nowaWielkosc - 1]) ;
                tablicaTymaczoswa[i-1] = nowaTabKolejnychPoteg[i-1];
            }
        }
        if(flag) nowaTabKolejnychPoteg[0] *= -1 *tabX[nowaWielkosc - 2] ;
        else nowaTabKolejnychPoteg[0] *= -1 *tabX[nowaWielkosc - 1] ;
        tablicaTymaczoswa[0] = nowaTabKolejnychPoteg[0];
        tablicaTymaczoswa[nowaWielkosc-2] = nowaTabKolejnychPoteg[nowaWielkosc-2];
        tablicaTymaczoswa[nowaWielkosc-1] = nowaTabKolejnychPoteg[nowaWielkosc-1];

        }
        return nowaTabKolejnychPoteg;
    }
}
void wczytanieDanych(float *&tabx , float *&taby, int& l_wezlow, float &punkt)
{
    cout << " podaj liczbe wezlow ";
    cin >> l_wezlow;
    tabx = new float[l_wezlow];
    taby = new float[l_wezlow];
    for(int i = 0 ;i < l_wezlow ; i++)
    {
        cout << " \n podaj x " << i  << " : ";
        cin >> tabx[i];
        if(i!= 0 && tabx[i] <= tabx[i - 1])
        {
            cout << "\n!! kolejne wartosci musza byc wieksze od siebie  !! \n";
            i--;
        }
    }
    for(int i = 0 ;i < l_wezlow ; i++)
    {
        cout << " \n podaj y " << i  << " : ";
        cin >> taby[i];

    }
    cout << "podaj punkt : ";
    cin >> punkt;
    while(punkt < tabx[0] || punkt > tabx[l_wezlow - 1 ])
    {
        cout << " \nniespelnione warunki interpolacji !, podaj punkt jeszcze raz " ;
        cin >> punkt;
    }
}

void wyswietlenieDanych(float *tabx, float *taby, int l_wezlow)
{
    cout << "\n tab x \n";
    for(int i = 0 ;i < l_wezlow ; i++)
    {
        cout << tabx[i] << " ";
    }
    cout << "\n tab y \n";
    for(int i = 0 ;i < l_wezlow ; i++)
    {
        cout << taby[i] << " ";
    }
}
void wyswietlenieWielomianu(float *tab,int size)
{
    cout << "\n\n wynik : \n";
    for(int i = size - 1; i >=0;i--)
    {
        if(i == 0 && tab[i]) cout << showpos <<tab[i];
        else if(i == 0 || tab[i] == 0) cout <<"";
        else if(i == 1 )cout << showpos <<tab[i] << "x"<< " ";

        else if(tab[i] == 1 ) cout << "+x^" << noshowpos << i << " ";
        else if(tab[i] == -1 ) cout << "-x^" << noshowpos << i << " ";
        else if(i == size - 1)
            if( tab[i] > 0)
                cout << noshowpos << " " <<tab[i] << "x^"<< noshowpos << i<< " ";
            else
                cout << showpos <<tab[i] << "x^"<< noshowpos << i<< " ";

        else cout << showpos <<tab[i] << "x^" << noshowpos << i << " ";

    }
}
float* interpolacja(float* tabX,float* tabY , int liczbaWezlow)
{
    float *mianownik = new float[liczbaWezlow];
    float *tabKolejnychPoteg ;
    float *wynik = new float[liczbaWezlow];
    for(int i = 0; i < liczbaWezlow ;i++)
    {
        mianownik[i] = 1;
        for(int j = 0; j < liczbaWezlow ; j++)
        {
            if(j != i)
            {
                mianownik[i] *= (tabX[i] - tabX[j]);
            }
        }

        tabKolejnychPoteg = obliczenieWielomianu(tabX,i,liczbaWezlow);

        mianownik[i] = tabY[i]/mianownik[i];

        //cout << "\n mianownik : " << mianownik[i];
        //wyswietlenieWielomianu(tabKolejnychPoteg,liczbaWezlow);


         //mianownik  = liczby wyciagniete przed nawias w ostatetcznym rachunku
        for(int k = 0;k < liczbaWezlow;k++)
        {

            wynik[k] += (tabKolejnychPoteg[k] * mianownik[i]);
        }
        //mnozymy razy kolejne x liczbe wyciagnieta przed nawias
    }

    return wynik;
}

float interpolacjaWPunkcie(float* tabWynikowa, float punkt, int liczbaWezlow)
{
    float wynik = tabWynikowa[0];
    for(int i = 1;i < liczbaWezlow;i++)
    {
            wynik += (tabWynikowa[i] * pow(punkt,i));
    }
    return wynik;
}
