#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct ItemNota {
    int noStan;
    string namaItem;
    long long harga;
    int qty;
    long long subtotal;
};

struct Stan {
    int noStan;
    string namaStan;
    long long totalOmzet;
    int totalItemTerjual;
};

void inisialisasiStan(Stan* daftarStan, int jumlahStan);
void inputNotaKertas(Stan* daftarStan, int jumlahStan, ItemNota* &riwayatNota, int &jumlahCatatan, long long rekapStan[][2]);
void lihatRiwayatNota(ItemNota* riwayatNota, int jumlahCatatan);
void laporanOmzetStan(Stan* daftarStan, int jumlahStan, long long rekapStan[][2]);
long long hitungTotalRekursif(Stan* daftarStan, int n);

int main() {
    int jumlahStan = 3;

    Stan* daftarStan = new Stan[jumlahStan];
    ItemNota* riwayatNota = nullptr;
    int jumlahCatatan = 0;

    long long rekapStan[3][2] = {0};

    inisialisasiStan(daftarStan, jumlahStan);

    int pilihan;
    do {
        cout << "\n======================================================\n";
        cout << "     SISTEM KASIR TERPUSAT KANTIN UM (INPUT NOTA)     \n";
        cout << "======================================================\n";
        cout << "1. Input Transaksi dari Nota Kertas\n";
        cout << "2. Lihat Semua Riwayat Item Nota Masuk\n";
        cout << "3. Laporan Omzet Stan (Bubble Sort & Matriks 2D)\n";
        cout << "4. Keluar Program\n";
        cout << "------------------------------------------------------\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputNotaKertas(daftarStan, jumlahStan, riwayatNota, jumlahCatatan, rekapStan);
                break;
            case 2:
                lihatRiwayatNota(riwayatNota, jumlahCatatan);
                break;
            case 3:
                laporanOmzetStan(daftarStan, jumlahStan, rekapStan);
                break;
            case 4:
                cout << "\nMenutup sistem dan membersihkan memori...\n";
                break;
            default:
                cout << "\n[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);

    delete[] daftarStan;
    delete[] riwayatNota;

    return 0;
}

void inisialisasiStan(Stan* daftarStan, int jumlahStan) {
    daftarStan[0] = {1, "Stan 1 - Geprek & Lalapan", 0, 0};
    daftarStan[1] = {2, "Stan 2 - Bakso & Mie Ayam", 0, 0};
    daftarStan[2] = {3, "Stan 3 - Aneka Minuman",    0, 0};
}

void inputNotaKertas(Stan* daftarStan, int jumlahStan, ItemNota* &riwayatNota, int &jumlahCatatan, long long rekapStan[][2]) {
    int noStan;
    char tambahItem;
    long long totalNotaIni = 0, uangBayar;

    cout << "\n--- INPUT DATA NOTA KERTAS ---\n";
    cout << "Daftar Stan Terdaftar:\n";
    for (int i = 0; i < jumlahStan; i++) {
        Stan* ptr = (daftarStan + i);
        cout << "  [" << ptr->noStan << "] " << ptr->namaStan << "\n";
    }

    cout << "\nMasukkan Nomor Stan Nota (1-" << jumlahStan << ") : ";
    cin >> noStan;

    if (noStan < 1 || noStan > jumlahStan) {
        cout << "[!] Nomor stan tidak terdaftar!\n";
        return;
    }

    int idxStan = noStan - 1;
    cout << ">> Mencatat nota untuk: " << daftarStan[idxStan].namaStan << "\n";

    do {
        string namaItem;
        long long harga;
        int qty;

        cout << "\nMasukkan Data Baris Nota:\n";
        cout << "  Nama Item         : ";
        cin.ignore();
        getline(cin, namaItem);

        cout << "  Harga Satuan (Rp) : ";
        cin >> harga;

        cout << "  Jumlah Beli (Qty) : ";
        cin >> qty;

        if (harga <= 0 || qty <= 0) {
            cout << "  [!] Harga dan jumlah harus lebih dari 0.\n";
        } else {
            long long subtotal = harga * qty;

            daftarStan[idxStan].totalOmzet += subtotal;
            daftarStan[idxStan].totalItemTerjual += qty;
            rekapStan[idxStan][0] += qty;
            rekapStan[idxStan][1] += subtotal;
            totalNotaIni += subtotal;

            ItemNota* temp = new ItemNota[jumlahCatatan + 1];
            for (int i = 0; i < jumlahCatatan; i++) {
                temp[i] = riwayatNota[i];
            }

            temp[jumlahCatatan].noStan = noStan;
            temp[jumlahCatatan].namaItem = namaItem;
            temp[jumlahCatatan].harga = harga;
            temp[jumlahCatatan].qty = qty;
            temp[jumlahCatatan].subtotal = subtotal;

            delete[] riwayatNota;
            riwayatNota = temp;
            jumlahCatatan++;

            cout << "  >> Tercatat: [Stan " << noStan << "] " << namaItem
                 << " x" << qty << " = Rp " << subtotal << "\n";
        }

        cout << "\nMasih ada item lain di nota kertas ini? (y/n): ";
        cin >> tambahItem;
    } while (tambahItem == 'y' || tambahItem == 'Y');

    if (totalNotaIni > 0) {
        cout << "\n======================================================\n";
        cout << "REKAP PEMBAYARAN NOTA (" << daftarStan[idxStan].namaStan << ")\n";
        cout << "Total Tagihan : Rp " << totalNotaIni << "\n";
        do {
            cout << "Uang Tunai    : Rp ";
            cin >> uangBayar;
            if (uangBayar < totalNotaIni) {
                cout << "[!] Uang pembayaran kurang!\n";
            }
        } while (uangBayar < totalNotaIni);
        cout << "Kembalian     : Rp " << (uangBayar - totalNotaIni) << "\n";
        cout << "======================================================\n";
    }
}

void lihatRiwayatNota(ItemNota* riwayatNota, int jumlahCatatan) {
    cout << "\n==================================================================\n";
    cout << "                 RIWAYAT SELURUH ITEM NOTA MASUK                  \n";
    cout << "==================================================================\n";

    if (jumlahCatatan == 0) {
        cout << "Belum ada data nota yang diinputkan.\n";
        return;
    }

    cout << left << setw(5) << "No"
         << left << setw(9) << "Stan"
         << left << setw(28) << "Nama Item"
         << right << setw(6) << "Qty"
         << right << setw(18) << "Subtotal" << "\n";
    cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahCatatan; i++) {
        cout << left << setw(5) << (i + 1)
             << "Stan " << left << setw(4) << riwayatNota[i].noStan
             << left << setw(28) << riwayatNota[i].namaItem
             << right << setw(6) << riwayatNota[i].qty
             << "   Rp " << right << setw(13) << riwayatNota[i].subtotal << "\n";
    }
    cout << "==================================================================\n";
}

