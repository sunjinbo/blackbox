/* ====================================================================
 * File: BlackboxWelcomeContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32property.h>
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknsSkinInstance.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <AknsControlContext.h>
#include <AknsBasicBackgroundControlContext.h>
#include <aknbutton.h>
#include <stringloader.h>
#include <Blackbox.rsg>
#include "BlackboxWelcomeContainer.h"
#include "BlackboxEditor.h"
#include "Blackbox.hrh"
#include "LayoutManager.h"
#include "BlackboxWelcomeView.h"
#include "Animation.h"
#include "BlackboxUtils.h"
#include "BlackboxPSKeys.h"
#include "Logger.h"

// CONSTANTS
_LIT( KResourceFile, "\\resource\\apps\\Blackbox.rsc" );

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeContainer* CBlackboxWelcomeContainer::NewL( 
        const TRect& aRect, CBlackboxWelcomeView& aView )
    {
    CBlackboxWelcomeContainer* self 
            = CBlackboxWelcomeContainer::NewLC( aRect, aView );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeContainer* CBlackboxWelcomeContainer::NewLC( 
        const TRect& aRect, CBlackboxWelcomeView& aView )
    {
    CBlackboxWelcomeContainer* self 
            = new ( ELeave ) CBlackboxWelcomeContainer( aView );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::~CBlackboxWelcomeContainer()
// Destructor
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeContainer::~CBlackboxWelcomeContainer()
    {
    delete iEditor;
    delete iBackGround;
    delete iButtonStart;
    delete iButtonOvi;
    delete iLayoutManager;
    delete iWelcAnim;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CBlackboxWelcomeContainer::CountComponentControls() const
    {
    TInt count = 0;

    if ( iEditor ) count++;
    if ( iButtonStart ) count++;
    if ( iButtonOvi ) count++;

    return count;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CBlackboxWelcomeContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0:
            return iEditor->Editor();
        case 1:
            return iButtonStart;
        case 2:
            return iButtonOvi;
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.Clear();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::Background( skin, iBackGround, gc, aRect );
    
    // Draw welcome icon
    TRect rect;
    rect = iLayoutManager->LayoutRect( EWelcIcon );

    if ( iWelcAnim )
        {
        iWelcAnim->Draw( gc, rect );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::SizeChanged()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::SizeChanged()
    {
    if ( iBackGround )
        {
        iBackGround->SetRect( Rect() );
        }

    LayoutControls();
    }

// --------------------------------------------------------------------------
// CSmartPromoUiSignupContainer::MopSupplyObject()
// Pass skin information if need.
// --------------------------------------------------------------------------
//
TTypeUid::Ptr CBlackboxWelcomeContainer::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId && iBackGround )
        {
        return MAknsControlContext::SupplyMopObject( aId, iBackGround );
        }
    return CCoeControl::MopSupplyObject(aId);
    }

// ----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        iLayoutManager->ResolutionChanged();
        SetRect( iWelcomeView.ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::HandleControlEventL()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::HandleControlEventL( CCoeControl* aControl,TCoeEvent aEventType )
    {
    if ( ( aEventType == EEventStateChanged ) )
        {    
        if( aControl == iButtonStart )
            {
            iWelcomeView.HandleCommandL( EBlackboxStartCmd );
            }
        else if( aControl == iButtonOvi )
            {
            iWelcomeView.HandleCommandL( EBlackboxOviCmd );
            }
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::AnimationPreparedL()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::AnimationPreparedL()
    {
    TInt err = RProperty::Set( 
                        KPSUidBlackbox, 
                        KBlackboxStartupStatus, 
                        EStartupScaleWelcImagesDone 
                        );
    User::LeaveIfError( err );
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::ConstructL( const TRect& aRect )
    {
    INFO( "CBlackboxWelcomeContainer::ConstructL" );

    CreateWindowL();

    //DrawableWindow()->SetOrdinalPosition( 0 );

    INFO( "Start to loading animation.." );
    LoadAnimationL();
    INFO( "The load of animation was done!" );
    
    iLayoutManager = CLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();
    INFO( "Layout manager was done!" );
    
    iEditor = CBlackboxEditor::NewL( this );
    iEditor->InitFormatsL();

    // Insert primary text
    HBufC* welcText = WelcGreetingTextL();
    CleanupStack::PushL( welcText );
    iEditor->InsertTextL( *welcText );
    CleanupStack::PopAndDestroy( welcText );
    INFO( "Editor was done!" );
    
    // Skin
    iBackGround = CAknsBasicBackgroundControlContext::NewL( 
        KAknsIIDQsnBgAreaMain, aRect, EFalse );

    TRgb textColor;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor,
                               KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6 );
    
    iButtonStart = static_cast< CAknButton* >
                    ( EikControlFactory::CreateByTypeL( EAknCtButton ).iControl );
    iButtonStart->ConstructFromResourceL ( R_BLACKBOX_BUTTON_START );
    iButtonStart->SetContainerWindowL( *this );
    iButtonStart->SetObserver( ( MCoeControlObserver* )this );
    iButtonStart->OverrideColorL( EColorButtonText, textColor );
    
    
    iButtonOvi = static_cast< CAknButton* >
                    ( EikControlFactory::CreateByTypeL( EAknCtButton ).iControl );
    iButtonOvi->ConstructFromResourceL ( R_BLACKBOX_BUTTON_OVI );
    iButtonOvi->SetContainerWindowL( *this );
    iButtonOvi->SetObserver( ( MCoeControlObserver* )this );
    iButtonOvi->OverrideColorL( EColorButtonText, textColor );
    
    INFO( "Buttons were done!" );
    
    SetRect( aRect );

    ActivateL();
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::CBlackboxWelcomeContainer()
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeContainer::CBlackboxWelcomeContainer( CBlackboxWelcomeView& aView )
: iCoeEnv( *CCoeEnv::Static() ), iWelcomeView( aView )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeContainer::LayoutControls()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::LayoutControls()
    {
    if ( iEditor )
        {
        iEditor->SetRect( iLayoutManager->LayoutRect( EWelcGreetingText ) );
        }

    if ( iButtonStart )
        {
        iButtonStart->SetRect( iLayoutManager->LayoutRect( EButtonStart ) );
        }

    if ( iButtonOvi )
        {
        iButtonOvi->SetRect( iLayoutManager->LayoutRect( EButtonOvi ) );
        }
    }

// ---------------------------------------------------------------------------
// CBlackboxWelcomeContainer::LoadAnimationL()
// ---------------------------------------------------------------------------
//
void CBlackboxWelcomeContainer::LoadAnimationL()
    {
    INFO( "CBlackboxWelcomeContainer::LoadAnimationL" );
    // Load resource file
    RFs& fileSession = iCoeEnv.FsSession();
    TFileName rscFileName( KResourceFile );
    TInt err = CompleteWithAppPath( rscFileName );
    if ( err != KErrNotSupported )
        {
        User::LeaveIfError( err );
        }

    // Get the exact filename of the resource file
    BaflUtils::NearestLanguageFile( fileSession, rscFileName );
    // Check if the resource file exists or not
    if ( ! BaflUtils::FileExists( fileSession, rscFileName ) )
        {
        User::Leave( KErrNotFound );
        }

    INFO_1( "rscFileName = %S", &rscFileName );
    
    TInt offset = 0;
    TRAP( err, offset = iCoeEnv.AddResourceFileL( rscFileName ) );
    TResourceReader reader;
    iCoeEnv.CreateResourceReaderLC( reader, R_BLACKBOX_WELCOME_ANIMATION );
    
    INFO( "Start to creating welcome anim.." );
    iWelcAnim = CAnimation::NewL( reader, *this );
    iWelcAnim->EnableControl( this );
    iWelcAnim->Start();
    INFO( "The creation of welcome anim was done." );
    
    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( offset );
    offset = 0;
    }

// ---------------------------------------------------------------------------
// CBlackboxWelcomeContainer::WelcGreetingTextL()
// ---------------------------------------------------------------------------
//
HBufC* CBlackboxWelcomeContainer::WelcGreetingTextL()
    {
    HBufC* text = StringLoader::LoadLC( R_BLACKBOX_WELC_GREETING_TEXT1 );
    HBufC* text2 = StringLoader::LoadLC( R_BLACKBOX_WELC_GREETING_TEXT2 );

    HBufC* welcText = HBufC::NewL( text->Length() + text2->Length() );
    welcText->Des().Append( *text );
    welcText->Des().Append( *text2 );
    
    CleanupStack::PopAndDestroy( text2 );
    CleanupStack::PopAndDestroy( text );

    TBlackboxUtils::FixLineBreaks( welcText );

    return welcText;
    }

// End of File
