/* ====================================================================
 * File: HyperlinkControl.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <eikappui.h>

#include <AknsDrawUtils.h>
#include <eikrted.h>
#include <txtrich.h> 
#include <txtfrmat.h>
#include <aknconsts.h>
#include "HyperlinkControl.h"
#include "Common.h"

CHyperLinkControl::CHyperLinkControl() :
iNumberOfLines(3), iLinesPerPage(3),iFirstVisibleLink( -1 )
    {
    }

CHyperLinkControl::~CHyperLinkControl()
    {
    AknsUtils::DeregisterControlPosition( iEdwin );
    delete iEdwin;
    iLinkTextLocationArray.Close();
    iLinkTextArray.Close();
    }



 void CHyperLinkControl::SetMessageTextL(const TDesC& aMessage)
    {
    _LIT (KOpeningLinkTag, "<a>");
    _LIT (KClosingLinkTag, "</a>");

    const TInt KLinkStartTagLength = 3;
    const TInt KLinkEndTagLength = 4;

    const TInt openingTag = aMessage.Find(KOpeningLinkTag);
    const TInt closingTag = aMessage.Find(KClosingLinkTag);

    if (openingTag != KErrNotFound && closingTag != KErrNotFound)
        {
        HBufC* buffer = aMessage.AllocLC();
        TPtr message = buffer->Des();

        message.Delete(closingTag, KLinkEndTagLength);
        message.Delete(openingTag, KLinkStartTagLength);

        RArray<TInt> formatTextLocationArray;
        RArray<TDesC*> formatTextArray;
        RArray<TFormatTag> formatTypeArray;

        TPtr text = message.MidTPtr(openingTag, closingTag - openingTag
                - KLinkStartTagLength);
        HBufC* textBuffer = text.AllocLC();

        formatTextArray.Append(textBuffer);
        formatTextLocationArray.Append(openingTag);
        formatTypeArray.Append(EFormatLink);

        SetMessageTextWithFormattingL(&message, &formatTextArray,
                &formatTextLocationArray, &formatTypeArray);

        CleanupStack::PopAndDestroy(textBuffer);
        CleanupStack::PopAndDestroy(buffer);

        formatTextArray.Close();
        formatTextLocationArray.Close();
        formatTypeArray.Close();

        }
    }         
    
void CHyperLinkControl::CreateEditorL()
    {
    if(iEdwin) return;
    iEdwin = new ( ELeave ) CEikRichTextEditor( TGulBorder::ENone );
    iEdwin->SetContainerWindowL( *this );
    iEdwin->ConstructL(iEdwin, 0,0, CEikEdwin::ENoAutoSelection | CEikEdwin::EDisplayOnly | CEikEdwin::EReadOnly);

    iEdwin->SetEdwinObserver( this );
    iEdwin->SetAvkonWrap( ETrue );                                  
    iEdwin->SetFocus( EFalse );
    iEdwin->SetNonFocusing();
    iEdwin->EnableKineticScrollingL(ETrue);
    }

void CHyperLinkControl::LayoutEditorL()
    {   
    iEdwin->SetRect(Rect());
    }    

TKeyResponse CHyperLinkControl::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode /*aModifiers*/ )
    {
    const TInt key( aKeyEvent.iCode );
    if( !(key == EKeyDownArrow || key == EKeyUpArrow) )
        return EKeyWasConsumed;
    
    const TBool moveDown = key == EKeyDownArrow; // Moving down?
        
    /* 4 transitions are possible:
    
    Text   -> *Link*
    *Link* -> *Link*
    *Link* -> Text
    Text   -> >>Scroll page>>
    
    */
    
    // If the editor was scrolled with pen, synchronize the query's and editor's states
    const TInt editorTopLine = iEdwin->TextLayout()->FirstLineInBand();
    if( editorTopLine != iTopLine )
        {
        if( LinkHighLighted() ) // Standing on a link?
            {
            // Synchronize to the query's position
            iEdwin->TextView()->SetViewLineAtTopL( iTopLine + 1 );    // Uses 1-based line numbers
            }
        else
            {
            // Synchronize to the editor's position
            iTopLine = editorTopLine;
            UpdatePageInfo();
            }
        }
        
    SetHighlightOnL( EFalse );  // Dehighlight the old link    
        
    // Move to the following position    
    iCurPos += moveDown? 1 : -1;
    if( iCurPos < 1 || iPositionsCount -1  <= iCurPos ) // Beyond the allowed range
        {
//        if( CanScrollPage( moveDown ) )
//            {
//            iTopLine += moveDown? iLinesPerPage - 1 : 1 - iLinesPerPage;
//            if( iTopLine >= iNumberOfLines - iLinesPerPage)
//                {
//                iTopLine = iNumberOfLines - iLinesPerPage;
//                }
//            if( iTopLine < 0)
//                {
//                iTopLine = 0;
//                }
//            iEdwin->MoveDisplayL( moveDown? TCursorPosition::EFPageDown : TCursorPosition::EFPageUp );
//            int lastPageLink = -1;
//            if( iFirstVisibleLink > -1 )
//                lastPageLink = moveDown?
//                    (iFirstVisibleLink + iVisibleLinksCount - 1): iFirstVisibleLink;
//            UpdatePageInfo();
//            if( lastPageLink > -1 && iFirstVisibleLink > -1 )
//                {
//                if( moveDown )
//                    {
//                    iCurPos = 1;
//                    while( lastPageLink-- >= iFirstVisibleLink )
//                        {
//                        iCurPos++;
//                        }
//                    }
//                
//                else
//                    {
//                    iCurPos = iPositionsCount - 2;
//                    while( lastPageLink++ <= iFirstVisibleLink + iVisibleLinksCount - 1 )
//                        {
//                        iCurPos--;
//                        }    
//                    }
//                
//                }
//            else
//                {
//                iCurPos = moveDown? 1 : iPositionsCount - 2;   // Proceed to top or bottom of the following page
//                }
//            }
//        else
//            {
//            iCurPos = moveDown? iPositionsCount - 1 : 0;    // Return to bottom or top of the current page
//            }
        }
    
    SetHighlightOnL( ETrue );   // Highlight the new link
    

    return( EKeyWasConsumed );
    }

