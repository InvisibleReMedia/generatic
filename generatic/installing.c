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
#include "dataModel.h"
#include "fileSystem.h"
#include <stdarg.h>
#include "girlParser.h"
#include "csv-reader.h"
#include "installing.h"


/**
 **   Quit application
 **/
bool quit(myPtrModel model, myPtrCommand cmd) {
    
    exit(EXIT_SUCCESS);
    
}

/**
 **  New project
 **
 **/
bool newProject(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    
    if (ptrCmd->parameters.used == 2) {

        myString path = createString(MINSIZE);
        myString dir = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&dir, p[1].value.strContent);
        
        /** create directory if not exist **/
        createDirectory(path.strContent, dir.strContent);

        return true;
    }
    
    wprintf(L"new project [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  Delete project
 **
 **/
bool deleteProject(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    
    if (ptrCmd->parameters.used == 2) {
        
        myString path = createString(MINSIZE);
        myString dir = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&dir, p[1].value.strContent);
        
        /** delete directory if exist **/
        deleteDirectory(path.strContent, dir.strContent);
        
        return true;
    }
    
    wprintf(L"delete project [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  Open project
 **
 **/
bool openProject(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    myModel* ptrModel = (myModel*)model;
    
    if (ptrCmd->parameters.used == 2) {
        
        myString path = createString(MINSIZE);
        myString dir = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&dir, p[1].value.strContent);
        
        writeString(&ptrModel->currentSession->currentProject.path, path.strContent);
        writeString(&ptrModel->currentSession->currentProject.name, dir.strContent);
        ptrModel->currentSession->currentProject.isReadOnly = false;
        
        return true;
    }
    
    wprintf(L"open project [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  Open readonly project
 **
 **/
bool openReadOnlyProject(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    myModel* ptrModel = (myModel*)model;
    
    if (ptrCmd->parameters.used == 3) {
        
        myString path = createString(MINSIZE);
        myString dir = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&dir, p[1].value.strContent);
        
        writeString(&ptrModel->currentSession->currentProject.path, path.strContent);
        writeString(&ptrModel->currentSession->currentProject.name, dir.strContent);
        ptrModel->currentSession->currentProject.isReadOnly = true;
        
        return true;
    }
    
    wprintf(L"open project [path],[file],readonly : manque path et/ou file\n");
    return false;
}

/**
 **  New file
 **
 **/
bool newFile(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;

    if (ptrCmd->parameters.used == 2) {
        
        myString path = createString(MINSIZE);
        myString file = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&file, p[1].value.strContent);
        
        /** create directory if not exist **/
        createFile(path.strContent, file.strContent);
        
        return true;
    }
    
    wprintf(L"new file [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  New file
 **
 **/
bool newLanguageFile(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    myModel* ptrModel = (myModel*)model;

    if (ptrCmd->parameters.used == 3) {
        
        myString path = createString(MINSIZE);
        myString file = createString(MINSIZE);
        myString lan = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&file, p[1].value.strContent);
        writeString(&lan, p[2].value.strContent);
        
        /** create directory if not exist **/
        createFile(path.strContent, file.strContent);
        
        writeString(&ptrModel->currentSession->language, lan.strContent);
        
        return true;
    }
    
    wprintf(L"new file [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  Delete file
 **
 **/
bool deleteProjectFile(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    
    if (ptrCmd->parameters.used == 2) {
        
        myString path = createString(MINSIZE);
        myString file = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&file, p[1].value.strContent);
        
        /** delete file if exist **/
        deleteFile(path.strContent, file.strContent);
        
        return true;
    }
    
    wprintf(L"delete file [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  Open file
 **
 **/
bool openFile(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    myModel* ptrModel = (myModel*)model;
    
    if (ptrCmd->parameters.used == 2) {
        
        myString path = createString(MINSIZE);
        myString file = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&file, p[1].value.strContent);
        
        writeString(&ptrModel->currentSession->currentFile.path, path.strContent);
        writeString(&ptrModel->currentSession->currentFile.name, file.strContent);
        ptrModel->currentSession->currentFile.isReadOnly = false;
        
        return true;
    }
    
    wprintf(L"open file [path],[file] : manque path et/ou file\n");
    return false;
}

/**
 **  Open readonly file
 **
 **/
bool openReadOnlyFile(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    myModel* ptrModel = (myModel*)model;
    
    if (ptrCmd->parameters.used == 3) {
        
        myString path = createString(MINSIZE);
        myString file = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&file, p[1].value.strContent);
        
        writeString(&ptrModel->currentSession->currentFile.path, path.strContent);
        writeString(&ptrModel->currentSession->currentFile.name, file.strContent);
        ptrModel->currentSession->currentFile.isReadOnly = true;
        
        return true;
    }
    
    wprintf(L"open file [path],[file],readonly : manque path et/ou file\n");
    return false;
}

/**
 **   Select language
 **
 **/
bool selectLanguage(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    myModel* ptrModel = (myModel*)model;
    
    if (ptrCmd->parameters.used == 1) {
        
        myString lan = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&lan, p[0].value.strContent);
        
        writeString(&ptrModel->currentSession->language, lan.strContent);
        
        return true;
    }
    
    wprintf(L"select language [name] : manque name\n");
    return false;
}


/**
 **   Read file
 **
 **/
bool readFile(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    
    if (ptrCmd->parameters.used == 2) {
        
        myString path = createString(MINSIZE);
        myString file = createString(MINSIZE);
        myCommand* p = ptrCmd->parameters.element;
        writeString(&path, p[0].value.strContent);
        writeString(&file, p[1].value.strContent);
        
        printFile(path.strContent, file.strContent);
        
        return true;
    }
    
    wprintf(L"read file [path],[file] : manque path et/ou file\n");
    return false;

}

/**
 **   Append code
 **/
bool appendCode(myPtrModel model, myPtrCommand cmd) {
    
    myCommand* ptrCmd = (myCommand*)cmd;
    
    if (ptrCmd->parameters.used == 1) {
        
        
        return true;
        
    }
    
    wprintf(L"add code [content] : manque content\n");
    return false;

}

/**
 **  Install commands
 **/
myCommandList install() {
    
    
    myCommandList cmd;
    
    cmd = createCommandList(MINSIZE);
    
    // HELP command
    myCommand c = createCommand();
    writeString(&c.name, L"help");
    
    writeCommand(&cmd, &c);
    
    // NEW project, path, name
    c = createCommand();
    writeString(&c.name, L"new");
    writeString(&c.option, L"project");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    myCommand cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    
    c.execCommand = newProject;
    
    writeCommand(&cmd, &c);
    
    // DELETE project, path, name
    c = createCommand();
    writeString(&c.name, L"delete");
    writeString(&c.option, L"project");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);

    c.execCommand = deleteProject;

    writeCommand(&cmd, &c);
    
    // OPEN project, path, name
    c = createCommand();
    writeString(&c.name, L"open");
    writeString(&c.option, L"project");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);

    c.execCommand = openProject;
    
    writeCommand(&cmd, &c);

    // OPEN project, path, name, readonly
    c = createCommand();
    writeString(&c.name, L"open");
    writeString(&c.option, L"project");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(3);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"readonly");
    writeCommand(&c.parameters, &cp);
    
    c.execCommand = openReadOnlyProject;
    
    writeCommand(&cmd, &c);
    

    // NEW file, path, name
    c = createCommand();
    writeString(&c.name, L"new");
    writeString(&c.option, L"file");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    
    c.execCommand = newFile;
    
    writeCommand(&cmd, &c);
    
    // NEW file, path, name
    c = createCommand();
    writeString(&c.name, L"new");
    writeString(&c.option, L"file");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(3);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"language");
    writeCommand(&c.parameters, &cp);

    c.execCommand = newLanguageFile;
    
    writeCommand(&cmd, &c);

    // DELETE file, path, name
    c = createCommand();
    writeString(&c.name, L"delete");
    writeString(&c.option, L"file");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    
    c.execCommand = deleteProjectFile;
    
    writeCommand(&cmd, &c);
    
    // OPEN file, path, name
    c = createCommand();
    writeString(&c.name, L"open");
    writeString(&c.option, L"file");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    
    c.execCommand = openFile;
    
    writeCommand(&cmd, &c);
    
    // OPEN file, path, name, readonly
    c = createCommand();
    writeString(&c.name, L"open");
    writeString(&c.option, L"file");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(3);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"readonly");
    writeCommand(&c.parameters, &cp);
    
    c.execCommand = openReadOnlyFile;
    
    writeCommand(&cmd, &c);
    
    // SELECT language, name
    c = createCommand();
    writeString(&c.name, L"select");
    writeString(&c.option, L"language");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(1);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);

    c.execCommand = selectLanguage;
    
    writeCommand(&cmd, &c);

    // READ file, path, name
    c = createCommand();
    writeString(&c.name, L"read");
    writeString(&c.option, L"file");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);

    c.execCommand = readFile;
    
    writeCommand(&cmd, &c);

    // ADD code, content
    c = createCommand();
    writeString(&c.name, L"add");
    writeString(&c.option, L"code");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(1);
    cp = createCommand();
    writeString(&cp.name, L"content");
    writeCommand(&c.parameters, &cp);
    
    writeCommand(&cmd, &c);
    
    
    // ADD code, content
    c = createCommand();
    writeString(&c.name, L"add");
    writeString(&c.option, L"code");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"content");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"lineNumber");
    writeCommand(&c.parameters, &cp);

    writeCommand(&cmd, &c);
    
    // INSERT code, content
    c = createCommand();
    writeString(&c.name, L"insert");
    writeString(&c.option, L"code");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"content");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"lineNumber");
    writeCommand(&c.parameters, &cp);
    
    writeCommand(&cmd, &c);

    
    // DELETE code, lineNumber
    c = createCommand();
    writeString(&c.name, L"delete");
    writeString(&c.option, L"code");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(1);
    cp = createCommand();
    writeString(&cp.name, L"lineNumber");
    writeCommand(&c.parameters, &cp);
    
    writeCommand(&cmd, &c);
    
    // DELETE code, lineNumber, lineNumber
    c = createCommand();
    writeString(&c.name, L"delete");
    writeString(&c.option, L"code");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(2);
    cp = createCommand();
    writeString(&cp.name, L"lineNumber");
    writeCommand(&c.parameters, &cp);
    cp = createCommand();
    writeString(&cp.name, L"lineNumber");
    writeCommand(&c.parameters, &cp);

    writeCommand(&cmd, &c);
    
    // NEW session, name
    c = createCommand();
    writeString(&c.name, L"new");
    writeString(&c.option, L"session");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(1);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    
    writeCommand(&cmd, &c);
    
    // DELETE session, name
    c = createCommand();
    writeString(&c.name, L"delete");
    writeString(&c.option, L"session");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(1);
    cp = createCommand();
    writeString(&cp.name, L"name");
    writeCommand(&c.parameters, &cp);
    
    writeCommand(&cmd, &c);
    
    // SELECT session, name
    c = createCommand();
    writeString(&c.name, L"select");
    writeString(&c.option, L"session");
    freeCommandList(&c.parameters);
    c.parameters = createCommandList(1);
    cp = createCommand();
    writeString(&cp.name, L"path");
    writeCommand(&c.parameters, &cp);
    
    writeCommand(&cmd, &c);

    // QUIT project
    c = createCommand();
    writeString(&c.name, L"quit");
    writeString(&c.option, L"project");
    
    writeCommand(&cmd, &c);
    
    // QUIT file
    c = createCommand();
    writeString(&c.name, L"quit");
    writeString(&c.option, L"file");
    
    writeCommand(&cmd, &c);
    
    // QUIT
    c = createCommand();
    writeString(&c.name, L"quit");
    c.execCommand = quit;
    
    writeCommand(&cmd, &c);
    
    return cmd;
}


/**
 **  Initialize the data model
 **/
myModel initialize() {
    
    return createModel();
    
}


void loadCSV() {
    
    csvLoader("test.csv");
    
}
