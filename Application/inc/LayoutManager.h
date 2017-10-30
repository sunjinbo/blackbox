/* ====================================================================
 * File: LayoutManager.h
 * Created: 09/05/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_LAYOUTMANAGER_H
#define C_LAYOUTMANAGER_H

// INCLUDE FILES
#include <e32base.h>
#include "LayoutManagerValues.h"


// FORWARD DECLARATIONS
class TAknLayoutRect;

// CLASS DECLARATION

/**
* CLayoutManager class
*
* @since S60 Symbian^3
*/
class CLayoutManager : public CBase
    {
public: // Constructor and Destructor
    static CLayoutManager* NewL();
    virtual ~CLayoutManager();    

public: // New functions
    void ResolutionChanged( TOrientation aOrientation = EAutomatic );
    TRect LayoutRect( TComponent aComponent ) const;

protected: // Constructor
    CLayoutManager();
    void ConstructL();

private: // Data members
    TResolution iResolution;
    };

#endif // C_LAYOUTMANAGER_H

// End of File
