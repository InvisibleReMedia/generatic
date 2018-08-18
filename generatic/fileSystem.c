/**
 **
 **   Langage C
 **   Projet Generatic
 **   17/7/18 CET 10:00
 **   business.forward.technology@gmail.com
 **   Ce source peut être compilé avec:
 **     - XCode (MacOS)
 **     - Code::Blocks et GNU GCC
 **
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include <assert.h>
#include "library-strings.h"
#include "fileSystem.h"



#define CREATEDIR_CMD "./createDirectory.sh '' ''"
#define CREATEFILE_CMD "./createFile.sh '' ''"
#define ISDIREXIST_CMD "./testDir.sh ''"
#define ISFILEEXIST_CMD "./testFile.sh '' ''"
#define RET_VALUE 512

/**
 **  Combine one argument
 **/
char* combine(char *src, char* arg1) {
    
    int state = 0;
    int num = 0;
    long len = strlen(src);
    char input[2];
    input[1] = '\0';
    char s[256];
    memset(s, 0, 256);
    for(int index = 0; index < len; ++index) {
        
        char c = src[index];
        input[0] = c;
        strcat(s, input);
        if (c == '\'') {
            
            if (state == 0) {
                
                if (num == 0) {
                    
                    strcat(s, arg1);
                    num = 1;
                    
                }
                state = 1;
                
            } else {
                
                state = 0;
                
            }
            
        }
        
    }
    
    strcpy(src, s);
    return src;
}

/**
 ** Combine two arguments
 **/
char* combine2(char *src, char* arg1, char* arg2) {
    
    int state = 0;
    int num = 0;
    long len = strlen(src);
    char input[2];
    input[1] = '\0';
    char s[256];
    memset(s, 0, 256);
    for(int index = 0; index < len; ++index) {
        
        char c = src[index];
        input[0] = c;
        strcat(s, input);
        if (c == '\'') {
            
            if (state == 0) {
                
                if (num == 0) {
                    
                    strcat(s, arg1);
                    num = 1;

                } else if (num == 1) {
                    
                    strcat(s, arg2);
                    num = 2;

                }
                state = 1;

            } else {
                
                state = 0;
                
            }
            
        }
        
    }
    
    strcpy(src, s);
    return src;
}

/**
 **  Function to create one directory
 **/
void createOneDirectory(wchar_t* path, wchar_t* dir) {
    
    long lenDir = wcslen(dir);
    long lenPath = wcslen(path);
    long lenText = strlen(CREATEDIR_CMD);

    if (lenDir + lenPath + lenText < 255) {
        char cmd[256] = CREATEDIR_CMD;
        char cdir[256], rdir[256];
        memset(cdir, 0, 256);
        memset(rdir, 0, 256);
        for(int index = 0; index < lenPath; ++index) {
            cdir[index] = (char)path[index];
        }
        for(int index = 0; index < lenDir; ++index) {
            rdir[index] = (char)dir[index];
        }
        char* res = combine2(cmd, cdir, rdir);
        system(res);

    } else {
        
        wprintf(L"Nom de répertoire trop long\n");
        
    }
}

void createAllDirectory(wchar_t* dir) {
    
    long len = wcslen(dir);
    wchar_t input[2];
    input[1] = L'\0';
    myString s = createString(MINSIZE);
    myString path = createString(MINSIZE);
    writeString(&path, L".");
    for(int index = 0; index < len; ++index) {
        
        wchar_t c = dir[index];
        if (c == L'/') {
            
            if (s.used > 0) {
                
                createOneDirectory(path.strContent, s.strContent);
                if (path.used > 0)
                    writeString(&path, L"/");
                writeString(&path, s.strContent);
                memset(s.strContent, 0, s.used);
                s.used = 0;
            }
            
        } else {
            
            input[0] = c;
            writeString(&s, input);
            
        }
        
    }
    
    if (s.used > 0) {
        
        createOneDirectory(path.strContent, s.strContent);
    }

    freeString(&s);
}


/**
 **  Request for a directory path
 **/
bool isDirectoryExist(wchar_t* dir) {
    
    char cmd[256] = ISDIREXIST_CMD;
    char cdir[256];
    
    long lenDir = wcslen(dir);
    long lenText = strlen(ISDIREXIST_CMD);
    
    if (lenDir + lenText < 255) {
        
        memset(cdir, 0, 256);
        for(int index = 0; index < lenDir; ++index) {
            cdir[index] = (char)dir[index];
        }
        char* res = combine(cmd, cdir);
        int x = system(res);
        if (x == RET_VALUE)
            return false;
        else
            return true;

    } else {
    
        wprintf(L"Nom de répertoire trop long\n");
        return false;
    }

}


/**
 **  Request for a file
 **/
bool isFileExist(wchar_t* path, wchar_t* dir) {
    
    long lenDir = wcslen(dir);
    long lenPath = wcslen(path);
    long lenText = strlen(ISFILEEXIST_CMD);
    
    if (lenDir + lenPath + lenText < 255) {
        char cmd[256] = ISFILEEXIST_CMD;
        char cdir[256], rdir[256];
        memset(cdir, 0, 256);
        memset(rdir, 0, 256);
        for(int index = 0; index < lenPath; ++index) {
            cdir[index] = (char)path[index];
        }
        for(int index = 0; index < lenDir; ++index) {
            rdir[index] = (char)dir[index];
        }
        char* res = combine2(cmd, cdir, rdir);
        int x = system(res);
        if (x == RET_VALUE)
            return false;
        else
            return true;

    } else {
        
        wprintf(L"Nom de répertoire trop long\n");
        return false;
    }

}



/**
 **  Create a file
 **/
void createFile(wchar_t* path, wchar_t* file) {
    
    if (!isDirectoryExist(path)) {
        
        createAllDirectory(path);
        
    }
    
    if (!isFileExist(path, file)) {
        
        long lenFile = wcslen(file);
        long lenPath = wcslen(path);
        long lenText = strlen(CREATEFILE_CMD);
        
        if (lenFile + lenPath + lenText < 255) {
            char cmd[256] = CREATEFILE_CMD;
            char cdir[256], rdir[256];
            memset(cdir, 0, 256);
            memset(rdir, 0, 256);
            for(int index = 0; index < lenPath; ++index) {
                cdir[index] = (char)path[index];
            }
            for(int index = 0; index < lenFile; ++index) {
                rdir[index] = (char)file[index];
            }
            char* res = combine2(cmd, cdir, rdir);
            system(res);
            
        } else {
            
            wprintf(L"Nom de répertoire trop long\n");
        }
        
    } else {
        
        wprintf(L"Fichier '%ls' dans '%ls' existe déjà\n", path, file);

    }
    
    
}
