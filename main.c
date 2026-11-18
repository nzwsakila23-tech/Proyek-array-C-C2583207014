#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define MAKS_PRODUK 50
#define PANJANG_NAMA 50
#define JUMLAH_DATA_AWAL 5

char namaProduk[MAKS_PRODUK][PANJANG_NAMA];
long long hargaProduk[MAKS_PRODUK];
int stokProduk[MAKS_PRODUK];
int terjualProduk[MAKS_PRODUK];
long long pendapatanProduk[MAKS_PRODUK];

int jumlahProduk = 0;

/* Membaca satu baris input dan membuang karakter newline. */
void bacaBaris(const char *pesan, char *buffer, size_t ukuran) {
    printf("%s", pesan);
    if (fgets(buffer, (int)ukuran, stdin) == NULL) {
        printf("\nInput berakhir. Program dihentikan.\n");
        exit(EXIT_SUCCESS);
    }

    size_t panjang = strlen(buffer);
    if (panjang > 0 && buffer[panjang - 1] == '\n') {
        buffer[panjang - 1] = '\0';
    } else {
        int karakter;
        while ((karakter = getchar()) != '\n' && karakter != EOF) {
            /* Menghabiskan sisa input yang terlalu panjang. */
        }
    }
}

/* Membaca bilangan bulat dengan validasi. */
long long bacaAngka(const char *pesan, long long minimum, long long maksimum) {
    char buffer[128];
    char *akhir;
    long long nilai;

    while (1) {
        bacaBaris(pesan, buffer, sizeof(buffer));
        errno = 0;
        nilai = strtoll(buffer, &akhir, 10);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (buffer[0] != '\0' && *akhir == '\0' && errno != ERANGE &&
            nilai >= minimum && nilai <= maksimum) {
            return nilai;
        }

        printf("Input tidak valid. Masukkan angka antara %lld dan %lld.\n",
               minimum, maksimum);
    }
}

/* Membaca nama produk yang tidak boleh kosong. */
void bacaNama(const char *pesan, char *nama, size_t ukuran) {
    while (1) {
        bacaBaris(pesan, nama, ukuran);
        if (strlen(nama) == 0) {
            printf("Nama produk tidak boleh kosong.\n");
        } else {
            return;
        }
    }
}

/* Membandingkan teks tanpa membedakan huruf besar/kecil. */
int samaTanpaKapital(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

/* Mengisi lima produk awal sesuai ketentuan proyek. */
void inisialisasiDataAwal(void) {
    const char *namaAwal[JUMLAH_DATA_AWAL] = {
        "Nasi Goreng", "Mie Goreng", "Roti Bakar", "Air Mineral", "Es Teh"
    };
    const long long hargaAwal[JUMLAH_DATA_AWAL] = {
        15000, 13000, 10000, 4000, 5000
    };
    const int stokAwal[JUMLAH_DATA_AWAL] = {20, 18, 15, 40, 30};

    for (int i = 0; i < JUMLAH_DATA_AWAL; i++) {
        strcpy(namaProduk[i], namaAwal[i]);
        hargaProduk[i] = hargaAwal[i];
        stokProduk[i] = stokAwal[i];
        terjualProduk[i] = 0;
        pendapatanProduk[i] = 0;
    }
    jumlahProduk = JUMLAH_DATA_AWAL;
}

void garis(void) {
    printf("--------------------------------------------------------------------------------\n");
}

void tampilkanMenu(void) {
    garis();
    printf("             SISTEM MONITORING STOK DAN PENJUALAN KANTIN KAMPUS\n");
    garis();
    printf("1. Lihat Daftar Produk\n");
    printf("2. Tambah Produk\n");
    printf("3. Ubah Produk\n");
    printf("4. Transaksi Penjualan\n");
    printf("5. Tambah Stok\n");
    printf("6. Cari Produk\n");
    printf("7. Urutkan Produk\n");
    printf("8. Laporan Penjualan\n");
    printf("9. Cek Stok Menipis\n");
    printf("0. Keluar\n");
    garis();
}

void tampilkanProduk(void) {
    if (jumlahProduk == 0) {
        printf("Belum ada data produk.\n");
        return;
    }

    garis();
    printf("%-5s %-25s %-15s %-10s %-12s\n",
           "No.", "Nama Produk", "Harga (Rp)", "Stok", "Terjual");
    garis();

    for (int i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-25s %-15lld %-10d %-12d\n",
               i + 1, namaProduk[i], hargaProduk[i],
               stokProduk[i], terjualProduk[i]);
    }
    garis();
}

