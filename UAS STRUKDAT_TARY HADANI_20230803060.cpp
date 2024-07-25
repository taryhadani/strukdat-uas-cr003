#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string nama_file = "perpustakaan.txt";

struct Buku {
    int id;
    string judul;
    string penulis;
    string kategori;
    int tahun;
};

vector<Buku> muat_buku() {
    vector<Buku> buku;
    ifstream file(nama_file);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Buku b;
            ss >> b.id;
            ss.ignore();
            getline(ss, b.judul, ',');
            getline(ss, b.penulis, ',');
            getline(ss, b.kategori, ',');
            ss >> b.tahun;
            buku.push_back(b);
        }
        file.close();
    }
    return buku;
}

void simpan_buku(const vector<Buku>& buku) {
    ofstream file(nama_file);
    if (file.is_open()) {
        for (const Buku& b : buku) {
            file << b.id << "," << b.judul << "," << b.penulis << "," << b.kategori << "," << b.tahun << endl;
        }
        file.close();
    }
}

void tambah_buku(const string& judul, const string& penulis, const string& kategori, int tahun) {
    vector<Buku> buku = muat_buku();
    int id = buku.empty() ? 1 : buku.back().id + 1;
    buku.push_back({id, judul, penulis, kategori, tahun});
    simpan_buku(buku);
    cout << "Buku berhasil ditambahkan." << endl;
}

void lihat_buku() {
    vector<Buku> buku = muat_buku();
    for (const Buku& b : buku) {
        cout << "ID: " << b.id << ", Judul: " << b.judul << ", Penulis: " << b.penulis << ", Kategori: " << b.kategori << ", Tahun: " << b.tahun << endl;
    }
}

void perbarui_buku(int id, const string& judul, const string& penulis, const string& kategori, int tahun) {
    vector<Buku> buku = muat_buku();
    bool ditemukan = false;
    for (Buku& b : buku) {
        if (b.id == id) {
            b.judul = judul;
            b.penulis = penulis;
            b.kategori = kategori;
            b.tahun = tahun;
            ditemukan = true;
            break;
        }
    }
    if (ditemukan) {
        simpan_buku(buku);
        cout << "Buku berhasil diperbarui." << endl;
    } else {
        cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void hapus_buku(int id) {
    vector<Buku> buku = muat_buku();
    auto it = remove_if(buku.begin(), buku.end(), [id](const Buku& b) {
        return b.id == id;
    });
    if (it != buku.end()) {
        buku.erase(it, buku.end());
        simpan_buku(buku);
        cout << "Buku berhasil dihapus." << endl;
    } else {
        cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
    }
}

int main() {
    int pilihan_peran;
    cout << "Silahkan Pilih Peran Yang Kalian Mau\n";
    cout << "1. Admin\n";
    cout << "2. Pengguna\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan_peran;

    int pilihan;
    while (true) {
        if (pilihan_peran == 1) {
        	cout << "==========Selamat Datang Di Perpustakaan Tary==========";
            cout << "\nMenu Admin:\n";
            cout << "1. Tambah Buku\n";
            cout << "2. Lihat Semua Buku\n";
            cout << "3. Perbarui Buku\n";
            cout << "4. Hapus Buku\n";
            cout << "5. Keluar\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihan;

            if (pilihan == 1) {
                string judul, penulis, kategori;
                int tahun;
                cout << "Masukkan judul buku: ";
                cin.ignore();
                getline(cin, judul);
                cout << "Masukkan penulis: ";
                getline(cin, penulis);
                cout << "Masukkan kategori: ";
                getline(cin, kategori);
                cout << "Masukkan tahun: ";
                cin >> tahun;
                tambah_buku(judul, penulis, kategori, tahun);
            } else if (pilihan == 2) {
                lihat_buku();
            } else if (pilihan == 3) {
                int id;
                string judul, penulis, kategori;
                int tahun;
                cout << "Masukkan ID buku untuk diperbarui: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan judul baru: ";
                getline(cin, judul);
                cout << "Masukkan penulis baru: ";
                getline(cin, penulis);
                cout << "Masukkan kategori baru: ";
                getline(cin, kategori);
                cout << "Masukkan tahun baru: ";
                cin >> tahun;
                perbarui_buku(id, judul, penulis, kategori, tahun);
            } else if (pilihan == 4) {
                int id;
                cout << "Masukkan ID buku untuk dihapus: ";
                cin >> id;
                hapus_buku(id);
            } else if (pilihan == 5) {
                break;
            } else {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        } else if (pilihan_peran == 2) {
            cout << "\nMenu Pengguna:\n";
            cout << "1. Lihat Semua Buku\n";
            cout << "2. Keluar\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihan;

            if (pilihan == 1) {
                lihat_buku();
            } else if (pilihan == 2) {
                break;
            } else {
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        } else {
            cout << "Pilihan peran tidak valid. Keluar..." << endl;
            break;
        }
    }
    return 0;
}
