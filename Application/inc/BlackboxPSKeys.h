/* ====================================================================
 * File: BlackboxPSKeys.h
 * Created: 07/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef BLACKBOXPSKEYS_H
#define BLACKBOXPSKEYS_H

/**
 * The Uid for the Publish&Subscribe itself
 * This PS holds the settings for Blackbox
 */
const TUid KPSUidBlackbox = { 0xAFF0567A };

const TUint32 KBlackboxStartupStatus = 0x00000001;

enum TBlackboxStartupStatus
    {
    EStartupUninitialized = 0x00000000,
    EStartupScaleWelcImagesDone = 0x00000001,
    EStartupScaleAvatarImagesDone = 0x00000002,
    EStartupScaleScoreImagesDone = 0x00000004,
    EStartupScaleSceneImagesDone = 0x00000008,
    EStartupAllDone = 0x0000000f
    };

#endif // BLACKBOXPSKEYS_H

// End of file