/* Mengembalikan indeks produk berdasarkan nomor yang dimasukkan. */
int pilihProduk(void) {
    if (jumlahProduk == 0) {
        printf("Belum ada produk yang tersedia.\n");
        return -1;
    }

    tampilkanProduk();
    int nomor = (int)bacaAngka("Masukkan nomor produk: ", 1, jumlahProduk);
    return nomor - 1;
}

void tambahProduk(void) {
    if (jumlahProduk >= MAKS_PRODUK) {
        printf("Kapasitas produk sudah penuh (maksimal %d produk).\n", MAKS_PRODUK);
        return;
    }

    char nama[PANJANG_NAMA];
    bacaNama("Masukkan nama produk: ", nama, sizeof(nama));

    for (int i = 0; i < jumlahProduk; i++) {
        if (samaTanpaKapital(namaProduk[i], nama)) {
            printf("Produk dengan nama tersebut sudah tersedia.\n");
            return;
        }
    }

    long long harga = bacaAngka("Masukkan harga produk (Rp): ", 0,  LLONG_MAX);
    int stok = (int)bacaAngka("Masukkan stok awal: ", 0, 2147483647);

    strcpy(namaProduk[jumlahProduk], nama);
    hargaProduk[jumlahProduk] = harga;
    stokProduk[jumlahProduk] = stok;
    terjualProduk[jumlahProduk] = 0;
    pendapatanProduk[jumlahProduk] = 0;
    jumlahProduk++;

    printf("Produk berhasil ditambahkan.\n");
}

void ubahProduk(void) {
    int indeks = pilihProduk();
    if (indeks == -1) return;

    printf("Mengubah data: %s\n", namaProduk[indeks]);
    long long harga = bacaAngka("Masukkan harga baru (Rp): ", 0, LLONG_MAX);
    int stok = (int)bacaAngka("Masukkan stok baru: ", 0, 2147483647);

    hargaProduk[indeks] = harga;
    stokProduk[indeks] = stok;
    printf("Harga dan stok produk berhasil diperbarui.\n");
}

/*
 * Transaksi menggunakan array sementara jumlahPesan.
 * Stok dan data penjualan baru diperbarui setelah transaksi dikonfirmasi,
 * sehingga transaksi yang dibatalkan/tidak valid tidak mengubah data.
 */
