/* ====================================================================
 * File: Lightbox.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Blackbox_scene.mbg>
#include "Lightbox.h"
#include "BoxObserver.h"
#include "BoxHelper.h"
#include "BlackboxConfig.h"
#include "Rays.h"
#include "Blackbox.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CLightbox::NewL()
// ---------------------------------------------------------------------------
//
CLightbox* CLightbox::NewL( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos )
    {
    CLightbox* self = new ( ELeave ) CLightbox( aObs, aHelper, aPos );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CLightbox::~CLightbox()
// ---------------------------------------------------------------------------
//
CLightbox::~CLightbox()
    {
    delete iRays;
    }

// ---------------------------------------------------------------------------
// CLightbox::SetIndexId()
// ---------------------------------------------------------------------------
//
void CLightbox::SetIndexId( TInt aIndexId )
    {
    iIndexId = aIndexId;
    }

// ---------------------------------------------------------------------------
// CLightbox::IndexId()
// ---------------------------------------------------------------------------
//
TInt CLightbox::IndexId() const
    {
    return iIndexId;
    }

// ---------------------------------------------------------------------------
// CLightbox::OnDraw()
// ---------------------------------------------------------------------------
//
void CLightbox::OnDraw()
    {
    TInt bitmap(0), mask(0);
    switch ( iLightboxState )
        {
        case EConceal:
            bitmap = EMbmBlackbox_sceneConceal;
            mask = EMbmBlackbox_sceneConceal_mask;
            break;
        case EDeflection:
            GetDeflectionBmpIx( bitmap, mask );
            break;
        case EComplexDeflection:
            GetComplexDeflectionBmpIx( bitmap, mask );
            break;
        case EDeflectionOut:
            GetDeflectionOutBmpIx( bitmap, mask );
            break;
        case EComplexDeflectionOut:
            GetComplexDeflectionOutBmpIx( bitmap, mask );
            break;
        case EReflection:
            bitmap = EMbmBlackbox_sceneReflection;
            mask = EMbmBlackbox_sceneReflection_mask;
            break;
        case EComplexReflection:
            GetComplexReflection( bitmap, mask );
            break;
        default:
            break;
        }

    TRect theRect;
    theRect = iHelper.BoxRect( iPosition.iX, iPosition.iY );
    iHelper.BmpContext().SetBrushStyle( CGraphicsContext::ENullBrush );
    /*
    iHelper.BmpContext().BitBltMasked( 
            theRect.iTl,
            iHelper.Bitmap( bitmap ),
            TRect( TPoint( 0, 0 ), theRect.Size() ),
            iHelper.Bitmap( mask ),
            ETrue
            );
    */
    iHelper.BmpContext().BitBlt( 
            theRect.iTl,
            iHelper.Bitmap( bitmap ),
            TRect( TPoint( 0, 0 ), theRect.Size() )
            );

    if ( iIndexId > 0 )
        {
        TRect indexRect = IndexRect( theRect );
    
        TInt baseline = 
            ( indexRect.Height() + iHelper.IndexFont()->HeightInPixels() ) / 2;
    
        TBuf<8> indexBuffer;
        indexBuffer.AppendNum( iIndexId );
        
        iHelper.BmpContext().SetPenStyle( CGraphicsContext::ESolidPen );
        
        if ( iLightboxState == EReflection )
            {
            iHelper.BmpContext().SetPenColor( KRgbBlack );
            }
        else
            {
            iHelper.BmpContext().SetPenColor( KRgbWhite );
            }

        iHelper.BmpContext().UseFont( iHelper.IndexFont() );
        iHelper.BmpContext().DrawText( 
                    indexBuffer,
                    indexRect, 
                    baseline, 
                    CGraphicsContext::ECenter, 
                    0 
                    );
        iHelper.BmpContext().DiscardFont();
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::UpdateStateL()
// ---------------------------------------------------------------------------
//
void CLightbox::UpdateStateL( TInt aState )
    {
    iLightboxState = (TLightboxState)aState;
    }

// ---------------------------------------------------------------------------
// CLightbox::State()
// ---------------------------------------------------------------------------
//
TInt CLightbox::State() const
    {
    return iLightboxState;
    }

// ---------------------------------------------------------------------------
// CLightbox::TriggerL()
// ---------------------------------------------------------------------------
//
void CLightbox::TriggerL()
    {
    if ( iLightboxState == EConceal )
        {
        if ( !iHelper.Settings().iUnlimitedRays )
            {
            if ( iHelper.RaysCount() >= iHelper.Settings().iMaxRays )
                {
                iObserver.StateChangedL( ESceneMaxRaysOverflow );
                return;
                }
            }

        if ( !iRays )
            {
            iRays = CRays::NewL( *this );
            iObserver.RaysCreated( iRays );
            SetIndexId( iHelper.RaysCount() );
            }
        }
    else
        {
        iObserver.StateChangedL( ESceneLightboxActivated );
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::ConstructL()
// ---------------------------------------------------------------------------
//
void CLightbox::ConstructL()
    {
    CBox::ConstructL();
    
    if ( iPosition.iX == 0 )
        {
        iLightboxDirection = ELightboxLeft;
        }
    else if ( iPosition.iY == 0 )
        {
        iLightboxDirection = ELightboxTop;
        }
    else if ( iPosition.iX == KHorizBoxNumber - 1 )
        {
        iLightboxDirection = ELightboxRight;
        }
    else
        {
        iLightboxDirection = ELightboxBottom;
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::CLightbox()
// ---------------------------------------------------------------------------
//
CLightbox::CLightbox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos )
: CBox( aObs, aHelper, aPos )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CLightbox::GetDeflectionBmpIx()
// ---------------------------------------------------------------------------
//
void CLightbox::GetDeflectionBmpIx( TInt& aBitmap, TInt& aMask )
    {
    switch ( iLightboxDirection )
        {
        case ELightboxTop:
            aBitmap = EMbmBlackbox_sceneDeflection_down;
            aMask = EMbmBlackbox_sceneDeflection_down_mask;
            break;
        case ELightboxBottom:
            aBitmap = EMbmBlackbox_sceneDeflection_up;
            aMask = EMbmBlackbox_sceneDeflection_up_mask;
            break;
        case ELightboxLeft:
            aBitmap = EMbmBlackbox_sceneDeflection_right;
            aMask = EMbmBlackbox_sceneDeflection_right_mask;
            break;
        case ELightboxRight:
            aBitmap = EMbmBlackbox_sceneDeflection_left;
            aMask = EMbmBlackbox_sceneDeflection_left_mask;
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::GetComplexDeflectionBmpIx()
// ---------------------------------------------------------------------------
//
void CLightbox::GetComplexDeflectionBmpIx( TInt& aBitmap, TInt& aMask )
    {
    switch ( iLightboxDirection )
        {
        case ELightboxTop:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_down;
            aMask = EMbmBlackbox_sceneComplexdeflection_down_mask;
            break;
        case ELightboxBottom:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_up;
            aMask = EMbmBlackbox_sceneComplexdeflection_up_mask;
            break;
        case ELightboxLeft:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_right;
            aMask = EMbmBlackbox_sceneComplexdeflection_right_mask;
            break;
        case ELightboxRight:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_left;
            aMask = EMbmBlackbox_sceneComplexdeflection_left_mask;
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::GetDeflectionOutBmpIx()
// ---------------------------------------------------------------------------
//
void CLightbox::GetDeflectionOutBmpIx( TInt& aBitmap, TInt& aMask )
    {
    switch ( iLightboxDirection )
        {
        case ELightboxTop:
            aBitmap = EMbmBlackbox_sceneDeflection_up;
            aMask = EMbmBlackbox_sceneDeflection_up_mask;
            break;
        case ELightboxBottom:
            aBitmap = EMbmBlackbox_sceneDeflection_down;
            aMask = EMbmBlackbox_sceneDeflection_down_mask;
            break;
        case ELightboxLeft:
            aBitmap = EMbmBlackbox_sceneDeflection_left;
            aMask = EMbmBlackbox_sceneDeflection_left_mask;
            break;
        case ELightboxRight:
            aBitmap = EMbmBlackbox_sceneDeflection_right;
            aMask = EMbmBlackbox_sceneDeflection_right_mask;
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::GetComplexDeflectionOutBmpIx()
// ---------------------------------------------------------------------------
//
void CLightbox::GetComplexDeflectionOutBmpIx( TInt& aBitmap, TInt& aMask )
    {
    switch ( iLightboxDirection )
        {
        case ELightboxTop:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_up;
            aMask = EMbmBlackbox_sceneComplexdeflection_up_mask;
            break;
        case ELightboxBottom:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_down;
            aMask = EMbmBlackbox_sceneComplexdeflection_down_mask;
            break;
        case ELightboxLeft:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_left;
            aMask = EMbmBlackbox_sceneComplexdeflection_left_mask;
            break;
        case ELightboxRight:
            aBitmap = EMbmBlackbox_sceneComplexdeflection_right;
            aMask = EMbmBlackbox_sceneComplexdeflection_right_mask;
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::GetComplexReflection()
// ---------------------------------------------------------------------------
//
void CLightbox::GetComplexReflection( TInt& aBitmap, TInt& aMask )
    {
    switch ( iLightboxDirection )
        {
        case ELightboxTop:
        case ELightboxBottom:
            aBitmap = EMbmBlackbox_sceneComplexreflection_vert;
            aMask = EMbmBlackbox_sceneComplexreflection_vert_mask;
            break;
        case ELightboxLeft:
        case ELightboxRight:
            aBitmap = EMbmBlackbox_sceneComplexreflection_horiz;
            aMask = EMbmBlackbox_sceneComplexreflection_horiz_mask;
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CLightbox::IndexRect()
// ---------------------------------------------------------------------------
//
TRect CLightbox::IndexRect( const TRect& aBoxRect ) const
    {
    TRect theRect = aBoxRect;
    theRect.iBr.iX = theRect.iTl.iX + theRect.Width() / 4;
    theRect.iBr.iY = theRect.iTl.iY + theRect.Height() / 4;
    return theRect;
    }

// End of file
