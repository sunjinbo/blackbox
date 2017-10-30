/* ====================================================================
 * File: SceneTaskScheduler.h
 * Created: 09/19/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCENETASKSCHEDULER_H
#define C_SCENETASKSCHEDULER_H

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>
#include "SceneTaskListener.h"

// FORWARD DECLARATIONS
class CSceneTask;

// CLASS DECLARATION
/**
* CSceneTaskScheduler class
*
* @since S60 3.1
*/
class CSceneTaskScheduler : public CBase, public MSceneTaskListener
    {
public: // Constructor and Destructor
    static CSceneTaskScheduler* NewL();
    virtual ~CSceneTaskScheduler();

public: // from base class MSceneTaskObserver
    virtual void TaskCompleted();

public: // New functions
    void AddTask( CSceneTask* aTask );
    void Clear();
    void OnDraw();

protected: // Constructor
    CSceneTaskScheduler();
    void ConstructL();

protected: // Data members
    RPointerArray<CSceneTask> iTaskList;
    TBool iRunning;
    };

#endif // C_SCENETASKSCHEDULER_H

// End of File
