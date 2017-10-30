/* ====================================================================
 * File: BlackboxSettingsContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknsSkinInstance.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <AknsControlContext.h>
#include <AknsBasicBackgroundControlContext.h>
#include <stringloader.h>
#include <eikfrlbd.h>
#include <Blackbox.rsg>
#include "BlackboxSettingsContainer.h"
#include "BlackboxSettingsView.h"
#include "BlackboxSliderSettingItem.h"
#include "BlackboxCheckboxSettingItem.h"

// CONSTANTS

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxSettingsContainer* CBlackboxSettingsContainer::NewL( 
        const TRect& aRect, CBlackboxSettingsView& aSettingsView )
    {
    CBlackboxSettingsContainer* self 
        = CBlackboxSettingsContainer::NewLC( aRect, aSettingsView );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxSettingsContainer* CBlackboxSettingsContainer::NewLC( 
        const TRect& aRect, CBlackboxSettingsView& aSettingsView )
    {
    CBlackboxSettingsContainer* self 
        = new ( ELeave ) CBlackboxSettingsContainer( aSettingsView );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::~CBlackboxSettingsContainer()
// Destructor
// -----------------------------------------------------------------------------
//
CBlackboxSettingsContainer::~CBlackboxSettingsContainer()
    {
    delete iBackGround;
    delete iSettingsList;
    
    iUnlimitedRays.Reset();
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CBlackboxSettingsContainer::CountComponentControls() const
    {
    return 1;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CBlackboxSettingsContainer::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iSettingsList;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.Clear();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::Background( skin, iBackGround, gc, aRect );
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::SizeChanged()
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsContainer::SizeChanged()
    {
    if ( iBackGround )
        {
        iBackGround->SetRect( Rect() );
        }
    if ( iSettingsList )
        {
        iSettingsList->SetRect( Rect() );
        }
    }

// --------------------------------------------------------------------------
// CSmartPromoUiSignupContainer::MopSupplyObject()
// Pass skin information if need.
// --------------------------------------------------------------------------
//
TTypeUid::Ptr CBlackboxSettingsContainer::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId && iBackGround )
        {
        return MAknsControlContext::SupplyMopObject( aId, iBackGround );
        }
    return CCoeControl::MopSupplyObject(aId);
    }

// ----------------------------------------------------------------------------
// CBlackboxSettingsContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CBlackboxSettingsContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetRect( iSettingsView.ClientRect() );
        }
    }

// ----------------------------------------------------------------------------
// CBlackboxSettingsContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CBlackboxSettingsContainer::OfferKeyEventL(    
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    if( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }
    else if( iSettingsList )
        {
        return iSettingsList->OfferKeyEventL( aKeyEvent, aType );
        }
    else
        {
        return EKeyWasNotConsumed;
        }
    }

// ----------------------------------------------------------------------------
// CBlackboxSettingsContainer::HandleItemChangedL
// ----------------------------------------------------------------------------
//
void CBlackboxSettingsContainer::HandleItemChangedL( TInt aIndex )
    {
    switch( aIndex )
        {
        case EBlackboxSettingsAvatar:
            iSettings.iAvatar
                = (TBlackboxAvatar)iAvatar;
            break;
            
        case EBlackboxSettingsPuzzleDifficulty:
            iSettings.iDifficulty 
                = (TBlackboxPuzzleDifficulty)iDifficulty;
            break;

        case EBlackboxSettingsGuessType:
            iSettings.iGuessType
                = (TBlackboxGuessType)iGuessType;
            break;

        case EBlackboxSettingsNumberOfNodes:
            iSettings.iNumberOfNodes = iNumberOfNodes;
            break;

        case EBlackboxSettingsUnlimitedRays:
            {
            if ( iUnlimitedRays.Count() > 0 
                && iUnlimitedRays[0] > 0 )
                {
                iSettings.iUnlimitedRays = ETrue;
                }
            else
                {
                iSettings.iUnlimitedRays = EFalse;
                }
            }
            break;

        case EBlackboxSettingsVibration:
            iSettings.iVibration = iVibration;
            break;

        case EBlackboxSettingsSound:
            {
            iSettings.iSound = iSound;
            if ( iSettings.iSound )
                {
                (*(iSettingsList->SettingItemArray()))
                        [EBlackboxSettingsVolumeValue]->SetHidden(EFalse);
                }
            else
                {
                (*(iSettingsList->SettingItemArray()))
                        [EBlackboxSettingsVolumeValue]->SetHidden(ETrue);
                }
            iSettingsList->HandleChangeInItemArrayOrVisibilityL();
            }
            break;

        case EBlackboxSettingsVolumeValue:
            iSettings.iVolumeValue = iVolumeValue;
            break;

        default:
            break;
        }

    // saves settings to file
    iSettings.ExternalizedL();
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    iBackGround = CAknsBasicBackgroundControlContext::NewL( 
        KAknsIIDQsnBgAreaMain, aRect, EFalse );
    
    iSettings.InternalizedL();

    iAvatar = iSettings.iAvatar;
    iDifficulty = iSettings.iDifficulty;
    iGuessType = iSettings.iGuessType;
    iNumberOfNodes = iSettings.iNumberOfNodes;
    iUnlimitedRays.AppendL( iSettings.iUnlimitedRays );
    iVibration = iSettings.iVibration;
    iSound = iSettings.iSound;
    iVolumeValue = iSettings.iVolumeValue;

    iSettingsList = CBlackboxSettingList::NewL( *this );
    iSettingsList->SetMopParent( this );
    iSettingsList->SetContainerWindowL( *this );
    iSettingsList->ConstructFromResourceL( R_BLACKBOX_SETTING_LIST );

    LoadListL();

    iSettingsList->MakeVisible(ETrue);
    iSettingsList->SetRect(aRect);
    iSettingsList->ActivateL();
    iSettingsList->ListBox()->UpdateScrollBarsL();
    iSettingsList->DrawNow();

    SetRect( aRect );

    ActivateL();
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::CBlackboxSettingsContainer()
// -----------------------------------------------------------------------------
//
CBlackboxSettingsContainer::CBlackboxSettingsContainer( 
                                    CBlackboxSettingsView& aSettingsView ) 
: iSettingsView( aSettingsView ), iUnlimitedRays( 3 )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsContainer::LoadListL()
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsContainer::LoadListL()
    {
    CArrayPtr<CGulIcon>* icons = 
            iSettingsList->ListBox()->ItemDrawer()->FormattedCellData()->IconArray();

    /* Avatar setting item */
    CAknEnumeratedTextPopupSettingItem* avatarItem 
        = new (ELeave) CAknEnumeratedTextPopupSettingItem( EBlackboxSettingsAvatar, iAvatar );
    CleanupStack::PushL( avatarItem );
    avatarItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsAvatar, // ordinal
            _L( "Avatar" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_AVATAR, // setting page resource id
            -1, // editor control type
            0, // setting editor resource id
            R_BLACKBOX_SETTING_AVATAR_TEXT // associated resource id
            );

    iSettingsList->SettingItemArray()->AppendL( avatarItem );
    CleanupStack::Pop( avatarItem );
    
    /* Puzzle difficulty setting item */
    CAknEnumeratedTextPopupSettingItem* puzzleDifficultyItem 
        = new (ELeave) CAknEnumeratedTextPopupSettingItem( EBlackboxSettingsPuzzleDifficulty, iDifficulty );
    CleanupStack::PushL( puzzleDifficultyItem );
    puzzleDifficultyItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsPuzzleDifficulty, // ordinal
            _L( "Puzzle difficulty" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_PUZZLEDIFFICULTY, // setting page resource id
            -1, // editor control type
            0, // setting editor resource id
            R_BLACKBOX_SETTING_PUZZLEDIFFICULTY_TEXT // associated resource id
            );

    iSettingsList->SettingItemArray()->AppendL( puzzleDifficultyItem );
    CleanupStack::Pop( puzzleDifficultyItem );

    /* Guess type setting item */
    CAknEnumeratedTextPopupSettingItem* guessTypeItem 
        = new (ELeave) CAknEnumeratedTextPopupSettingItem( EBlackboxSettingsGuessType, iGuessType );
    CleanupStack::PushL( guessTypeItem );
    guessTypeItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsGuessType, // ordinal
            _L( "Guess type" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_GUESSTYPE, // setting page resource id
            -1, // editor control type
            0, // setting editor resource id
            R_BLACKBOX_SETTING_GUESSTYPE_TEXT // associated resource id
            );

    iSettingsList->SettingItemArray()->AppendL( guessTypeItem );
    CleanupStack::Pop( guessTypeItem );
    
    /* Number of nodes setting item */
    CBlackboxSliderSettingItem* numberOfNodesItem
        = new (ELeave) CBlackboxSliderSettingItem( EBlackboxSettingsNumberOfNodes, iNumberOfNodes );
    CleanupStack::PushL( numberOfNodesItem );
    numberOfNodesItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsNumberOfNodes,  // ordinal
            _L( "Number of nodes" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_NUMBEROFNODES, // setting page resource id
            -1 // editor control type
            );
    iSettingsList->SettingItemArray()->AppendL( numberOfNodesItem );
    CleanupStack::Pop( numberOfNodesItem );
    
    
    /* Unlimited rays setting item */
    CBlackboxCheckboxSettingItem* unlimitedRaysItem
        = new (ELeave) CBlackboxCheckboxSettingItem( EBlackboxSettingsUnlimitedRays, iUnlimitedRays );
    CleanupStack::PushL( unlimitedRaysItem );
    unlimitedRaysItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsNumberOfNodes,  // ordinal
            _L( "Rays' number" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_UNLIMITEDRAYS, // setting page resource id
            -1, // editor control type
            0, // setting editor resource id
            R_BLACKBOX_SETTING_UNLIMITEDRAYS_TEXT // associated resource id
            );
    iSettingsList->SettingItemArray()->AppendL( unlimitedRaysItem );
    CleanupStack::Pop( unlimitedRaysItem );
    
    
    // ToDo:
    
    /* Vibration setting item */

    CAknBinaryPopupSettingItem* vibrationItem
        = new (ELeave) CAknBinaryPopupSettingItem( EBlackboxSettingsVibration, iVibration );
    CleanupStack::PushL( vibrationItem );
    vibrationItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsVibration,  // ordinal
            _L( "Vibration" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_VIBRATION, // setting page resource id
            -1, // editor control type
            0, // setting editor resource id
            R_BLACKBOX_SETTING_BINARY_TEXT // associated resource id
            );
    iSettingsList->SettingItemArray()->AppendL( vibrationItem );
    CleanupStack::Pop( vibrationItem );


    /* Sound setting item */

    CAknBinaryPopupSettingItem* soundItem
        = new (ELeave) CAknBinaryPopupSettingItem( EBlackboxSettingsSound, iSound );
    CleanupStack::PushL( soundItem );
    soundItem->ConstructL( 
            EFalse, // Is number style
            EBlackboxSettingsSound,  // ordinal
            _L( "Sound" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_SOUND, // setting page resource id
            -1, // editor control type
            0, // setting editor resource id
            R_BLACKBOX_SETTING_BINARY_TEXT // associated resource id
            );
    iSettingsList->SettingItemArray()->AppendL( soundItem );
    CleanupStack::Pop( soundItem );

    
    /* Volume setting item */

    CAknVolumeSettingItem* volumeItem 
        = new (ELeave) CAknVolumeSettingItem( EBlackboxSettingsVolumeValue, iVolumeValue );
    CleanupStack::PushL( volumeItem );
    volumeItem->ConstructL(
            EFalse, // Is number style
            EBlackboxSettingsSound,  // ordinal
            _L( "Volume value" ), // setting title
            icons, // icon array
            R_BLACKBOX_SETTING_PAGE_VOLUMEVALUE, // setting page resource id
            -1 // editor control type
            );
    iSettingsList->SettingItemArray()->AppendL( volumeItem );
    CleanupStack::Pop( volumeItem );

    if ( !iSound )
        {
        (*(iSettingsList->SettingItemArray()))
                [EBlackboxSettingsVolumeValue]->SetHidden(ETrue);
        iSettingsList->HandleChangeInItemArrayOrVisibilityL();
        }

    // Required when there is only one setting item.
    iSettingsList->SettingItemArray()->RecalculateVisibleIndicesL();

    iSettingsList->HandleChangeInItemArrayOrVisibilityL();
    }

// End of File
