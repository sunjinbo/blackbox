/* ====================================================================
 * File: TipsManager.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_TIPSMANAGER_H
#define C_TIPSMANAGER_H

// INCLUDE FILES
#include <e32base.h>
#include <coecntrl.h>
#include "BlackboxSettings.h"

// FORWARD DECLARATIONS
class TResourceReader;
class CTips;
class CCoeEnv;

// CLASS DECLARATION

/**
* CTipsManager class
*
* @since S60 5.0
*/
class CTipsManager : public CBase
    {
public:
    static CTipsManager* NewL();
    virtual ~CTipsManager();

public:
    CTips* Tips() const;
    TInt Count() const;
    void Next();
    
private:
    void ConstructL();
    CTipsManager();

private: // new methods
    void CreateResourceReaderL( TResourceReader& aReader );
    void Sort();

private: // Data
    CCoeEnv& iCoeEnv;
    RPointerArray<CTips> iTipsArray;
    TInt iCurrentTips;
    TBlackboxSettings iBlackboxSettings;
    };

#endif // C_TIPSMANAGER_H

// End of file