void CHyperLinkControl::SizeChanged()
    {
    TRAP_IGNORE( DoSizeChangedL() );
    }


TSize CHyperLinkControl::MinimumSize()
    {    
    return Rect().Size();
    } 


TRect CHyperLinkControl::LayoutRect() const
    {    
    return Rect();
    }

TInt CHyperLinkControl::CountComponentControls() const
    {
     return 1;
    }


CCoeControl* CHyperLinkControl::ComponentControl( TInt ) const
    {
    return iEdwin;
    }         

void CHyperLinkControl::ActivateL()
    {
    CCoeControl::ActivateL();
    }

 void CHyperLinkControl::Draw( const TRect& /*aRect*/ ) const
    {
//    CWindowGc& gc=SystemGc(); 
//    TRect messageQueryControlRect( Rect() );
//    TRect popupRect(LayoutRect());
//
//    TRect backgroundRect(messageQueryControlRect.iTl, popupRect.iBr);    
//    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
//    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

//    TRegionFix<4> clipReg;
//    clipReg.AddRect( backgroundRect );
//    
//    if ( iEdwin )
//        {
//        clipReg.SubRect( iEdwin->Rect() );
//        }
//    
//    gc.SetClippingRegion( clipReg );
//    AknsDrawUtils::Background( skin, cc, this, gc, Rect(), 
//            KAknsDrawParamNoClearUnderImage );
//    gc.CancelClippingRegion();
    }

TInt CHyperLinkControl::CurrentLink() const
    {
    if( 0 < iCurPos && iCurPos < iPositionsCount - 1 ) // The current position is on a link
        {
        return iCurPos - 1 + iFirstVisibleLink;
        }
    else    // No link is active
        {
        return -1;
        }
    }

 TBool CHyperLinkControl::LinkHighLighted() const
    {
    return CurrentLink() > -1;
    }

