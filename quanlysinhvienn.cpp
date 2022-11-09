#include <iostream>
#include <string>
using namespace std;

struct SinhVien {
    int MSSV;
    string TEN;
    float DTB;
};


void Nhap(SinhVien& sv) {
    cout << "Nhap ma so sinh vien: ";
    cin >> sv.MSSV;
    cin.ignore();
    cout << "Nhap ho va ten cua sinh vien: ";
    getline(cin, sv.TEN);
    cout << "Nhap diem trung binh cua sinh vien: ";
    cin >> sv.DTB;
}

void In(SinhVien x) {
    cout << "Ma so sinh vien: " << x.MSSV << endl;
    cout << "Ho va ten cua sinh vien: " << x.TEN << endl;
    cout << "Diem trung binh cua sinh vien: " << x.DTB << endl;
}

typedef struct tagNode {
    SinhVien data;
    tagNode* pNext;
} Node;

typedef struct tagList {
    Node* pHead;
    Node* pTail;
} List;

Node* CreateNode(SinhVien sv) {
    Node* p = new Node;
    if (p == NULL) exit(1);
    p->data = sv;
    p->pNext = NULL;
    return p;
}

void CreateList(List& l) {
    l.pHead = NULL;
    l.pTail = NULL;
}

void AddHead(List& l, Node* p) {
    if (l.pHead == NULL) {
        l.pHead = p;
        l.pTail = l.pHead;
    }
    else {
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

void Input(List& l, int& n) {
    SinhVien sv;
    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin sinh vien thu " << i+1 << endl;
        Nhap(sv);
        AddHead(l, CreateNode(sv));
    }
}

void Output(List l) {
    for (Node* p = l.pHead; p != NULL; p = p->pNext) {
        In(p->data);
        cout << endl;
    }
}

Node * FindX(List l, int x) {
    for (Node* p = l.pHead; p != NULL; p = p->pNext) {
        if (p->data.MSSV == x) return p;
    }
    return NULL;
}

void DelX(List& l, int& n, int x) {
    if (FindX(l, x) != NULL) {
        if (l.pHead->data.MSSV == x) {
            Node* p;
            p = l.pHead;
            l.pHead = l.pHead->pNext;
            delete p;
            n--;
            return;
        }
        if (l.pTail->data.MSSV == x) {
            for (Node* p = l.pHead; p != NULL; p = p->pNext) {
                if (p->pNext == l.pTail) {
                    Node* q = l.pTail;
                    l.pTail->pNext = NULL;
                    l.pTail = p;
                    delete q;
                    n--;
                    return;
                }
            }
        }
        for (Node* p = l.pHead; p != NULL; p = p->pNext) {
            if (p->pNext->data.MSSV == x) {
                Node* q = p->pNext;
                p->pNext = p->pNext->pNext;
                delete q;
                n--;
                return;
            }
        }
    }
    else cout << "Khong co sinh vien co ma so " << x << " trong danh sach\n";
}

void HigherThan5(List l) {
    int dem = 0;
    for (Node* p = l.pHead; p != NULL; p = p->pNext) {
        if (p->data.DTB >= 5) {
            dem++;
            cout << "\nDANH SACH SINH VIEN CO DIEM TB LON HON HOAC BANG 5\n";
            break;
        }
    }
    if (dem == 0) cout << "Khong co sinh vien nao co diem trung binh lon hon hoac bang 5\n";
    else {
        for (Node* p = l.pHead; p != NULL; p = p->pNext) {
            if (p->data.DTB >= 5) {
                In(p->data);
            }
        }
    }
}
void Menu() {
    cout << "=================MENU================\n";
    cout << "CHON CHUONG TRINH BAN MUON THUC HIEN\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "1. Nhap thong tin sinh vien\n";
    cout << "2. hien thi danh sach sinh vien\n";
    cout << "3. tim kiem thong tin sinh vien\n";
    cout << "4. xoa thong tin sinh vien\n";
    cout << "5.danh sach sinh vien co diem trung binh lon hon 5\n";
    cout << "=====================================\n";
}
int main() { 
    int n, x, y, z;
    List list;
    CreateList(list);
    Menu();
    do {
        cout << "\n-> Chon chuong trinh ban muon thuc hien: ";
        cin >> x;
        switch (x) {
        case 0:
            cout << "*** CHUONG TRINH KET THUC ***\n";
            return 0;
        case 1:
            cout << "\n*** BAN DA CHON CHUONG TRINH SO 1 ***\n";
            cout << "Nhap so luong sinh vien: ";
            cin >> n;
            Input(list, n);
            break;
        case 2:
            cout << "\n*** BAN DA CHON CHUONG TRINH SO 2 ***\n";
            Output(list);
            break;
        case 3:
            cout << "\n*** BAN DA CHON CHUONG TRINH SO 3 ***\n";
            cout << "Nhap ma so sinh vien can tim: ";
            cin >> y;
            if (FindX(list, y) != NULL) {
                cout << "Co sinh vien can tim trong danh sach\n";
                In(FindX(list, y)->data);
            }
            else
                cout << "Khong co sinh vien can tim trong danh sach\n";
            break;
        case 4:
            cout << "\n*** BAN DA CHON CHUONG TRINH SO 4 ***\n";
            cout << "Nhap ma so sinh vien can xoa: ";
            cin >> z;
            DelX(list, n, z);
            break;
        case 5:
            cout << "\n*** BAN DA CHON CHUONG TRINH SO 5 ***\n";
            HigherThan5(list);
            break;
        }
    } while (x >= 0 && x <= 5);
  
    return 0;
}
