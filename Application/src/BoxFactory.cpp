/* ====================================================================
 * File: BoxFactory.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include "BoxFactory.h"
#include "SceneModel.h"
#include "BlackboxConfig.h"
#include "Blackbox.h"
#include "Nookbox.h"
#include "Lightbox.h"
#include "Mirror.h"

// CONSTANS
const TInt KPuzzleEasyGap = 3;
const TInt KPuzzleChallengeGap = 0;

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CBoxFactory::NewL()
// ---------------------------------------------------------------------------
//
CBoxFactory* CBoxFactory::NewL( CSceneModel& aModel, TBlackboxSettings& aSettings )
    {
    CBoxFactory* self = new ( ELeave ) CBoxFactory( aModel, aSettings );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CBoxFactory::GetBoxArrayL()
// ---------------------------------------------------------------------------
//
void CBoxFactory::GetBoxArrayL( RPointerArray<CBox>& aBoxArray )
    {
    aBoxArray.ResetAndDestroy();
    
    // Create lightbox, blackbox and nookbox
    for ( TInt i = 0; i < KHorizBoxNumber; i++ )   
        for ( TInt j = 0; j < KVerticalBoxNumber; j++ )
            {
            if ( ( i == 0 ) 
                || ( j == 0 ) 
                || ( i == KHorizBoxNumber - 1 ) 
                || ( j == KVerticalBoxNumber- 1 ) )
                {
                if ( ( i > 0 && i < KHorizBoxNumber - 1 )
                    || ( j > 0 && j < KVerticalBoxNumber - 1 ) )
                    {
                    CLightbox* lightbox 
                        = CLightbox::NewL( iModel, iModel, TPoint( i, j ) );
                    aBoxArray.Append( lightbox );
                    }
                else
                    {
                    CNookbox* nookbox 
                        = CNookbox::NewL( iModel, iModel, TPoint( i, j ) );
                    aBoxArray.Append( nookbox );
                    }
                continue;
                }
            CBlackbox* blackbox 
                = CBlackbox::NewL( iModel, iModel, TPoint( i, j ) );
            aBoxArray.Append( blackbox );
            }
    }

// ---------------------------------------------------------------------------
// CBoxFactory::GetMirrorArrayL()
// ---------------------------------------------------------------------------
//
void CBoxFactory::GetMirrorArrayL( RPointerArray<CMirror>& aMirrorArray )
    {
    // Create mirror
    TInt numberOfNodes = 0;
    TInt puzzleEasyGap = KPuzzleEasyGap;
    TInt count = 0;
    while( iSettings.iNumberOfNodes > numberOfNodes )
        {
        TInt x = Rand( KHorizBoxNumber - 2 ) + 1;
        TInt y = Rand( KVerticalBoxNumber - 2 ) + 1;
        
        TBool repeat = EFalse;
        for ( TInt i = 0; i < aMirrorArray.Count(); i++ )
            {
            TInt xGap = Abs( aMirrorArray[i]->Position().iX - x );
            TInt yGap = Abs( aMirrorArray[i]->Position().iY - y );
            TInt pGap = puzzleEasyGap;

            if ( iSettings.iDifficulty == EPuzzleChallenge )
                {
                pGap = KPuzzleChallengeGap;
                }

            if ( xGap <= pGap && yGap <= pGap )
                {
                repeat = ETrue;
                break;
                }
            }

        if ( !repeat )
            {
            CMirror* mirror 
                = CMirror::NewL( iModel, TPoint( x, y ) );
            aMirrorArray.Append( mirror );
            ++numberOfNodes;
            }
            
        ++count;
        if ( count >= ( KHorizBoxNumber - 2 ) * ( KVerticalBoxNumber - 2 ) )
            {
            --puzzleEasyGap;
            count = 0;
            }
        }
    }

// ---------------------------------------------------------------------------
// CBoxFactory::SetSettings()
// ---------------------------------------------------------------------------
//
void CBoxFactory::SetSettings( const TBlackboxSettings& aSettings )
    {
    iSettings = aSettings;
    }

// ---------------------------------------------------------------------------
// CBoxFactory::ConstructL()
// ---------------------------------------------------------------------------
//
void CBoxFactory::ConstructL()
    {
    // no implemention required
    }

// ---------------------------------------------------------------------------
// CBoxFactory::CBoxFactory()
// ---------------------------------------------------------------------------
//
CBoxFactory::CBoxFactory( CSceneModel& aModel, TBlackboxSettings& aSettings )
: iModel( aModel ), iSettings( aSettings )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CBoxFactory::Rand
// ----------------------------------------------------------------------------
//
TInt CBoxFactory::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// End of file
