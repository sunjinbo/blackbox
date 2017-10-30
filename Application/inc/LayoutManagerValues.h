/* ====================================================================
 * File: LayoutManagerValues.h
 * Created: 09/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef LAYOUTMANAGERVALUES_H
#define LAYOUTMANAGERVALUES_H

// INCLUDE FILES
#include <avkon.hrh>

/////////////////////////////////////////////////////////////////////////////
//
// SUPPORTED UI RESOLUTIONS ARE:
//
// qHD RESOLUTION PORTRAIT     360x640 for Symbian^3
// qHD RESOLUTION LANDSCAPE    640x360 for Symbian^3
//
////////////////////////////////////////////////////////////////////////////

// Supported screen resolutions
enum TResolution
    {
    EQhdPortrait,
    EQhdLandscape,
    ENotSupported
    };

// Supported screen orientation
enum TOrientation
    {
    EAutomatic,
    EPortrait,
    ELandscape
    };

// Component enumerations
enum TComponent
    {
    EScreen,
    EButtonStart,
    EButtonOvi,
    EScenePane,
    EScorePane,
    EScoreGuessPane,
    EScoreRaysPane,
    EWelcIcon,
    EWelcGreetingText,
    EWelcQuery,
    EWelcQueryTitle,
    EWelcQueryMainPane,
    EWelcQueryHyperLink,
    EPromoBrand,
    EPromoLoading,
    EAvatarPane,
    EAvatar,
    EAvatarDialog,
    EAvatarDialogText
    };

/////////////////////////////////////////////////////////////////////////////
//
// BLACK-BOX COMPONENTS VALUES
//
//  * LAYOUT RECT
//  * TEXT FONT
//  * TEXT BASELINE
//
/////////////////////////////////////////////////////////////////////////////

// Screen
static const TInt KQhdLandscapeWidth = 640;
static const TInt KQhdLandscapeHeight = 360;

static const TInt KQhdPortraitWidth = 360;
static const TInt KQhdPortraitHeight = 640;

// Screen
static const TInt KQhdLscBgLeft = 0;
static const TInt KQhdLscBgTop = 0;
static const TInt KQhdLscBgRight = 640;
static const TInt KQhdLscBgBottom = 360;
static const TInt KQhdLscBgWidth = 640;
static const TInt KQhdLscBgHeight = 360;

static const TInt KQhdPrtBgLeft = 0;
static const TInt KQhdPrtBgTop = 0;
static const TInt KQhdPrtBgRight = 360;
static const TInt KQhdPrtBgBottom = 640;
static const TInt KQhdPrtBgWidth = 360;
static const TInt KQhdPrtBgHeight = 640;

// Button Start
static const TInt KQhdLscButtonStartLeft = 0;
static const TInt KQhdLscButtonStartTop = 0;
static const TInt KQhdLscButtonStartRight = 0;
static const TInt KQhdLscButtonStartBottom = 0;
static const TInt KQhdLscButtonStartWidth = 0;
static const TInt KQhdLscButtonStartHeight = 0;

static const TInt KQhdPrtButtonStartLeft = 10;
static const TInt KQhdPrtButtonStartTop = 300;
static const TInt KQhdPrtButtonStartRight = 350;
static const TInt KQhdPrtButtonStartBottom = 370;
static const TInt KQhdPrtButtonStartWidth = 340;
static const TInt KQhdPrtButtonStartHeight = 70;

// Button Ovi
static const TInt KQhdLscButtonOviLeft = 0;
static const TInt KQhdLscButtonOviTop = 0;
static const TInt KQhdLscButtonOviRight = 0;
static const TInt KQhdLscButtonOviBottom = 0;
static const TInt KQhdLscButtonOviWidth = 0;
static const TInt KQhdLscButtonOviHeight = 0;

static const TInt KQhdPrtButtonOviLeft = 10;
static const TInt KQhdPrtButtonOviTop = 390;
static const TInt KQhdPrtButtonOviRight = 350;
static const TInt KQhdPrtButtonOviBottom = 460;
static const TInt KQhdPrtButtonOviWidth = 340;
static const TInt KQhdPrtButtonOviHeight = 70;

// Scene Pane
static const TInt KQhdLscScenePaneLeft = 0;
static const TInt KQhdLscScenePaneTop = 0;
static const TInt KQhdLscScenePaneRight = 0;
static const TInt KQhdLscScenePaneBottom = 0;
static const TInt KQhdLscScenePaneWidth = 0;
static const TInt KQhdLscScenePaneHeight = 0;

static const TInt KQhdPrtScenePaneLeft = 0;
static const TInt KQhdPrtScenePaneTop = 0;
static const TInt KQhdPrtScenePaneRight = 360;
static const TInt KQhdPrtScenePaneBottom = 360;
static const TInt KQhdPrtScenePaneWidth = 360;
static const TInt KQhdPrtScenePaneHeight = 360;

// Score Pane
static const TInt KQhdLscScorePaneLeft = 0;
static const TInt KQhdLscScorePaneTop = 0;
static const TInt KQhdLscScorePaneRight = 0;
static const TInt KQhdLscScorePaneBottom = 0;
static const TInt KQhdLscScorePaneWidth = 0;
static const TInt KQhdLscScorePaneHeight = 0;

static const TInt KQhdPrtScorePaneLeft = 0;
static const TInt KQhdPrtScorePaneTop = 360;
static const TInt KQhdPrtScorePaneRight = 360;
static const TInt KQhdPrtScorePaneBottom = 430;
static const TInt KQhdPrtScorePaneWidth = 360;
static const TInt KQhdPrtScorePaneHeight = 70;

// Score Guess Pane
static const TInt KQhdLscScoreGuessPaneLeft = 0;
static const TInt KQhdLscScoreGuessPaneTop = 0;
static const TInt KQhdLscScoreGuessPaneRight = 0;
static const TInt KQhdLscScoreGuessPaneBottom = 0;
static const TInt KQhdLscScoreGuessPaneWidth = 0;
static const TInt KQhdLscScoreGuessPaneHeight = 0;

static const TInt KQhdPrtScoreGuessPaneLeft = 180;
static const TInt KQhdPrtScoreGuessPaneTop = 360;
static const TInt KQhdPrtScoreGuessPaneRight = 360;
static const TInt KQhdPrtScoreGuessPaneBottom = 390;
static const TInt KQhdPrtScoreGuessPaneWidth = 180;
static const TInt KQhdPrtScoreGuessPaneHeight = 30;

// Score Rays Pane
static const TInt KQhdLscScoreRaysPaneLeft = 0;
static const TInt KQhdLscScoreRaysPaneTop = 0;
static const TInt KQhdLscScoreRaysPaneRight = 0;
static const TInt KQhdLscScoreRaysPaneBottom = 0;
static const TInt KQhdLscScoreRaysPaneWidth = 0;
static const TInt KQhdLscScoreRaysPaneHeight = 0;

static const TInt KQhdPrtScoreRaysPaneLeft = 75;
static const TInt KQhdPrtScoreRaysPaneTop = 395;
static const TInt KQhdPrtScoreRaysPaneRight = 350;
static const TInt KQhdPrtScoreRaysPaneBottom = 425;
static const TInt KQhdPrtScoreRaysPaneWidth = 275;
static const TInt KQhdPrtScoreRaysPaneHeight = 30;

// Welcome icon
static const TInt KQhdLscWelcIconLeft = 325;
static const TInt KQhdLscWelcIconTop = 200;
static const TInt KQhdLscWelcIconRight = 635;
static const TInt KQhdLscWelcIconBottom = 260;
static const TInt KQhdLscWelcIconWidth = 360;
static const TInt KQhdLscWelcIconHeight = 360;

static const TInt KQhdPrtWelcIconLeft = 130;
static const TInt KQhdPrtWelcIconTop = 0;
static const TInt KQhdPrtWelcIconRight = 230;
static const TInt KQhdPrtWelcIconBottom = 100;
static const TInt KQhdPrtWelcIconWidth = 100;
static const TInt KQhdPrtWelcIconHeight = 100;

// Welcome greeting text
static const TInt KQhdLscWelcGreetingTextLeft = 325;
static const TInt KQhdLscWelcGreetingTextTop = 200;
static const TInt KQhdLscWelcGreetingTextRight = 635;
static const TInt KQhdLscWelcGreetingTextBottom = 260;
static const TInt KQhdLscWelcGreetingTextWidth = 360;
static const TInt KQhdLscWelcGreetingTextHeight = 360;

static const TInt KQhdPrtWelcGreetingTextLeft = 0;
static const TInt KQhdPrtWelcGreetingTextTop = 120;
static const TInt KQhdPrtWelcGreetingTextRight = 360;
static const TInt KQhdPrtWelcGreetingTextBottom = 320;
static const TInt KQhdPrtWelcGreetingTextWidth = 360;
static const TInt KQhdPrtWelcGreetingTextHeight = 200;

// Welcome query
static const TInt KQhdLscWelcQueryLeft = 0;
static const TInt KQhdLscWelcQueryTop = 0;
static const TInt KQhdLscWelcQueryRight = 0;
static const TInt KQhdLscWelcQueryBottom = 0;
static const TInt KQhdLscWelcQueryWidth = 0;
static const TInt KQhdLscWelcQueryHeight = 0;

static const TInt KQhdPrtWelcQueryLeft = 0;
static const TInt KQhdPrtWelcQueryTop = 280;
static const TInt KQhdPrtWelcQueryRight = 360;
static const TInt KQhdPrtWelcQueryBottom = 640;
static const TInt KQhdPrtWelcQueryWidth = 360;
static const TInt KQhdPrtWelcQueryHeight = 360;

// Welcome query title
static const TInt KQhdLscWelcQueryTitleLeft = 0;
static const TInt KQhdLscWelcQueryTitleTop = 0;
static const TInt KQhdLscWelcQueryTitleRight = 0;
static const TInt KQhdLscWelcQueryTitleBottom = 0;
static const TInt KQhdLscWelcQueryTitleWidth = 0;
static const TInt KQhdLscWelcQueryTitleHeight = 0;

static const TInt KQhdPrtWelcQueryTitleLeft = 19;
static const TInt KQhdPrtWelcQueryTitleTop = 23;
static const TInt KQhdPrtWelcQueryTitleRight = 316;
static const TInt KQhdPrtWelcQueryTitleBottom = 56;
static const TInt KQhdPrtWelcQueryTitleWidth = 297;
static const TInt KQhdPrtWelcQueryTitleHeight = 33;

// Welcome query main pane
static const TInt KQhdLscWelcQueryMainPaneLeft = 0;
static const TInt KQhdLscWelcQueryMainPaneTop = 0;
static const TInt KQhdLscWelcQueryMainPaneRight = 0;
static const TInt KQhdLscWelcQueryMainPaneBottom = 0;
static const TInt KQhdLscWelcQueryMainPaneWidth = 0;
static const TInt KQhdLscWelcQueryMainPaneHeight = 0;

static const TInt KQhdPrtWelcQueryMainPaneLeft = 19;
static const TInt KQhdPrtWelcQueryMainPaneTop = 60;
static const TInt KQhdPrtWelcQueryMainPaneRight = 316;
static const TInt KQhdPrtWelcQueryMainPaneBottom = 234;
static const TInt KQhdPrtWelcQueryMainPaneWidth = 297;
static const TInt KQhdPrtWelcQueryMainPaneHeight = 174;

// Welcome query hyperLink
static const TInt KQhdLscWelcQueryHyperLinkLeft = 0;
static const TInt KQhdLscWelcQueryHyperLinkTop = 0;
static const TInt KQhdLscWelcQueryHyperLinkRight = 0;
static const TInt KQhdLscWelcQueryHyperLinkBottom = 0;
static const TInt KQhdLscWelcQueryHyperLinkWidth = 0;
static const TInt KQhdLscWelcQueryHyperLinkHeight = 0;

static const TInt KQhdPrtWelcQueryHyperLinkLeft = 19;
static const TInt KQhdPrtWelcQueryHyperLinkTop = 234;
static const TInt KQhdPrtWelcQueryHyperLinkRight = 316;
static const TInt KQhdPrtWelcQueryHyperLinkBottom = 292;
static const TInt KQhdPrtWelcQueryHyperLinkWidth = 297;
static const TInt KQhdPrtWelcQueryHyperLinkHeight = 58;

// Promo brand
static const TInt KQhdLscPromoBrandLeft = 0;
static const TInt KQhdLscPromoBrandTop = 0;
static const TInt KQhdLscPromoBrandRight = 0;
static const TInt KQhdLscPromoBrandBottom = 0;
static const TInt KQhdLscPromoBrandWidth = 0;
static const TInt KQhdLscPromoBrandHeight = 0;

static const TInt KQhdPrtPromoBrandLeft = 90;
static const TInt KQhdPrtPromoBrandTop = 200;
static const TInt KQhdPrtPromoBrandRight = 270;
static const TInt KQhdPrtPromoBrandBottom = 320;
static const TInt KQhdPrtPromoBrandWidth = 180;
static const TInt KQhdPrtPromoBrandHeight = 120;

// Promo loading
static const TInt KQhdLscPromoLoadingLeft = 0;
static const TInt KQhdLscPromoLoadingTop = 0;
static const TInt KQhdLscPromoLoadingRight = 0;
static const TInt KQhdLscPromoLoadingBottom = 0;
static const TInt KQhdLscPromoLoadingWidth = 0;
static const TInt KQhdLscPromoLoadingHeight = 0;

static const TInt KQhdPrtPromoLoadingLeft = 132;
static const TInt KQhdPrtPromoLoadingTop = 560;
static const TInt KQhdPrtPromoLoadingRight = 228;
static const TInt KQhdPrtPromoLoadingBottom = 588;
static const TInt KQhdPrtPromoLoadingWidth = 96;
static const TInt KQhdPrtPromoLoadingHeight = 28;

// Avatar pane
static const TInt KQhdLscAvatarPaneLeft = 0;
static const TInt KQhdLscAvatarPaneTop = 0;
static const TInt KQhdLscAvatarPaneRight = 0;
static const TInt KQhdLscAvatarPaneBottom = 0;
static const TInt KQhdLscAvatarPaneWidth = 0;
static const TInt KQhdLscAvatarPaneHeight = 0;

static const TInt KQhdPrtAvatarPaneLeft = 0;
static const TInt KQhdPrtAvatarPaneTop = 360;
static const TInt KQhdPrtAvatarPaneRight = 360;
static const TInt KQhdPrtAvatarPaneBottom = 430;
static const TInt KQhdPrtAvatarPaneWidth = 360;
static const TInt KQhdPrtAvatarPaneHeight = 70;

// Avatar
static const TInt KQhdLscAvatarLeft = 0;
static const TInt KQhdLscAvatarTop = 0;
static const TInt KQhdLscAvatarRight = 0;
static const TInt KQhdLscAvatarBottom = 0;
static const TInt KQhdLscAvatarWidth = 0;
static const TInt KQhdLscAvatarHeight = 0;

static const TInt KQhdPrtAvatarLeft = 0;
static const TInt KQhdPrtAvatarTop = 360;
static const TInt KQhdPrtAvatarRight = 84;
static const TInt KQhdPrtAvatarBottom = 430;
static const TInt KQhdPrtAvatarWidth = 84;
static const TInt KQhdPrtAvatarHeight = 70;

// Avatar dialog
static const TInt KQhdLscAvatarDialogLeft = 0;
static const TInt KQhdLscAvatarDialogTop = 0;
static const TInt KQhdLscAvatarDialogRight = 0;
static const TInt KQhdLscAvatarDialogBottom = 0;
static const TInt KQhdLscAvatarDialogWidth = 0;
static const TInt KQhdLscAvatarDialogHeight = 0;

static const TInt KQhdPrtAvatarDialogLeft = 75;
static const TInt KQhdPrtAvatarDialogTop = 360;
static const TInt KQhdPrtAvatarDialogRight = 360;
static const TInt KQhdPrtAvatarDialogBottom = 430;
static const TInt KQhdPrtAvatarDialogWidth = 285;
static const TInt KQhdPrtAvatarDialogHeight = 70;

// Avatar dialog text
static const TInt KQhdLscAvatarDialogTextLeft = 0;
static const TInt KQhdLscAvatarDialogTextTop = 0;
static const TInt KQhdLscAvatarDialogTextRight = 0;
static const TInt KQhdLscAvatarDialogTextBottom = 0;
static const TInt KQhdLscAvatarDialogTextWidth = 0;
static const TInt KQhdLscAvatarDialogTextHeight = 0;

static const TInt KQhdPrtAvatarDialogTextLeft = 100;
static const TInt KQhdPrtAvatarDialogTextTop = 365;
static const TInt KQhdPrtAvatarDialogTextRight = 355;
static const TInt KQhdPrtAvatarDialogTextBottom = 425;
static const TInt KQhdPrtAvatarDialogTextWidth = 255;
static const TInt KQhdPrtAvatarDialogTextHeight = 60;

#endif // LAYOUTMANAGERVALUES_H

// End of File
