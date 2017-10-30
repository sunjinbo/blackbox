/* ====================================================================
 * File: Nookbox.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_NOOKBOX_H
#define C_NOOKBOX_H

// INCLUDES
#include <e32base.h>
#include "Box.h"

// Enums
enum TNookboxState
    {
    EInitState
    };

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CNookbox class
 */
class CNookbox : public CBox
    {
public:   // Constructors and destructor
    static CNookbox* NewL( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );
    virtual ~CNookbox();

public: // from CBox
    void OnDraw();
    void UpdateStateL( TInt aState );
    TInt State() const;

public: // from MTriggerBehavior
    void TriggerL();

private:   // Symbian 2nd Constructors
    void ConstructL();
    CNookbox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );

private: // Data
    };

#endif // C_NOOKBOX_H


// End of File
