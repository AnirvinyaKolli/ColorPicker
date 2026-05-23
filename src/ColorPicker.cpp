#include <string> 
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

