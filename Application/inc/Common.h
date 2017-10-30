/* ====================================================================
 * File: Common.h
 * Created: 09/17/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef COMMON_H
#define COMMON_H

// INCLUDE FILES

// CONSTANTS
const TInt KFooterFontSize = 110;

// ---------------------------------------------------------------------------
// TRgb FontColor()
// ---------------------------------------------------------------------------
//
static TRgb FontColor()
    {
    TRgb textColor;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
            textColor, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6 );
    return textColor;
    }

// ---------------------------------------------------------------------------
// TRgb FontForFooter()
// ---------------------------------------------------------------------------
//
static CFont* FontForFooter()
    {

    TFontSpec myFontSpec;
    myFontSpec.iHeight = KFooterFontSize;
    CGraphicsDevice* screenDevice = CEikonEnv::Static()->ScreenDevice();
    
    CFont* font = NULL;
    screenDevice->GetNearestFontToMaxHeightInTwips(font, myFontSpec, KFooterFontSize);
    return font;
    }

// ---------------------------------------------------------------------------
// TRgb FormatLayerMainL()
// ---------------------------------------------------------------------------
//
static CCharFormatLayer* FormatLayerMainL()
    {
    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
    charFormat.iFontSpec = AknLayoutUtils::FontFromId(EAknLogicalFontSecondaryFont)->FontSpecInTwips();
    charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightNormal);

    charFormat.iFontPresentation.iTextColor = TLogicalRgb(FontColor());
    charFormatMask.SetAll();

    return CCharFormatLayer::NewL(charFormat, charFormatMask);
    }

// ---------------------------------------------------------------------------
// TRgb FormatLayerFooterL()
// ---------------------------------------------------------------------------
//
static CCharFormatLayer* FormatLayerFooterL( 
                        CFont*& aFont, TBool aUnderline = EFalse )
    {
    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
    aFont = FontForFooter();
    charFormat.iFontSpec = aFont->FontSpecInTwips();
    charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightNormal);    
    charFormat.iFontPresentation.iTextColor = TLogicalRgb( FontColor() );
    
    if (aUnderline)
        charFormat.iFontPresentation.iUnderline = EUnderlineOn;
    
    charFormatMask.SetAll();
    
    return CCharFormatLayer::NewL( charFormat,charFormatMask );
    }

#endif /* COMMON_H */

// End of file
