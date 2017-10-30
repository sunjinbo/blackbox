/* ====================================================================
 * File: SceneTask.h
 * Created: 09/19/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCENETASK_H
#define C_SCENETASK_H

// INCLUDE FILES
#include <e32base.h>

// ENUMERATES

// FORWARD DECLARATIONS
class MSceneTaskListener;
class CScenePane;
class CBlackboxBmpUtils;

// ENUMS
enum TSceneTaskType
    {
    ESceneGuessingTask = 1,
    ESceneGuessFailedTask,
    ESceneGuessedTask
    };

// CLASS DECLARATION

/**
* CSceneTask class
*
* @since S60 3.1
*/
class CSceneTask : public CTimer
    {
public: // Constructor and Destructor
    static CSceneTask* NewL( CScenePane& aScenePane, MSceneTaskListener& aListener );
    virtual ~CSceneTask();

public: // New functions
    void Start();
    void SetRect( const TRect& aRect );
    void SetTaskType( TSceneTaskType aTaskType );
    void SetUtils( CBlackboxBmpUtils* aUtils );
    void OnDraw();

private: // Constructor
    CSceneTask( CScenePane& aControl, MSceneTaskListener& aListener );
    void ConstructL();

private: // from CTimer
    void RunL();

private: // Data members
    MSceneTaskListener& iListener;
    CScenePane& iScenePane;
    CBlackboxBmpUtils* iUtils; // not owned.
    TRect iRect;
    TInt iBitmapIndex;
    TSceneTaskType iTaskType;
    TBool iRewind;
    };

#endif // C_SCENETASK_H

// End of File
