/* ====================================================================
 * File: AnimationFrame.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef T_ANIMATIONFRAME_H
#define T_ANIMATIONFRAME_H

// INCLUDE FILES
#include <e32cmn.h>
#include <barsread.h>

// CLASS DECLARATION

/**
* TAnimationFrame class
*
*/
class TAnimationFrame
    {
public:
    enum { EUninit = -1 };
    /**
    Constructs default animation frame
    */
    inline TAnimationFrame();
    inline TAnimationFrame( TInt aBitmapId, TInt aMaskId );
    inline TAnimationFrame( TResourceReader& aReader );
    inline TBool IsNull();

public: // Member data
    /**
    The bitmap resource id.
    */
    TInt iBitmapId;

    /**
    The mask resource id.
    */
    TInt iMaskId;
    };
#include "AnimationFrame.inl"

#endif // T_ANIMATIONFRAME_H

// End of File
