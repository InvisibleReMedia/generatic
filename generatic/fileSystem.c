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
#define ISPATHEXIST_CMD "./testPath.sh ''"
#define ISDIREXIST_CMD "./testDir.sh '' ''"
#define ISFILEEXIST_CMD "./testFile.sh '' ''"
#define DELETEDIR_CMD "./deleteDir.sh '' ''"
#define READFILE_CMD "./readFile.sh '' ''"
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
 **  Request for a path
 **/
bool isPathExist(wchar_t* dir) {
    
    char cmd[256] = ISPATHEXIST_CMD;
    char cdir[256];
    
    long lenDir = wcslen(dir);
    long lenText = strlen(ISPATHEXIST_CMD);
    
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
 **  Request for a directory path
 **/
bool isDirectoryExist(wchar_t* path, wchar_t* dir) {
    
    long lenDir = wcslen(dir);
    long lenPath = wcslen(path);
    long lenText = strlen(ISDIREXIST_CMD);
    
    if (lenDir + lenPath + lenText < 255) {
        char cmd[256] = ISDIREXIST_CMD;
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
        
        wprintf(L"Nom de fichier trop long\n");
        return false;
    }

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


/**
 **   Create all successives directory
 **/
void createAllDirectory(wchar_t* dir) {
    
    if (!isPathExist(dir)) {
        
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
}


/**
 **  Delete directory
 **/
void deleteDirectory(wchar_t* path, wchar_t* dir) {
    
    if (isPathExist(path) && isDirectoryExist(path, dir)) {
        
        long lenDir = wcslen(dir);
        long lenPath = wcslen(path);
        long lenText = strlen(DELETEDIR_CMD);
        
        if (lenDir + lenPath + lenText < 255) {
            char cmd[256] = DELETEDIR_CMD;
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

    } else {
        
        wprintf(L"Répertoire '%ls' dans '%ls' n'existe pas\n", dir, path);

    }
    
}

/**
 **  Create a file
 **/
void createFile(wchar_t* path, wchar_t* file) {
    
    if (!isPathExist(path)) {
        
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
            
            wprintf(L"Nom de fichier trop long\n");
        }
        
    } else {
        
        wprintf(L"Fichier '%ls' dans '%ls' existe déjà\n", file, path);

    }
    
    
}


/**
 **  Delete file
 **/
void deleteFile(wchar_t* path, wchar_t* file) {
    
    if (isPathExist(path) && isFileExist(path, file)) {
        
        long lenFile = wcslen(file);
        long lenPath = wcslen(path);
        long lenText = strlen(DELETEDIR_CMD);
        
        if (lenFile + lenPath + lenText < 255) {
            char cmd[256] = DELETEDIR_CMD;
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
            
            wprintf(L"Nom de fichier trop long\n");
        }
        
    } else {
        
        wprintf(L"Fichier '%ls' dans '%ls' n'existe pas\n", file, path);
        
    }
    
}

/**
 **  Create a directory
 **/
void createDirectory(wchar_t* path, wchar_t* dir) {
    
    if (!isPathExist(path)) {
        
        createAllDirectory(path);
        
    }
    
    if (!isDirectoryExist(path, dir)) {
        
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
        
    } else {
        
        wprintf(L"Répertoire '%ls' dans '%ls' existe déjà\n", dir, path);
        
    }
    
    
}


/**
 **  Print a file
 **/
void printFile(wchar_t* path, wchar_t* file) {
    
    if (!isPathExist(path)) {
        
        createAllDirectory(path);
        
    }
    
    if (isFileExist(path, file)) {
        
        long lenFile = wcslen(file);
        long lenPath = wcslen(path);
        long lenText = strlen(READFILE_CMD);
        
        if (lenFile + lenPath + lenText < 255) {
            char cmd[256] = READFILE_CMD;
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
            
            wprintf(L"Nom de fichier trop long\n");
        }
        
    } else {
        
        wprintf(L"Fichier '%ls' dans '%ls' n'existe pas\n", file, path);
        
    }
    
    
}

/**
 **   Efface un fichier
 **   strfName : nom du fichier
 **/
void eraseFile(char* strfName) {
    
    remove(strfName);
    
}

/**
 **   Ecrit dans un fichier
 **   strfName : nom du fichier
 **   writePart : function callback
 **/
void writeFile(char *destfName, writePart f) {
    
    myString line;
    FILE* writeFile = NULL;
    
    line = createString(MINSIZE);
    
    eraseFile(destfName);
    
    if ((writeFile = fopen(destfName, "w")) != NULL) {
        
        bool result;
        do {
            
            memset(line.strContent, 0, line.used);
            line.used = 0;
            result = f(&line);
            fwprintf(writeFile, L"%ls\n", line.strContent);
            
        } while(!result);
        
        fclose(writeFile);
        
    } else {
        
        perror("Ecriture du fichier en erreur :");
    }
    
    freeString(&line);
    
}


/**
 **   Lit depuis un fichier
 **   strfName : nom du fichier
 **   readPart : function callback
 **   grammar  : for grammar parser
 **   object   : gather data
 **/
void readFromFile(char *strfName, readPart f, void* grammar, void* object) {
    
    myString line;
    FILE* readFile = NULL;
    
    line = createString(128);
    
    if ((readFile = fopen(strfName, "r")) != NULL) {
        
        bool result;
        do {
            
            memset(line.strContent, 0, line.used);
            line.used = fwscanf(readFile, L"%127ls", line.strContent);
            result = f(&line, grammar, object);
            
        } while(!feof(readFile) && result);
        
        fclose(readFile);
        
    } else {
        
        perror("Lecture du fichier en erreur :");
    }
    
    freeString(&line);
    
}


