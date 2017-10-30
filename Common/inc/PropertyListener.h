/* ====================================================================
 * File: PropertyListener.h
 * Created: 07/06/10
 * Modified: 07/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_PROPERTYLISTENER_H
#define C_PROPERTYLISTENER_H

// INCLUDE FILES
#include <e32base.h>
#include <e32property.h>

// FORWARD DECLARATIONS
class MPropertyListenerCallBack;

/**
 * CPropertyListener
 */
class CPropertyListener : public CActive
    {
public:

    // Two phased constructors
    IMPORT_C static CPropertyListener* NewL(const TUid& aCategory,
            const TUint32& aKey, MPropertyListenerCallBack& aCallBack);
    IMPORT_C static CPropertyListener* NewLC(const TUid& aCategory,
            const TUint32& aKey, MPropertyListenerCallBack& aCallBack);

    // Destructor
    IMPORT_C virtual ~CPropertyListener();

public:
    // New methods

    // Start listening
    IMPORT_C void Listen();

private:
    // From base classes

    // @see CActive
    void RunL();

    // @see CActive
    void DoCancel();

    // @see CActive
    TInt RunError(TInt aError);

private:
    CPropertyListener(MPropertyListenerCallBack& aCallBack);
    
    void ConstructL(const TUid& aCategory, const TUint32& aKey);

private:

    // Own: P&S property
    RProperty iProperty;

    // Ref: Call back
    MPropertyListenerCallBack& iCallBack;

    };

#endif //C_PROPERTYLISTENER_H
