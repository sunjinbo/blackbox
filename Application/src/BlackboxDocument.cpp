/* ====================================================================
 * File: BlackboxDocument.cpp
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include "BlackboxAppUi.h"
#include "BlackboxDocument.h"
#include "Logger.h"

// Standard Symbian OS construction sequence
CBlackboxDocument* CBlackboxDocument::NewL(CEikApplication& aApp)
    {
    CBlackboxDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CBlackboxDocument* CBlackboxDocument::NewLC(CEikApplication& aApp)
    {
    CBlackboxDocument* self = new (ELeave) CBlackboxDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBlackboxDocument::ConstructL()
    {
    CREATE_INFO_FILE
    }    

CBlackboxDocument::CBlackboxDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // no implementation required
    }

CBlackboxDocument::~CBlackboxDocument()
    {
    // no implementation required
    }

CEikAppUi* CBlackboxDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CBlackboxAppUi;
    return appUi;
    }

// End of file
