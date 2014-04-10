#include <ncurses.h>
#include <sstream>
#include <string>
#include "PayStationImpl.h"
#include "PayStationFactory.h"
#include "AlphaTownFactory.h"
#include "BetaTownFactory.h"
#include "GammaTownFactory.h"
#include "Receipt.h"

PayStationFactory setUpPayStation() {
  mvprintw(0,0,"***** Welcome to PayStation *****");
  mvprintw(2,0,"## Instructions - Press the [KEY] for the desired command ##");
  mvprintw(4,0,"[1] - Select Alpha Town (Linear Rate 	  / Standard Receipt / Standard Display)");
  mvprintw(5,0,"[2] - Select Beta Town  (Progressive Rate / Barcode Receipt  / Standard Display)");
  mvprintw(6,0,"[3] - Select Gamma Town (Alternating Rate / Standar Receipt  / Standard Display)");
  mvprintw(7,0,"[q] - To Quit");
  refresh();

  int ch = getch();

  while (ch != ERR) {
    if ('1' == ch) {
      return new AlphaTownFactory();
    }
    else if ('2' == ch) {
      return new BetaTownFactory();
    }
    else if ('3' == ch) {
      return new GammaTownFactory();
    }
    else if ('Q' == ch || 'q' == ch) {
      return NULL;
    }
   	
    ch = getchar();
  }
}

void displayInstructions() {
  mvprintw(4,0,"## Instructions - Press the [KEY] for the desired command ##");
  mvprintw(5,0, "[1] - Insert 5 cents");
  mvprintw(6,0, "[2] - Insert 10 cents");
  mvprintw(7,0, "[3] - Insert 25 cents");
  mvprintw(8,0, "[b] - Buy");
  mvprintw(9,0, "[c] - Cancel");
  mvprintw(10,0, "[q] - Quit Application");
}

void clearDisplay() {
  move(0, 0);
  clrtoeol();
  move(1, 0);
  clrtoeol();
  move(2, 0);
  clrtoeol();
  move(3, 0);
  clrtoeol();
}

void startPayStation(PayStationFactory psf) {
	clear();

  PayStationImpl* payStation = new PayStationImpl(psf);
  
  mvprintw(0,0, std::to_string(payStation->readDisplay()).c_str());
  displayInstructions();

  int ch = getch();

  while (ch != ERR && ch != 'Q' && ch != 'q') {

  	if ('1' == ch) { // add 5
  		payStation->addPayment(5);
  	}
  	else if ('2' == ch) { // add 10
  		payStation->addPayment(10);
  	}
  	else if ('3' == ch) { // add 25
  		payStation->addPayment(25);
  	}
  	else if ('b' == ch || 'B' == ch) { // buy
  		Receipt receipt = payStation->buy();
      std::stringstream ss;
  		receipt->print(ss);

      const std::string tmp = ss.str();
      const char* cstr = tmp.c_str();

      clear();
  		mvprintw(0,0, cstr);
      mvprintw(4,0,"## Instructions - Press the [KEY] for the desired command ##");
      mvprintw(5,0, "[1] - Take Receipt");
      mvprintw(6,0, "[q] - Quit Application");

      refresh();

      int ch2 = getch();
      while (ch2 != ERR && ch2 != 'Q' && ch2 != 'q' && ch2 != '1') {
        ch2 = getch();
      }

      delete receipt;
  	}
  	else if ('c' == ch || 'C' == ch) { // cancel
  		payStation->cancel();
      clearDisplay();
      mvprintw(0,0, std::to_string(payStation->readDisplay()).c_str());
  	}

    clearDisplay();
    mvprintw(0,0, std::to_string(payStation->readDisplay()).c_str());
    displayInstructions();
    refresh();
  	ch = getchar();
  }

  delete payStation;
  endwin();
}

int main() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  
  PayStationFactory payStationFactory = setUpPayStation();

  if (payStationFactory != NULL) {
    startPayStation(payStationFactory);
  }

  delete payStationFactory;

  return 0;	
}