void transaksiPenjualan(void) {
    int jumlahPesan[MAKS_PRODUK] = {0};
    int adaPesanan = 0;

    if (jumlahProduk == 0) {
        printf("Belum ada produk untuk dijual.\n");
        return;
    }

    printf("\n=== TRANSAKSI PENJUALAN ===\n");
    printf("Masukkan nomor produk dan jumlah pembelian. Masukkan 0 untuk selesai.\n");

    while (1) {
        tampilkanProduk();
        int nomor = (int)bacaAngka("Nomor produk (0 untuk selesai): ", 0, jumlahProduk);
        if (nomor == 0) break;

        int indeks = nomor - 1;
        int sisaStok = stokProduk[indeks] - jumlahPesan[indeks];

        if (sisaStok <= 0) {
            printf("Stok %s sudah tidak mencukupi untuk ditambahkan ke transaksi.\n",
                   namaProduk[indeks]);
            continue;
        }

        char pesan[120];
        snprintf(pesan, sizeof(pesan), "Jumlah %s (tersedia %d): ",
                 namaProduk[indeks], sisaStok);
        int jumlah = (int)bacaAngka(pesan, 1, 2147483647);

        if (jumlah > sisaStok) {
            printf("Pembelian ditolak. Stok tersedia hanya %d.\n", sisaStok);
            continue;
        }

        if (jumlahPesan[indeks] > 2147483647 - jumlah) {
            printf("Jumlah pembelian terlalu besar.\n");
            continue;
        }

        jumlahPesan[indeks] += jumlah;
        adaPesanan = 1;
        printf("%d %s ditambahkan ke keranjang.\n", jumlah, namaProduk[indeks]);

        long long lanjut = bacaAngka("Tambah produk lain? (1=Ya, 0=Tidak): ", 0, 1);
        if (lanjut == 0) break;
    }

    if (!adaPesanan) {
        printf("Transaksi dibatalkan karena tidak ada produk yang dipesan.\n");
        return;
    }

    long long total = 0;
    printf("\n================ STRUK PEMBELIAN ================\n");
    printf("%-25s %-8s %-15s %-15s\n", "Produk", "Jumlah", "Harga", "Subtotal");
    garis();

    for (int i = 0; i < jumlahProduk; i++) {
        if (jumlahPesan[i] > 0) {
            long long subtotal = hargaProduk[i] * jumlahPesan[i];
            printf("%-25s %-8d %-15lld %-15lld\n",
                   namaProduk[i], jumlahPesan[i], hargaProduk[i], subtotal);
            total += subtotal;
        }
    }
    garis();
    printf("TOTAL PEMBAYARAN: Rp %lld\n", total);

    long long konfirmasi = bacaAngka("Konfirmasi transaksi? (1=Ya, 0=Batalkan): ", 0, 1);
    if (konfirmasi == 0) {
        printf("Transaksi dibatalkan. Stok tidak berubah.\n");
        return;
    }

    for (int i = 0; i < jumlahProduk; i++) {
        if (jumlahPesan[i] > 0) {
            long long subtotal = hargaProduk[i] * jumlahPesan[i];
            stokProduk[i] -= jumlahPesan[i];
            terjualProduk[i] += jumlahPesan[i];
            pendapatanProduk[i] += subtotal;
        }
    }

    printf("Transaksi berhasil. Stok dan laporan penjualan telah diperbarui.\n");
}

void tambahStok(void) {
    int indeks = pilihProduk();
    if (indeks == -1) return;

    int tambahan = (int)bacaAngka("Masukkan jumlah stok tambahan: ", 1, 2147483647);
    if (stokProduk[indeks] > 2147483647 - tambahan) {
        printf("Penambahan ditolak karena melebihi batas penyimpanan stok.\n");
        return;
    }

    stokProduk[indeks] += tambahan;
    printf("Stok %s berhasil ditambah. Stok sekarang: %d.\n",
           namaProduk[indeks], stokProduk[indeks]);
}

void cariProduk(void) {
    char kataKunci[PANJANG_NAMA];
    bacaNama("Masukkan nama produk yang dicari: ", kataKunci, sizeof(kataKunci));

    int ditemukan = 0;
    for (int i = 0; i < jumlahProduk; i++) {
        if (samaTanpaKapital(namaProduk[i], kataKunci)) {
            printf("\nProduk ditemukan:\n");
            printf("Nama   : %s\n", namaProduk[i]);
            printf("Harga  : Rp %lld\n", hargaProduk[i]);
            printf("Stok   : %d\n", stokProduk[i]);
            printf("Terjual: %d\n", terjualProduk[i]);
            ditemukan = 1;
            break;
        }
    }

    if (!ditemukan) {
        printf("Produk '%s' tidak ditemukan.\n", kataKunci);
    }
}

/* Menukar seluruh atribut pada dua indeks agar data tetap konsisten. */
void tukarProduk(int a, int b) {
    char namaSementara[PANJANG_NAMA];
    long long angkaSementara;
    int intSementara;

    strcpy(namaSementara, namaProduk[a]);
    strcpy(namaProduk[a], namaProduk[b]);
    strcpy(namaProduk[b], namaSementara);

    angkaSementara = hargaProduk[a];
    hargaProduk[a] = hargaProduk[b];
    hargaProduk[b] = angkaSementara;

    intSementara = stokProduk[a];
    stokProduk[a] = stokProduk[b];
    stokProduk[b] = intSementara;

    intSementara = terjualProduk[a];
    terjualProduk[a] = terjualProduk[b];
    terjualProduk[b] = intSementara;

    angkaSementara = pendapatanProduk[a];
    pendapatanProduk[a] = pendapatanProduk[b];
    pendapatanProduk[b] = angkaSementara;
}

