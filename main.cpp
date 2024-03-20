#include <iostream>
#include <windows.h>

// part that normally should be in resource.h file
#define IDR_RCDATA1                     300

#define IDS_STRING1                     1
#define IDS_STRING2                     2
#define IDS_STRING3                     3
// end of this part

// dynamic procedure type definition
typedef unsigned long (CALLBACK *FPROC)(unsigned char*);

// dynamic procedure definition
FPROC DLL_1;

unsigned char CALLBACK __export Test(unsigned char* test) {
    return ((unsigned char)DLL_1(test));
};
// end of dynamic procedure definition

int main(void) {
    unsigned char test[5];
    char test3[256];
    HINSTANCE hLib=LoadLibrary("testlib2.dll");
    if(hLib < 32) {
        std::cout << "FAIL" << std::endl;
    } else {
        std::cout << "OK" << std::endl;
        DLL_1=(FPROC)GetProcAddress(hLib,"Test");
        if(DLL_1!=NULL) {
            std::cout << "OK" << std::endl;
            test[0]=3;
            test[1]=4;
            std::cout << (unsigned int)Test(test) << std::endl;
        }
        HGLOBAL hMem = LoadResource(hLib,FindResource(hLib,MAKEINTRESOURCE(IDR_RCDATA1),RT_RCDATA));
        if(hMem==NULL) {
            std::cout << "FAIL" << std::endl;
        } else {
            std::cout << "OK" << std::endl;
            WORD *test2 = (WORD*)LockResource(hMem);
            if(test2==NULL) {
                std::cout << "FAIL" << std::endl;
            } else {
                std::cout << "OK" << std::endl;
                unsigned int x=0;
                while(test2[x]) {
                    test3[x]=(char)test2[x];
                    ++x;
                }
                test3[x]=0;
                std::cout << test3 << std::endl;
                UnlockResource(hMem);
            }
            FreeResource(hMem);
        }
        if(LoadString(hLib,IDS_STRING1,test3,256)) {
            std::cout << test3 << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        if(LoadString(hLib,IDS_STRING2,test3,256)) {
            std::cout << test3 << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        if(LoadString(hLib,IDS_STRING3,test3,256)) {
            std::cout << test3 << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        FreeLibrary(hLib);
    }
    return 0;
}
