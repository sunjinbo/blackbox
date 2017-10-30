/* ====================================================================
 * File: SceneTaskListener.h
 * Created: 09/19/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_SCENETASKLISTENER_H
#define M_SCENETASKLISTENER_H


// CLASS DECLARATION
/**
* MSceneTaskListener class
*
* @since S60 3.1
*/
class MSceneTaskListener
    {
public:
    // Called when task completes and observer needs to be notified.
    virtual void TaskCompleted() = 0;
    };

#endif // M_SCENETASKLISTENER_H

// End of File