long long hitungTotalRekursif(Stan* daftarStan, int n) {
    if (n <= 0) return 0;
    return daftarStan[n - 1].totalOmzet + hitungTotalRekursif(daftarStan, n - 1);
}

void laporanOmzetStan(Stan* daftarStan, int jumlahStan, long long rekapStan[][2]) {
    Stan* urut = new Stan[jumlahStan];
    for (int i = 0; i < jumlahStan; i++) urut[i] = daftarStan[i];

    for (int i = 0; i < jumlahStan - 1; i++) {
        for (int j = 0; j < jumlahStan - i - 1; j++) {
            if (urut[j].totalOmzet < urut[j + 1].totalOmzet) {
                Stan temp = urut[j];
                urut[j] = urut[j + 1];
                urut[j + 1] = temp;
            }
        }
    }

    long long grandTotal = hitungTotalRekursif(daftarStan, jumlahStan);

    cout << "\n========================================================================\n";
    cout << "           PERINGKAT PEMASUKAN MULTI-STAN (BUBBLE SORT)                 \n";
    cout << "========================================================================\n";
    cout << left << setw(6) << "Rank"
         << left << setw(30) << "Nama Stan"
         << right << setw(10) << "Terjual"
         << right << setw(15) << "Total Omzet"
         << right << setw(11) << "Porsi %" << "\n";
    cout << "------------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahStan; i++) {
        double persen = (grandTotal > 0) ? ((double)urut[i].totalOmzet / grandTotal) * 100.0 : 0.0;
        cout << left << setw(6) << (i + 1)
             << left << setw(30) << urut[i].namaStan
             << right << setw(6) << urut[i].totalItemTerjual << " pcs"
             << "   Rp " << right << setw(10) << urut[i].totalOmzet
             << right << setw(9) << fixed << setprecision(1) << persen << "%\n";
    }
    cout.unsetf(ios::fixed);
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(46) << "TOTAL KESELURUHAN PEMASUKAN KANTIN"
         << "   Rp " << right << setw(10) << grandTotal << "\n";
    cout << "========================================================================\n";

    cout << "\n========================================================================\n";
    cout << "               MATRIKS REKAPITULASI PER STAN (ARRAY 2D)                 \n";
    cout << "========================================================================\n";
    cout << left << setw(30) << "Nama Stan"
         << right << setw(20) << "Total Item (pcs)"
         << right << setw(20) << "Total Omzet (Rp)" << "\n";
    cout << "------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlahStan; i++) {
        cout << left << setw(30) << daftarStan[i].namaStan
             << right << setw(20) << rekapStan[i][0]
             << right << setw(20) << rekapStan[i][1] << "\n";
    }
    cout << "========================================================================\n";

    delete[] urut;
}