#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct User
{
    string username;
    string password;
    string role;
};

bool login(User users[], int totalUsers, string username, string password, User &loggedInUser);
// Fungsi Login 2 user
bool login(User users[], int totalUsers, string username, string password, User &loggedInUser)
{
    for (int i = 0; i < totalUsers; ++i)
    {
        if (users[i].username == username && users[i].password == password)
        {
            loggedInUser = users[i];
            return true;
        }
    }
    return false;
}

// Fungsi untuk menampilkan menu utama
void tampilMenuUtama()
{
    cout << "\t============================" << endl;
    cout << "\t         MENU UTAMA         " << endl;
    cout << "\t============================" << endl;
    cout << "\t1. Data Master" << endl;
    cout << "\t2. Transaksi" << endl;
    cout << "\t3. Laporan" << endl;
    cout << "\t4. Logout" << endl;
    cout << "\t============================" << endl;
    cout << "\tPilihan Anda: ";
}

// Fungsi untuk menampilkan menu Data Master
void tampilMenuDataMaster()
{
    cout << " MENU DATA MASTER " << endl;
    cout << " 1. Data Barang" << endl;
    cout << " 2. Data Supplier" << endl;
    cout << " 3. Kembali" << endl;
    cout << " Pilihan Anda: ";
}
// Fungsi menu transaksi
void tampilMenuTransaksi()
{
    cout << " MENU TRANSAKSI " << endl;
    cout << " 1. Tampilkan Transaksi" << endl;
    cout << " 2. Tambah Barang Masuk" << endl;
    cout << " 3. Tambah Barang Keluar" << endl;
    cout << " 4. Hapus Transaksi" << endl;
    cout << " 5. Kembali" << endl;
    cout << " Pilih : ";
}
// Fungsi menu laporan
void tampilMenuLaporan()
{
    cout << " MENU LAPORAN " << endl;
    cout << " 1. Laporan Barang Masuk" << endl;
    cout << " 2. Laporan Barang Keluar" << endl;
    cout << " 3. Laporan Supplier" << endl;
    cout << " 4. Laporan Gudang" << endl;
    cout << " 5. Kembali" << endl;
    cout << " Pilihan Anda: ";
    cout << endl;
}
// FUNGSI UNTUK BARANG
struct Barang
{
    string kode;
    string nama;
    int jumlah;
    Barang *prev;
    Barang *next;
};

class Inventaris
{
private:
    Barang *head;
    Barang *tail;

public:
    Inventaris() : head(nullptr), tail(nullptr) {}

    ~Inventaris()
    {
        simpan_ke_file();
        while (head != nullptr)
        {
            Barang *helpS = head;
            head = head->next;
            delete helpS;
        }
    }

    void tambah_barang(const string &kode, const string &nama, int jumlah)
    {
        Barang *baru = new Barang;
        baru->kode = kode;
        baru->nama = nama;
        baru->jumlah = jumlah;
        baru->prev = nullptr;
        baru->next = nullptr;

        if (head == nullptr)
        {
            head = baru;
            tail = baru;
        }
        else
        {
            tail->next = baru;
            baru->prev = tail;
            tail = baru;
        }
        simpan_ke_file();
    }

    void tampilkan_inventaris()
    {
        if (head == nullptr)
        {
            cout << "Inventaris kosong" << endl;
        }
        else
        {
            cout << "------------------------------------------------" << endl;
            cout << "|     Kode     |         Nama         | Jumlah |" << endl;
            cout << "------------------------------------------------" << endl;

            Barang *current = head;
            while (current != nullptr)
            {
                cout << "| " << setw(12) << left << current->kode << " | " << setw(20) << left << current->nama << " | " << setw(6) << right << current->jumlah << " |" << endl;
                current = current->next;
            }
            cout << "------------------------------------------------" << endl;
            cout << endl;
        }
    }

