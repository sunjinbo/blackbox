/* ====================================================================
 * File: BlackboxSettings.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef BLACKBOXSETTINGS_H
#define BLACKBOXSETTINGS_H

// INCLUDE
#include <e32def.h>
#include "Blackbox.hrh"

// FORWARD DECLARATION
class RFs;

// CLASS DECLARATION

/**
 *  TBlackboxSettings class
 */
class TBlackboxSettings
    {
public: // Default C++ constructor
    TBlackboxSettings();
    TBlackboxSettings( const TBlackboxSettings& aSettings );
    TBlackboxSettings& operator=( const TBlackboxSettings& aSettings );

public: // new methods
    void InternalizedL();
    void ExternalizedL();

private:
    void CreateDefaultSettingsL();

public: // Data
    RFs& iFs;
    TBool iFirstTimeUse;
    TBlackboxAvatar iAvatar;
    TBlackboxPuzzleDifficulty iDifficulty;
    TBlackboxGuessType iGuessType;
    TInt iNumberOfNodes;
    TInt iMaxRays;
    TBool iUnlimitedRays;
    TBool iVibration;
    TBool iSound;
    TInt iVolumeValue;
    TInt iTipsIndex;
    };

#endif // BLACKBOXSETTINGS_H

// End Of File
