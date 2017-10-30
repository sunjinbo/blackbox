/* ====================================================================
 * File: Blackbox.pan
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __BLACKBOX_PAN__
#define __BLACKBOX_PAN__

/** Blackbox application panic codes */
enum TBlackboxPanics 
    {
    EBlackboxUi = 1,
    EBlackboxBadCommand,
    EBlackboxBadIndex,
    EBlackboxInvaildParam
    // add further panics here
    };

inline void Panic(TBlackboxPanics aReason)
    {
    _LIT(applicationName,"Blackbox");
    User::Panic(applicationName, aReason);
    }

#endif // __BLACKBOX_PAN__