void urutkanHarga(void) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (hargaProduk[j] > hargaProduk[j + 1]) {
                tukarProduk(j, j + 1);
            }
        }
    }
    printf("Produk berhasil diurutkan berdasarkan harga termurah.\n");
    tampilkanProduk();
}

void urutkanTerjual(void) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (terjualProduk[j] < terjualProduk[j + 1]) {
                tukarProduk(j, j + 1);
            }
        }
    }
    printf("Produk berhasil diurutkan berdasarkan jumlah terjual terbanyak.\n");
    tampilkanProduk();
}

void menuPengurutan(void) {
    printf("\n=== MENU PENGURUTAN ===\n");
    printf("1. Berdasarkan harga termurah\n");
    printf("2. Berdasarkan jumlah terjual terbanyak\n");
    int pilihan = (int)bacaAngka("Pilih pengurutan: ", 1, 2);

    if (pilihan == 1) {
        urutkanHarga();
    } else {
        urutkanTerjual();
    }
}

void laporanPenjualan(void) {
    long long totalPendapatan = 0;
    long long totalUnit = 0;
    int indeksTerlaris = -1;

    printf("\n================ LAPORAN PENJUALAN ================\n");
    printf("%-5s %-25s %-12s %-20s\n",
           "No.", "Nama Produk", "Terjual", "Pendapatan (Rp)");
    garis();

    for (int i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-25s %-12d %-20lld\n",
               i + 1, namaProduk[i], terjualProduk[i], pendapatanProduk[i]);
        totalUnit += terjualProduk[i];
        totalPendapatan += pendapatanProduk[i];

        if (indeksTerlaris == -1 ||
            terjualProduk[i] > terjualProduk[indeksTerlaris]) {
            indeksTerlaris = i;
        }
    }

    garis();
    printf("Total unit terjual : %lld\n", totalUnit);
    printf("Total pendapatan   : Rp %lld\n", totalPendapatan);

    if (indeksTerlaris != -1 && totalUnit > 0) {
        printf("Produk terlaris    : %s (%d unit)\n",
               namaProduk[indeksTerlaris], terjualProduk[indeksTerlaris]);
    } else {
        printf("Produk terlaris    : Belum ada penjualan.\n");
    }
    garis();
}

void cekStokMenipis(void) {
    int ditemukan = 0;
    printf("\n========== PERINGATAN STOK MENIPIS (STOK < 5) ==========\n");
    printf("%-5s %-25s %-10s\n", "No.", "Nama Produk", "Stok");
    garis();

    for (int i = 0; i < jumlahProduk; i++) {
        if (stokProduk[i] < 5) {
            printf("%-5d %-25s %-10d\n", i + 1, namaProduk[i], stokProduk[i]);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Tidak ada produk dengan stok kurang dari 5.\n");
    }
    garis();
}

int main(void) {
    inisialisasiDataAwal();

    int pilihan;
    do {
        tampilkanMenu();
        pilihan = (int)bacaAngka("Pilih menu: ", 0, 9);

        switch (pilihan) {
            case 1: tampilkanProduk(); break;
            case 2: tambahProduk(); break;
            case 3: ubahProduk(); break;
            case 4: transaksiPenjualan(); break;
            case 5: tambahStok(); break;
            case 6: cariProduk(); break;
            case 7: menuPengurutan(); break;
            case 8: laporanPenjualan(); break;
            case 9: cekStokMenipis(); break;
            case 0: printf("Terima kasih telah menggunakan aplikasi kantin kampus.\n"); break;
            default: printf("Pilihan menu tidak tersedia.\n"); break;
        }

        if (pilihan != 0) {
            char jeda[8];
            bacaBaris("\nTekan Enter untuk kembali ke menu utama...", jeda, sizeof(jeda));
        }
    } while (pilihan != 0);

    return 0;
}
