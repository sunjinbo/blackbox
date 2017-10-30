/* ====================================================================
 * File: BlackboxGameContainer.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXGAMECONTAINER_H
#define C_BLACKBOXGAMECONTAINER_H

// INCLUDES
#include <aknview.h>
#include <akndef.h>
#include "SceneObserver.h"
#include "BlackboxSettings.h"

// FORWARD DECLARATIONS
class CBlackboxGameView;
class CLayoutManager;
class CScenePane;
class CAvatarPane;
class CScorePane;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;

// CLASS DECLARATION

/**
*  CBlackboxGameContainer container control class.
*  An instance of CBlackboxGameContainer contains the view drawn to the screen
*  for CBlackboxGameView
*/
class CBlackboxGameContainer : public CCoeControl, public MSceneObserver
    {
public: // Constructors and destructor

    static CBlackboxGameContainer* NewL( const TRect& aRect, CBlackboxGameView& aView );
    static CBlackboxGameContainer* NewLC( const TRect& aRect, CBlackboxGameView& aView );
    virtual ~CBlackboxGameContainer();

public: // new methods
    void HandleCommandL( TInt aCommand );

public: // from CCoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void HandleResourceChange( TInt aType );
    void SizeChanged();
    
public: // from MSceneObserver
    void StateChangedL( TInt aNewState );

private: // Constructor
    void ConstructL( const TRect& aRect );
    CBlackboxGameContainer( CBlackboxGameView& aView );

private: // new methods
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    void Stop();
    void DoFrame();
    static TInt TimerCallback( TAny* aPtr );
    void OnDraw();

private: // Data
    CBlackboxGameView& iGameView;
    CFbsBitmap* iBmpBuffer; // owned
    CFbsBitmapDevice* iBmpBufferDevice; // owned
    CFbsBitGc* iBmpBufferContext; // owned
    CPeriodic* iPeriodic; // owned
    CLayoutManager* iLayoutManager; // owned
    CScenePane* iScenePane; // owned
    CAvatarPane* iAvatarPane; // owned
    CScorePane* iScorePane; // owned
    TBlackboxSettings iSettings;
    };

#endif // C_BLACKBOXGAMECONTAINER_H

// End of File
