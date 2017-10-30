/* ====================================================================
 * File: BoxObserver.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_BOXOBSERVER_H
#define M_BOXOBSERVER_H

// INCLUDE

// FORWARD DECLARATIONS
class CRays;

// CLASS DECLARATION

/**
* MBoxObserver class
*
* @since S60 5.0
*/
class MBoxObserver
    {
public:
    // Called when box state changes and observer needs to be notified.
    virtual void StateChangedL( TInt aNewState ) = 0;
    virtual void RaysCreated( CRays* aNewRays ) = 0;
    };

#endif // M_BOXOBSERVER_H

// End of File
