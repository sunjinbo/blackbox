/* ====================================================================
 * File: BlackboxSettingsContainer.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXSETTINGSCONTAINER_H
#define C_BLACKBOXSETTINGSCONTAINER_H

// INCLUDES
#include <aknview.h>
#include <akndef.h>
#include "BlackboxSettings.h"
#include "BlackboxSettingList.h"

// FORWARD DECLARATIONS
class CAknsBasicBackgroundControlContext;
class CBlackboxSettingsView;

// CLASS DECLARATION

/**
*  CBlackboxSettingsContainer container control class.
*  An instance of CBlackboxSettingsContainer contains the view drawn to the screen
*  for CBlackboxSettingsView
*/
class CBlackboxSettingsContainer : public CCoeControl
                                    , public MSettingsListObserver
    {
public: // Constructors and destructor
    static CBlackboxSettingsContainer* NewL( 
            const TRect& aRect, CBlackboxSettingsView& aSettingsView );
    static CBlackboxSettingsContainer* NewLC( 
            const TRect& aRect, CBlackboxSettingsView& aSettingsView );
    virtual ~CBlackboxSettingsContainer();

public: // from CoeControl

    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void SizeChanged();
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    void HandleResourceChange( TInt aType );
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                TEventCode aType );

private: // from MSettingsListObserver
    void HandleItemChangedL( TInt aIndex );
    
private: // Constructor
    void ConstructL( const TRect& aRect );
    CBlackboxSettingsContainer( CBlackboxSettingsView& aSettingsView );

private: // Internal new functions
    /**
    * Loads the setting list dynamically.
    */    
    void LoadListL();

private: // Data
    CBlackboxSettingsView& iSettingsView;
    CAknsBasicBackgroundControlContext* iBackGround; // owns
    CBlackboxSettingList* iSettingsList;
    TBlackboxSettings iSettings;
    TInt iAvatar;
    TInt iDifficulty;
    TInt iGuessType;
    TInt iNumberOfNodes;
    CArrayFixFlat<TInt> iUnlimitedRays;
    TBool iVibration;
    TBool iSound;
    TInt iVolumeValue;
    };

#endif // C_BLACKBOXSETTINGSCONTAINER_H

// End of File
