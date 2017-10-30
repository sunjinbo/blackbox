/* ====================================================================
 * File: SceneTask.cpp
 * Created: 04/19/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include <Blackbox_effects.mbg>
#include "SceneTask.h"
#include "ScenePane.h"
#include "SceneTaskListener.h"
#include "BlackboxBmpUtils.h"

// CONSTANTS
const TInt KSceneTaskTimeOut = 50000;
const TInt KSceneHorizMove = 0;
const TInt KSceneVertMove = -4;
const TInt KSceneBitmapOffset = 2;
const TInt KSceneMaskOffset = 1;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CSceneTask::NewL
// ----------------------------------------------------------------------------
//
CSceneTask* CSceneTask::NewL( CScenePane& aScenePane, 
    MSceneTaskListener& aListener )
    {
    CSceneTask* self = new (ELeave) CSceneTask( aScenePane, aListener );
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CSceneTask::~CSceneTask
// ----------------------------------------------------------------------------
//
CSceneTask::~CSceneTask()
    {
    Cancel();
    }

// ----------------------------------------------------------------------------
// CSceneTask::Start
// ----------------------------------------------------------------------------
//
void CSceneTask::Start()
    {
    if ( !IsActive() )
        {
        switch ( iTaskType )
            {
            case ESceneGuessingTask:
                iBitmapIndex = EMbmBlackbox_effectsGuessing01;
                break;
            case ESceneGuessFailedTask:
            	iBitmapIndex = EMbmBlackbox_effectsGuessfailed01;
                break;
            case ESceneGuessedTask:
                iBitmapIndex = EMbmBlackbox_effectsGuessed01;
                break;
            default:
                break;
            }
        CTimer::After( KSceneTaskTimeOut );
        }
    }

// ----------------------------------------------------------------------------
// CSceneTask::SetRect
// ----------------------------------------------------------------------------
//
void CSceneTask::SetRect( const TRect& aRect )
    {
    iRect = aRect;
    }

// ----------------------------------------------------------------------------
// CSceneTask::SetTaskType
// ----------------------------------------------------------------------------
//
void CSceneTask::SetTaskType( TSceneTaskType aTaskType )
    {
    iTaskType = aTaskType;
    }

// ----------------------------------------------------------------------------
// CSceneTask::SetUtils
// ----------------------------------------------------------------------------
//
void CSceneTask::SetUtils( CBlackboxBmpUtils* aUtils )
    {
    iUtils = aUtils;
    }

// ----------------------------------------------------------------------------
// CSceneTask::OnDraw
// ----------------------------------------------------------------------------
//
void CSceneTask::OnDraw()
    {
    if ( iUtils )
        {
        iScenePane.iBmpContext.SetPenStyle( CGraphicsContext::ENullPen );
        iScenePane.iBmpContext.SetBrushStyle( CGraphicsContext::ENullBrush );

        iScenePane.iBmpContext.BitBltMasked( 
            iRect.iTl,
            iUtils->Bitmap( iBitmapIndex ),
            TRect( TPoint( 0, 0 ), iRect.Size() ),
            iUtils->Bitmap( iBitmapIndex + KSceneMaskOffset ),
            ETrue 
            );
        }
    }

// ----------------------------------------------------------------------------
// CSceneTask::CSceneTask
// ----------------------------------------------------------------------------
//
CSceneTask::CSceneTask( CScenePane& aScenePane, MSceneTaskListener& aListener )
: CTimer( EPriorityStandard + 1 ), 
  iListener( aListener ), 
  iScenePane( aScenePane )
    {
    CActiveScheduler::Add( this );
    }

// ----------------------------------------------------------------------------
// CSceneTask::ConstructL
// ----------------------------------------------------------------------------
//
void CSceneTask::ConstructL()
    {
    CTimer::ConstructL();
    }

// ----------------------------------------------------------------------------
// CSceneTask::RunL
// ----------------------------------------------------------------------------
//
void CSceneTask::RunL()
    {
    if ( iStatus.Int() == KErrNone )
        {
        switch ( iTaskType )
            {
            case ESceneGuessingTask:
                {
                if ( iRewind )
                    {
                    iBitmapIndex -= KSceneBitmapOffset;
                    if ( iBitmapIndex < EMbmBlackbox_effectsGuessing01 )
                        {
                        iListener.TaskCompleted();
                        }
                    else
                        {
                        CTimer::After( KSceneTaskTimeOut );   
                        }
                    }
                else
                    {
                    iBitmapIndex += KSceneBitmapOffset;
                    if ( iBitmapIndex > EMbmBlackbox_effectsGuessing04 )
                        {
                        iBitmapIndex = EMbmBlackbox_effectsGuessing04;
                        iRewind = ETrue;
                        }
                    CTimer::After( KSceneTaskTimeOut );   
                    }
                }
                break;
            case ESceneGuessFailedTask:
                {
                iBitmapIndex += KSceneBitmapOffset;
                if ( iBitmapIndex > EMbmBlackbox_effectsGuessfailed16 )
                    {
                    iListener.TaskCompleted();
                    }
                else
                    {
                    iRect.Move( KSceneHorizMove, KSceneVertMove );
                    CTimer::After( KSceneTaskTimeOut );   
                    }
                }
                break;
            case ESceneGuessedTask:
                {
                iBitmapIndex += KSceneBitmapOffset;
                if ( iBitmapIndex > EMbmBlackbox_effectsGuessed16 )
                    {
                    iListener.TaskCompleted();
                    }
                else
                    {
                    iRect.Move( KSceneHorizMove, KSceneVertMove );
                    CTimer::After( KSceneTaskTimeOut );   
                    }
                }
                break;
            default:
                break;
            }
        }
    }

// End of File
