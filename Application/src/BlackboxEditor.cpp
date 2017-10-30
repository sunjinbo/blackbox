/* ====================================================================
 * File: BlackboxEditor.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <eikrted.h>
#include <gulicon.h>
#include <txtrich.h>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <gdi.h>
#include "BlackboxEditor.h"
#include "BlackboxUtils.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CBlackboxEditor::CBlackboxEditor()
// ---------------------------------------------------------------------------
//
CBlackboxEditor* CBlackboxEditor::NewL(const CCoeControl* aControl)
    {
    CBlackboxEditor* self = new (ELeave)CBlackboxEditor;
    CleanupStack::PushL( self );
    self->ConstructL(aControl);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CBlackboxEditor::CBlackboxEditor()
// ---------------------------------------------------------------------------
//
CBlackboxEditor::~CBlackboxEditor()
    {
    delete iEditor;
    }

// -----------------------------------------------------------------------------
// CPaPluginContainer::InsertPrimaryTextL()
// -----------------------------------------------------------------------------
//
void CBlackboxEditor::InsertTextL(const TDesC& aText)
    {
    RichText().InsertL( iPos, aText );

    iParaFormat.iHorizontalAlignment = CParaFormat::ELeftAlign;
    iParaFormatMask.SetAttrib( EAttAlignment );
    iParaFormat.iVerticalAlignment = CParaFormat::ETopAlign;
    iParaFormatMask.SetAttrib( EAttVerticalAlignment );

    RichText().ApplyParaFormatL( &iParaFormat, iParaFormatMask, iPos = 0, 0 );

    iPos += aText.Length();

    iEditor->SetCursorPosL(iEditor->Text()->DocumentLength(), EFalse);

    iEditor->HandleTextChangedL();
    
    iEditor->UpdateScrollBarsL();
    }

// -----------------------------------------------------------------------------
// CPaPluginContainer::InitFormatsL()
// -----------------------------------------------------------------------------
//
void CBlackboxEditor::InitFormatsL()
    {
    // Initialize attributes of char and paragraph formats
    iCharFormatMask.SetAttrib( EAttFontTypeface );
    iCharFormatMask.SetAttrib( EAttFontHeight );
    iCharFormatMask.SetAttrib( EAttColor );
    iParaFormatMask.SetAttrib( EAttVerticalAlignment );
    iParaFormatMask.SetAttrib( EAttAlignment );
    iParaFormatMask.SetAttrib( EAttLeftMargin );
    iParaFormatMask.SetAttrib( EAttRightMargin );

    // Set global vertical alignment and margins
    CGraphicsDevice* gDev = CEikonEnv::Static()->ScreenDevice();
    iParaFormat.iVerticalAlignment = CParaFormat::ECenterAlign;
    TBlackboxPromoMargins margins = TBlackboxUtils::GetMargins();
    iParaFormat.iLeftMarginInTwips = gDev->HorizontalPixelsToTwips(
            margins.iLeftMargin );    // left margin
    iParaFormat.iRightMarginInTwips = gDev->HorizontalPixelsToTwips(
            margins.iRightMargin ); // right margin
    iEditor->ApplyParaFormatL( &iParaFormat, iParaFormatMask ); // apply
    iEditor->SetTextL( &KNullDesC );

    // Set font and character format
    const CFont* logicalFont = AknLayoutUtils::FontFromId(
            EAknLogicalFontPrimarySmallFont );
    iCharFormat.iFontSpec = logicalFont->FontSpecInTwips(); // set font
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), iTextColor,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6 );
    iCharFormat.iFontPresentation.iTextColor = TLogicalRgb( iTextColor ); // set font color
    RichText().SetInsertCharFormatL( iCharFormat, iCharFormatMask, iPos = 0 ); // apply
    }

// -----------------------------------------------------------------------------
// CBlackboxEditor::SetRect()
// -----------------------------------------------------------------------------
//
void CBlackboxEditor::SetRect( const TRect& aRect )
    {
    TRAP_IGNORE( SetRectL( aRect ) );
    }

// -----------------------------------------------------------------------------
// CBlackboxEditor::HandleSkinChangeL()
// -----------------------------------------------------------------------------
//
void CBlackboxEditor::HandleSkinChangeL()
    {
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), iTextColor,
                               KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6 );
    iCharFormat.iFontPresentation.iTextColor = TLogicalRgb( iTextColor );    
    
    iEditor->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, 0, iPos );
    iEditor->HandleTextChangedL();
    }

// ---------------------------------------------------------------------------
// CBlackboxEditor::CBlackboxEditor()
// ---------------------------------------------------------------------------
//
CBlackboxEditor::CBlackboxEditor() : iPos( 0 )
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CBlackboxEditor::CBlackboxEditor()
// ---------------------------------------------------------------------------
//
void CBlackboxEditor::ConstructL(const CCoeControl* aControl)
    {
    iEditor = new(ELeave)CEikRichTextEditor; 
    iEditor->ConstructL( aControl, 0, 0, 
            CEikEdwin::EDisplayOnly |             // no response to input
            CEikEdwin::EReadOnly |                // cannot add text
            CEikEdwin::EAvkonDisableCursor |    // no cursor
            CEikEdwin::EAvkonEditor |
            CEikEdwin::EEdwinAlternativeWrapping |
            CEikEdwin::ENoAutoSelection  );        // no selection
    iEditor->SetContainerWindowL( *aControl );
    iEditor->SetFocus( ETrue );
    //iEditor->SetBorderViewMargins( TMargins8( 0, 0, 0, 0 ) );
    iEditor->SetBorder( TGulBorder::ENone );
    iEditor->CreateTextViewL();
    iEditor->UpdateScrollBarsL();
    }

// ---------------------------------------------------------------------------
// CBlackboxEditor::CBlackboxEditor()
// ---------------------------------------------------------------------------
//
CRichText& CBlackboxEditor::RichText() const
    {
    return *iEditor->RichText();
    }

// -----------------------------------------------------------------------------
// CBlackboxEditor::SetRectL()
// -----------------------------------------------------------------------------
//
void CBlackboxEditor::SetRectL( const TRect& aRect )
    {
    TRect editorRect = aRect;

    iEditor->SetRect( editorRect );
    iEditor->TextView()->FormatTextL();
    iEditor->TextView()->FinishBackgroundFormattingL();

    const TInt docLength = iEditor->RichText()->DocumentLength();

    TPoint lastCharPos( editorRect.iBr );
    TInt lastCharVisible = iEditor->TextView()->XyPosToDocPosL(  lastCharPos  );
    iEditor->TextView()->DocPosToXyPosL( lastCharVisible, lastCharPos );

    iEditor->CreateScrollBarFrameL()->SetScrollBarVisibilityL( 
            CEikScrollBarFrame::EOn,
            CEikScrollBarFrame::EOn 
            );

    CEikScrollBar* scrlBar = 
        iEditor->ScrollBarFrame() ? iEditor->ScrollBarFrame()->VerticalScrollBar() : NULL;
    if ( scrlBar )
        {
        CEikScrollBarFrame::TScrollBarVisibility visibility = CEikScrollBarFrame::EOff;
        if ( lastCharVisible < docLength || lastCharPos.iY > editorRect.iBr.iY )
            {
            visibility = CEikScrollBarFrame::EOn;
            }
        iEditor->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff, visibility );

        scrlBar = iEditor->ScrollBarFrame()->VerticalScrollBar();

        TRect scrollbarRect = scrlBar->Rect();
        TRect editorRect = iEditor->Rect();
        TInt screenheight = editorRect.Height();
        TInt screenwidth = editorRect.Width();

        if ( AknLayoutUtils::LayoutMirrored() )
            {
            editorRect.iTl.iX = scrollbarRect.Width();    
            editorRect.iBr.iX -= scrollbarRect.Width(); 
            }
        else
            {
            editorRect.iBr.iX -= scrollbarRect.Width();
            } // mirroredUI

        iEditor->SetRect( editorRect );
        iEditor->UpdateScrollBarsL();
        }

    iEditor->DrawDeferred();    
    }

// End of file
