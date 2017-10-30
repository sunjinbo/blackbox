/* ====================================================================
 * File: AvatarPane.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32property.h>
#include <e32math.h>
#include <eikenv.h>
#include <Blackbox_avatar.mbg>
#include "AvatarPane.h"
#include "LayoutManager.h"
#include "BlackboxBmpUtils.h"
#include "BlackboxPSKeys.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KAvatarFileName, "Z:\\resource\\apps\\Blackbox_avatar.mbm" );
#else
_LIT( KAvatarFileName, "\\resource\\apps\\Blackbox_avatar.mbm" );
#endif // __WINS__

const TInt KAvatarBlinkTimeout = 8000000;
const TInt KBlinkDelayFrameNumber = 3;
const TInt KTalkDelayFrameNumber = 1;
const TInt KDoBlinkDelayTimeout = 500000;
const TInt KDoBlinkUpdateTimeout = 2500000;
const TInt KLetterTimeout = 100000;
const TInt KWordsHeadIndex = 0;
const TInt KTalkBitmapOffset = 4;

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CAvatarPane::NewL()
// ---------------------------------------------------------------------------
//
CAvatarPane* CAvatarPane::NewL( CFbsBitGc& aBmpContext )
    {
    CAvatarPane* self = new ( ELeave ) CAvatarPane( aBmpContext );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CAvatarPane::~CAvatarPane()
// ---------------------------------------------------------------------------
//
CAvatarPane::~CAvatarPane()
    {
    delete iTimeout;
    delete iLayoutManager;
    delete iBmpUtils;
    iWordsArray.ResetAndDestroy();
    iWordsArray.Close();
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::SetAvatar
// ----------------------------------------------------------------------------
//
void CAvatarPane::SetAvatar( TBlackboxAvatar aAvatar )
    {
    iAvatar = aAvatar;
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoDraw
// ----------------------------------------------------------------------------
//
void CAvatarPane::OnDraw()
    {
    switch ( iAvatarState )
        {
        case EAvatarSilentState:
            break;
        case EAvatarTalkState:
            {
            --iDelayFrameNumber;
            if ( iDelayFrameNumber < 0 )
                {
                if ( iAvatarBitmapId == AvatarBitmapId() )
                    {
                    iAvatarBitmapId += KTalkBitmapOffset;
                    iAvatarBitmapId += ( ( Math::Random() % 2 + 1 ) * 2 );
                    }
                else
                    {
                    iAvatarBitmapId = AvatarBitmapId();
                    }
                iDelayFrameNumber = KTalkDelayFrameNumber;
                }
            }
            break;
        case EAvatarBlinkState:
            {
            --iDelayFrameNumber;
            if ( iDelayFrameNumber < 0 )
                {
                iAvatarState = EAvatarSilentState;
                iAvatarBitmapId = AvatarBitmapId();
                }
            }
            break;
        default:
            break;
        }

    iBmpContext.SetPenStyle( CGraphicsContext::ENullPen );
    iBmpContext.SetBrushStyle( CGraphicsContext::ENullBrush );
    iBmpContext.BitBlt(
        iAvatarRect.iTl,
        iBmpUtils->Bitmap( iAvatarBitmapId ),
        TRect( TPoint( 0, 0 ), iAvatarRect.Size() )
        );
    
    if ( iAvatarState == EAvatarTalkState )
        {
        iBmpContext.BitBlt(
            iAvatarDialogRect.iTl,
            iBmpUtils->Bitmap( AvatarDialogBitmapId() ),
            TRect( TPoint( 0, 0 ), iAvatarDialogRect.Size() )
            );

        DrawDialogText();
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::TalkL
// ----------------------------------------------------------------------------
//
void CAvatarPane::TalkL( const TDesC& aText )
    {
    HBufC* buf = HBufC::NewL( aText.Length() + 1 );
    TPtr text( buf->Des() );
    text.Copy( aText );
    iWordsArray.Append( buf );
    
    if ( iAvatarState != EAvatarTalkState )
        {
        iAvatarState = EAvatarTalkState;
        iCurrentWords = iWordsArray[ KWordsHeadIndex ];
        iTimeout->Start( aText.Length() * KLetterTimeout );
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::TalkL
// ----------------------------------------------------------------------------
//
void CAvatarPane::TalkL( TTalkType aTalkType )
    {
    switch ( aTalkType )
        {
        case ETalkPraise:
            {
            DoPraiseL();
            }
            break;
            
        case ETalkCriticism:
            {
            DoCriticismL();
            }
            break;
            
        case ETalkEncourage:
            {
            DoEncourageL();
            }
            break;
            
        case ETalkCongratulate:
            {
            DoCongratulateL();
            }
            break;
            
        case ETalkComplain:
            {
            DoComplainL();
            }
            break;
            
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::HandleTimeoutL
// ----------------------------------------------------------------------------
//
void CAvatarPane::HandleTimeoutL()
    {
    HBufC* words = iWordsArray[ KWordsHeadIndex ];
    delete words;
    words = NULL;

    iWordsArray.Remove( KWordsHeadIndex );
    iWordsArray.Compress();

    if ( iWordsArray.Count() )
        {
        iCurrentWords = iWordsArray[ KWordsHeadIndex ];
        iTimeout->Start( iCurrentWords->Length() * KLetterTimeout );
        }
    else
        {
        iAvatarState = EAvatarSilentState;
        }
    }

// ---------------------------------------------------------------------------
// CAvatarPane::ConstructL()
// ---------------------------------------------------------------------------
//
void CAvatarPane::ConstructL()
    {
    // Create a window for this application view
    CreateWindowL();
    
    iAvatarBitmapId = AvatarBitmapId();

    iLayoutManager = CLayoutManager::NewL();
    iAvatarRect = iLayoutManager->LayoutRect( EAvatar );
    iAvatarDialogRect = iLayoutManager->LayoutRect( EAvatarDialog );
    iAvatarDialogTextRect = iLayoutManager->LayoutRect( EAvatarDialogText );
    TRect theRect = iLayoutManager->LayoutRect( EAvatarPane );
    SetRect( theRect );

    iBmpUtils = CBlackboxBmpUtils::NewL( 
            KAvatarFileName,
            EMbmBlackbox_avatarLeslie,
            EMbmBlackbox_avatarLastElement );

    ScaleBmpUtils();

    TInt err = RProperty::Set( 
                        KPSUidBlackbox, 
                        KBlackboxStartupStatus, 
                        EStartupScaleAvatarImagesDone 
                        );
    User::LeaveIfError( err );
    
    iTimeout = CRegistrationTimeout::NewL( *this );

    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KDoBlinkDelayTimeout,
            KDoBlinkUpdateTimeout,
            TCallBack( TimerCallback, this ) );
 
    DrawableWindow()->SetOrdinalPosition( 0 );

#if defined ( __S60_50__ )
    // Enables handling of drag events
    EnableDragEvents();
#endif // __S60_50__

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CAvatarPane::CAvatarPane()
// ---------------------------------------------------------------------------
//
CAvatarPane::CAvatarPane( CFbsBitGc& aBmpContext ) : iBmpContext( aBmpContext )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CAvatarPane::ScaleBmpUtils
// ----------------------------------------------------------------------------
//
void CAvatarPane::ScaleBmpUtils()
    {
    TRect theRect = iLayoutManager->LayoutRect( EAvatar );

    for ( TInt i = EMbmBlackbox_avatarLeslie; i <= EMbmBlackbox_avatarRex_talk4; i += 2 )
        {
        iBmpUtils->SetSize( i, theRect.Size() );
        }

    theRect = iLayoutManager->LayoutRect( EAvatarDialog );

    for ( TInt ii = EMbmBlackbox_avatarLeslie_dialog; ii <= EMbmBlackbox_avatarRex_dialog; ii += 2 )
        {
        iBmpUtils->SetSize( ii, theRect.Size() );
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::AvatarBitmapId
// ----------------------------------------------------------------------------
//
TInt CAvatarPane::AvatarBitmapId() const
    {
    TInt bmpId = 0;

    switch ( iAvatar )
        {
        case EAvatarLeslie:
            bmpId = EMbmBlackbox_avatarLeslie;
            break;
        case EAvatarMardeline:
            bmpId = EMbmBlackbox_avatarMardeline;
            break;
        case EAvatarRex:
            bmpId = EMbmBlackbox_avatarRex;
            break;
        default:
            break;
        }
    return bmpId;
    }

// ----------------------------------------------------------------------------
// CAvatarPane::AvatarDialogBitmapId
// ----------------------------------------------------------------------------
//
TInt CAvatarPane::AvatarDialogBitmapId() const
    {
    TInt bmpId = 0;

    switch ( iAvatar )
        {
        case EAvatarLeslie:
            bmpId = EMbmBlackbox_avatarLeslie_dialog;
            break;
        case EAvatarMardeline:
            bmpId = EMbmBlackbox_avatarMardeline_dialog;
            break;
        case EAvatarRex:
            bmpId = EMbmBlackbox_avatarRex_dialog;
            break;
        default:
            break;
        }
    return bmpId;
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoBlink
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoBlink()
    {
    if ( iAvatarState == EAvatarSilentState )
        {
        iAvatarState = EAvatarBlinkState;
        iDelayFrameNumber = KBlinkDelayFrameNumber;
        TInt bmpId = AvatarBitmapId();
        iAvatarBitmapId = bmpId + ( ( Math::Random() % 2 + 1 ) * 2 );
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CAvatarPane::TimerCallback( TAny* aPtr )
    {
    CAvatarPane* self = static_cast<CAvatarPane*> ( aPtr );
    self->DoBlink();
    return 0;
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DrawDialogText
// ----------------------------------------------------------------------------
//
void CAvatarPane::DrawDialogText()
    {
    const CFont* font = iEikonEnv->SymbolFont();
    iBmpContext.UseFont( font );
    iBmpContext.SetPenStyle( CGraphicsContext::ESolidPen );
    iBmpContext.SetPenColor( KRgbWhite );
    
    TPoint point( 10, font->HeightInPixels() + 10 );
    TInt curWidth = 0;
    TInt p;
    
    HBufC* currentWords = HBufC::NewL( iCurrentWords->Length() );
    TPtr text( currentWords->Des() );
    text.Copy( *iCurrentWords );

    while ( currentWords->Length() > 0 )
        {
        TBuf<20> word;
        TInt newWidth;
        
        p = currentWords->Find( _L( " " ) );
        if ( p > 0 )
            {
            word.Copy( currentWords->Left( p + 1 ) );
            currentWords->Des().Copy( currentWords->Right( currentWords->Length() - p - 1 ) );
            }
        else
            {
            word.Copy( currentWords->Des() );
            currentWords->Des().SetLength( 0 );
            }
        
        newWidth = font->TextWidthInPixels( word );
        if ( curWidth + newWidth > iAvatarDialogTextRect.Width() )
            {
            point.iY += font->FontLineGap();
            point.iX = 10;
            curWidth = 0;
            }
        
        iBmpContext.DrawText( word, point + iAvatarDialogTextRect.iTl );
        curWidth += newWidth;
        point.iX += newWidth;
        }

    delete currentWords;
    currentWords = NULL;

    iBmpContext.DiscardFont();
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoPraiseL
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoPraiseL()
    {
    TInt praiseType = Math::Random() % 7;
    switch ( praiseType )
        {
        case 0:
            TalkL( _L( "Well done, Buddy!" ) );
            break;
        case 1:
            TalkL( _L( "Nice try, and keep it.." ) );
            break;
        case 2:
            TalkL( _L( "You did a good job!" ) );
            break;
        case 3:
            TalkL( _L( "Good job! I knew you could do it!" ) );
            break;
        case 4:
            TalkL( _L( "Wow, You are really amazing!" ) );
            break;
        case 5:
            TalkL( _L( "You guess it!" ) );
            break;
        case 6:
            TalkL( _L( "You're such a brain!" ) );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoCriticismL
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoCriticismL()
    {
    TInt criticismType = Math::Random() % 8;
    switch ( criticismType )
        {
        case 0:
            TalkL( _L( "You are not doing well, you know?" ) );
            break;
        case 1:
            TalkL( _L( "Ouch! You guessed the wrong point!" ) );
            break;
        case 2:
            TalkL( _L( "Uh, just be nice, always think twice! !" ) );
            break;
        case 3:
            TalkL( _L( "You need to use your brain more often." ) );
            break;
        case 4:
            TalkL( _L( "Wrong, but you almost got it. Guess again." ) );
            break;
        case 5:
            TalkL( _L( "You didn't guess right!" ) );
            break;
        case 6:
            TalkL( _L( "You've guessed wrong." ) );
            break;
        case 7:
            TalkL( _L( "I am afraid that you would be wrong." ) );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoEncourageL
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoEncourageL()
    {
    TInt encourageType = Math::Random() % 5;
    switch ( encourageType )
        {
        case 0:
            TalkL( _L( "Please don’t lose heart." ) );
            break;
        case 1:
            TalkL( _L( "Keep your chin up." ) );
            break;
        case 2:
            TalkL( _L( "Never say die. Try again and you'll probably succeed." ) );
            break;
        case 3:
            TalkL( _L( "Don't get discouraged." ) );
            break;
        case 4:
            TalkL( _L( "Oh, hei, don't lose heart. Try again!" ) );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoCongratulateL
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoCongratulateL()
    {
    TInt congratsType = Math::Random() % 5;
    switch ( congratsType )
        {
        case 0:
            TalkL( _L( "You win! Congratulate!" ) );
            break;
        case 1:
            TalkL( _L( "I knew you could do it. Congratulations!" ) );
            break;
        case 2:
            TalkL( _L( "You are the winner, congrats!!" ) );
            break;
        case 3:
            TalkL( _L( "Well, you win. Pop the champagne." ) );
            break;
        case 4:
            TalkL( _L( "You won, you lucky dog." ) );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoComplainL
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoComplainL()
    {
    TInt complainType = Math::Random() % 2;
    switch ( complainType )
        {
        case 0:
            TalkL( _L( "Get move on!" ) );
            break;
        case 1:
            TalkL( _L( "Let's hurry up." ) );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAvatarPane::DoOpeningL
// ----------------------------------------------------------------------------
//
void CAvatarPane::DoOpeningL()
    {
    TInt openingType = Math::Random() % 3;
    switch ( openingType )
        {
        case 0:
            TalkL( _L( "ok now, let's begin!" ) );
            break;
        case 1:
            TalkL( _L( "All right, go ahead.." ) );
            break;
        case 2:
            TalkL( _L( "Let's start our game now.." ) );
            break;
        default:
            break;
        }
    }

// End of file
