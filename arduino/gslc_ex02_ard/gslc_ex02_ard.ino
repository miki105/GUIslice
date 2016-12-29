//
// GUIslice Library Examples
// - Calvin Hass
// - http://www.impulseadventure.com/elec/microsdl-sdl-gui.html
// - Example 02 (Arduino):
//     Accept touch input, text button
//

#include "GUIslice.h"
#include "GUIslice_ex.h"
#include "GUIslice_drv.h"

// Defines for resources

// Enumerations for pages, elements, fonts, images
enum {E_PG_MAIN};
enum {E_ELEM_BOX,E_ELEM_BTN_QUIT};
enum {E_FONT_BTN};

bool    m_bQuit = false;

// Instantiate the GUI
#define MAX_FONT            1
gslc_tsGui                  m_gui;
gslc_tsDriver               m_drv;
gslc_tsFont                 m_asFont[MAX_FONT];

#define MAX_PAGE            1
#define MAX_ELEM_PG_MAIN    2
gslc_tsPage                 m_asPage[MAX_PAGE];
gslc_tsElem                 m_asPageElem[MAX_ELEM_PG_MAIN];


// Button callbacks
bool CbBtnQuit(void* pvGui,void *pvElem,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  if (eTouch == GSLC_TOUCH_UP_IN) {
    m_bQuit = true;
  }
  return true;
}
  
void setup()
{
  bool          bOk = true;
  gslc_tsElem*  pElem = NULL;

Serial.begin(9600);
Serial.println("GUIslice begin");
  // -----------------------------------
  // Initialize
  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { exit(1); }

  // Load Fonts
  bOk = gslc_FontAdd(&m_gui,E_FONT_BTN,"",1);
  //if (!bOk) { printf("ERROR: gslc_FontAdd() failed\n"); exit(1); }


  // -----------------------------------
  // Create page elements
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPageElem,MAX_ELEM_PG_MAIN);  
  
  // Background flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_GRAY_DK2);

  // Create background box
  pElem = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX,E_PG_MAIN,(gslc_tsRect){10,50,300,150});
  gslc_ElemSetCol(pElem,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create Quit button with text label
  static const char mstr1[] PROGMEM = "Quit";
  pElem = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_QUIT,E_PG_MAIN,
    (gslc_tsRect){120,100,80,40},(char*)&mstr1,strlen_P(mstr1),E_FONT_BTN,&CbBtnQuit);
  gslc_ElemSetTxtMem(pElem,GSLC_TXT_MEM_PROG);
  

  // -----------------------------------
  // Start display

  // Start up display on main page
  gslc_SetPageCur(&m_gui,E_PG_MAIN);

  // -----------------------------------
  // Main event loop

  m_bQuit = false;
  while (!m_bQuit) {
  
    // Periodically call GUIslice update function    
    gslc_Update(&m_gui);   

  } // bQuit


  // -----------------------------------
  // Close down display

  gslc_Quit(&m_gui);
}

void loop() { }


