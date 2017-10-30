/* ====================================================================
 * File: Blackbox.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOX_H
#define C_BLACKBOX_H

// INCLUDES
#include <e32base.h>
#include "Box.h"

// ENUMS
enum TBlackboxState
    {
    EUnguess,
    EGuessing,
    EGuessFailed,
    EGuessed
    };

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 *  CBlackbox class
 */
class CBlackbox : public CBox
    {
public:   // Constructors and destructor
    static CBlackbox* NewL( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );
    virtual ~CBlackbox();

public: // from CBox
    void OnDraw();
    void UpdateStateL( TInt aState );
    TInt State() const;

public: // from MTriggerBehavior
    void TriggerL();

private:   // Symbian 2nd Constructors
    void ConstructL();
    CBlackbox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );

private: // Data
    TBlackboxState iBlackboxState;
    };

#endif // C_BLACKBOX_H

// End of File
