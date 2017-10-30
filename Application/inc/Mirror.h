/* ====================================================================
 * File: Mirror.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MIRROR_H
#define C_MIRROR_H

// INCLUDES
#include <e32base.h>
#include "DrawerBehavior.h"
#include "RegistrationTimeout.h"

// FORWARD DECLARATIONS
class CSceneModel;

// CLASS DECLARATION

/**
 *  CMirror class
 */
class CMirror : public CBase, public MDrawerBehavior,
        public MTimeoutCallback
    {
public:   // Constructors and destructor
    static CMirror* NewL( CSceneModel& aModel, const TPoint& aPos );
    virtual ~CMirror();

public: // New functions
    TInt Radius() const;
    TPoint Position() const;
    void SetFullMirror( TBool aFullMirror );
    TBool IsFullMirror() const;
    void SetVisible( TBool aVisible );
    TBool IsVisible() const;
    void SetGuessed( TBool aGuessed );
    TBool IsGuessed() const;

public: // from MDrawerBehavior
    void OnDraw();

private: // from MTimeoutCallback
    void HandleTimeoutL();

private:   // Symbian 2nd Constructors
    void ConstructL();
    CMirror( CSceneModel& aModel, const TPoint& aPos );

private: // new methods
    TInt Rand( TInt aRange ) const;

private: // Data
    CSceneModel& iModel;
    CRegistrationTimeout* iTimeout;
    TPoint iPosition;
    TBool iFullMirror;
    TBool iVisible;
    TBool iGuessed;
    TBool iMirrorEffectRevert;
    TInt iMirrorBitmapId;
    TInt iMirrorMaskId;
    };

#endif // C_MIRROR_H


// End of File
