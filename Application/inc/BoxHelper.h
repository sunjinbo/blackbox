/* ====================================================================
 * File: BoxHelper.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_BOXHELPER_H
#define M_BOXHELPER_H

// INCLUDE
#include "BlackboxSettings.h"

// FORWARD DECLARATIONS
class CBox;
class CFbsBitGc;
class CFbsBitmap;
class CFont;

// CLASS DECLARATION

/**
* MBoxHelper class
*
* @since S60 5.0
*/
class MBoxHelper
    {
public:
    // interface methods.
    virtual TRect BoxRect( TInt aX, TInt aY ) const = 0;
    virtual CBox* Box( TInt aX, TInt aY ) const = 0;
    virtual TBool HasMirror( TInt aX, TInt aY ) const = 0;
    virtual CFbsBitGc& BmpContext() const = 0;
    virtual CFbsBitmap* Bitmap( TInt aIndex ) const = 0;
    virtual CFont* IndexFont() const = 0;
    virtual TInt RaysCount() const = 0;
    virtual const TBlackboxSettings& Settings() const = 0;
    virtual void DoEffectL( TInt aEffectType, TInt aX, TInt aY ) = 0;
    };

#endif // M_BOXHELPER_H

// End of File
