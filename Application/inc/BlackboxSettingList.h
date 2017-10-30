/* ====================================================================
 * File: BlackboxSettingList.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXSETTINGLIST_H
#define C_BLACKBOXSETTINGLIST_H

// INCLUDES
#include <AknSettingItemList.h>
#include "BlackboxSettings.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  MSettingsListObserver
*/
class MSettingsListObserver
    {
public: // callback function
    virtual void HandleItemChangedL( TInt aIndex ) = 0;
    };

/**
*  CBlackboxSettingList
*/
class CBlackboxSettingList : public CAknSettingItemList
    {
public: // Constructors and destructor
    static CBlackboxSettingList* NewL( MSettingsListObserver& aObs );
    virtual ~CBlackboxSettingList();

public:
    void SetListBoxContentL();

private: // Symbian 2nd constructors
    void ConstructL();
    CBlackboxSettingList( MSettingsListObserver& aObs );

private: // CAknSettingItemList 
    void EditItemL( TInt aIndex, TBool aCalledFromMenu );

private: // Member data
    MSettingsListObserver& iObserver;
    TInt iAvatar;
    TInt iPuzzleDifficulty;
    TInt iGuessType;
    TInt iNumberOfNodes;
    CArrayFixFlat<TInt> iUnlimitedRays;
    TBool iVibration;
    TBool iSound;
    TInt iVolumeValue;
    };

#endif // C_BLACKBOXSETTINGLIST_H

// End of File
