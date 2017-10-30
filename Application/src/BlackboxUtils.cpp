/* ====================================================================
 * File: BlackboxUtils.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknUtils.h> 
#include <AknIconUtils.h>
#include <gulicon.h>
#include <StringLoader.h>
#include <txtrich.h>
#include "BlackboxUtils.h"

// CONSTANS
const TInt KBlackboxQHDWidth = 360;
const TInt KBlackboxQHDHeight = 640;
const TInt KBlackboxVGAWidth = 480;
const TInt KBlackboxVGAHeight = 640;

const TBlackboxPromoMargins KBlackboxQHDMargins={7,7,0,0};
const TBlackboxPromoMargins KBlackboxVGAMargins={8,8,0,0};
const TBlackboxPromoMargins KBlackboxQVGAMargins={5,5,0,0};

const TBlackboxListBoxTweaks KBlackboxQHDListbox = {72,2,-1,0};
const TBlackboxListBoxTweaks KBlackboxVGAListbox = {93,2,-1,0};
const TBlackboxListBoxTweaks KBlackboxQVGAListbox = {64,2,-1,0};

_LIT( KBlackboxIcon, "z:\\resource\\apps\\blackbox.mif" );
_LIT( KLineBreakChar, "\n" );
_LIT( KTabChar, "\t"  );
_LIT( KBlackboxCheckboxLabelFormat, "%d\t%S\t" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// TBlackboxUtils::GetDisplayMode()
// -----------------------------------------------------------------------------
//
TInt TBlackboxUtils::GetDisplayMode()
    {
    TRect r;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, r );
    //Get screen layout
    if( (r.Height() == KBlackboxQHDHeight && r.Width() == KBlackboxQHDWidth)
            || (r.Height() == KBlackboxQHDWidth && r.Width() == KBlackboxQHDHeight) )
        { //QHD
        return EBlackboxDisplayModeQHD;
        }
    else if( (r.Height() == KBlackboxVGAHeight && r.Width() == KBlackboxVGAWidth)
            || (r.Height() == KBlackboxVGAWidth && r.Width() == KBlackboxVGAHeight) )
        { //VGA
        return EBlackboxDisplayModeVGA;
        }
    else
        return EBlackboxDisplayModeQVGA;
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::GetMargins()
// -----------------------------------------------------------------------------
//
TBlackboxPromoMargins TBlackboxUtils::GetMargins()
    {
    TBlackboxPromoMargins margins;
    switch( GetDisplayMode() )
        {
        case EBlackboxDisplayModeQHD: //QHD
            margins = KBlackboxQHDMargins;
            break;

        case EBlackboxDisplayModeVGA: //VGA
            margins = KBlackboxVGAMargins;
            break;

        case EBlackboxDisplayModeQVGA: //QVGA
        default:
            margins = KBlackboxQVGAMargins;
            break;
        }
    return margins;
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::GetListBoxTweaks()
// -----------------------------------------------------------------------------
//
TBlackboxListBoxTweaks TBlackboxUtils::GetListBoxTweaks()
    {
    TBlackboxListBoxTweaks listBoxTweaks;
    switch( GetDisplayMode() )
        {
        case EBlackboxDisplayModeQHD: //QHD
            listBoxTweaks = KBlackboxQHDListbox;
            break;

        case EBlackboxDisplayModeVGA: //VGA
            listBoxTweaks = KBlackboxVGAListbox;
            break;
            
        case EBlackboxDisplayModeQVGA: //QVGA
        default:
            listBoxTweaks = KBlackboxQVGAListbox;
            break;
        }
    return listBoxTweaks;
    }

// -----------------------------------------------------------------------------
// CBlackboxPluginContainer::CreateIconL()
// -----------------------------------------------------------------------------
//
CGulIcon* TBlackboxUtils::CreateIconL(TInt aBitmap, TInt aMask)
    {
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    // Default mask index
    if( aMask == 0 )
        aMask = aBitmap + 1;

    // Load icon bitmaps and scale it later
    AknIconUtils::CreateIconLC( bitmap, mask, KBlackboxIcon, aBitmap, aMask );

    // Create gul icon from the bitmaps
    CGulIcon* icon = CGulIcon::NewL( bitmap, mask );

    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );

    return icon;
    }

// -----------------------------------------------------------------------------
// CBlackboxPluginContainer::AddIconL()
// -----------------------------------------------------------------------------
//
void TBlackboxUtils::AddIconL(CArrayPtr<CGulIcon>& aIconList, TInt aBitmap,
        TInt aMask)
    {
    CGulIcon* icon = CreateIconL( aBitmap, aMask );
    CleanupStack::PushL( icon );
    aIconList.AppendL( icon );
    CleanupStack::Pop( icon );
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::AppendLoadTextL()
// -----------------------------------------------------------------------------
//
void TBlackboxUtils::AppendLoadTextL(HBufC* aText, TInt aResourceId)
    {
    HBufC* text = NULL;
    if( aResourceId )
        {
        text = StringLoader::LoadLC( aResourceId ); // load string from resource
        // Re-allocate memory, text is lengthened
        aText = aText->ReAllocL( aText->Length() + text->Length() );
        CleanupStack::Pop( text );
        // Append loaded text
        aText->Des().Append( *text );

        delete text;
        text = NULL;
        }
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::LoadCheckboxLabelLC()
// -----------------------------------------------------------------------------
//
HBufC* TBlackboxUtils::LoadCheckboxLabelLC(TInt aResourceId, TInt aIcon)
    {
    HBufC* caption = StringLoader::LoadLC( aResourceId );
    TBlackboxUtils::ReplaceLineBreakWithTab( caption );
    //HBufC* label = caption->ReAllocL( caption->Length() + 5 ); // Add extra chars
    HBufC* label = HBufC::NewL( caption->Length() + 5 ); // Add extra chars

    label->Des().Format( KBlackboxCheckboxLabelFormat, aIcon, caption );
    
    CleanupStack::PopAndDestroy( caption );
    CleanupStack::PushL( label );
    
    return label;
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::FixLineBreaks()
// -----------------------------------------------------------------------------
//
void TBlackboxUtils::FixLineBreaks(HBufC* aText)
    {
    TPtr text = aText->Des();
    ReplaceAll( text, KLineBreakChar, KBlackboxLineBreak );
    // Replease all carriage returns with unicode line breaks
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::ReplaceLineBreakWithTab()
// -----------------------------------------------------------------------------
//
void TBlackboxUtils::ReplaceLineBreakWithTab(HBufC* aText)
    {
    TPtr text = aText->Des();
    ReplaceAll( text, KLineBreakChar, KTabChar );
    }

// -----------------------------------------------------------------------------
// TBlackboxUtils::ReplaceAll()
// -----------------------------------------------------------------------------
//
void TBlackboxUtils::ReplaceAll(TDes& aText, const TDesC& aOld, const TDesC& aNew)
    {
    TInt pos = aText.Find( aOld );
    while (pos >= 0) // if found
        {
        aText.Replace( pos, 1, aNew ); // replace
        pos = aText.Find( aOld );
        }
    }

// End of file
