/* ====================================================================
 * File: SceneTaskScheduler.cpp
 * Created: 04/19/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "SceneTaskScheduler.h"
#include "SceneTask.h"

// CONSTANTS
const TInt KSceneTaskListCranularity = 5;
const TInt KSceneTaskListHeadIndex = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::NewL
// ----------------------------------------------------------------------------
//
CSceneTaskScheduler* CSceneTaskScheduler::NewL()
    {
    CSceneTaskScheduler* self = new (ELeave) CSceneTaskScheduler;
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::~CSceneTaskScheduler
// ----------------------------------------------------------------------------
//
CSceneTaskScheduler::~CSceneTaskScheduler()
    {
    iTaskList.ResetAndDestroy();
    iTaskList.Close();
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::TaskCompleted
// ----------------------------------------------------------------------------
//
void CSceneTaskScheduler::TaskCompleted()
    {
    CSceneTask* task( iTaskList[ KSceneTaskListHeadIndex ] );
    delete task;
    task = NULL;
    iTaskList.Remove( KSceneTaskListHeadIndex );
    iTaskList.Compress();

    if ( iTaskList.Count() )
        {
        iTaskList[ KSceneTaskListHeadIndex ]->Start();
        }
    else
        {
        iRunning = EFalse;
        }
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::AddTask
// ----------------------------------------------------------------------------
//
void CSceneTaskScheduler::AddTask( CSceneTask* aTask )
    {
    iTaskList.Append( aTask );

    if ( ! iRunning )
        {
        iRunning = ETrue;
        iTaskList[ KSceneTaskListHeadIndex ]->Start();
        }
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::Clear
// ----------------------------------------------------------------------------
//
void CSceneTaskScheduler::Clear()
    {
    iTaskList.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::OnDraw
// ----------------------------------------------------------------------------
//
void CSceneTaskScheduler::OnDraw()
    {
    if ( iRunning )
        {
        iTaskList[ KSceneTaskListHeadIndex ]->OnDraw();
        }
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::CSceneTaskScheduler
// ----------------------------------------------------------------------------
//
CSceneTaskScheduler::CSceneTaskScheduler()
: iTaskList( KSceneTaskListCranularity ),  iRunning( EFalse )
    { 
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// CSceneTaskScheduler::CSceneTaskScheduler
// ----------------------------------------------------------------------------
//
void CSceneTaskScheduler::ConstructL()
    { 
    // No implementation required
    }

// End of File
