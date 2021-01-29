// ******************************************************
// * NOMEN SEARCH
// * File:     nomensearch.js
// * Purpose:  smart checkboxes for the nomenclature
// *           search form
// * History:  Deborah Lee Soltesz dls 5/20/2002 Author
// *
// ******************************************************


  function turnOff (turnMeOff, turnOffName, turnOffValue) {
    if (document.getElementById) {
      (document.getElementById(turnMeOff)).checked = false ;
    }
    else {
      turnOffNameVal (turnOffName, turnOffValue) ;
    }
  }

  function turnOffNameVal (turnOffName, turnOffValue) {
    for (var i = 0 ; i < document.searchForm.elements.length ; i++) {
      if (document.searchForm.elements[i].name  == turnOffName &&
          document.searchForm.elements[i].value == turnOffValue) {
        document.searchForm.elements[i].checked = false ;
        return ;
      }
    }
  }


  function turnOffFields () {

    turnOff("fname", "show", "Fname") ;
    turnOff("flat", "show", "Lat") ;
    turnOff("flong", "show", "Long") ;
    turnOff("fdiam", "show", "Diam") ;

    turnOff("fcont", "show", "Cont") ;
    turnOff("fenth", "show", "Enth") ;
    turnOff("fquad", "show", "Quad") ;
    turnOff("fmap", "show", "Map") ;

    turnOff("fstat", "show", "Stat") ;
    turnOff("fyear", "show", "Year") ;
    turnOff("fref", "show", "Ref") ;
    turnOff("forig", "show", "Orig");   
  }

  function turnOffColumnShow () {

    turnOff("sys", "showcol", "Sys") ;
    turnOff("body", "showcol", "Body") ;
    turnOff("flat", "showcol", "Lat") ;
    turnOff("flong", "showcol", "Long") ;
    turnOff("fdiam", "showcol", "Diam") ;

    turnOff("fcont", "showcol", "Cont") ;
    turnOff("fenth", "showcol", "Enth") ;
    turnOff("fquad", "showcol", "Quad") ;
    turnOff("fmap", "showcol", "Map") ;
    turnOff("fstat", "showcol", "Stat") ;

    turnOff("fyear", "showcol", "Year") ;
    turnOff("fref",  "showcol", "Ref") ;
    turnOff("ftype",  "showcol", "Ftype") ;
    turnOff("forig", "showcol", "Orig");   
  }


