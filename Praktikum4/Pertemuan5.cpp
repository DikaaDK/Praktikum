#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double penggunaan;
    double hargaSebelumDiskon;
    double presentaseDiskon;
    double diskon;
    double hargaSetelahDiskon;
    int pilihan;
    char pilihanDiskon;

    cout << fixed << setprecision(2);

    do {
        diskon = 0.00;
        cout << "Masukan penggunaan listrik (kWh): ";
        cin >> penggunaan;

        if (penggunaan <= 100) {
            hargaSebelumDiskon = penggunaan * 1500;
        } else if (penggunaan <= 300) {
            hargaSebelumDiskon = penggunaan * 2000;
        } else {
            hargaSebelumDiskon = penggunaan * 3000;
        }
        if (hargaSebelumDiskon > 1000000) {
            diskon = 0,10 * hargaSebelumDiskon;
        }

        cout << "Apakah Anda ingin memasukkan diskon? (y/t): ";
        cin >> pilihanDiskon;

        if (pilihanDiskon == 'y' || pilihanDiskon == 'Y') {
            cout << "Masukkan diskon %: ";
            cin >> presentaseDiskon;
            diskon = (presentaseDiskon / 100) * hargaSebelumDiskon;
        }

        hargaSetelahDiskon = hargaSebelumDiskon - diskon;

        cout << "Total Penggunaan Listrik: " << penggunaan << " kWh";
        cout << "Total Tagihan Setelah Diskon: Rp " << hargaSebelumDiskon << "\n";
        cout << "Diskon : Rp " << diskon << "\n";
        cout << "Total Tagihan Sebelum Diskon: Rp " << hargaSetelahDiskon << "\n";

        cout << "Ingin menghitung tagihan untuk penggunaan lain? (1 untuk ya, selain itu untuk tidak): ";
        cin >> pilihan;

    } while (pilihan == 1);
    return 0;
}