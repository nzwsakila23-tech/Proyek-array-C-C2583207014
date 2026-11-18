# Proyek Sistem Monitoring Stok dan Penjualan Kantin Kampus

# Identitas Mahasiswa
- Nama: Nazwa Sakila Nur'ajijah
- NIM: C2583207014
- Kelas: PTI 3B 
- Program Studi: Pendidikan Teknologi Informasi
- Mata Kuliah: Algoritma dan Pemrograman Lanjutan
- Dosen Pengampu: Taofik Muhammad, M.Kom

# Deskripsi
Aplikasi console berbasis bahasa C untuk mengelola produk kantin kampus, stok, transaksi beberapa produk, pencarian, pengurutan, dan laporan penjualan. Data disimpan di memori selama program berjalan; aplikasi tidak menggunakan database atau file eksternal.

# Fitur
1. Melihat daftar produk.
2. Menambah produk (maksimal 50 produk).
3. Mengubah harga dan stok.
4. Transaksi beberapa produk dalam satu pembelian.
5. Menambah stok.
6. Mencari produk berdasarkan nama (tidak membedakan kapital).
7. Mengurutkan harga dari termurah dan jumlah terjual dari terbanyak.
8. Laporan unit terjual, pendapatan, dan produk terlaris.
9. Peringatan stok kurang dari 5.
10. Validasi input dan penanganan kesalahan.

# Penerapan Array
Program menggunakan array paralel sebagai struktur data utama:
- char namaProduk[50][50]: array karakter dua dimensi untuk nama produk.
- long long hargaProduk[50]: array satu dimensi untuk harga.
- int stokProduk[50]: array satu dimensi untuk stok.
- int terjualProduk[50]: array satu dimensi untuk jumlah unit terjual.
- long long pendapatanProduk[50]: array satu dimensi untuk akumulasi pendapatan per produk.
Indeks yang sama pada seluruh array mewakili satu produk. Ketika pengurutan dilakukan, semua atribut pada indeks yang dibandingkan ikut ditukar agar hubungan data tetap benar.

# Fungsi Utama
- inisialisasiDataAwal(): memasukkan lima produk awal.
- tampilkanProduk(): menampilkan seluruh data produk.
- tambahProduk(): menambah produk baru.
- ubahProduk(): mengubah harga dan stok.
- transaksiPenjualan(): memproses beberapa produk dalam satu transaksi dan memperbarui stok setelah transaksi dikonfirmasi.
- tambahStok(): menambah stok produk.
- cariProduk(): mencari nama produk.
- urutkanHarga() dan urutkanTerjual(): mengurutkan produk dengan bubble sort.
- laporanPenjualan(): menghitung total unit, total pendapatan, dan produk terlaris.
- cekStokMenipis(): menampilkan produk dengan stok kurang dari 5.

# Cara Kompilasi
Pastikan GCC sudah terpasang. Buka terminal pada folder proyek, lalu jalankan:
gcc -std=c99 -Wall -Wextra -pedantic main.c -o kantin
Cara Menjalankan
Linux/macOS:
./kantin
Windows (MinGW):
kantin.exe

# 1. Tambah Produk
   <img width="1366" height="768" alt="Screenshot (88)" src="https://github.com/user-attachments/assets/2023cd9e-c727-4a4b-a39c-888cd2c62a43" />
   
# 2. Transaksi Beberapa Produk
   <img width="1366" height="768" alt="Screenshot (89)" src="https://github.com/user-attachments/assets/14ed7237-5022-4556-b9e6-77182a42f19a" />
   <img width="1366" height="768" alt="Screenshot (90)" src="https://github.com/user-attachments/assets/fc7b98ba-d0e4-4623-81b1-3ffda6f04fc6" />
   
# 3. Pembaharuan Stok
   <img width="1366" height="768" alt="Screenshot (91)" src="https://github.com/user-attachments/assets/e82543ce-7a38-4c48-877e-2195f96173a5" />
   
# 4. Stok Tidak Cukup
   <img width="1366" height="768" alt="Screenshot (92)" src="https://github.com/user-attachments/assets/3deda18c-4287-4793-9d06-bd9187f39067" />
   
# 5. Laporan Penjualan
   <img width="1366" height="768" alt="Screenshot (93)" src="https://github.com/user-attachments/assets/62f99de6-c806-457e-988c-c46171de675a" />
   
# 6. Pengurutan
   <img width="1366" height="768" alt="Screenshot (94)" src="https://github.com/user-attachments/assets/0276f241-3806-45e8-9bd3-8790a904b6d7" />
   <img width="1366" height="768" alt="Screenshot (95)" src="https://github.com/user-attachments/assets/c9f4378a-eb42-4901-a276-6ec2df1dcf84" />
   
# 7. Pencarian dan Stok Menipis
   <img width="1366" height="768" alt="Screenshot (96)" src="https://github.com/user-attachments/assets/e41ece34-61cc-4c9b-9314-139176bd7397" />

