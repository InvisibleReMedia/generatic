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
#include "installing.h"

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
    
    writeCommand(&cmd, &c);
    
    return cmd;
}


/**
 **  Initialize the data model
 **/
myModel initialize() {
    
    return createModel();
    
}
