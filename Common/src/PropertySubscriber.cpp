/* ====================================================================
 * File: PropertySubscriber.cpp
 * Created: 07/06/10
 * Modified: 07/06/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "PropertySubscriber.h"
#include "PropertyObserver.h"

// CONSTANTS

// ============================= MEMBER FUNCTIONS =============================

// ----------------------------------------------------------------------------
// CSysApSubscriber::NewL()
// ----------------------------------------------------------------------------
EXPORT_C CPropertySubscriber* CPropertySubscriber::NewL( 
                                        MPropertyObserver* aPropertyObserver, 
                                        const TUid& aCategory, 
                                        TUint aKey )
    {
    CPropertySubscriber* self = new (ELeave) CPropertySubscriber( 
                                                            aPropertyObserver, 
                                                            aCategory, 
                                                            aKey );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); //self
    return self;
    }


// ----------------------------------------------------------------------------
// CPropertySubscriber::ConstructL()
// ----------------------------------------------------------------------------
EXPORT_C void CPropertySubscriber::ConstructL()
    {
    CActiveScheduler::Add( this );
    iProperty.Attach( iCategory, iKey );
    }


// ----------------------------------------------------------------------------
// CPropertySubscriber::Subscribe()
// ----------------------------------------------------------------------------
EXPORT_C void CPropertySubscriber::Subscribe()
    {
    iProperty.Cancel();
    iProperty.Subscribe( iStatus );
    SetActive();
    }

// ----------------------------------------------------------------------------
// CPropertySubscriber::CPropertySubscriber()
// ----------------------------------------------------------------------------
CPropertySubscriber::CPropertySubscriber( 
                                MPropertyObserver* aPropertyObserver, 
                                const TUid& aCategory, 
                                TUint aKey ) :
    CActive( EPriorityStandard ),
    iPropertyObserver( aPropertyObserver ),
    iCategory( aCategory),
    iKey( aKey )
    {
    }

// ----------------------------------------------------------------------------
// CPropertySubscriber::RunL()
// ----------------------------------------------------------------------------
void CPropertySubscriber::RunL()
    {
    Subscribe();
    iPropertyObserver->HandlePropertyChangedL( iCategory, iKey );
    }

// ----------------------------------------------------------------------------
// CPropertySubscriber::DoCancel()
// ----------------------------------------------------------------------------
void CPropertySubscriber::DoCancel()
    {
    iProperty.Cancel();
    }

// ----------------------------------------------------------------------------
// CPropertySubscriber::RunError()
// ----------------------------------------------------------------------------
TInt CPropertySubscriber::RunError( TInt aError )
    {
    return aError;
    }

// ----------------------------------------------------------------------------
// CPropertySubscriber::~CPropertySubscriber()
// ----------------------------------------------------------------------------
CPropertySubscriber::~CPropertySubscriber()
    {
    Cancel();
    iProperty.Close();
    }

// End of File
