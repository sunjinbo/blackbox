/* ====================================================================
 * File: Tips.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_TIPS_H
#define C_TIPS_H

// INCLUDE FILES
#include <e32base.h>
#include <coecntrl.h>
#include "AnimationObserver.h"

// FORWARD DECLARATIONS
class CAnimation;

// CLASS DECLARATION

/**
* CTips class
*
* @since S60 5.0
*/
class CTips : public CBase, public MAnimationObserver
    {
public: // Construtor and destructor
    static CTips* NewL( TResourceReader& aReader );
    virtual ~CTips();

public: // new methods
    static TInt Compare( const CTips& aFirst, const CTips& aSecond );
    TInt Id() const;
    CAnimation* Animation() const;
    HBufC* ShortTipsText() const;
    HBufC* TipsText() const;

private: // from MAnimationObserver
    void AnimationPreparedL();
    
private: // Symbian 2nd constructor
    void ConstructL( TResourceReader& aReader );
    CTips();

private: // Data
    TInt iId;
    CAnimation* iAnimation; // owned
    HBufC* iShortTipsText; // owned
    HBufC* iTipsText; // owned
    };

#endif // C_TIPS_H

// End of file