    Barang *cari_barang(const string &kode)
    {
        Barang *current = head;
        while (current != nullptr)
        {
            if (current->kode == kode)
            {
                cout << "Barang ditemukan" << endl;
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool hapus_barang(const string &kode)
    {
        Barang *current = head;
        while (current != nullptr)
        {
            if (current->kode == kode)
            {
                if (current == head && current == tail)
                {
                    head = nullptr;
                    tail = nullptr;
                }
                else if (current == head)
                {
                    head = head->next;
                    head->prev = nullptr;
                }
                else if (current == tail)
                {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                simpan_ke_file();
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool cek_ketersediaan_barang(const string &kode)
    {
        Barang *current = head;
        while (current != nullptr)
        {
            if (current->kode == kode && current->jumlah > 0)
            {
                cout << "Barang tersedia sebanyak : " << current->jumlah << endl;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void simpan_ke_file()
    {
        ofstream file("inventaris.txt");
        if (file.is_open())
        {
            Barang *current = head;
            while (current != nullptr)
            {
                file << current->kode << " " << current->nama << " " << current->jumlah << endl;
                current = current->next;
            }
            file.close();
        }
        else
        {
            cout << "Gagal membuka file untuk penyimpanan inventaris." << endl;
        }
    }

    void muat_dari_file()
    {
        ifstream file("inventaris.txt");
        if (file.is_open())
        {
            string kode, nama;
            int jumlah;
            while (file >> kode >> nama >> jumlah)
            {
                tambah_barang(kode, nama, jumlah);
            }
            file.close();
        }
        else
        {
            cout << "Gagal membuka file untuk memuat inventaris." << endl;
        }
    }
};

struct Supplier
{
    int id;
    string nama;
    string alamat;
    Supplier *prev;
    Supplier *next;
};

// FUNGSI UNTUK SUPPLIER
Supplier *dataSupplierHead = nullptr; // Deklarasi variabel global untuk linked list supplier

// Fungsi untuk menambahkan supplier ke linked list
void tambahSupplier(Supplier *&head, Supplier *&tail, int id, string nama, string alamat)
{
    Supplier *baru = new Supplier;
    baru->id = id;
    baru->nama = nama;
    baru->alamat = alamat;
    baru->prev = nullptr;
    baru->next = nullptr;

    if (head == nullptr)
    {
        head = baru;
        tail = baru;
    }
    else
    {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
}

// Fungsi menghapus supplier dari linked list
void hapusSupplier(Supplier *&head, Supplier *&tail, int id)
{
    if (head == nullptr)
    {
        cout << "Data supplier kosong." << endl;
        return;
    }

    Supplier *current = head;
    while (current != nullptr)
    {
        if (current->id == id)
        {
            if (current == head && current == tail)
            {
                head = nullptr;
                tail = nullptr;
            }
            else if (current == head)
            {
                head = head->next;
                head->prev = nullptr;
            }
            else if (current == tail)
            {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            cout << "Supplier berhasil dihapus." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Supplier tidak ditemukan." << endl;
}

// Fungsi untuk menampilkan data supplier dari linked list
void tampilkanDataSupplier(Supplier *head)
{
    if (head == nullptr)
    {
        cout << "Data supplier kosong." << endl;
        return;
    }

    cout << "=== Data Supplier ===" << endl;
    Supplier *temp = head;
    while (temp != nullptr)
    {
        cout << "ID: " << temp->id << endl;
        cout << "Nama: " << temp->nama << endl;
        cout << "Alamat: " << temp->alamat << endl;
        cout << "---------------------------" << endl;
        temp = temp->next;
    }
}

// Fungsi untuk menyimpan data supplier ke dalam file
void simpanDataSupplierKeFile(Supplier *head)
{
    ofstream file("supplier.txt");
    if (file.is_open())
    {
        Supplier *current = head;
        while (current != nullptr)
        {
            file << current->id << " " << current->nama << " " << current->alamat << endl;
            current = current->next;
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file untuk menyimpan data supplier." << endl;
    }
}

// Fungsi untuk memuat data supplier dari file
void muatDataSupplierDariFile(Supplier *&head, Supplier *&tail)
{
    ifstream file("supplier.txt");
    if (file.is_open())
    {
        int id;
        string nama;
        string alamat;
        while (file >> id)
        {
            file.ignore();
            getline(file, nama, ' ');
            getline(file, alamat);
            tambahSupplier(head, tail, id, nama, alamat);
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file untuk memuat data supplier." << endl;
    }
}

//FUNGSI-FUNGSI MENU TRANSAKSI
struct Transaksi
{
    string kodeBarang;
    string namaBarang;
    int jumlah;
    string jenis;
    Transaksi *prev;
    Transaksi *next;
};

struct TransaksiList
{
    Transaksi *head = nullptr;
    Transaksi *tail = nullptr;
};

// Fungsi untuk menambahkan transaksi ke dalam linked list transaksi
void tambahTransaksi(TransaksiList &list, const string &kode, const string &nama, int jumlah, const string &jenis)
{
    Transaksi *baru = new Transaksi{kode, nama, jumlah, jenis, nullptr, nullptr};
    if (list.tail)
    {
        list.tail->next = baru;
        baru->prev = list.tail;
        list.tail = baru;
    }
    else
    {
        list.head = list.tail = baru;
    }
}

// Fungsi untuk menghapus transaksi dari linked list transaksi berdasarkan kode barang
void hapusTransaksi(TransaksiList &list, const string &kode)
{
    Transaksi *current = list.head;
    while (current)
    {
        if (current->kodeBarang == kode)
        {
            if (current->prev)
            {
                current->prev->next = current->next;
            }
            else
            {
                list.head = current->next;
            }
            if (current->next)
            {
                current->next->prev = current->prev;
            }
            else
            {
                list.tail = current->prev;
            }
            delete current;
            cout << "Transaksi dengan kode " << kode << " berhasil dihapus." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Transaksi dengan kode " << kode << " tidak ditemukan." << endl;
}

// Fungsi untuk menampilkan seluruh transaksi yang ada dalam linked list transaksi
void tampilkanTransaksi(const TransaksiList &list)
{
    Transaksi *current = list.head;
    cout << "Data Transaksi:" << endl;
    while (current)
    {
        cout << "| Kode : " << current->kodeBarang << "| Nama : " << current->namaBarang << "| Jumlah: " << current->jumlah << "| Jenis: " << current->jenis << "|" << endl;
        current = current->next;
    }
}

// Fungsi untuk menyimpan data transaksi ke dalam file
void simpanDataTransaksiKeFile(const TransaksiList &list)
{
    ofstream file("transaksi.txt");
    if (file.is_open())
    {
        Transaksi *current = list.head;
        while (current != nullptr)
        {
            file << current->kodeBarang << " " << current->namaBarang << " " << current->jumlah << " " << current->jenis << endl;
            current = current->next;
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file untuk menyimpan data transaksi." << endl;
    }
}

// Fungsi untuk memuat data transaksi dari file
void muatDataTransaksiDariFile(TransaksiList &list)
{
    ifstream file("transaksi.txt");
    if (file.is_open())
    {
        string kodeBarang;
        string namaBarang;
        int jumlah;
        string jenis;
        while (file >> kodeBarang >> namaBarang >> jumlah >> jenis)
        {
            tambahTransaksi(list, kodeBarang, namaBarang, jumlah, jenis);
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file untuk memuat data transaksi." << endl;
    }
}

// FUNGSI-FUNGSI UNTUK MENU LAPORAN
//  Fungsi untuk menampilkan laporan barang masuk
void tampilLaporanBarangMasuk(const TransaksiList &list)
{
    Transaksi *current = list.head;
    cout << "\nLaporan Barang Masuk:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "| Kode Barang | Nama Barang | Jumlah |" << endl;
    cout << "--------------------------------------" << endl;
    while (current)
    {
        if (current->jenis == "masuk")
        {
            cout << "| " << setw(12) << left << current->kodeBarang
                 << "| " << setw(12) << left << current->namaBarang
                 << "| " << setw(6) << right << current->jumlah << " |" << endl;
        }
        current = current->next;
    }
    cout << "--------------------------------------" << endl;
}

// Fungsi untuk menampilkan laporan barang keluar
void tampilLaporanBarangKeluar(const TransaksiList &list)
{
    Transaksi *current = list.head;
    cout << "\nLaporan Barang Keluar:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "| Kode Barang | Nama Barang | Jumlah |" << endl;
    cout << "--------------------------------------" << endl;
    while (current)
    {
        if (current->jenis == "keluar")
        {
            cout << "| " << setw(12) << left << current->kodeBarang
                 << "| " << setw(12) << left << current->namaBarang
                 << "| " << setw(6) << right << current->jumlah << " |" << endl;
        }
        current = current->next;
    }
    cout << "--------------------------------------" << endl;
}

// Fungsi untuk menampilkan laporan supplier
void tampilLaporanSupplier(Supplier *head)
{
    if (head == nullptr)
    {
        cout << "\nData supplier kosong." << endl;
        return;
    }

    cout << "\nLaporan Supplier:" << endl;
    cout << "-------------------------------" << endl;
    cout << "| ID | Nama Supplier | Alamat |" << endl;
    cout << "-------------------------------" << endl;
    Supplier *current = head;
    while (current)
    {
        cout << "| " << setw(3) << left << current->id
             << "| " << setw(14) << left << current->nama
             << "| " << setw(20) << left << current->alamat << " |" << endl;
        current = current->next;
    }
    cout << "-------------------------------" << endl;
}

// Fungsi untuk menampilkan laporan gudang (inventaris barang)
void tampilLaporanGudang(Inventaris &inventaris)
{
    cout << "\nLaporan Gudang:" << endl;
    inventaris.tampilkan_inventaris();
}

int main()
{
    bool keluar = false;

    cout << "\t============================" << endl;
    cout << "\t SELAMAT DATANG DI APLIKASI " << endl;
    cout << "\t INVENTARIS TOKO KELONTONG  " << endl;
    cout << "\t============================" << endl;
    cout << endl;
    const int maxUsers = 2;
    int totalUsers = 2;
    User users[maxUsers] = {
        {"manager", "pass1", "Manager"},
        {"admin", "pass2", "Admin"}};

    string username, password;
    User loggedInUser;

    cout << "Login" << endl;
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    if (login(users, totalUsers, username, password, loggedInUser))
    {
        cout << "Login berhasil" << endl;
        cout << endl;
        cout << "Sebagai : " << loggedInUser.role << endl;
        cout << endl;

        Inventaris inventaris_gudang;
        inventaris_gudang.muat_dari_file();

        Supplier *dataSupplierHead = NULL;
        Supplier *dataSupplierTail = NULL;
        muatDataSupplierDariFile(dataSupplierHead, dataSupplierTail);

        TransaksiList transaksilist;
        muatDataTransaksiDariFile(transaksilist);

        TransaksiList transaksiList = {NULL, NULL};

        int menuM;
        int menuSM;
        int menuLM;
        char kembali1;
        if (loggedInUser.role == "Manager")
        {
            do
            {
                cout << " MENU UTAMA"<<endl;
                cout << "1.Data Supplier" << endl;
                cout << "2.laporan" << endl;
                cout << "3.Log out" << endl;
                cout << "Pilih : ";
                cin >> menuM;
                switch (menuM)
                {
                case 1:
                {
                    cout << endl;
                    cout << "Data Supplier" << endl;
                    tampilkanDataSupplier(dataSupplierHead);
                    cout << endl;
                    cout << "1. Tambah Supplier" << endl;
                    cout << "2. Hapus Supplier" << endl;
                    cout << "3. Kembali" << endl;
                    cout << "Pilih: ";
                    cin >> menuSM;
                    cout << endl;
                    if (menuSM == 1)
                    {
                        int id;
                        string nama, alamat;
                        cout << "Tambah Supplier" << endl;
                        cout << "ID Supplier: ";
                        cin >> id;
                        cout << "Nama Supplier: ";
                        cin >> nama;
                        cout << "Alamat Supplier: ";
                        cin >> alamat;
                        tambahSupplier(dataSupplierHead, dataSupplierTail, id, nama, alamat);
                        cout << "Berhasil ditambahkan." << endl;
                        cout << endl;
                    }
                    else if (menuSM == 2)
                    {
                        int id;
                        cout << "Hapus Supplier" << endl;
                        cout << "Masukkan ID supplier yang ingin dihapus: ";
                        cin >> id;
                        hapusSupplier(dataSupplierHead, dataSupplierTail, id);
                        cout << endl;
                    }
                    else if (menuSM == 3)
                    {
                        simpanDataSupplierKeFile(dataSupplierHead);
                        break; // Kembali to Data Master menu
                    }
                    else
                    {
                        cout << "Pilihan tidak valid" << endl;
                    }
                }

                case 2:
                    while(true){
                    cout<<endl;
                    cout << "Laporan" << endl;
                    tampilMenuLaporan();
                    cin >> menuLM;
                    cout << endl;
                    switch (menuLM)
                    {
                    case 1:
                        tampilLaporanBarangMasuk(transaksiList);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali1;
                        break;
                    case 2:
                        tampilLaporanBarangKeluar(transaksiList);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali1;
                        break;
                    case 3:
                        tampilLaporanSupplier(dataSupplierHead);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali1;
                        break;
                    case 4:
                        tampilLaporanGudang(inventaris_gudang);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali1;
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
                        break;
                    }
                    };

                case 3:
                    keluar = true;
                    cout << "\t============================" << endl;
                    cout << "\t        TERIMAKASIIH        " << endl;
                    cout << "\t   SELAMAT DATANG KEMBALI   " << endl;
                    cout << "\t============================" << endl;
                    break;

                default:
                    cout<<"Pilihan tidak valid"<<endl;
                    break;
                }

            } while (!keluar);
        }
        else if (loggedInUser.role == "Admin")
        {
            do
            {
                int menuU;
                int menuDM;
                int menuDM1;
                int menuL;
                char kembali2;
                tampilMenuUtama();
                cin >> menuU;
                cout << endl;

                switch (menuU)
                {
                case 1:
                    do
                    {
                        tampilMenuDataMaster();
                        cin >> menuDM;
                        switch (menuDM)
                        {
                        case 1:
                            do
                            {
                                cout << endl;
                                cout << "Data barang" << endl;
                                inventaris_gudang.tampilkan_inventaris();
                                cout << endl;
                                cout << "1. Tambah barang" << endl;
                                cout << "2. Hapus Barang" << endl;
                                cout << "3. Cek Stok" << endl;
                                cout << "4. Cari Barang" << endl;
                                cout << "5. Kembali" << endl;
                                cout << "pilih :";
                                cin >> menuDM1;
                                cout << endl;
                                if (menuDM1 == 1)
                                {
                                    string kode, nama;
                                    int jumlah;
                                    cout << "Tambah Barang " << endl;
                                    cout << "Kode barang : ";
                                    cin >> kode;
                                    cout << "Nama barang : ";
                                    cin >> nama;
                                    cout << "Jumlah barang : ";
                                    cin >> jumlah;
                                    inventaris_gudang.tambah_barang(kode, nama, jumlah);
                                    cout << "Berhasil ditambahkan." << endl;
                                    cout << endl;
                                }
                                else if (menuDM1 == 2)
                                {
                                    string kode_barang;
                                    cout << "Hapus Barang" << endl;
                                    cout << "Masukkan kode barang yang ingin dihapus: ";
                                    cin >> kode_barang;
                                    inventaris_gudang.hapus_barang(kode_barang);
                                    cout << "Barang berhasil dihapus." << endl;
                                    cout << endl;
                                }
                                else if (menuDM1 == 3)
                                {
                                    string kode_barang;
                                    cout << "Masukkan kode barang yang ingin dicek : ";
                                    cin >> kode_barang;
                                    cout << endl;
                                    if (inventaris_gudang.cek_ketersediaan_barang(kode_barang))
                                    {
                                        cout << "Barang tersedia." << endl;
                                    }
                                    else
                                    {
                                        cout << "Barang tidak tersedia atau stok kosong." << endl;
                                    }
                                    cout << endl;
                                }
                                else if (menuDM1 == 4)
                                {
                                    string cari_kode;
                                    cout << "Masukkan kode barang yang dicari: ";
                                    cin >> cari_kode;
                                    cout << endl;

                                    Barang *hasil_cari = inventaris_gudang.cari_barang(cari_kode);
                                    if (hasil_cari != nullptr)
                                    {
                                        cout << "Kode Barang: " << hasil_cari->kode << endl;
                                        cout << "Nama Barang: " << hasil_cari->nama << endl;
                                        cout << "Jumlah Barang: " << hasil_cari->jumlah << endl;
                                    }
                                    else
                                    {
                                        cout << "Barang tidak ditemukan." << endl;
                                    }
                                    cout << endl;
                                }
                                else if (menuDM1 == 5)
                                {
                                    break; // Kembali to Data Master menu
                                }
                                else
                                {
                                    cout << "pilihan tidak valid" << endl;
                                }
                            } while (menuDM1 != 5);
                            break;
                        case 2:
                            while (true)
                            {
                                cout << endl;
                                cout << "Data Supplier" << endl;
                                tampilkanDataSupplier(dataSupplierHead);
                                cout << endl;
                                cout << "1. Tambah Supplier" << endl;
                                cout << "2. Hapus Supplier" << endl;
                                cout << "3. Kembali" << endl;
                                cout << "Pilih: ";
                                cin >> menuDM;
                                cout << endl;
                                if (menuDM == 1)
                                {
                                    int id;
                                    string nama, alamat;
                                    cout << "Tambah Supplier" << endl;
                                    cout << "ID Supplier: ";
                                    cin >> id;
                                    cout << "Nama Supplier: ";
                                    cin >> nama;
                                    cout << "Alamat Supplier: ";
                                    cin >> alamat;
                                    tambahSupplier(dataSupplierHead, dataSupplierTail, id, nama, alamat);
                                    cout << "Berhasil ditambahkan." << endl;
                                    cout << endl;
                                }
                                else if (menuDM == 2)
                                {
                                    int id;
                                    cout << "Hapus Supplier" << endl;
                                    cout << "Masukkan ID supplier yang ingin dihapus: ";
                                    cin >> id;
                                    hapusSupplier(dataSupplierHead, dataSupplierTail, id);
                                    cout << endl;
                                }
                                else if (menuDM == 3)
                                {
                                    simpanDataSupplierKeFile(dataSupplierHead);
                                    break; // Kembali to Data Master menu
                                }
                                else
                                {
                                    cout << "Pilihan tidak valid" << endl;
                                }
                            }
                            break;
                        case 3:
                            break; // Kembali to Main menu
                        default:
                            cout << "Pilihan tidak valid" << endl;
                            break;
                        }
                    } while (menuDM != 3);
                    break;

                case 2:{
                    int menuTr;
                    do
                    {
                        tampilMenuTransaksi();
                        cin >> menuTr;
                        cout << endl;
                        switch (menuTr)
                        {
                        case 1:
                            tampilkanTransaksi(transaksiList);
                            cout << endl;
                            break;
                        case 2:
                        {
                            string kode;
                            string nama;
                            int jumlah;
                            cout << "Tambah Barang Masuk" << endl;
                            cout << "Kode barang : ";
                            cin >> kode;
                            cout << "Nama barang : ";
                            cin >> nama;
                            cout << "Jumlah barang : ";
                            cin >> jumlah;
                            tambahTransaksi(transaksiList, kode, nama, jumlah, "masuk");
                            cout << "Transaksi Barang masuk berhasil ditambahkan." << endl;
                            simpanDataTransaksiKeFile(transaksiList);
                            cout << endl;
                            break;
                        }
                        case 3:
                        {
                            string kode;
                            string nama;
                            int jumlah;
                            cout << "Tambah Barang Keluar" << endl;
                            cout << "Kode barang : ";
                            cin >> kode;
                            cout << "Nama barang : ";
                            cin >> nama;
                            cout << "Jumlah barang : ";
                            cin >> jumlah;
                            tambahTransaksi(transaksiList, kode, nama, jumlah, "keluar");
                            cout << "Transaksi barang keluar berhasil ditambahkan." << endl;
                            simpanDataTransaksiKeFile(transaksiList);
                            cout << endl;
                            break;
                        }
                        case 4:
                        {
                            string kode;
                            cout << "Hapus Transaksi" << endl;
                            cout << "Kode barang : ";
                            cin >> kode;
                            hapusTransaksi(transaksiList, kode);
                            cout << endl;
                            break;
                        }
                        case 5:
                            break; // Kembali to Main menu
                        default:
                            cout << "Pilihan tidak valid" << endl;
                            break;
                        }
                    } while (menuTr != 5);
                    break;
                }
                case 3:
                {
                    cout << "Laporan" << endl;
                    tampilMenuLaporan();
                    cin >> menuL;
                    cout << endl;
                    switch (menuL)
                    {
                    case 1:
                        tampilLaporanBarangMasuk(transaksiList);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali2;
                        break;
                    case 2:
                        tampilLaporanBarangKeluar(transaksiList);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali2;
                        break;
                    case 3:
                        tampilLaporanSupplier(dataSupplierHead);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali2;
                        break;
                    case 4:
                        tampilLaporanGudang(inventaris_gudang);
                        cout << endl;
                        cout << "Kembali ? : ";
                        cin >> kembali2;
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
                        break;
                    }
                    break;
                }
                case 4:
                {
                    keluar = true;
                    cout << "\t============================" << endl;
                    cout << "\t        TERIMAKASIIH        " << endl;
                    cout << "\t   SELAMAT DATANG KEMBALI   " << endl;
                    cout << "\t============================" << endl;
                    break;
                }
                default:
                    cout << "Pilihan tidak valid" << endl;
                    break;
                }
            } while (!keluar);
        }
    }
    else
    {
        cout << "Gagal login, silakan coba lagi." << endl;
    }

    return 0;
    
}
