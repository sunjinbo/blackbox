/* ====================================================================
 * File: AnimationObserver.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_ANIMATIONOBSERVER_H
#define M_ANIMATIONOBSERVER_H

// INCLUDE


// CLASS DECLARATION

/**
* MAnimationObserverclass
*
* @since S60 5.0
*/
class MAnimationObserver
    {
public:
    // Called when animation state changes and observer needs to be notified.
    virtual void AnimationPreparedL() = 0;
    };

#endif // M_ANIMATIONOBSERVER_H

// End of File
