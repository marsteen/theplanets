
  // SCRIPT:   Utility Functions
  // Filename: utility.js
  // Purpose:  miscellaneous little handy JavaScript fuctions
  //
  // Author:   Deborah Lee Soltesz, USGS, 11/2001


  // browser checks
  ns4    = (document.layers) ? true:false ;
  ns6    = (document.getElementById) ? true:false ;
  isNav  = (navigator.appName.indexOf("Netscape")  != -1)
  isMSIE = (navigator.appName.indexOf("Microsoft") != -1)


  // *****************************************************************

  // POP UP WINDOW
  // Open an image (or other file) in new window sized to width-height.
  // If window exists, close and open with new size attributes.
  // NO decor (toolbars, menus, scrollbars, etc.) and NOT resizable.

  function popUpWindow (url, width, height) {
    if (window["POP"] && window["POP"].closed == false) {
      POP = window["POP"] ;
      if (ns4) {
        POP.close() ;
      }
      else {
        POP.resizeTo (width + 30, height + 50) ;
      }
    }
    POP = open(url,"POP","toolbar=0,location=0,status=0,menubar=0,scrollbars=0,resizable=1,width=" + (width + 20) + ",height=" + (height + 20));
    POP.focus() ;
  }

  function popUpWindowScrolling (url, width, height) {
    if (window["POPs"] && window["POPs"].closed == false) {
      POPs = window["POPs"] ;
      if (ns4) {
        POP.close() ;
      }
      else {
        POPs.resizeTo (width + 30, height + 50) ;
      }
    }
    POPs = open(url,"POPs","toolbar=0,location=0,status=0,menubar=0,scrollbars=1,resizable=1,width=" + (width + 20) + ",height=" + (height + 20));
    POPs.focus() ;
  }

  // CLEAN UP POP UP WINDOW
  function cleanUpPopUpWindow () {
    if (window["POP"] && window["POP"].closed == false) {
      POP = window["POP"] ;
      POP.close() ;
    }
  }


  function writeLastModified () {
    document.write("This document was last modified " + document.lastModified) ;
  }
