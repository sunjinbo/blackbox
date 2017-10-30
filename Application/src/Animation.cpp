/* ====================================================================
 * File: Animation.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Animation.h"
#include "AnimationObserver.h"
#include "BlackboxBmpUtils.h"
#include "Logger.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CAnimation::NewL()
// ---------------------------------------------------------------------------
//
CAnimation* CAnimation::NewL( TResourceReader& aReader, MAnimationObserver& aObserver )
    {
    CAnimation* self = new (ELeave)CAnimation( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL( aReader );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAnimation::~CAnimation()
// ---------------------------------------------------------------------------
//
CAnimation::~CAnimation()
    {
    if ( iTimer )
        {
        iTimer->Cancel();
        delete iTimer;
        }
    iAnimArray.Reset();
    iAnimArray.Close();
    
    delete iBmpUtils;
    delete iFileName;
    
    if ( iIdle )
        {
        iIdle->Cancel();
        delete iIdle;
        }
    }

// ---------------------------------------------------------------------------
// CTipsManager::EnableControl()
// ---------------------------------------------------------------------------
//
void CAnimation::EnableControl( CCoeControl* aControl )
    {
    iControl = aControl;
    }

// ---------------------------------------------------------------------------
// CTipsManager::DisableControl()
// ---------------------------------------------------------------------------
//
void CAnimation::DisableControl()
    {
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CAnimation::Start()
// ---------------------------------------------------------------------------
//
void CAnimation::Start()
    {
    TCallBack callback( TimerCompleted, this );
    iTimer->Cancel();
    iTimer->Start( iDelayInterval, iFrameInterval, callback );
    }

// ---------------------------------------------------------------------------
// CAnimation::Draw()
// ---------------------------------------------------------------------------
//
void CAnimation::Draw( CWindowGc& aGc, const TRect& aRect )
    {
    aGc.BitBltMasked( 
            aRect.iTl,
            iBmpUtils->Bitmap( iAnimArray[ iFrameIndex ].iBitmapId ),
            TRect( TPoint( 0 , 0 ), iSize ),
            iBmpUtils->Bitmap( iAnimArray[ iFrameIndex ].iMaskId ),
            EFalse 
            );
    }

// ---------------------------------------------------------------------------
// CAnimation::ConstructL()
// ---------------------------------------------------------------------------
//
void CAnimation::ConstructL( TResourceReader& aReader )
    {
    INFO( "CAnimation::ConstructL" )
    iRepeat = aReader.ReadUint8();
    iRevert = aReader.ReadUint8();
    iSize.iWidth = aReader.ReadUint16();
    iSize.iHeight = aReader.ReadUint16();
    iDelayInterval = aReader.ReadUint32();
    iFrameInterval = aReader.ReadUint32();
    iBmpFrom = aReader.ReadUint32();
    iBmpTo = aReader.ReadUint32();
    iFileName  = aReader.ReadHBufCL();
    iFrameCount = aReader.ReadInt16();
    
    INFO_1( "iFrameCount = %d", iFrameCount )

    INFO( "Start to appending anim frame.." )
    for ( TInt i = 0; i < iFrameCount; i++ )
        {
        TAnimationFrame animFrame( aReader );
        iAnimArray.Append( animFrame );
        }
    INFO( "The creation of anim frame was done." )
    
    iTimer = CPeriodic::NewL( EPriorityNormal );
    
    INFO( "Start to scaling bmp.." )
    iBmpUtils = CBlackboxBmpUtils::NewL( *iFileName, iBmpFrom, iBmpTo );
    INFO( "Bmp utils was created!" )

    iScaleIndex = iBmpFrom;
    iIdle = CIdle::New( CActive::EPriorityStandard );
    iIdle->Start( TCallBack( ScaleCallback, this ) );
    }

// ---------------------------------------------------------------------------
// CAnimation::CAnimation()
// ---------------------------------------------------------------------------
//
CAnimation::CAnimation( MAnimationObserver& aObserver )
: iObserver( aObserver )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CAnimation::TimerCompleted
// ----------------------------------------------------------------------------
// 
TInt CAnimation::TimerCompleted( TAny* aPtr )
    {
    CAnimation* animator = STATIC_CAST( CAnimation*, aPtr );
    animator->DrawNow();
    return 0;
    }

// ----------------------------------------------------------------------------
// CAnimation::DrawNow
// ----------------------------------------------------------------------------
//
void CAnimation::DrawNow()
    {
    if ( iControl )
        {
        iControl->DrawNow();
        }

    if ( iRewind )
        {
        --iFrameIndex;
        if ( iFrameIndex < 0 )
            {
            iFrameIndex = 0;

            if ( iRepeat )
                {
                if ( iRevert )
                    {
                    iRewind = EFalse;
                    }
                else
                    {
                    iFrameIndex = iFrameCount - 1;
                    }
                }
            }
        }
    else
        {
        ++iFrameIndex;
        if ( iFrameIndex >= iFrameCount )
            {
            iFrameIndex = iFrameCount - 1;

            if ( iRepeat )
                {
                if ( iRevert )
                    {
                    iRewind = ETrue;
                    }
                else
                    {
                    iFrameIndex = 0;
                    }
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CAnimation::ScaleCallback
// ----------------------------------------------------------------------------
// 
TInt CAnimation::ScaleCallback( TAny* aPtr )
    {
    CAnimation* animator = STATIC_CAST( CAnimation*, aPtr );
    animator->Scale();
    return 0;
    }

// ----------------------------------------------------------------------------
// CAnimation::Scale
// ----------------------------------------------------------------------------
//
void CAnimation::Scale()
    {
    iBmpUtils->SetSize( iScaleIndex, iSize );

    ++iScaleIndex;
    
    if ( iScaleIndex < iBmpTo && !iIdle->IsActive() )
        {
        iIdle->Start( TCallBack( ScaleCallback, this ) );
        }
    else
        {
        INFO( "Scale was done." )
        TRAP_IGNORE( iObserver.AnimationPreparedL() );
        }
    }

// End of file
