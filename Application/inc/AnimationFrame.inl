/* ====================================================================
 * File: AnimationFrame.inl
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TAnimationFrame::TAnimationFrame()
// ----------------------------------------------------------------------------
//
inline TAnimationFrame::TAnimationFrame()
: iBitmapId ( EUninit ), iMaskId ( EUninit )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// TAnimationFrame::TAnimationFrame()
// ----------------------------------------------------------------------------
//
inline TAnimationFrame::TAnimationFrame( TInt aBitmapId, TInt aMaskId )
: iBitmapId ( aBitmapId ), iMaskId ( aMaskId )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// TAnimationFrame::TAnimationFrame()
// ----------------------------------------------------------------------------
//
inline TAnimationFrame::TAnimationFrame( TResourceReader& aReader )
    {
    iBitmapId = aReader.ReadInt32();
    iMaskId = aReader.ReadInt32();
    }

// ----------------------------------------------------------------------------
// TAnimationFrame::IsNull
// ----------------------------------------------------------------------------
//
inline TBool TAnimationFrame::IsNull()
    {
    if ( ( iBitmapId == EUninit ) 
        || ( iMaskId == EUninit )
       )
        {
        return ETrue;
        }
    return EFalse;
    }

// End of File
