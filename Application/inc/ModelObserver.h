/* ====================================================================
 * File: ModelObserver.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_MODELOBSERVER_H
#define M_MODELOBSERVER_H

// INCLUDE


// CLASS DECLARATION

/**
* MModelObserver class
*
* @since S60 5.0
*/
class MModelObserver
    {
public:
    // Called when box state changes and observer needs to be notified.
    virtual void StateChangedL( TInt aNewState ) = 0;
    virtual void DoEffectL( TInt aEffectType, TInt aX, TInt aY ) = 0;
    };

#endif // M_MODELOBSERVER_H

// End of File
