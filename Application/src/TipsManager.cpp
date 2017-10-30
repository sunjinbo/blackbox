/* ====================================================================
 * File: TipsManager.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknUtils.h>
#include <Blackbox.rsg>
#include "TipsManager.h"
#include "Tips.h"
#include "Blackbox.pan"

// CONSTANTS
_LIT( KResourceFile, "\\resource\\apps\\Blackbox.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CTipsManager::NewL()
// ---------------------------------------------------------------------------
//
CTipsManager* CTipsManager::NewL()
    {
    CTipsManager* self = new (ELeave)CTipsManager;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CTipsManager::~CTipsManager()
// ---------------------------------------------------------------------------
//
CTipsManager::~CTipsManager()
    {
    iTipsArray.ResetAndDestroy();
    iTipsArray.Close();
    }

// ---------------------------------------------------------------------------
// CTipsManager::Tips()
// ---------------------------------------------------------------------------
//
CTips* CTipsManager::Tips() const
    {
    __ASSERT_ALWAYS( iCurrentTips < Count(), Panic( EBlackboxBadIndex ) );
    return iTipsArray[iCurrentTips];;;
    }

// ---------------------------------------------------------------------------
// CTipsManager::Count()
// ---------------------------------------------------------------------------
//
TInt CTipsManager::Count() const
    {
    return iTipsArray.Count();
    }

// --------------------------------------------------------------------------
// CTipsManager::Next()
// ---------------------------------------------------------------------------
//
void CTipsManager::Next()
    {
    ++iCurrentTips;
    if ( iCurrentTips >= iTipsArray.Count() )
        {
        iCurrentTips = 0;
        }
    iBlackboxSettings.iTipsIndex = iCurrentTips;
    // stores settings to file
    TRAP_IGNORE( iBlackboxSettings.ExternalizedL() );
    }

// ---------------------------------------------------------------------------
// CTipsManager::ConstructL()
// ---------------------------------------------------------------------------
//
void CTipsManager::ConstructL()
    {
    // Load blackbox settings
    iBlackboxSettings.InternalizedL();

    // Load resource file
    RFs& fileSession = iCoeEnv.FsSession();
    TFileName rscFileName( KResourceFile );
    TInt err = CompleteWithAppPath( rscFileName );
    if ( err != KErrNotSupported )
        {
        User::LeaveIfError( err );
        }

    // Get the exact filename of the resource file
    BaflUtils::NearestLanguageFile( fileSession, rscFileName );
    // Check if the resource file exists or not
    if ( ! BaflUtils::FileExists( fileSession, rscFileName ) )
        {
        User::Leave( KErrNotFound );
        }

    TInt offset = 0;
    TRAP( err, offset = iCoeEnv.AddResourceFileL( rscFileName ) );
    TResourceReader reader;
    iCoeEnv.CreateResourceReaderLC( reader, R_BLACKBOX_TIPS_LIST );

    TRAPD( error, CreateResourceReaderL( reader ) );
    if ( error )
        {
        iTipsArray.ResetAndDestroy();
        User::Leave( error );
        }

    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( offset );
    offset = 0;
    }

// ---------------------------------------------------------------------------
// CTipsManager::CTipsManager()
// ---------------------------------------------------------------------------
//
CTipsManager::CTipsManager()
: iCoeEnv( *CCoeEnv::Static() )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CTipsManager::CreateResourceReaderL()
// ---------------------------------------------------------------------------
//
void CTipsManager::CreateResourceReaderL( TResourceReader& aReader )
    {
    // The second WORD contains the number of DATA structs within the resource
    TInt number = aReader.ReadInt16();

    // Add all newly created CGameLevel objects to the array
    for ( TInt ix = 0; ix < number; ix++ )
        {
        CTips* tips = CTips::NewL( aReader );
        iTipsArray.Append( tips );
        }

    // Sorts these tip(s) by id
    Sort();
    }

// ----------------------------------------------------------------------------
// CTipsManager::Sort
// ----------------------------------------------------------------------------
//
void CTipsManager::Sort()
    {
    TLinearOrder<CTips> order( CTips::Compare );
    iTipsArray.Sort( order );
    }

// End of file
