/* ====================================================================
 * File: RegistrationTimeout.cpp
 * Created: 07/06/10
 * Modified: 07/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDES
#include "RegistrationTimeout.h"

// CONTANTS
#ifdef __WINS__
const TInt KTimeout = 1;
#else
const TInt KTimeout = 25;
#endif

//-----------------------------------------------------------------------------
// CRegistrationTimeout::NewL
//-----------------------------------------------------------------------------
//
EXPORT_C CRegistrationTimeout* CRegistrationTimeout::NewL(MTimeoutCallback& aCallback)
    {
    CRegistrationTimeout* self =
            new (ELeave) CRegistrationTimeout( aCallback );
    CleanupStack::PushL( self );
    self->ConstructL(); // inherited CTimer construction, do not remove
    CleanupStack::Pop( self );
    return self;
    }

//-----------------------------------------------------------------------------
// CRegistrationTimeout::~CRegistrationTimeout
//-----------------------------------------------------------------------------
//
EXPORT_C CRegistrationTimeout::~CRegistrationTimeout()
    {
    Cancel();
    }

//-----------------------------------------------------------------------------
// CRegistrationTimeout::Start
//-----------------------------------------------------------------------------
//
EXPORT_C void CRegistrationTimeout::Start(TInt aTimeoutInMicroseconds )
    {
    TInt timeout( aTimeoutInMicroseconds );
    if( timeout <= 0 ) // missing timeout argument
        {
        timeout = KTimeout;
        }
    After( TTimeIntervalMicroSeconds32( timeout ) );
    }

//-----------------------------------------------------------------------------
// CRegistrationTimeout::CRegistrationTimeout
//-----------------------------------------------------------------------------
//
CRegistrationTimeout::CRegistrationTimeout(MTimeoutCallback& aCallback) :
    CTimer( EPriorityStandard ), iCallback( aCallback )
    {
    CActiveScheduler::Add( this );
    }

//-----------------------------------------------------------------------------
// CRegistrationTimeout::RunL
//-----------------------------------------------------------------------------
//
void CRegistrationTimeout::RunL()
    {
    if( iStatus == KErrNone )
        {
        iCallback.HandleTimeoutL();
        }
    }

// End of file
