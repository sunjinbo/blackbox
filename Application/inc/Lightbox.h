/* ====================================================================
 * File: Lightbox.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_LIGHTBOX_H
#define C_LIGHTBOX_H

// INCLUDES
#include <e32base.h>
#include "Box.h"

// FORWARD DECLARATIONS
class CRays;

// ENUMS
enum TLightboxState
    {
    EConceal,
    EDeflection,
    EComplexDeflection,
    EDeflectionOut,
    EComplexDeflectionOut,
    EReflection,
    EComplexReflection
    };

// CLASS DECLARATION

/**
 *  CLightbox class
 */
class CLightbox : public CBox
    {
public: // friend class declaration
    friend class CRays;

public:   // Constructors and destructor
    static CLightbox* NewL( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );
    virtual ~CLightbox();

public: // new methods
    void SetIndexId( TInt aIndexId );
    TInt IndexId() const;
    
public: // from CBox
    void OnDraw();
    void UpdateStateL( TInt aState );
    TInt State() const;

public: // from MTriggerBehavior
    void TriggerL();

private:  // Symbian 2nd Constructors
    void ConstructL();
    CLightbox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );

private: // new methods
    void GetDeflectionBmpIx( TInt& aBitmap, TInt& aMask );
    void GetComplexDeflectionBmpIx( TInt& aBitmap, TInt& aMask );
    void GetDeflectionOutBmpIx( TInt& aBitmap, TInt& aMask );
    void GetComplexDeflectionOutBmpIx( TInt& aBitmap, TInt& aMask );
    void GetComplexReflection( TInt& aBitmap, TInt& aMask );
    TRect IndexRect( const TRect& aBoxRect ) const;

private: // Data
    CRays* iRays; // owned
    TLightboxState iLightboxState;
    enum TLightboxDirection
        {
        ELightboxTop,
        ELightboxBottom,
        ELightboxLeft,
        ELightboxRight
        };
    TLightboxDirection iLightboxDirection;
    TInt iIndexId;
    };

#endif // C_LIGHTBOX_H

// End of File
