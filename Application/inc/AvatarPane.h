/* ====================================================================
 * File: AvatarPane.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_AVATARPANE_H
#define C_AVATARPANE_H

// INCLUDES
#include <coecntrl.h>
#include "Blackbox.hrh"
#include "RegistrationTimeout.h"

// FORWARD DECLARATIONS
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CLayoutManager;
class CBlackboxBmpUtils;

// CLASS DECLARATION

/**
 *  CAvatarPane class
 */
class CAvatarPane : public CCoeControl, public MTimeoutCallback
    {
public: // friend class
    friend class CSceneTask;

public: // Enumerations
    enum TTalkType
        {
        ETalkPraise,
        ETalkCriticism,
        ETalkEncourage,
        ETalkCongratulate,
        ETalkComplain,
        ETalkOpening
        };

public: // Constructors and destructor
    static CAvatarPane* NewL( CFbsBitGc& aBmpContext );
    virtual ~CAvatarPane();

public: // New methods
    void SetAvatar( TBlackboxAvatar aAvatar );
    void OnDraw();
    void TalkL( const TDesC& aText );
    void TalkL( TTalkType aTalkType );

public: // from MTimeoutCallback
    void HandleTimeoutL();
    
private: // Symbian 2nd Constructors
    void ConstructL();
    CAvatarPane( CFbsBitGc& aBmpContext );

private: // New methods
    void ScaleBmpUtils();
    TInt AvatarBitmapId() const;
    TInt AvatarDialogBitmapId() const;
    void DoBlink();
    static TInt TimerCallback( TAny* aPtr );
    void DrawDialogText();
    void DoPraiseL();
    void DoCriticismL();
    void DoEncourageL();
    void DoCongratulateL();
    void DoComplainL();
    void DoOpeningL();

private: // Enums
    enum TAvatarState
        {
        EAvatarSilentState,
        EAvatarTalkState,
        EAvatarBlinkState
        };

private: // Data
    CFbsBitGc& iBmpContext;
    CLayoutManager* iLayoutManager; // owned
    CBlackboxBmpUtils* iBmpUtils; // owned
    CRegistrationTimeout* iTimeout; // owned
    CPeriodic* iPeriodic; // owned
    RPointerArray<HBufC> iWordsArray;
    HBufC* iCurrentWords; // not owned
    TRect iAvatarRect;
    TRect iAvatarDialogRect;
    TRect iAvatarDialogTextRect;
    TBlackboxAvatar iAvatar;
    TAvatarState iAvatarState;
    TInt iAvatarBitmapId;
    TInt iDelayFrameNumber;
    };

#endif // C_AVATARPANE_H
