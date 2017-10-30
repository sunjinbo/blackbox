/* ====================================================================
 * File: SceneObserver.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_SCENEOBSERVER_H
#define M_SCENEOBSERVER_H

// INCLUDE


// CLASS DECLARATION

/**
* MSceneObserver class
*
* @since S60 5.0
*/
class MSceneObserver
    {
public:
    // Called when box state changes and observer needs to be notified.
    virtual void StateChangedL( TInt aNewState ) = 0;
    };

#endif // M_SCENEOBSERVER_H

// End of File
