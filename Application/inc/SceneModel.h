/* ====================================================================
 * File: SceneModel.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCENEMODEL_H
#define C_SCENEMODEL_H

// INCLUDES
#include <e32base.h>
#include "BoxObserver.h"
#include "BoxHelper.h"
#include "Rays.h"

// FORWARD DECLARATIONS
class MModelObserver;
class CBoxFactory;
class CMirror;
class CBlackboxBmpUtils;
class CFont;
class CCoeEnv;

// CONSTANTS

// CLASS DECLARATION

/**
 *  CSceneModel class
 */
class CSceneModel : public CBase
        , public MBoxObserver
        , public MBoxHelper
        , public MRaysObserver
    {
public:   // Constructors and destructor
    static CSceneModel* NewL( 
            MModelObserver& aObs,
            CFbsBitGc& aGc,
            const TRect& aRect );
    virtual ~CSceneModel();

public: // New method
    void TriggerL( TInt aX, TInt aY );
    void OnDraw();
    void HandleCommandL( TInt aCommand );

public: // from MBoxObserver
    void StateChangedL( TInt aNewState );
    void RaysCreated( CRays* aNewRays );

public: // from MBoxHelper
    TRect BoxRect( TInt aX, TInt aY ) const;
    CBox* Box( TInt aX, TInt aY ) const;
    TBool HasMirror( TInt aX, TInt aY ) const;
    CFbsBitGc& BmpContext() const;
    CFbsBitmap* Bitmap( TInt aIndex ) const;
    CFont* IndexFont() const;
    TInt RaysCount() const;
    const TBlackboxSettings& Settings() const;
    void DoEffectL( TInt aEffectType, TInt aX, TInt aY );

public: // from MRaysObserver
    void AnimCompltedL();

private:   // Symbian 2nd Constructors
    void ConstructL( const TRect& aRect );
    CSceneModel( MModelObserver& aObs, CFbsBitGc& aGc );

private: // new method
    CMirror* Mirror( TInt aX, TInt aY ) const;
    
private: // new methods
    void SolvePuzzleL();
    void DoGuessL();
    void ScaleBmpUtils();
    void LoadSettingsL();
    
private: // Data
    MModelObserver& iObs;
    CFbsBitGc& iGc;
    CCoeEnv& iCoeEnv;
    TRect iRect;
    CBoxFactory* iBoxFactory; // owned
    RPointerArray<CBox> iBoxArray; // owned
    RPointerArray<CRays> iRaysArray; // owned
    RPointerArray<CMirror> iMirrorArray; // owned
    CBlackboxBmpUtils* iBmpUtils; // owned
    CFont* iIndexFont; // owned
    TBlackboxSettings iSettings;
    TInt iRaysIndex;
    };

#endif // C_SCENEMODEL_H

// End of File
