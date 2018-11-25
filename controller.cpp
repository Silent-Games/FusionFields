#include "controller.h"

const int WIDGETITEMAT = 1;
const int HEADERDARKER = 150;

Controller::Controller( QWidget *parent ) : QWidget( parent )
{
  setupUi( this );
  QIcon appIcon( Config::getConfig()->APPICONIMAGEFILE );
  setWindowIcon( appIcon );

  header->setHidden( true );
  menuButton->setHidden( true );
  showMenu();

  connect( menuButton, SIGNAL( leftClicked() ), this, SLOT( showLeftClickedWidget() ) );
  connect( menuButton, SIGNAL( middleClicked() ), this, SLOT( showMiddleClickedWidget() ) );
  connect( menuButton, SIGNAL( rightClicked() ), this, SLOT( showRightClickedWidget() ) );
}

Controller::~Controller( void )
{
}

void Controller::showMenu( void )
{
  setWindowTitle( tr( "Menu" ) );
  menu = new Menu( this );
  delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), menu )->widget();
  menu->setObjectName( "Menu" );
  //MenuButton
  setMenuButton();
  //Header
  bool headerHiddenStateBefore = header->isHidden();
  header->setHidden( false );
  header->setHeader( tr( "FusionFields" ) );
  header->setCaption( "" );
  header->setBackgroundColor( DARKGRAY.darker( HEADERDARKER ) );
  if( headerHiddenStateBefore != header->isHidden() )
    header->animate();
  //BackgroundColor
  backgroundColor = DARKGRAY;
}

void Controller::showChallenges( int startChallengeNr )
{
  setWindowTitle( tr( "Challenges" ) );
  if( startChallengeNr >= 1 && startChallengeNr < Data::getData()->challenge.length() )
    this->startChallengeNr = startChallengeNr;
  challenges = new Challenges( this );
  delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), challenges )->widget();
  challenges->setObjectName( "Challenges" );
  //MenuButton
  setMenuButton();
  //Header
  bool headerHiddenStateBefore = header->isHidden();
  header->setHidden( false );
  header->setHeader( tr( "Challenges" ) );
  header->setCaption( QString::number( this->startChallengeNr ) + " - " + QString::number( Data::getData()->challenge.length() < this->startChallengeNr + 24 ? Data::getData()->challenge.length() : this->startChallengeNr + 24 ) );
  header->setBackgroundColor( CHALLENGECOLOR.darker( HEADERDARKER ) );
  if( headerHiddenStateBefore != header->isHidden() )
    header->animate();
  //BackgroundColor
  backgroundColor = CHALLENGECOLOR;
}

void Controller::showFusionFields( Challenge *challenge )
{
  if( !Data::getData()->lastTutorialFinished )
  {
    showTutorial( Data::getData()->tutorialLevel );
    return;
  }

  setWindowTitle( tr( "FusionFields" ) );
  if( challenge->getId() < 0 )
    challenge->setGameId( HIGHSCOREGAMEID );
  fusionFields = new FusionFields( challenge, this );
  delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), fusionFields )->widget();
  fusionFields->setObjectName( "FusionFields" );
  //MenuButton
  setMenuButton();
  //Header
  header->setHidden( true );
  //BackgroundColor
  backgroundColor = challenge->getId() >= 0 ? CHALLENGECOLOR : HIGHSCORECOLOR;
}

void Controller::showItems( void )
{
  setWindowTitle( tr( "Items" ) );
  items = new Items( Data::getData()->itemSlot, this );
  delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), items )->widget();
  items->setObjectName( "Items" );
  //MenuButton
  setMenuButton();
  //Header
  bool headerHiddenStateBefore = header->isHidden();
  header->setHidden( false );
  header->setHeader( tr( "Items" ) );
  header->setCaption( "" );
  header->setBackgroundColor( ITEMCOLOR.darker( HEADERDARKER ) );
  if( headerHiddenStateBefore != header->isHidden() )
    header->animate();
  //BackgroundColor
  backgroundColor = ITEMCOLOR;
}

void Controller::showItemSelection( int itemSlotNr )
{
  setWindowTitle( tr( "Item Selection" ) );
  this->itemSlotNr = itemSlotNr;
  itemSelection = new ItemSelection( Data::getData()->itemSlot[ itemSlotNr - 1 ], this );
  connect( itemSelection, SIGNAL( itemSelected( int ) ), this, SLOT( setItemSlot( int ) ) );
  delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), itemSelection )->widget();
  itemSelection->setObjectName( "ItemSelection" );
  //MenuButton
  setMenuButton();
  //Header
  bool headerHiddenStateBefore = header->isHidden();
  header->setHidden( false );
  header->setHeader( tr( "Item Selection" ) );
  header->setCaption( tr( "Slot " ) + QString::number( itemSlotNr ) );
  header->setBackgroundColor( ITEMCOLOR.darker( HEADERDARKER ) );
  if( headerHiddenStateBefore != header->isHidden() )
    header->animate();
  itemSelection->animate();
  //BackgroundColor
  backgroundColor = ITEMCOLOR;
}

void Controller::setItemSlot( int itemId )
{
  Data::getData()->itemSlot[ itemSlotNr - 1 ] = itemId;
  Data::getData()->setResetAllGame( true );
  saveData( SaveDataThread::Info );
}

void Controller::showAppInfo( void )
{
  setWindowTitle( tr( "App Info" ) );
  appInfo = new AppInfo();
  delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), appInfo )->widget();
  appInfo->setObjectName( "AppInfo" );
  //MenuButton
  setMenuButton();
  //Header
  bool headerHiddenStateBefore = header->isHidden();
  header->setHidden( false );
  header->setHeader( tr( "App Info" ) );
  header->setCaption( "" );
  header->setBackgroundColor( DARKGRAY.darker( HEADERDARKER ) );
  if( headerHiddenStateBefore != header->isHidden() )
    header->animate();
  //BackgroundColor
  backgroundColor = DARKGRAY;
}

