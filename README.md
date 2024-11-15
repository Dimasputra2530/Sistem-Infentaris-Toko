# Sistem-Infentaris-Toko
prototype
Deskripsi Proyek
Program ini adalah Sistem Manajemen Inventaris yang dirancang untuk menangani operasi dasar seperti mengelola data, melakukan transaksi, dan membuat laporan. Sistem ini menggunakan antarmuka berbasis menu sederhana untuk berinteraksi dengan pengguna. Sistem ini mencakup fungsi login untuk membatasi akses berdasarkan peran pengguna.

Fitur
1. Sistem Login
- Memungkinkan pengguna untuk login menggunakan nama pengguna dan kata sandi mereka.
- Membatasi akses berdasarkan pengguna yang diautentikasi.

2. Menu Utama
- Menyediakan opsi untuk mengakses:
- Master Data
- Transaksi
- Laporan
- Keluar

3. Menu Master Data
- Opsi meliputi:
- Mengelola data item
- Mengelola data pemasok
- Kembali ke menu utama

4. Menu Transaksi
- Fitur meliputi:
- Menampilkan transaksi
- Menambahkan item masuk
- Menambahkan item keluar
- Menghapus transaksi
- Kembali ke menu utama

5. Menu Laporan
- Membuat laporan untuk:
- Item masuk
- Item keluar
- Pemasok
- Status gudang
- Kembali ke menu utama

Struktur Berkas
- main.cpp: Berisi logika program utama.
- Pengguna: Struktur yang mendefinisikan properti pengguna (nama pengguna, kata sandi, peran).

Cara Menjalankan Program
1. Kompilasi program:
g++ -o inventory_management main.cpp

2. Jalankan program:
./inventory_management

## Peran Pengguna
Pengguna dikelola melalui struktur Pengguna, yang meliputi:
- Nama Pengguna
- Kata Sandi
- Peran

Petunjuk Penggunaan
1. Login:
- Masukkan nama pengguna dan kata sandi yang valid untuk mengakses sistem.
- 
2. Menu Utama:
- Pilih dari opsi berikut:
- 1: Akses menu Master Data.
- 2: Akses menu Transaksi.
- 3: Akses menu Laporan.
- 4: Keluar dari sistem.

3. Submenu:
- Ikuti perintah untuk menjalankan tindakan di setiap submenu.

4. Logout:
- Kembali ke layar login dengan memilih Logout.

Peningkatan di Masa Mendatang
- Integrasi Basis Data: Menyimpan data secara terus-menerus dalam basis data.
- Manajemen Peran Pengguna: Menerapkan kontrol akses berbasis peran.
- Penanganan Kesalahan: Meningkatkan validasi dan pesan kesalahan.
- Operasi Berkas: Menambahkan opsi untuk menyimpan dan memuat data dari berkas.

Kontribusi
Jangan ragu untuk melakukan forking repositori dan mengirimkan permintaan tarik untuk peningkatan atau perbaikan bug.
