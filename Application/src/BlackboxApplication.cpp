/* ====================================================================
 * File: BlackboxApplication.cpp
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include <eikstart.h>
#include "BlackboxDocument.h"
#include "BlackboxApplication.h"

// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidBlackboxApp = {0xAFF0567A};

CApaDocument* CBlackboxApplication::CreateDocumentL()
    {  
    // Create an Blackbox document, and return a pointer to it
    CApaDocument* document = CBlackboxDocument::NewL(*this);
    return document;
    }

TUid CBlackboxApplication::AppDllUid() const
    {
    // Return the UID for the Blackbox application
    return KUidBlackboxApp;
    }

// Create an application, and return a pointer to it
CApaApplication* NewApplication()
    {
    return new CBlackboxApplication;
    }

TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of file
