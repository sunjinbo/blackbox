/* ====================================================================
 * File: QueryDialog.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <touchfeedback.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsDrawUtils.h>
#include <aknutils.h>
#include <stringloader.h>
#include <Blackbox.rsg>
#include "QueryDialog.h"
#include "Common.h"
#include "LayoutManager.h"

// GLOBAL FUNCTIONS
static CCharFormatLayer* FormatLayerByLogicalIdL( TInt aFontLogicalId );

//---------------------------------------------------------------------------------------
// CQueryDialog::NewL()
//---------------------------------------------------------------------------------------
CQueryDialog* CQueryDialog::NewL( MHyperLinkControlObserver& aObserver )
    {
	CQueryDialog* self = new (ELeave) CQueryDialog( aObserver );
	CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

//---------------------------------------------------------------------------------------
// CQueryDialog::~CQueryDialog()
//---------------------------------------------------------------------------------------
CQueryDialog::~CQueryDialog()
    {
	delete iLayoutManager;

    if ( iTitlePane )
        {
        AknsUtils::DeregisterControlPosition( iTitlePane );
        delete iTitlePane;
        }

    if ( iMainPane )
        {
        AknsUtils::DeregisterControlPosition( iMainPane );
        delete iMainPane;
        }

    if ( iHyperLinkControl )
        {
        AknsUtils::DeregisterControlPosition( iHyperLinkControl );
        delete iHyperLinkControl;
        }
    }

//---------------------------------------------------------------------------------------
// TInt CQueryDialog::ExecuteLD()
//---------------------------------------------------------------------------------------
TInt CQueryDialog::ExecuteLD()
    {
    return CAknQueryDialog::ExecuteLD( R_BLACKBOX_WELCOME_DIALOG ); 
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::PreLayoutDynInitL()
//---------------------------------------------------------------------------------------
void CQueryDialog::PreLayoutDynInitL()
    {
    CAknQueryDialog::PreLayoutDynInitL();
    SetEditableL( EFalse );

    const TInt edwinFlags 
        = CEikEdwin::ENoAutoSelection | CEikEdwin::EDisplayOnly | CEikEdwin::EReadOnly;

    //create title control
    delete iTitlePane; 
    iTitlePane = NULL;

    iTitlePane = new (ELeave) CEikEdwin;
    iTitlePane->ConstructL( edwinFlags );
    iTitlePane->SetContainerWindowL( *this );
    iTitlePane->SetCharFormatLayer( FormatLayerByLogicalIdL( EAknLogicalFontPrimaryFont ) );

    //create main control
    delete iMainPane; 
    iMainPane = NULL;

    iMainPane = new (ELeave) CEikEdwin;
    iMainPane->ConstructL( edwinFlags );
    iMainPane->SetContainerWindowL( *this );
    iMainPane->SetCharFormatLayer( FormatLayerByLogicalIdL( EAknLogicalFontPrimarySmallFont ) );

    //create hyperlink control
    delete iHyperLinkControl; 
    iHyperLinkControl = NULL;

    iHyperLinkControl = new (ELeave) CHyperLinkControl;
    iHyperLinkControl->SetContainerWindowL( *this );
    iHyperLinkControl->SetObserver( this );
    iHyperLinkControl->CreateEditorL();
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::PostLayoutDynInitL()
//---------------------------------------------------------------------------------------
void CQueryDialog::PostLayoutDynInitL()
    {
    if ( iTitlePane )
        {
        HBufC* title = StringLoader::LoadLC( R_BLACKBOX_FIRSTTIMEUSE_TITLE );
        iTitlePane->SetTextL( title );
        CleanupStack::PopAndDestroy( title );
        }

    if (iMainPane)
        {
        HBufC* contents = StringLoader::LoadLC( R_BLACKBOX_FIRSTTIMEUSE_CONTENTS );  
        iMainPane->SetTextL( contents );
        CleanupStack::PopAndDestroy( contents );
        }

    if ( iHyperLinkControl )
        {
        HBufC* link = StringLoader::LoadLC( R_BLACKBOX_FIRSTTIMEUSE_LINK );
        iHyperLinkControl->SetMessageTextL( *link );
        CleanupStack::PopAndDestroy( link );
        }
    }

//---------------------------------------------------------------------------------------
// TInt CQueryDialog::CountComponentControls() const
//---------------------------------------------------------------------------------------
TInt CQueryDialog::CountComponentControls() const
    {
    return ELastControl;
    }

//---------------------------------------------------------------------------------------
// CCoeControl* CQueryDialog::ComponentControl(TInt aIndex) const
//---------------------------------------------------------------------------------------
CCoeControl* CQueryDialog::ComponentControl(TInt aIndex) const
    {
    switch( aIndex )
        {
        case ETitleControl:
            return iTitlePane;
        case EMainControl:
            return iMainPane;
        case EHyperLinkControl:
            return iHyperLinkControl;
        default:
            return NULL;
        };
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::Draw( const TRect& aRect ) const
//---------------------------------------------------------------------------------------
void CQueryDialog::Draw( const TRect& aRect ) const
    {
    // Get the standard graphics context
    CWindowGc& gc = SystemGc();
    
    //draw dialog's background
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, gc, aRect, KAknsDrawParamNoClearUnderImage );
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::SizeChanged()
//---------------------------------------------------------------------------------------
void CQueryDialog::SizeChanged()
    {
    TRect rect( Rect() );

    if ( iTitlePane )
        {
        TRect edwinRect = rect;
        RectForTitle( edwinRect );
        iTitlePane->SetRect( edwinRect );
        AknsUtils::RegisterControlPosition( iTitlePane );
        }
    
    if ( iMainPane )
        {
        TRect edwinRect = rect;
        RectForMain( edwinRect );
        iMainPane->SetRect( edwinRect );
        AknsUtils::RegisterControlPosition( iMainPane );
        }
    
    if ( iHyperLinkControl )
        {
        TRect edwinRect = rect;
        RectForHyperLink( edwinRect );
        iHyperLinkControl->SetRect( edwinRect );
        AknsUtils::RegisterControlPosition( iHyperLinkControl );
        }    
    
    CAknQueryDialog::SizeChanged();
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::SetSizeAndPosition()
//---------------------------------------------------------------------------------------
void CQueryDialog::SetSizeAndPosition( const TSize &aSize )
    {
    CAknQueryDialog::SetSizeAndPosition( aSize );

    // Get correct dialog size from the layout data.
    TRect theRect = iLayoutManager->LayoutRect( EWelcQuery );

    SetExtent( theRect.iTl, theRect.Size() );
    }

//---------------------------------------------------------------------------------------
// CQueryDialog::CQueryDialog()
//---------------------------------------------------------------------------------------
CQueryDialog::CQueryDialog( MHyperLinkControlObserver& aObserver )
: CAknQueryDialog( CAknQueryDialog::EConfirmationTone ), iObserver( aObserver )
    {
    // no implementation required
    }

//---------------------------------------------------------------------------------------
// CQueryDialog::ConstructL()
//---------------------------------------------------------------------------------------
void CQueryDialog::ConstructL()
    {
	iLayoutManager = CLayoutManager::NewL();
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::RectForTitle(TRect& aRect) const
//---------------------------------------------------------------------------------------
void CQueryDialog::RectForTitle( TRect& aRect ) const
    {
    aRect = iLayoutManager->LayoutRect( EWelcQueryTitle );
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::RectForMain(TRect& aRect) const
//---------------------------------------------------------------------------------------
void CQueryDialog::RectForMain( TRect& aRect ) const
    {
	aRect = iLayoutManager->LayoutRect( EWelcQueryMainPane );
    }

//---------------------------------------------------------------------------------------
// void CQueryDialog::RectForHyperLink(TRect& aRect) const
//---------------------------------------------------------------------------------------
void CQueryDialog::RectForHyperLink( TRect& aRect ) const
    {
	aRect = iLayoutManager->LayoutRect( EWelcQueryHyperLink );
    }

//---------------------------------------------------------------------------------------
// CCharFormatLayer* FormatLayerByLogicalIdL(TInt aFontLogicalId)
//---------------------------------------------------------------------------------------
static CCharFormatLayer* FormatLayerByLogicalIdL(TInt aFontLogicalId)
    {
    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
    charFormat.iFontSpec = AknLayoutUtils::FontFromId(aFontLogicalId)->FontSpecInTwips();
    charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightNormal);

    charFormat.iFontPresentation.iTextColor = TLogicalRgb( FontColor() );
    charFormatMask.SetAll();

    return CCharFormatLayer::NewL( charFormat, charFormatMask );
    }

//---------------------------------------------------------------------------------------
// CCharFormatLayer* FormatLayerByLogicalIdL(TInt aFontLogicalId)
//---------------------------------------------------------------------------------------
void CQueryDialog::HyperLinkControlTappedL()
    {
    MTouchFeedback* feedBack = MTouchFeedback::Instance();
    if (feedBack)
        {
        feedBack->InstantFeedback( ETouchFeedbackBasic );
        iObserver.HyperLinkControlTappedL();
        }
    }

// End of file
