/* ====================================================================
 * File: BlackboxBmpUtils.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXBMPUTILS_H
#define C_BLACKBOXBMPUTILS_H

// INCLUDE FILES
#include <e32base.h>
#include <e32std.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CBlackboxBmpUtils class
*
* @since S60 5.0
*/
class CBlackboxBmpUtils : public CBase
    {
public: // Constructor and destructor

    static CBlackboxBmpUtils* NewL( const TDesC& aFileName, TInt aFrom, TInt aTo );
    virtual ~CBlackboxBmpUtils();

public: // New functions

    void SetSize( TInt aIndex, TSize aSize );
    void SetSizeAndRotation( TInt aIndex, TSize aSize, TInt aAngle = 0 );
    CFbsBitmap* Bitmap( TInt aIndex ) const;

protected: // Default destructor

    CBlackboxBmpUtils( TInt aFrom, TInt aTo );
    void ConstructL( const TDesC& aFileName );

private: // New function
    void LoadBitmapL ();

protected: // Data members
    TInt iFrom;
    TInt iTo;
    HBufC* iFileName; // Own
    RPointerArray<CFbsBitmap>  iBitmapArray;
    };

#endif // C_BLACKBOXBMPUTILS_H

// End of File
