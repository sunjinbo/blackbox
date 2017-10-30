/* ====================================================================
 * File: BlackboxSettings.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <f32file.h>
#include <s32file.h>
#include <eikenv.h>
#include "BlackboxSettings.h"

// CONSTANTS
const TBool KDefaultFirstTimeUse = ETrue;
const TBlackboxAvatar KDefaultAvatar = EAvatarLeslie;
const TBlackboxPuzzleDifficulty KDefaultDifficulty = EPuzzleEasy;
const TBlackboxGuessType KDefaultGuessType = EAllAtATime;
const TInt KDefaultNumberOfNodes = 4;
const TInt KDefaultMaxRays = 8;
const TBool KDefaultUnlimitedRays = EFalse;
const TBool KDefaultVibration = ETrue;
const TBool KDefaultSound = ETrue;
const TInt KDefaultVolumeValue = 3;
const TInt KDefaultTipsIndex = 0;

_LIT( KBlackboxFile, "Blackbox.txt" );

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// TBlackboxSettings::TBlackboxSettings()
// ---------------------------------------------------------------------------
//
TBlackboxSettings::TBlackboxSettings()
: iFs( CCoeEnv::Static()->FsSession() )
  , iAvatar( KDefaultAvatar )
  , iDifficulty( EPuzzleEasy )
  , iGuessType( EAllAtATime )
  , iNumberOfNodes( KDefaultNumberOfNodes )
  , iMaxRays( KDefaultMaxRays )
  , iUnlimitedRays( EFalse )
  , iVibration( ETrue )
  , iSound( ETrue )
  , iVolumeValue( KDefaultVolumeValue )
  , iTipsIndex( KDefaultTipsIndex )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// TBlackboxSettings::TBlackboxSettings()
// ---------------------------------------------------------------------------
//
TBlackboxSettings::TBlackboxSettings( const TBlackboxSettings& aSettings )
: iFs( CCoeEnv::Static()->FsSession() )
    {
    iFirstTimeUse = aSettings.iFirstTimeUse;
    iAvatar = aSettings.iAvatar;
    iDifficulty = aSettings.iDifficulty;
    iGuessType = aSettings.iGuessType;
    iNumberOfNodes = aSettings.iNumberOfNodes;
    iMaxRays = aSettings.iMaxRays;
    iUnlimitedRays = aSettings.iUnlimitedRays;
    iVibration = aSettings.iVibration;
    iSound = aSettings.iSound;
    iVolumeValue = aSettings.iVolumeValue;
    iTipsIndex = aSettings.iTipsIndex;
    }

// ---------------------------------------------------------------------------
// TBlackboxSettings::operator=()
// ---------------------------------------------------------------------------
//
TBlackboxSettings& TBlackboxSettings::operator=( const TBlackboxSettings& aSettings )
    {
    iFirstTimeUse = aSettings.iFirstTimeUse;
    iAvatar = aSettings.iAvatar;
    iDifficulty = aSettings.iDifficulty;
    iGuessType = aSettings.iGuessType;
    iNumberOfNodes = aSettings.iNumberOfNodes;
    iMaxRays = aSettings.iMaxRays;
    iUnlimitedRays = aSettings.iUnlimitedRays;
    iVibration = aSettings.iVibration;
    iSound = aSettings.iSound;
    iVolumeValue = aSettings.iVolumeValue;
    iTipsIndex = aSettings.iTipsIndex;

    return *this;
    }

// ---------------------------------------------------------------------------
// TBlackboxSettings::InternalizedL()
// ---------------------------------------------------------------------------
//
void TBlackboxSettings::InternalizedL()
    {
    RFile file;
    while ( file.Open( iFs, KBlackboxFile, EFileRead ) != KErrNone )
        {
        CreateDefaultSettingsL();
        }

    RFileReadStream inStream( file );
    CleanupClosePushL( inStream );

    TInt32 value = 0;
    value = inStream.ReadInt32L();
    iFirstTimeUse = (TBool)value;
    value = inStream.ReadInt32L();
    iAvatar = (TBlackboxAvatar)value;
    value = inStream.ReadInt32L();
    iDifficulty = (TBlackboxPuzzleDifficulty)value;
    value = inStream.ReadInt32L();
    iGuessType = (TBlackboxGuessType)value;
    value = inStream.ReadInt32L();
    iNumberOfNodes = (TInt)value;
    value = inStream.ReadInt32L();
    iMaxRays = (TInt)value;
    value = inStream.ReadInt32L();
    iUnlimitedRays = (TBool)value;
    value = inStream.ReadInt32L();
    iVibration = (TBool)value;
    value = inStream.ReadInt32L();
    iSound = (TBool)value;
    value = inStream.ReadInt32L();
    iVolumeValue = (TInt)value;
    value = inStream.ReadInt32L();
    iTipsIndex = (TInt)value;

    CleanupStack::PopAndDestroy( &inStream );
    file.Close();
    }

// ---------------------------------------------------------------------------
// TBlackboxSettings::ExternalizedL()
// ---------------------------------------------------------------------------
//
void TBlackboxSettings::ExternalizedL()
    {
    RFile file;
    while ( file.Open( iFs, KBlackboxFile, EFileWrite ) != KErrNone )
        {
        CreateDefaultSettingsL();
        }

    RFileWriteStream outStream( file );
    CleanupClosePushL( outStream );

    outStream.WriteInt32L( (TInt32)iFirstTimeUse );
    outStream.WriteInt32L( (TInt32)iAvatar );
    outStream.WriteInt32L( (TInt32)iDifficulty );
    outStream.WriteInt32L( (TInt32)iGuessType );
    outStream.WriteInt32L( (TInt32)iNumberOfNodes );
    outStream.WriteInt32L( (TInt32)iMaxRays );
    outStream.WriteInt32L( (TInt32)iUnlimitedRays );
    outStream.WriteInt32L( (TInt32)iVibration );
    outStream.WriteInt32L( (TInt32)iSound );
    outStream.WriteInt32L( (TInt32)iVolumeValue );
    outStream.WriteInt32L( (TInt32)iTipsIndex );

    outStream.CommitL();
    CleanupStack::PopAndDestroy( &outStream );
    file.Close();
    }

// ---------------------------------------------------------------------------
// TBlackboxSettings::CreateDefaultSettingsL()
// ---------------------------------------------------------------------------
//
void TBlackboxSettings::CreateDefaultSettingsL()
    {
    RFile file;
    User::LeaveIfError( file.Create( iFs, KBlackboxFile, EFileWrite ) );
    RFileWriteStream outStream( file );
    CleanupClosePushL( outStream );

    outStream.WriteInt32L( (TInt32)KDefaultFirstTimeUse );
    outStream.WriteInt32L( (TInt32)KDefaultAvatar );
    outStream.WriteInt32L( (TInt32)KDefaultDifficulty );
    outStream.WriteInt32L( (TInt32)KDefaultGuessType );
    outStream.WriteInt32L( (TInt32)KDefaultNumberOfNodes );
    outStream.WriteInt32L( (TInt32)KDefaultMaxRays );
    outStream.WriteInt32L( (TInt32)KDefaultUnlimitedRays );
    outStream.WriteInt32L( (TInt32)KDefaultVibration );
    outStream.WriteInt32L( (TInt32)KDefaultSound );
    outStream.WriteInt32L( (TInt32)KDefaultVolumeValue );
    outStream.WriteInt32L( (TInt32)KDefaultTipsIndex );

    outStream.CommitL();
    CleanupStack::PopAndDestroy( &outStream );
    file.Close();
    }

// End of file
