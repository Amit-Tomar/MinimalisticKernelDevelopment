#include "displayDriver.h"
#include "utility.h"
#include "interruptServiceRoutine.h"
#include "interruptDescriptorTable.h"
#include "interruptRequests.h"
#include "timerHandler.h"
#include "keyBoardHandler.h"

int main()
{
  // All our initialisation calls will go in here.
  initializeGraphicsDriver();
  setTextColor ( eLightGrey ) ;
  putStringOnScreen("\n--------------------------------------------------------------------------------\n");
  setTextColor ( eGreen ) ;
  putStringOnScreen("\n                           IIITB Kernel Development Team    \n\n");
  putStringOnScreen("                                    Version 1.0                \n\n");
  setTextColor ( eDarkGrey ) ;
  putStringOnScreen("                                     Amit Tomar                  \n");
  putStringOnScreen("                                    Asutosh Vyas                  \n");
  putStringOnScreen("                                   Pankaj Agarwal                  \n");
  putStringOnScreen("                                 Rakesh Rajpurohit                  \n");
  setTextColor ( eLightGrey ) ;
  putStringOnScreen("\n--------------------------------------------------------------------------------");

  setTextColor ( eCyan ) ;
  putStringOnScreen("\nWelcome user!\n\n1. Press keys to check keyboard.\n\n2. Press 't' to start timer.\n\n3. Press 'e' to raise and exception\n\n(Note: Raising an exception haults the system.)\n\n");
  
  loadAndInitializeIDT();
  initialize_interruptServiceRoutine();
  initialize_interruptRequestService();  
  
  asm volatile("sti");
  
  return 0;
}
