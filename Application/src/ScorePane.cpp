/* ====================================================================
 * File: ScorePane.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32property.h>
#include <e32math.h>
#include <eikenv.h>
#include <Blackbox_score.mbg>
#include "ScorePane.h"
#include "LayoutManager.h"
#include "BlackboxBmpUtils.h"
#include "BlackboxSettings.h"
#include "BlackboxPSKeys.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KScoreFileName, "Z:\\resource\\apps\\Blackbox_score.mbm" );
#else
_LIT( KScoreFileName, "\\resource\\apps\\Blackbox_score.mbm" );
#endif // __WINS__

const TInt KEffectGradualFrequency = 3;
const TInt KDefaultGuessIndex = 0;
const TInt KMinNumberOfRays = 0;

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CScorePane::NewL()
// ---------------------------------------------------------------------------
//
CScorePane* CScorePane::NewL( CFbsBitGc& aBmpContext, TBlackboxSettings& aSettings )
    {
    CScorePane* self = new ( ELeave ) CScorePane( aBmpContext, aSettings );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScorePane::~CScorePane()
// ---------------------------------------------------------------------------
//
CScorePane::~CScorePane()
    {
    delete iLayoutManager;
    delete iBmpUtils;
    iDrawerItemArray.Close();
    }

// ----------------------------------------------------------------------------
// CScorePane::DoDraw
// ----------------------------------------------------------------------------
//
void CScorePane::OnDraw()
    {
    iBmpContext.SetPenStyle( CGraphicsContext::ESolidPen );
    iBmpContext.SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBmpContext.SetPenColor( KRgbBlack );
    iBmpContext.SetBrushColor( KRgbBlack );
    iBmpContext.DrawRect( Rect() );

    iBmpContext.SetPenStyle( CGraphicsContext::ENullPen );
    iBmpContext.SetBrushStyle( CGraphicsContext::ENullBrush );

    for ( TInt i = 0; i < iDrawerItemArray.Count(); i++ )
        {
        TInt bitmapId = 0;

        switch ( iDrawerItemArray[i].iDrawerType )
            {
            case TDrawerItem::EDrawerUnguess:
                {
                bitmapId = EMbmBlackbox_scoreUnguess;
                }
                break;

            case TDrawerItem::EDrawerGuess:
                {
                bitmapId = EMbmBlackbox_scoreGuessing;
                }
                break;

            case TDrawerItem::EDrawerGuessing:
                {
                bitmapId = iEffectGuessBitmapId;
                if ( iEffectGradualFrequency == 0 )
                    {
                    if ( !iEffectGuessRevert )
                        {
                        iEffectGuessBitmapId += 2;
                        if ( iEffectGuessBitmapId > EMbmBlackbox_scoreEffects8 )
                            {
                            iEffectGuessRevert = ETrue;
                            iEffectGuessBitmapId = EMbmBlackbox_scoreEffects8;
                            }
                        }
                    else
                        {
                        iEffectGuessBitmapId -= 2;
                        if ( iEffectGuessBitmapId < EMbmBlackbox_scoreEffects1 )
                            {
                            iEffectGuessRevert = EFalse;
                            iEffectGuessBitmapId = EMbmBlackbox_scoreEffects1;
                            }
                        }
                    }
                }
                break;

            case TDrawerItem::EDrawerGuessSuccess:
                {
                bitmapId = EMbmBlackbox_scoreGuessed;
                }
                break;

            default:
                break;
            }

        iBmpContext.BitBlt(
            iDrawerItemArray[i].iRect.iTl,
            iBmpUtils->Bitmap( bitmapId ),
            TRect( TPoint( 0, 0 ), iDrawerItemArray[i].iRect.Size() )
            );
        }
    
    ++iEffectGradualFrequency;
    if ( iEffectGradualFrequency == KEffectGradualFrequency )
        {
        iEffectGradualFrequency = 0;
        }
    
    // Draw residual rays

    const CFont* font = iEikonEnv->LegendFont();
    iBmpContext.UseFont( font );
    iBmpContext.SetPenStyle( CGraphicsContext::ESolidPen );
    
    TRgb color;

    switch ( iSettings.iAvatar )
        {
        case EAvatarLeslie:
            color = TRgb( 228, 108, 11 );
            break;
        case EAvatarMardeline:
            color = TRgb( 66, 173, 223 );
            break;
        case EAvatarRex:
            color = TRgb( 255, 255, 255 );
            break;
        default:
            break;
        }

    iBmpContext.SetPenColor( color );
    
    TBuf<256> buffer;
    if ( iSettings.iUnlimitedRays )
    	{
    	buffer.Append( _L( "Unlimited rays" ) );
    	}
    else
    	{
        buffer.Append( _L( "Residual rays: " ) );
        buffer.AppendNum( iNumberOfRays );
    	}

    TRect raysTextRect = iLayoutManager->LayoutRect( EScoreRaysPane );
    TInt baseline = 
        ( raysTextRect.Height() + font->HeightInPixels() ) / 2;

    iBmpContext.DrawText( buffer, raysTextRect, baseline, CGraphicsContext::ERight, 0 );

    iBmpContext.DiscardFont();
    }

// ---------------------------------------------------------------------------
// CScorePane::Reset()
// ---------------------------------------------------------------------------
//
void CScorePane::Reset()
    {
    iDrawerItemArray.Reset();

    TRect guessRect = iLayoutManager->LayoutRect( EScoreGuessPane );

    for ( TInt i = 0; i < iSettings.iNumberOfNodes; i++ )
        {
        TDrawerItem drawerItem;
        drawerItem.iDrawerType = TDrawerItem::EDrawerUnguess;
        drawerItem.iRect.iTl.iX = guessRect.iBr.iX - guessRect.Height() * ( i + 1 );
        drawerItem.iRect.iTl.iY = guessRect.iTl.iY;
        drawerItem.iRect.iBr.iX = guessRect.iBr.iX - guessRect.Height() * i;
        drawerItem.iRect.iBr.iY = guessRect.iBr.iY;

        iDrawerItemArray.Append( drawerItem );
        }
    
    iEffectGuessBitmapId = EMbmBlackbox_scoreEffects1;
    iEffectGuessRevert = EFalse;
    iNumberOfRays = iSettings.iMaxRays;
    }

// ---------------------------------------------------------------------------
// CScorePane::AddGuess()
// ---------------------------------------------------------------------------
//
void CScorePane::AddGuess()
    {
    TInt index = CurrentGuessIndex();
    iDrawerItemArray[ index ].iDrawerType 
        = TDrawerItem::EDrawerGuess;
    }

// ---------------------------------------------------------------------------
// CScorePane::RemoveGuess()
// ---------------------------------------------------------------------------
//
void CScorePane::RemoveGuess()
    {
    TInt index = CurrentGuessIndex();
    --index;
    iDrawerItemArray[ index ].iDrawerType 
        = TDrawerItem::EDrawerUnguess;
    }

// ---------------------------------------------------------------------------
// CScorePane::SetGuess()
// ---------------------------------------------------------------------------
//
void CScorePane::SetGuess()
    {
    for ( TInt i = 0; i < iDrawerItemArray.Count(); i++ )
        {
        if ( iDrawerItemArray[i].iDrawerType == TDrawerItem::EDrawerGuessing )
            {
            iDrawerItemArray[i].iDrawerType
                = TDrawerItem::EDrawerGuess;
            }
        }
    }

// ---------------------------------------------------------------------------
// CScorePane::SetGuessing()
// ---------------------------------------------------------------------------
//
void CScorePane::SetGuessing()
    {
    for ( TInt i = 0; i < iDrawerItemArray.Count(); i++ )
        {
        if ( iDrawerItemArray[i].iDrawerType == TDrawerItem::EDrawerGuess )
            {
            iDrawerItemArray[i].iDrawerType
                = TDrawerItem::EDrawerGuessing;
            }
        }
    }

// ---------------------------------------------------------------------------
// CScorePane::SetGuessSuccess()
// ---------------------------------------------------------------------------
//
void CScorePane::SetGuessSuccess()
    {
    for ( TInt i = 0; i < iDrawerItemArray.Count(); i++ )
        {
        if ( iDrawerItemArray[i].iDrawerType == TDrawerItem::EDrawerGuessing )
            {
            iDrawerItemArray[i].iDrawerType
                = TDrawerItem::EDrawerGuessSuccess;
            }
        }
    }

// ---------------------------------------------------------------------------
// CScorePane::AddRay()
// ---------------------------------------------------------------------------
//
void CScorePane::AddRay()
	{
	--iNumberOfRays;
	if ( iNumberOfRays < KMinNumberOfRays )
		{
		iNumberOfRays = KMinNumberOfRays;
		}
	}

// ---------------------------------------------------------------------------
// CScorePane::ConstructL()
// ---------------------------------------------------------------------------
//
void CScorePane::ConstructL()
    {
    // Create a window for this application view
    CreateWindowL();

    iLayoutManager = CLayoutManager::NewL();
    
    TRect rect = iLayoutManager->LayoutRect( EScorePane );
    SetRect( rect );

    iBmpUtils = CBlackboxBmpUtils::NewL( 
            KScoreFileName,
            EMbmBlackbox_scoreUnguess,
            EMbmBlackbox_scoreLastElement );

    ScaleBmpUtils();
    TInt err = RProperty::Set( 
                        KPSUidBlackbox, 
                        KBlackboxStartupStatus, 
                        EStartupScaleSceneImagesDone 
                        );
    User::LeaveIfError( err );

    Reset(); // init all drawer items
    
    DrawableWindow()->SetOrdinalPosition( 0 );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CScorePane::CScorePane()
// ---------------------------------------------------------------------------
//
CScorePane::CScorePane( CFbsBitGc& aBmpContext, TBlackboxSettings& aSettings ) : 
        iBmpContext( aBmpContext ), iSettings( aSettings )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CScorePane::ScaleBmpUtils()
// ---------------------------------------------------------------------------
//
void CScorePane::ScaleBmpUtils()
    {
    TRect rect = iLayoutManager->LayoutRect( EScoreGuessPane );
    TSize size( rect.Height(), rect.Height() );

    for ( TInt i = EMbmBlackbox_scoreUnguess; i < EMbmBlackbox_scoreLastElement; i += 2 )
        {
        iBmpUtils->SetSize( i, size );
        }
    }

// ---------------------------------------------------------------------------
// CScorePane::CurrentGuessIndex()
// ---------------------------------------------------------------------------
//
TInt CScorePane::CurrentGuessIndex() const
    {
    TInt retVal = iDrawerItemArray.Count();

    for ( TInt i = 0; i < iDrawerItemArray.Count(); i++ )
        {
        if ( iDrawerItemArray[i].iDrawerType == TDrawerItem::EDrawerUnguess )
            {
            retVal = i;
            break;
            }
        }
    return retVal;
    }

// End of file
