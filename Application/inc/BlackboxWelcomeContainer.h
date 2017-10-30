/* ====================================================================
 * File: BlackboxWelcomeContainer.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXWELCOMECONTAINER_H
#define C_BLACKBOXWELCOMECONTAINER_H

// INCLUDES
#include <aknview.h>
#include <akndef.h>
#include "AnimationObserver.h"

// FORWARD DECLARATIONS
class CAknsBasicBackgroundControlContext;
class CBlackboxEditor;
class CAknButton;
class CLayoutManager;
class CBlackboxWelcomeView;
class CCoeEnv;
class CAnimation;

// CLASS DECLARATION

/**
*  CBlackboxWelcomeContainer container control class.
*  An instance of CBlackboxWelcomeContainer contains the view drawn to the screen
*  for CBlackboxWelcomeView
*/
class CBlackboxWelcomeContainer : public CCoeControl
                    , public MCoeControlObserver, public MAnimationObserver
    {
public: // Constructors and destructor

    static CBlackboxWelcomeContainer* NewL( const TRect& aRect, CBlackboxWelcomeView& aView );
    static CBlackboxWelcomeContainer* NewLC( const TRect& aRect, CBlackboxWelcomeView& aView );
    virtual ~CBlackboxWelcomeContainer();

public: // from CoeControl

    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void SizeChanged();
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    void HandleResourceChange( TInt aType );

private: // from MCoeControlObserver
    void HandleControlEventL( CCoeControl* aControl,TCoeEvent aEventType );

private: // from MAnimationObserver
    void AnimationPreparedL();
    
private: // Constructor
    void ConstructL( const TRect& aRect );
    CBlackboxWelcomeContainer( CBlackboxWelcomeView& aView );

private: // new methods
    void LayoutControls();
    void LoadAnimationL();
    HBufC* WelcGreetingTextL();

private: // Data
    CCoeEnv& iCoeEnv;
    CBlackboxWelcomeView& iWelcomeView;
    CLayoutManager* iLayoutManager; // owned
    CAknsBasicBackgroundControlContext* iBackGround; // owned
    CBlackboxEditor* iEditor; // owned
    CAknButton* iButtonStart; // owned
    CAknButton* iButtonOvi; // owned
    CAnimation* iWelcAnim; // owned
    };

#endif // C_BLACKBOXWELCOMECONTAINER_H

// End of File
