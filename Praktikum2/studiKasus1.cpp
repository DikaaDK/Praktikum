#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    string nama;
    int jamKerja;
    int gajiPerJam;
    int gajiTotal;

    cout << "Masukan nama anda: ";
    getline(cin, nama); 
    
    cout << "Masukan jam kerja anda: ";
    cin >> jamKerja;
    cout << "Masukan gaji per jam anda: ";
    cin >> gajiPerJam;

    gajiTotal = jamKerja * gajiPerJam;

    cout << left << setw(20) << "Nama" << setw(15) << "Jam kerja" << setw(15) << "Tarif per jam" << setw(15) << "Gaji total" << endl;
    cout << left << setw(20) << nama << setw(15) << jamKerja << setw(15) << gajiPerJam << setw(15) << gajiTotal << endl;

    return 0;
}