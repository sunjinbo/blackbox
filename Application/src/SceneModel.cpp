/* ====================================================================
 * File: SceneModel.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknUtils.h>
#include <coecntrl.h>
#include <Blackbox_scene.mbg>
#include "SceneModel.h"
#include "ModelObserver.h"
#include "BoxFactory.h"
#include "Blackbox.pan"
#include "Box.h"
#include "TriggerBehavior.h"
#include "BlackboxConfig.h"
#include "Mirror.h"
#include "Blackbox.hrh"
#include "Blackbox.h"
#include "BlackboxBmpUtils.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KSceneFileName, "Z:\\resource\\apps\\Blackbox_scene.mbm" );
#else
_LIT( KSceneFileName, "\\resource\\apps\\Blackbox_scene.mbm" );
#endif // __WINS__

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CSceneModel:NewL()
// ---------------------------------------------------------------------------
//
CSceneModel* CSceneModel::NewL( MModelObserver& aObs,
        CFbsBitGc& aGc, const TRect& aRect )
    {
    CSceneModel* self = new ( ELeave ) CSceneModel( aObs, aGc );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CSceneModel::NewL()
// ---------------------------------------------------------------------------
//
CSceneModel::~CSceneModel()
    {
    iBoxArray.ResetAndDestroy();
    iBoxArray.Close();
    //iRaysArray.ResetAndDestroy();
    iRaysArray.Close();
    iMirrorArray.ResetAndDestroy();
    iMirrorArray.Close();
    iCoeEnv.ScreenDevice()->ReleaseFont( iIndexFont );

    delete iBoxFactory;
    delete iBmpUtils;
    }

// ---------------------------------------------------------------------------
// CSceneModel::TriggerL()
// ---------------------------------------------------------------------------
//
void CSceneModel::TriggerL( TInt aX, TInt aY )
    {
    CBox* box = Box( aX, aY );
    if ( box != NULL )
        {
        MTriggerBehavior* behavior = static_cast<CBox*>( box );
        behavior->TriggerL();
        }
    }

// ---------------------------------------------------------------------------
// CSceneModel::OnDraw()
// ---------------------------------------------------------------------------
//
void CSceneModel::OnDraw()
    {
    TInt i = 0;
    // draw blackbox
    for ( i = 0; i < iBoxArray.Count(); i++ )
        {
        if ( ( iBoxArray[i]->Position().iX == 0 ) 
            || ( iBoxArray[i]->Position().iY == 0 ) 
            || ( iBoxArray[i]->Position().iX == KHorizBoxNumber - 1 ) 
            || ( iBoxArray[i]->Position().iY == KVerticalBoxNumber- 1 ) )
            {
            // do nothing.
            }
        else
            {
            iBoxArray[i]->OnDraw();
            }
        }

    // draw rays
    for ( i = 0; i < iRaysArray.Count(); i++ )
        {
        iRaysArray[i]->OnDraw();
        }
    
    // draw mirror
    for ( i = 0; i < iMirrorArray.Count(); i++ )
        {
        iMirrorArray[i]->OnDraw();
        }

    // draw lightbox and nookbox
    for ( i = 0; i < iBoxArray.Count(); i++ )
        {
        if ( ( iBoxArray[i]->Position().iX == 0 ) 
            || ( iBoxArray[i]->Position().iY == 0 ) 
            || ( iBoxArray[i]->Position().iX == KHorizBoxNumber - 1 ) 
            || ( iBoxArray[i]->Position().iY == KVerticalBoxNumber- 1 ) )
            {
            iBoxArray[i]->OnDraw();
            }
        }
    }

// ---------------------------------------------------------------------------
// CSceneModel::HandleCommandL()
// ---------------------------------------------------------------------------
//
void CSceneModel::HandleCommandL( TInt aCommand )
    {
    switch( aCommand )
        {
        case ESceneGuessCmd:
            DoGuessL();
            break;
        case ESceneSkipGuessCmd:
            break;
            
        case ESceneSolvePuzzleCmd:
            {
            SolvePuzzleL();
            }
            break;
            
        case ESceneRestartCmd:
            {
            iBoxArray.ResetAndDestroy();
            iMirrorArray.ResetAndDestroy();
            iRaysArray.Reset();
            iBoxFactory->GetBoxArrayL( iBoxArray );
            iBoxFactory->GetMirrorArrayL( iMirrorArray );
            }
            break;

        case ESceneUpdateSettingsCmd:
            {
            // Updates settings.
            iSettings.InternalizedL();
            }
            break;

        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CSceneModel::StateChangedL()
// ---------------------------------------------------------------------------
//
void CSceneModel::StateChangedL( TInt aNewState )
    {
    iObs.StateChangedL( aNewState );
    }

// ---------------------------------------------------------------------------
// CSceneModel::RaysCreated()
// ---------------------------------------------------------------------------
//
void CSceneModel::RaysCreated( CRays* aNewRays )
    {
    aNewRays->SetObserver( this );
    iRaysArray.Append( aNewRays );
    TRAP_IGNORE( iObs.StateChangedL( ESceneRaysCreated ) );
    }

// ---------------------------------------------------------------------------
// CSceneModel::BoxRect()
// ---------------------------------------------------------------------------
//
TRect CSceneModel::BoxRect( TInt aX, TInt aY ) const
    {
    __ASSERT_DEBUG( ( aX >= 0 ) && ( aX < KHorizBoxNumber ), Panic( EBlackboxInvaildParam ) );
    __ASSERT_DEBUG( ( aY >= 0 ) && ( aX < KVerticalBoxNumber ), Panic( EBlackboxInvaildParam ) );
    TInt w = iRect.Width() / KHorizBoxNumber;
    TInt h = iRect.Height() / KVerticalBoxNumber;
    TInt x = iRect.iTl.iX + w * aX;
    TInt y = iRect.iTl.iY + h * aY;
    return TRect( TPoint( x, y ), TSize( w, h ) );
    }

// ---------------------------------------------------------------------------
// CSceneModel::Box()
// ---------------------------------------------------------------------------
//
CBox* CSceneModel::Box( TInt aX, TInt aY ) const
    {
    CBox* box = NULL;
    for ( TInt i = 0; i < iBoxArray.Count(); i++ )
        {
        if ( iBoxArray[i]->Position() == TPoint( aX, aY )  )
            {
            box = iBoxArray[i];
            break;
            }
        }
    return box;
    }

// ---------------------------------------------------------------------------
// CSceneModel::HasMirror()
// ---------------------------------------------------------------------------
//
TBool CSceneModel::HasMirror( TInt aX, TInt aY ) const
    {
    TBool hasMirror = EFalse;
    if ( Mirror( aX, aY ) != NULL )
        {
        hasMirror = ETrue;
        }
    return hasMirror;
    }

// ---------------------------------------------------------------------------
// CSceneModel::BmpContext()
// ---------------------------------------------------------------------------
//
CFbsBitGc& CSceneModel::BmpContext() const
    {
    return iGc;
    }

// ---------------------------------------------------------------------------
// CSceneModel::Bitmap()
// ---------------------------------------------------------------------------
//
CFbsBitmap* CSceneModel::Bitmap( TInt aIndex ) const
    {
    return iBmpUtils->Bitmap( aIndex );
    }

// ---------------------------------------------------------------------------
// CSceneModel::IndexFont()
// ---------------------------------------------------------------------------
//
CFont* CSceneModel::IndexFont() const
    {
    return iIndexFont;
    }

// ---------------------------------------------------------------------------
// CSceneModel::RaysCount()
// ---------------------------------------------------------------------------
//
TInt CSceneModel::RaysCount() const
    {
    return iRaysArray.Count();
    }

// ---------------------------------------------------------------------------
// CSceneModel::Settings()
// ---------------------------------------------------------------------------
//
const TBlackboxSettings& CSceneModel::Settings() const
    {
    return iSettings;
    }

// ---------------------------------------------------------------------------
// CSceneModel::DoEffectL()
// ---------------------------------------------------------------------------
//
void CSceneModel::DoEffectL( TInt aEffectType, TInt aX, TInt aY )
    {
    iObs.DoEffectL( aEffectType, aX, aY );
    }

// ---------------------------------------------------------------------------
// CSceneModel::AnimCompltedL()
// ---------------------------------------------------------------------------
//
void CSceneModel::AnimCompltedL()
    {
    ++iRaysIndex;
    if ( iRaysIndex >= iRaysArray.Count() )
        {
        iRaysIndex = 0;
        }
    iRaysArray[iRaysIndex]->Start();
    }

// ---------------------------------------------------------------------------
// CSceneModel::ConstructL()
// ---------------------------------------------------------------------------
//
void CSceneModel::ConstructL( const TRect& aRect )
    {
    __ASSERT_DEBUG( ( aRect.IsEmpty() == EFalse ), Panic( EBlackboxInvaildParam ) );
    
    iRect = aRect;
    
    iBmpUtils = CBlackboxBmpUtils::NewL( 
            KSceneFileName,
            EMbmBlackbox_sceneMirror1,
            EMbmBlackbox_sceneLastElement );
    
    ScaleBmpUtils();
    
    iSettings.InternalizedL();
    
    iBoxFactory = CBoxFactory::NewL( *this, iSettings );
    
    iBoxFactory->GetBoxArrayL( iBoxArray );

    iBoxFactory->GetMirrorArrayL( iMirrorArray );

    TFontSpec fontSpec = iCoeEnv.NormalFont()->FontSpecInTwips();
    fontSpec.iFontStyle.SetBitmapType( EMonochromeGlyphBitmap );
    fontSpec.iHeight = fontSpec.iHeight / 3;

    User::LeaveIfError( iCoeEnv.ScreenDevice()->GetNearestFontInTwips( iIndexFont, fontSpec ) );
    }

// ---------------------------------------------------------------------------
// CSceneModel::ConstructL()
// ---------------------------------------------------------------------------
//
CSceneModel::CSceneModel( MModelObserver& aObs, CFbsBitGc& aGc )
: iObs( aObs ), iGc( aGc ), iCoeEnv( *CCoeEnv::Static() )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CSceneModel::SolvePuzzleL()
// ---------------------------------------------------------------------------
//
void CSceneModel::SolvePuzzleL()
    {
    for ( TInt i = 0; i < iRaysArray.Count(); i++ )
        {
        iRaysArray[i]->SetVisible( ETrue );
        }
    
    // start to show the animation of rays.
    if ( iRaysArray.Count() > 0 )
        {
        iRaysIndex = 0;
        iRaysArray[iRaysIndex]->Start();
        }

    for ( TInt j = 0; j < iMirrorArray.Count(); j++ )
        {
        iMirrorArray[j]->SetFullMirror( ETrue );
        iMirrorArray[j]->SetVisible( ETrue );
        }
    }

// ---------------------------------------------------------------------------
// CSceneModel::DoGuessL()
// ---------------------------------------------------------------------------
//
void CSceneModel::DoGuessL()
    {
    TInt numberOfNodes = iSettings.iNumberOfNodes;
    TInt numberOfGuessedNodes = 0;

    for ( TInt i = 1; i < KHorizBoxNumber - 1; i++ )
        for ( TInt j = 1; j < KVerticalBoxNumber - 1; j++ )
            {
            CBox* box = Box( i, j );
            
            if ( iSettings.iGuessType == EAllAtATime )
                {
                if ( box && box->State() == EGuessing )
                    {
                    CMirror* mirror = Mirror( i, j );
                    if ( mirror != NULL )
                        {
                        mirror->SetGuessed( ETrue );
                        box->UpdateStateL( EGuessed );
                        }
                    else
                        {
                        box->UpdateStateL( EGuessFailed );
                        }
                    //break;
                    }
                
                if ( box && box->State() == EGuessed )
                    {
                    ++numberOfGuessedNodes;
                    if ( numberOfGuessedNodes == iSettings.iNumberOfNodes )
                        {
                        iObs.StateChangedL( ESceneGameOver );
                        }
                    }
                }
            else
                {
                if ( box && box->State() == EGuessing )
                    {
                    if ( HasMirror( i, j ) )
                        {
                        --numberOfNodes;
                        if ( numberOfNodes == 0 )
                            {
                            // ...success
                            break;
                            }
                        }
                    else
                        {
                        // failed..
                        break;
                        }
                    }
                }
            }
    }

// ---------------------------------------------------------------------------
// CSceneModel::ScaleBmpUtils()
// ---------------------------------------------------------------------------
//
void CSceneModel::ScaleBmpUtils()
    {
    TSize boxSize;
    boxSize.iWidth = iRect.Width() / KHorizBoxNumber;
    boxSize.iHeight = iRect.Height() / KVerticalBoxNumber;
    
    for ( TInt i = EMbmBlackbox_sceneMirror1; i < EMbmBlackbox_sceneLastElement; i++ )
        {
        iBmpUtils->SetSize( i, boxSize );
        }
    }

// ---------------------------------------------------------------------------
// CSceneModel::Mirror()
// ---------------------------------------------------------------------------
//
CMirror* CSceneModel::Mirror( TInt aX, TInt aY ) const
    {
    CMirror* mirror = NULL;
    for ( TInt i = 0; i < iMirrorArray.Count(); i++ )
        {
        if ( iMirrorArray[i]->Position() == TPoint( aX, aY ) )
            {
            mirror = iMirrorArray[i];
            break;
            }
        }
    return mirror;
    }

// End of file
