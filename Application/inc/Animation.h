/* ====================================================================
 * File: Animation.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ANIMATION_H
#define C_ANIMATION_H

// INCLUDE FILES
#include <e32base.h>
#include <coecntrl.h>
#include "AnimationFrame.h"

// FORWARD DECLARATIONS
class CBlackboxBmpUtils;
class MAnimationObserver;

// CLASS DECLARATION
/**
* CAnimation class
*
* @since S60 5.0
*/
class CAnimation : public CBase
    {
public: // Constructor and destructor
    static CAnimation* NewL( TResourceReader& aReader, MAnimationObserver& aObserver );
    virtual ~CAnimation();

public: // new methods
    void EnableControl( CCoeControl* aControl );
    void DisableControl();
    void Start();
    void Draw( CWindowGc& aGc, const TRect& aRect );

private: // Sybmain 2nd Constructor
    void ConstructL( TResourceReader& aReader );
    CAnimation( MAnimationObserver& aObserver );

private: // new methods
    static TInt TimerCompleted( TAny* aPtr );
    void DrawNow();
    static TInt ScaleCallback( TAny* aPtr );
    void Scale();

private: // Data
    MAnimationObserver& iObserver;
    CCoeControl* iControl; // no owned
    CPeriodic* iTimer; // owned
    HBufC* iFileName; // owned
    CBlackboxBmpUtils* iBmpUtils; // owned
    CIdle* iIdle; // owned
    RArray<TAnimationFrame> iAnimArray;
    TInt iDelayInterval;
    TInt iFrameInterval;
    TInt iBmpFrom;
    TInt iBmpTo;
    TInt iFrameCount;
    TInt iFrameIndex;
    TInt iScaleIndex;
    TBool iRepeat;
    TBool iRevert;
    TBool iRewind;
    TSize iSize;
    };

#endif // C_ANIMATION_H

// End of file