void CHyperLinkControl::SetHighlightOnL( TBool aOn )
    {
    if( !LinkHighLighted() )
        return;
    iCharFormatMask.ClearAll();
    if ( iEdwin && iEdwin->TextLength() > 0 &&
        iLinkTextArray.Count() > 0 && iLinkTextArray[CurrentLink()]->Length() > 0 )
        {
        iCharFormatMask.SetAttrib( EAttFontHighlightStyle );
        iCharFormatMask.SetAttrib( EAttFontHighlightColor );
        if ( aOn )
            {
            iCharFormat.iFontPresentation.iHighlightStyle = TFontPresentation::EFontHighlightNormal;
            
            TRgb color = AKN_LAF_COLOR( 244 );
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG1 ); 
            iCharFormat.iFontPresentation.iHighlightColor = color;
            
            color = AKN_LAF_COLOR( 210 );
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG3 );                    
            iCharFormat.iFontPresentation.iTextColor = color;           
            }
        else
            {
            iCharFormat.iFontPresentation.iHighlightStyle = TFontPresentation::EFontHighlightNone;
            }

        if ( iLinksCount > 0 )
            {
            iEdwin->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, ( iLinkTextLocationArray )[CurrentLink()], ( iLinkTextArray )[CurrentLink()]->Length() );
            }

        iEdwin->DrawNow();
        }
    }

