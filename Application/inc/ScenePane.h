/* ====================================================================
 * File: ScenePane.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCENEPANE_H
#define C_SCENEPANE_H

// INCLUDES
#include <coecntrl.h>
#include "ModelObserver.h"

// FORWARD DECLARATIONS
class MSceneObserver;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CLayoutManager;
class CSceneTaskScheduler;
class CSceneModel;
class CBlackboxBmpUtils;

// Enums


// CLASS DECLARATION

/**
 *  CScenePane class
 */
class CScenePane : public CCoeControl, public MModelObserver
    {
public: // friend class
    friend class CSceneTask;

public: // Constructors and destructor
    static CScenePane* NewL( CFbsBitGc& aBmpContext, MSceneObserver& aObserver );
    virtual ~CScenePane();

public: // New methods
    void OnDraw();
    void HandleCommandL( TInt aCommand );

public: // from CCoeControl
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

public: // from MModelObserver
    void StateChangedL( TInt aNewState );
    void DoEffectL( TInt aEffectType, TInt aX, TInt aY );

private: // Symbian 2nd Constructors
    void ConstructL();
    CScenePane( CFbsBitGc& aBmpContext, MSceneObserver& aObserver );

private: // New methods
    void ScaleBmpUtils();

private: // Data
    CFbsBitGc& iBmpContext;
    MSceneObserver& iObserver;
    CLayoutManager* iLayoutManager; // owned
    CSceneTaskScheduler* iScheduler; // owned
    CSceneModel* iModel; // owned
    CBlackboxBmpUtils* iBmpUtils; // owned
    TBool iGameOver; // mark game over.
    };

#endif // C_SCENEPANE_H

