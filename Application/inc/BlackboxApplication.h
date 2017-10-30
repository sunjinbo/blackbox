/* ====================================================================
 * File: BlackboxApplication.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXAPPLICATION_H
#define C_BLACKBOXAPPLICATION_H

// INCLUDE FILE
#include <aknapp.h>

// CLASS DECLARATION

/**
 *  CBlackboxApplication class
 */
class CBlackboxApplication : public CAknApplication
    {
public:  // from CAknApplication
    TUid AppDllUid() const;

protected: // from CAknApplication
    CApaDocument* CreateDocumentL();
    };

#endif // C_BLACKBOXAPPLICATION_H

// End of file
