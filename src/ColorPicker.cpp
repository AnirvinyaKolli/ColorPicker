#include <windows.h>
#include <string>
#include <iostream>
using std::string; 

//0-0, 1-1 ... 10-a, 11-b, 12-c, 13-d, 14-e, 15-f 16-g 


string toHex(int decVal){ 
    
    int sPlace = decVal % 16; 
    int fPlace = decVal / 16; 
    
    char sChar =  ((sPlace < 10) ? sPlace + '0': (char) ('A'+ sPlace-10));
    char fChar =  ((fPlace < 10) ? fPlace + '0': (char) ('A'+ fPlace-10));

    return {fChar, sChar};
}

string getHexcode(int r, int g, int b) {
    return string("#") + toHex(r) + toHex(g) + toHex(b);
}

void copyToClipboard(const string& text){
    if (!OpenClipboard(nullptr)) return;
    EmptyClipboard();

    size_t size = text.length() + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, size);
    if (!hMem) {
        CloseClipboard();
        return;
    }

    void* pMem = GlobalLock(hMem);
    if (pMem) {
        memcpy(pMem, text.c_str(), size);
        GlobalUnlock(hMem);

        if (!SetClipboardData(CF_TEXT, hMem)) {
            GlobalFree(hMem); 
        }
    } else {
        GlobalFree(hMem);
    }

    CloseClipboard();
}