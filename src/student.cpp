// =============================================================================
// student.cpp — Implementasi Mahasiswa
// Pertemuan 8: Binary Search Tree
// =============================================================================
// FILE YANG BOLEH DIEDIT      : src/student.cpp
// FILE YANG TIDAK BOLEH DIEDIT: src/student.h, tests/checker.cpp, tests/report.h

#include "student.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// =============================================================================
// SUDAH DISEDIAKAN — TIDAK DINILAI, TIDAK PERLU DIUBAH
// =============================================================================
void inorder(const Node* root) {
    if (root == nullptr) return;

    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

void clear(Node*& root) {
    if (root == nullptr) return;

    clear(root->left);
    clear(root->right);

    delete root;
    root = nullptr;
}
// =============================================================================

// =============================================================================
// SOAL 1a — insert (20 poin)
// =============================================================================

bool insert(Node*& root, int nilai) {

    // Jika posisi kosong, buat node baru
    if (root == nullptr) {
        root = new Node;
        root->data = nilai;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }

    // Tolak nilai duplikat
    if (nilai == root->data) {
        return false;
    }

    // Jika lebih kecil, masukkan ke kiri
    if (nilai < root->data) {
        return insert(root->left, nilai);
    }

    // Jika lebih besar, masukkan ke kanan
    return insert(root->right, nilai);
}

// =============================================================================
// SOAL 1b — cari (15 poin)
// =============================================================================

const Node* cari(const Node* root, int nilai) {

    // Jika kosong, nilai tidak ditemukan
    if (root == nullptr) {
        return nullptr;
    }

    // Jika nilai ditemukan
    if (nilai == root->data) {
        return root;
    }

    // Jika lebih kecil, cari ke kiri
    if (nilai < root->data) {
        return cari(root->left, nilai);
    }

    // Jika lebih besar, cari ke kanan
    return cari(root->right, nilai);
}

// =============================================================================
// SOAL 2a — minimum (10 poin)
// =============================================================================

const Node* minimum(const Node* root) {

    // Jika tree kosong
    if (root == nullptr) {
        return nullptr;
    }

    // Cari node paling kiri
    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}

// =============================================================================
// SOAL 2b — hapus (30 poin)
// =============================================================================

bool hapus(Node*& root, int nilai) {

    // Jika tree kosong atau nilai tidak ditemukan
    if (root == nullptr) {
        return false;
    }

    // Cari nilai pada cabang kiri
    if (nilai < root->data) {
        return hapus(root->left, nilai);
    }

    // Cari nilai pada cabang kanan
    if (nilai > root->data) {
        return hapus(root->right, nilai);
    }

    // Jika sudah ditemukan, lakukan penghapusan

    // KEADAAN 1: Node tidak memiliki anak
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        return true;
    }

    // KEADAAN 2: Node hanya memiliki anak kanan
    if (root->left == nullptr) {
        Node* temp = root;
        root = root->right;
        delete temp;
        return true;
    }

    // KEADAAN 2: Node hanya memiliki anak kiri
    if (root->right == nullptr) {
        Node* temp = root;
        root = root->left;
        delete temp;
        return true;
    }

    // KEADAAN 3: Node memiliki dua anak
    // Cari nilai terkecil pada subtree kanan
    const Node* successor = minimum(root->right);

    // Salin nilai successor ke node yang akan dihapus
    root->data = successor->data;

    // Hapus node successor dari subtree kanan
    return hapus(root->right, successor->data);
}

// =============================================================================
// SOAL 3 — termahalTerbeli (25 poin)
// =============================================================================

const Node* termahalTerbeli(const Node* root, int uang) {

    // Jika tree kosong
    if (root == nullptr) {
        return nullptr;
    }

    const Node* hasil = nullptr;

    // Selama masih ada node
    while (root != nullptr) {

        // Jika harga sama dengan uang atau lebih murah
        if (root->data <= uang) {

            // Simpan sebagai kandidat jawaban
            hasil = root;

            // Cari harga yang lebih mahal di cabang kanan
            root = root->right;
        }

        // Jika harga terlalu mahal
        else {

            // Cari harga yang lebih murah di cabang kiri
            root = root->left;
        }
    }

    return hasil;
}

// =============================================================================
// MAIN() — PROGRAM PENGUJIAN (TIDAK DINILAI)
// =============================================================================

#ifndef ADA_MAIN_LAIN

static ostream& baris(const string& label) {
    return cout << "    " << left << setw(22) << label << ": ";
}

static const char* benarSalah(bool nilai) {
    return nilai ? "true" : "false";
}

static void tampilkanNode(const string& label, const Node* n) {
    baris(label);
    if (n == nullptr) cout << "(tidak ada)\n";
    else cout << n->data << "\n";
}

static void tampilkanIsi(const string& label, const Node* root) {
    baris(label);
    inorder(root);
    cout << "\n";
}

int main() {
    cout << "==========================================\n";
    cout << " Latihan — Binary Search Tree\n";
    cout << "==========================================\n";

    cout << "\n[1] Soal 1a — insert()\n";

    Node* root = nullptr;
    const int masuk[] = {50, 30, 70, 20, 40, 60, 80};

    for (int i = 0; i < 7; ++i) {
        insert(root, masuk[i]);
    }

    tampilkanIsi("inorder", root);

    cout << "\n[2] Soal 1a — menolak duplikat\n";
    baris("insert 55") << benarSalah(insert(root, 55)) << "\n";
    baris("insert 40") << benarSalah(insert(root, 40)) << "\n";
    tampilkanIsi("inorder", root);

    cout << "\n[3] Soal 1b — cari()\n";
    tampilkanNode("cari 60", cari(root, 60));
    tampilkanNode("cari 20", cari(root, 20));
    tampilkanNode("cari 25", cari(root, 25));
    tampilkanNode("tree kosong", cari(nullptr, 10));

    cout << "\n[4] Soal 2a — minimum()\n";
    tampilkanNode("minimum seluruh tree", minimum(root));
    if (root != nullptr) {
        tampilkanNode("minimum subtree kanan", minimum(root->right));
    }
    tampilkanNode("tree kosong", minimum(nullptr));

    cout << "\n[5] Soal 3 — termahalTerbeli()\n";
    tampilkanNode("uang 65", termahalTerbeli(root, 65));
    tampilkanNode("uang 30", termahalTerbeli(root, 30));
    tampilkanNode("uang 45", termahalTerbeli(root, 45));
    tampilkanNode("uang 99", termahalTerbeli(root, 99));
    tampilkanNode("uang 15", termahalTerbeli(root, 15));

    cout << "\n[6] Soal 2b — hapus()\n";

    baris("hapus 20") << benarSalah(hapus(root, 20)) << "\n";
    tampilkanIsi("inorder", root);

    baris("hapus 60") << benarSalah(hapus(root, 60)) << "\n";
    tampilkanIsi("inorder", root);

    baris("hapus 50") << benarSalah(hapus(root, 50)) << "\n";
    tampilkanIsi("inorder", root);

    baris("hapus 25") << benarSalah(hapus(root, 25)) << "\n";
    tampilkanIsi("inorder", root);

    clear(root);

    return 0;
}
#endif
