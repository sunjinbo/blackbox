/* ====================================================================
 * File: BlackboxSettingList.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <Blackbox.rsg>
#include "BlackboxSettingList.h"
#include "BlackboxSliderSettingItem.h"
#include "Blackbox.hrh"
#include "BlackboxCheckboxSettingItem.h"

// CONSTANTS

// ========================= MEMBER FUNCTIONS ==================================


// -----------------------------------------------------------------------------
// CBlackboxSettingList::NewL
// -----------------------------------------------------------------------------
//
CBlackboxSettingList* CBlackboxSettingList::NewL( MSettingsListObserver& aObs )
    {
    CBlackboxSettingList* self = new ( ELeave ) CBlackboxSettingList( aObs );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingList::~CBlackboxSettingList
// -----------------------------------------------------------------------------
//
CBlackboxSettingList::~CBlackboxSettingList()
    {
    iUnlimitedRays.Reset();
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingList::SetListBoxContentL
// -----------------------------------------------------------------------------
//
void CBlackboxSettingList::SetListBoxContentL()
    {
    CArrayPtr<CGulIcon>* icons = 
            ListBox()->ItemDrawer()->FormattedCellData()->IconArray();

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

    SettingItemArray()->AppendL( avatarItem );
    CleanupStack::Pop( avatarItem );
    
    /* Puzzle difficulty setting item */
    CAknEnumeratedTextPopupSettingItem* puzzleDifficultyItem 
        = new (ELeave) CAknEnumeratedTextPopupSettingItem( EBlackboxSettingsPuzzleDifficulty, iPuzzleDifficulty );
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

    SettingItemArray()->AppendL( puzzleDifficultyItem );
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

    SettingItemArray()->AppendL( guessTypeItem );
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
    SettingItemArray()->AppendL( numberOfNodesItem );
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
    SettingItemArray()->AppendL( unlimitedRaysItem );
    CleanupStack::Pop( unlimitedRaysItem );
    
    
    // ToDo:
    
    /* Vibration setting item */
    /*
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
    */

    /* Sound setting item */
    /*
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
    */
    
    /* Volume setting item */
    /*
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
    */

    // Required when there is only one setting item.
    SettingItemArray()->RecalculateVisibleIndicesL();

    HandleChangeInItemArrayOrVisibilityL();
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingList::ConstructL
// -----------------------------------------------------------------------------
//
void CBlackboxSettingList::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingList::CBlackboxSettingList
// -----------------------------------------------------------------------------
//
CBlackboxSettingList::CBlackboxSettingList( MSettingsListObserver& aObs )
     : iObserver( aObs ), iUnlimitedRays( 3 )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingList::EditCurrentItemL
// -----------------------------------------------------------------------------
//
void CBlackboxSettingList::EditItemL( TInt aIndex, TBool aCalledFromMenu )
    {
    // Invoke EditItemL on the current item
    CAknSettingItemList::EditItemL( aIndex/*ListBox()->CurrentItemIndex()*/,    // the item index
            aCalledFromMenu );    // invoked from menu

    //Updating CAknPasswordSettingItem.
    /*
    if( ListBox()->CurrentItemIndex() == 5 )
        {
        (*(SettingItemArray()))[ListBox()->CurrentItemIndex()]->UpdateListBoxTextL();
        }
    */
    StoreSettingsL();
    
    iObserver.HandleItemChangedL( aIndex );
    }

// End of File