TBool CHyperLinkControl::IsLinkVisible( TInt aIndex ) const
    {
    if ( aIndex >= iLinksCount )
        {
        return EFalse;
        }
    TInt linkLine( iEdwin->TextLayout()->GetLineNumber( iLinkTextLocationArray[aIndex] ) );
    if ( iTopLine <= linkLine && linkLine < iTopLine + iLinesPerPage )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

void CHyperLinkControl::UpdatePageInfo()
    {
    TBool firstFound( EFalse );
    iVisibleLinksCount = 0;
    iFirstVisibleLink = -1;
    
    // Update visible links
    for( TInt count = 0; count < iLinksCount; count++ )
        {
        if( IsLinkVisible( count ) )
            {
            iVisibleLinksCount++;
            if( !firstFound )
                {
                iFirstVisibleLink = count;
                firstFound = ETrue;
                }
            }
        else if( firstFound )   // All visible links have been already found
            {
            break;
            }
        }
    
    // Update number of cursor positions
    if( iVisibleLinksCount > 0 )
        {
        iPositionsCount = iVisibleLinksCount + 2;
        }
    else
        {
        iPositionsCount = 1;
        }
    }

void CHyperLinkControl::SetMessageTextWithFormattingL( TDesC* aMessage, RArray<TDesC*>* aFormatTextArray, RArray<TInt>* aFormatTextLocationArray, RArray<TFormatTag>* aFormatTypeArray )
    {
    CreateEditorL();
    iEdwin->TextLayout()->SetAmountToFormat( CTextLayout::EFFormatAllText );
    if ( aMessage->Length() > iEdwin->UpperFullFormattingLength() )
        iEdwin->SetUpperFullFormattingLength( aMessage->Length() ); 
    iEdwin->RichText()->DeleteL( 0, iEdwin->RichText()->DocumentLength() );
    iEdwin->RichText()->InsertL ( 0, *aMessage );
                
    // Initialize link data
    for ( TInt count = 0; count < aFormatTypeArray->Count(); count++ )
        {
        if ( (*aFormatTypeArray)[count] == EFormatLink )
            {
            // Add the link location and text keeping the arrays sorted on the location
            TInt location = (*aFormatTextLocationArray)[count];
            iLinkTextLocationArray.InsertInOrder( location );
            TInt index = iLinkTextLocationArray.FindInOrder( location );
            iLinkTextArray.Insert( (*aFormatTextArray)[count], index );
            }
        }
    iLinksCount = iLinkTextLocationArray.Count();

    iCharFormatMask.ClearAll();  
    
    CFont* font = FontForFooter();
    
    iCharFormat.iFontSpec = font->FontSpecInTwips();
    iCharFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightNormal);    
    iCharFormat.iFontPresentation.iTextColor = TLogicalRgb( FontColor() );
    iEikonEnv->ReleaseScreenFont(font);
    
    
    iCharFormatMask.SetAll();
    iEdwin->RichText()->ApplyCharFormatL(iCharFormat, iCharFormatMask, 0, iEdwin->TextLength());
    
    /////
    CParaFormat* paraformat = CParaFormat::NewLC(); 
    TParaFormatMask paraFormatMask; 
    paraFormatMask.SetAttrib(EAttLineSpacing);
    paraFormatMask.SetAttrib(EAttLineSpacingControl);
    paraformat->iLineSpacingControl = CParaFormat::ELineSpacingExactlyInTwips;
    const TReal KLineSpacingFactor = 1.2;
    TInt lineHeight = iCharFormat.iFontSpec.iHeight * KLineSpacingFactor;
    paraformat->iLineSpacingInTwips = lineHeight;
    iEdwin->RichText()->ApplyParaFormatL(paraformat, paraFormatMask,0,iEdwin->TextLength());
    CleanupStack::PopAndDestroy(paraformat);
    /////
    
    // Set link font
    if (aMessage->Length() > 0)
        {
        // Set font color and underlining
           for (TInt count = 0; count < iLinksCount; count++)
            {    
            if ((iLinkTextLocationArray )[count] != KErrNotFound)
                {
                iCharFormatMask.SetAttrib( EAttFontUnderline );
                iCharFormatMask.SetAttrib( EAttColor );
                iCharFormat.iFontPresentation.iUnderline = EUnderlineOn;
                
                TRgb color = AKN_LAF_COLOR( 210 );
                AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG3 );
                    
                iCharFormat.iFontPresentation.iTextColor = color;
                
                iEdwin->RichText()->ApplyCharFormatL(iCharFormat, iCharFormatMask, (iLinkTextLocationArray)[count], ((iLinkTextArray )[count])->Length());
                }            
            }     
        
        iCharFormatMask.ClearAll();
        
        // Set font boldness
        for ( TInt count = 0; count < aFormatTextLocationArray->Count(); count++ )
            {    
            if ((*aFormatTextLocationArray)[count] != KErrNotFound && (*aFormatTypeArray)[count] == EFormatBold)
                {
                iCharFormatMask.SetAttrib( EAttFontStrokeWeight );
                iCharFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
                iEdwin->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, (*aFormatTextLocationArray)[count], (*aFormatTextArray )[count]->Length() );
                }
            }
        }
        
    LayoutEditorL();
    
    if ( aMessage->Locate( '\n' ) != KErrNotFound )
        {
        iEdwin->SetCursorPosL( 1, EFalse );
        SEdwinFindModel findModel;
        _LIT( KNChar,"\n" ); 
        _LIT( KFChar,"\f" );
        TBuf<1> text( KNChar );
        TBuf<1> replaceText( KFChar );
        findModel.iFlags = 0;
        findModel.iText = text;
        findModel.iReplaceText = replaceText;
        findModel.iReplaceOption = EReplaceAll;
        iEdwin->ReplaceAllL( &findModel );
        }
        
    iNumberOfLines = iEdwin->TextLayout()->NumFormattedLines();
    iTopLine = 0;
    iCurPos = 0;   // Page top, no link selected
    
    UpdatePageInfo();
    }


/**
 * CHyperLinkControl::HandlePointerEventL()
 *
 * Transfers pointerevent to editor control.
 * Checks for the object destruction after the pointer event handling.
 */
void CHyperLinkControl::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    TBool highlightBefore = LinkHighLighted();

    // Call default implementation of HandlePointerEventL to transfer event to correct control.
    CAknControl::HandlePointerEventL( aPointerEvent );
    
    TBool highlightAfter = LinkHighLighted();
    if( aPointerEvent.iType == TPointerEvent::EButton1Down && 
        highlightBefore == highlightAfter && highlightAfter )
        {
        DehighlightLink();
        }
    
    if (iObserver && aPointerEvent.iType == TPointerEvent::EButton1Down)
        iObserver->HyperLinkControlTappedL();    
    }