void Controller::showTutorial( int level )
{
  setWindowTitle( tr( "Tutorial" ) );
  if( level == 2 )
  {
    tutorial = new Tutorial2();
    delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), tutorial )->widget();
    connect( tutorial, SIGNAL( tutorialFinished() ), this, SLOT( setTutorialFinished() ) );
    connect( tutorial, SIGNAL( tutorialFinished() ), this, SLOT( showItems() ) );
    tutorial->setObjectName( "Tutorial" );
  }
  else
  {
    tutorial1 = new Tutorial1();
    delete layout()->replaceWidget( layout()->itemAt( WIDGETITEMAT )->widget(), tutorial1 )->widget();
    connect( tutorial1, SIGNAL( tutorialFinished() ), this, SLOT( setTutorialFinished() ) );
    connect( tutorial1, SIGNAL( tutorialFinished() ), this, SLOT( showMenu() ) );
    tutorial1->setObjectName( "Tutorial" );
  }
  //MenuButton
  setMenuButton();
  //Header
  bool headerHiddenStateBefore = header->isHidden();
  header->setHidden( false );
  header->setHeader( tr( "Tutorial" ) );
  header->setCaption( "" );
  header->setBackgroundColor( DARKGRAY.darker( HEADERDARKER ) );
  if( headerHiddenStateBefore != header->isHidden() )
    header->animate();
  //BackgroundColor
  backgroundColor = DARKGRAY;
}

void Controller::setTutorialFinished()
{
  Data::getData()->lastTutorialFinished = true;
  saveData( SaveDataThread::Info );
}

void Controller::setMenuButton( void )
{
  bool menuButtonHiddenStateBefore = menuButton->isHidden();
  if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "FusionFields" ||
      layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "Menu" ||
      layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "Tutorial" )
  {
    menuButton->setHidden( true );
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "ItemSelection" )
  {
    menuButton->setHidden( false );
    menuButton->setLeftButtonText( tr( "Cancel" ) );
    menuButton->setLeftButtonImage( Config::getConfig()->CANCELIMAGE );
    menuButton->setMiddleButtonText( tr( "Menu" ) );
    menuButton->setMiddleButtonImage( Config::getConfig()->MENUIMAGE );
    menuButton->setRightButtonText( tr( "Check" ) );
    menuButton->setRightButtonImage( Config::getConfig()->CHECKIMAGE  );
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "Challenges" )
  {
    menuButton->setHidden( false );
    QImage img( Config::getConfig()->ARROWIMAGE );
    QTransform transform;
    transform.rotate( 270 );
    img = img.transformed( transform );
    menuButton->setLeftButtonText( tr( "Back" ) );
    menuButton->setLeftButtonImage( img );
    menuButton->setMiddleButtonText( tr( "Menu" ) );
    menuButton->setMiddleButtonImage( Config::getConfig()->MENUIMAGE );
    menuButton->setRightButtonText( tr( "Next" ) );
    transform.rotate( 270 );
    img = img.transformed( transform );
    menuButton->setRightButtonImage( img );
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "FusionFields" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "ItemSelection" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "Menu" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "Challenges" ||
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "AppInfo" )
  {
    menuButton->setHidden( false );
    menuButton->setLeftButtonText( tr( "Highscore" ) );
    menuButton->setLeftButtonImage( Config::getConfig()->HIGHSCOREIMAGE );
    menuButton->setMiddleButtonText( tr( "Menu" ) );
    menuButton->setMiddleButtonImage( Config::getConfig()->MENUIMAGE );
    menuButton->setRightButtonText( tr( "Challenges" ) );
    menuButton->setRightButtonImage( Config::getConfig()->CHALLENGEIMAGE );
  }
  if( menuButtonHiddenStateBefore != menuButton->isHidden() )
    menuButton->animate();
}

void Controller::showLeftClickedWidget( void )
{
  if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "Challenges" )
  {
    showChallenges( startChallengeNr - 20 );
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "ItemSelection" )
  {
    showItems();
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "FusionFields" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "ItemSelection" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "Challenges" ||
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "AppInfo" )
  {
    showFusionFields();
  }
}

void Controller::showMiddleClickedWidget( void )
{
  showMenu();
}

void Controller::showRightClickedWidget( void )
{
  if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "Challenges" )
  {
    showChallenges( startChallengeNr + 20 );
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "ItemSelection" )
  {
    setItemSlot( itemSelection->getSelectedItemId() );
    showItems();
  }
  else if( layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "FusionFields" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "ItemSelection" &&
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() != "Challenges" ||
           layout()->itemAt( WIDGETITEMAT )->widget()->objectName() == "AppInfo" )
  {
    showChallenges();
  }
}

void Controller::saveData( int whatSaving, int gameId, int challengeId )
{
  SaveDataThread *saveDataThread = new SaveDataThread;
  saveDataThread->setGameId( gameId );
  saveDataThread->setChallengeId( challengeId );
  saveDataThread->setWhatSaving( whatSaving );
  saveDataThread->start();
}

void Controller::paintEvent( QPaintEvent * )
{
  header->setFixedHeight( height() * 0.08 );
  menuButton->setFixedHeight( height() * 0.1 );

  QPainter painter( this );
  painter.setBrush( backgroundColor );
  this->setStyleSheet("background-color: rgb(" + QString::number(backgroundColor.red()) + ", " + QString::number(backgroundColor.green()) + ", " + QString::number(backgroundColor.blue()) + ");");
  painter.drawRect( QRectF( QPointF( 0, 0 ), QSizeF( width(), -height()) ) );
}