//----------------------------------------------------------------------------------
// CHyperLinkControl::LinkTapped()
// Checks if a link is tapped and hightlights it. 
//----------------------------------------------------------------------------------
//

TBool CHyperLinkControl::LinkTappedL( TInt aPos )
    {
    if ( iLinksCount <= 0 )
        {
        return EFalse; 
        }
    /** There can be 3 possible results.
    1. The link is found and it's a new link.
    2. The link is found, but it's the current link.
    3. The link was not found at the tapped position. 
    */
    TInt oldLink = CurrentLink();
    TInt linkPos = 0; 
    for ( TInt count = 0; count < iLinksCount; count++ )
        {
        linkPos = iLinkTextLocationArray[count];
        if ( linkPos <= aPos && aPos < linkPos + iLinkTextArray[count]->Length() ) // The tapped link found
            {
            if ( oldLink != count ) // A new link
                {
                TInt editorTopLine = iEdwin->TextLayout()->FirstLineInBand();
                if( iTopLine != editorTopLine ) // User scrolled with the pen
                    {
                    // Synchronize query's top line with editor's one
                    iTopLine = editorTopLine;
                    UpdatePageInfo();
                    }
                SetCurPosL( count - iFirstVisibleLink + 1 ); 
                }
            return ETrue; 
            }
        }
    DehighlightLink();
    return EFalse; 
    }


TBool CHyperLinkControl::SetCurPosL( TInt aCurPos )
    {
    if( aCurPos < 0 || aCurPos >= iPositionsCount )
        return EFalse;
    SetHighlightOnL( EFalse );  // Dehighlight the old link
    iCurPos = aCurPos;
    SetHighlightOnL( ETrue );     // Highlight the new link
    return ETrue;
    }
    
void CHyperLinkControl::DehighlightLink()
    {
    if ( !LinkHighLighted() )
        {
        return; 
        }
    TRAP_IGNORE( SetHighlightOnL( EFalse ) );  // Dehighlight the old link
    iCurPos = 0;    // Move the cursor to the top of the page
    }


void CHyperLinkControl::DoSizeChangedL()
    {        
        iNumberOfLines = iEdwin->TextLayout()->NumFormattedLines();
        iLinesPerPage = iNumberOfLines;
        iEdwin->SetRect(Rect());
    }

void CHyperLinkControl::HandleEdwinEventL( CEikEdwin* , TEdwinEvent aEventType )
    {
    if( aEventType == MEikEdwinObserver::EEventScroll )
        {
        DehighlightLink();
        }
    }

void CHyperLinkControl::FocusOnLinkL( TBool aOn )
    {
    iIsLinkFocused = aOn;

    if( iLinksCount > 0 )
        {
        if ( aOn )
            {
            TInt count = 0;
			const TInt KHighlightColor = 244;
			const TInt KTextColor = 210;
            iCharFormatMask.ClearAll();
            iCharFormatMask.SetAttrib( EAttFontHighlightStyle );
            iCharFormatMask.SetAttrib( EAttFontHighlightColor );

            iCharFormat.iFontPresentation.iHighlightStyle = TFontPresentation::EFontHighlightNormal;

			TRgb color = AKN_LAF_COLOR( KHighlightColor );
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG1 );
            iCharFormat.iFontPresentation.iHighlightColor = color;

			color = AKN_LAF_COLOR( KTextColor );
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG3 );
            iCharFormat.iFontPresentation.iTextColor = color;
            iEdwin->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, ( iLinkTextLocationArray )[count], iLinkLength );
            iEdwin->DrawNow();
            }
        else
            {
            TInt count = 0;
            iCharFormat.iFontPresentation.iHighlightStyle = TFontPresentation::EFontHighlightNone;
            iEdwin->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, ( iLinkTextLocationArray )[count], iLinkLength );
            iEdwin->DrawNow();
            }
        }
    }

TBool CHyperLinkControl::IsLinkFocused()
    {
    return iIsLinkFocused;
    }

//  End of File
