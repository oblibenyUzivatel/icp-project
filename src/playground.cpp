// playground.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>
#include <string>

#include <QMouseEvent>
#include <QPainter>

#include "debug.h"
#include "playground.h"

// prehodit mosepressevent do sceny -> oprava view
// guiblock subclasses podle poctu vstupu a vystupu
template<class T>
void printNOISOMap(T a)
{
    for(auto i:a)
    {
        std::cout << "map: " << i.first << " " << i.second << std::endl;
    }
}

PlayGround::PlayGround(QWidget* parent): QWidget(parent)
{
  mscene = new QGraphicsScene(this);
  mview = new PlayGroundView(this);
  mview->setScene(mscene);
  mscene->setBackgroundBrush(QColor(220,220,220));

  mview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // (0;0) coordinates are in the top left corner (hopefully)
  // scene is 3000*3000 pixels big. Hopefully it is enough.
  mscene->setSceneRect(0, 0, 3000, 3000);
  mview->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(mview);


  // connects mapper to playground: block -> playground communication
  QObject::connect(&mmapper, SIGNAL(mapped(int)),
                   this, SLOT(slotBlockClick(int)));
}

void PlayGround::reinit()
{
    for(auto& it: mBlocks) { mscene->removeItem(it.second.get()); }
    for(auto& it: mWires) {
        for(auto& i: it.second->getLine()) { mscene->removeItem(i.get()); }
        mscene->removeItem(it.second->getText());
    }
    for(auto& it: mInputs) { mscene->removeItem(it.second.get()); }
    mBlocks.clear();
    mWires.clear();
    mInputs.clear();

    annulateChoice();
}

void PlayGround::setWireValue(long id, Value v)
{
    std::shared_ptr<MyWire> wire = mWires[id];

    wire.get()->setValue(v);
/*
    std::string str = std::to_string(newValue);
    wire.get()->getText()->setPlainText(QString::fromStdString(std::to_string(newValue)));
*/
}
void PlayGround::setBlockValue(long id, Value v)
{
    if(mInputs.count(id) > 0) { return; }   // model cannot change value of input

    std::shared_ptr<GuiBlock> block = mBlocks[id];
    block.get()->setValue(v);
/*
    std::string str = std::to_string(newValue);
    wire.get()->getText()->setPlainText(QString::fromStdString(std::to_string(newValue)));
*/
}
void PlayGround::setWireColor(long id, bool active)
{
    std::shared_ptr<MyWire> wire = mWires[id];

    wire.get()->setColor(active);
}
void PlayGround::setBlockColor(long id, bool active)
{
    if(mInputs.count(id) > 0) { return; }   // model cannot change color of input ??

    std::shared_ptr<GuiBlock> block = mBlocks[id];
    block.get()->setColor(active);
}
void PlayGround::setAllDefaultColor()
{
    for(auto const& x: mWires)
    {
        x.second.get()->setColor(false);
    }
    for(auto x: mBlocks)
    {
        x.second.get()->setColor(false);
    }
}

void PlayGround::slotViewLeftClick(QMouseEvent *event)
{
    //std::cout << event->x() << " PG " << event->y() << std::endl;

    // umisteni dratu - K CEMU TO JE DOBRE??? Draty tvorim klikem na blok, ne na playground
    if(mwire)
    {

    }
    // umisteni vstupu
    else if(minput)
    {
        std::shared_ptr<GuiInput> newInput = std::make_shared<GuiInput>(event->pos());
        if(!newInput->isOk()) return;
        mscene->addItem(newInput.get());

        // collisions
        QList<QGraphicsItem *> tempList;
        tempList = newInput->collidingItems();
        if(tempList.empty() != true)
        {
            mscene->removeItem(newInput.get());
            return;
        }

        long id;
        emit sigCreateInput(newInput->getValue(), id);

        Debug::Gui("Create block "+std::to_string(id));

        mmapper.setMapping(newInput.get(), id);
        QObject::connect(newInput.get(), SIGNAL(sigBlockClick()),
                         &mmapper, SLOT(map()));

        mInputs.insert( std::make_pair(id,newInput) );

    }
    // umisteni krabicky
    else if(mchoice >= 0)
    {
        // create guiblock
        std::shared_ptr<GuiBlock> newBlock = std::make_shared<GuiBlock>(event->pos(), mchoice);
        mscene->addItem(newBlock.get());

        // collisions
        QList<QGraphicsItem *> tempList;
        tempList = newBlock->collidingItems();
        if(tempList.empty() != true)
        {
            mscene->removeItem(newBlock.get());
            return;
        }

        // poslat zadost o id modelu
        long id; /**< Tady budes mit to id z modelu */
        emit sigCreateBlock(mchoice, id);

        Debug::Gui("Create block "+std::to_string(id));

        // map signals
        mmapper.setMapping(newBlock.get(), id);
        QObject::connect(newBlock.get(), SIGNAL(sigBlockClick()),
                         &mmapper, SLOT(map()));

        //rect = mscene->addRect(newBlock);
        //rect->setFlag(QGraphicsItem::ItemIsMovable);

        // a ulozis si to sem:
        mBlocks.insert( std::make_pair(id,newBlock) );
    }
    //std::cout << "PG: Accepted signal left click\n";
}
void PlayGround::slotViewRightClick(QMouseEvent *event)
{
    (void *)event;

    // for testing a loop detection
    //long id;
    //emit sigCreateWire({0,-1}, {1,0}, id);
    //emit sigCreateWire({1,-1}, {0,0}, id);

    //std::cout << "PG: Accepted signal right click\n";
}

long PlayGround::getIDFromBlock(std::shared_ptr<GuiBlock> block)
{
    for(auto i: mBlocks) { if(i.second == block) return i.first; }
    return -1;
}
long PlayGround::getIDFromInput(std::shared_ptr<GuiInput> block)
{
    for(auto i: mInputs) { if(i.second == block) return i.first; }
    return -1;
}

bool PlayGround::createWireFunction()
{
    // wire request
    long id;
    bool success = true;
    long begin;
    if(block1 == nullptr) begin = getIDFromInput(iblock1);
    else begin = getIDFromBlock(block1);
    long end;
    if(block2 == nullptr) end = getIDFromInput(iblock2);
    else end = getIDFromBlock(block2);
    Debug::Gui("Create wire: "+std::to_string(begin)+"<->"+std::to_string(end));
    emit sigCreateWire({/*getIDFromBlock(block1)*/begin,connector1}, {/*getIDFromBlock(block2)*/end,connector2}, id, success);
    if(!success) return false;

    // put wire into map
    QPointF point1;
    if(block1 == nullptr) point1 = iblock1->getConnectorPoint(connector1);
    else point1 = block1->getConnectorPoint(connector1);
    QPointF point2;
    if(block2 == nullptr) point2 = iblock2->getConnectorPoint(connector2);
    else point2 = block2->getConnectorPoint(connector2);
    std::shared_ptr<MyWire> newWire;
    if(block1 != nullptr && block2 != nullptr) newWire = std::make_shared<MyWire>(id,point1, point2, block1, block2, connector1, connector2);
    else if(block1 == nullptr) newWire = std::make_shared<MyWire>(id,point1, point2, iblock1, block2, connector1, connector2);
    else newWire = std::make_shared<MyWire>(id,point1, point2, block1, iblock2, connector1, connector2);
    mWires.insert( std::make_pair(id,newWire) );
    // draw wire
    for(auto& it: newWire->getLine()) { mscene->addItem(it.get()); }
    mscene->addItem(newWire->getText());

    QObject::connect(newWire.get(), SIGNAL(sigForkWire(long, QPointF)),
                     this, SLOT(slotForkWire(long, QPointF)));
    QObject::connect(newWire.get(), SIGNAL(sigDeleteWire(long)),
                     this, SLOT(slotDeleteWire(long)));

    return true;
}

void PlayGround::deleteWireFunction(long i)
{

    Debug::Gui( "PlayGround::deleteWireFunction("+std::to_string(i)+")" );
    emit sigDeleteWire(i);
    std::shared_ptr<MyWire> wire = mWires.at(i);

    if(wire->getBlock1() == nullptr) wire->getIBlock1()->setConnectorAvailability(wire->getConnector1(), 0);
    else wire->getBlock1()->setConnectorAvailability(wire->getConnector1(), 0);
    if(wire->getBlock2() == nullptr) wire->getIBlock2()->setConnectorAvailability(wire->getConnector2(), 0);
    else wire->getBlock2()->setConnectorAvailability(wire->getConnector2(), 0);

    for(auto& it: wire->getLine()) { mscene->removeItem(it.get()); }
    mscene->removeItem(wire->getText());
    mWires.erase(i);

}

void PlayGround::slotDeleteWire(long id)
{
    Debug::Events("Deleting wire "+std::to_string(id));
    deleteWireFunction(id);
}

void PlayGround::slotForkWire(long id, QPointF)
{
    Debug::Events("Forking wire "+std::to_string(id));
}


// ---------------------------------- INPUT BLOCK ------------------------------


void PlayGround::inputClick(int i)
{
    Debug::Events("PlayGround::inputClick "+std::to_string(i));
    if(mInputs.at(i)->getMouseEvent()->button() == Qt::RightButton)
    {
        emit sigDeleteBlock(i);
        mscene->removeItem(mInputs.at(i).get());
        mInputs.erase(i);
    }
    else if(mInputs.at(i)->getMouseEvent()->button() == Qt::LeftButton)
    {
        //QGraphicsSceneMouseEvent * event;
        auto block = mInputs.at(i);
        //event = block->getMouseEvent();

        if(mwire)
        {
            bool wireFree;
            int connector;

            block->getPointFromBlock(&connector, &wireFree);
            if(iblock1.get() == nullptr && block1.get() == nullptr)
            {
                iblock1 = block;
                connector1 = connector;
                createWire = createWire || wireFree;
            }
            else        // cannot connect two inputs
            {
                iblock2 = block;
                connector2 = connector;
                createWire = createWire && wireFree;
                // wire cannot connect 2 input blocks
                if(createWire && (iblock1 == nullptr || iblock2 == nullptr))
                {
                    if(createWireFunction())
                    {
                        if(block1 == nullptr) iblock1->setConnectorAvailability(connector1, true);
                        else block1->setConnectorAvailability(connector1, true);
                        if(block2 == nullptr) iblock2->setConnectorAvailability(connector2, true);
                        else block2->setConnectorAvailability(connector2, true);
                    }
                }
                iblock1 = nullptr;
                block1 = nullptr;
                iblock2 = nullptr;
                block2 = nullptr;
                createWire = false;
                //printNOISOMap(mWires);
            }
        }
    }
}

void PlayGround::slotBlockClick(int i)
{
    QGraphicsSceneMouseEvent * event;
    if(mInputs.count(i) > 0) { inputClick(i); return; }
    auto block = mBlocks.at(i);
    event = block->getMouseEvent();

    if(event->button() == Qt::LeftButton)
    {
        Debug::Events("PlayGround: Left click from block "+std::to_string(i));

        // wire selected ...
        if(mwire)
        {
            bool wireFree;
            int connector;

            block->getPointFromBlock(&connector, &wireFree);
            if(block1.get() == nullptr && iblock1.get() == nullptr)
            {
                block1 = block;
                connector1 = connector;
                createWire = createWire || wireFree;
            }
            else
            {
                block2 = block;
                connector2 = connector;
                createWire = createWire && wireFree;
                // wire cannot connect 2 input blocks
                if(createWire && (iblock1 == nullptr || iblock2 == nullptr))
                {
                    if(createWireFunction())
                    {
                        if(iblock1 != nullptr) iblock1->setConnectorAvailability(connector1, true);
                        else block1->setConnectorAvailability(connector1, true);
                        if(iblock2 != nullptr) iblock2->setConnectorAvailability(connector2, true);
                        else block2->setConnectorAvailability(connector2, true);
                    }
                }
                iblock1 = nullptr;
                block1 = nullptr;
                iblock2 = nullptr;
                block2 = nullptr;
                createWire = false;
                //printNOISOMap(mWires);
            }
        }
    }
    else if(event->button() == Qt::RightButton) // delete block
    {
        Debug::Events("PlayGround: Right click, deleting block "+std::to_string(i));
        emit sigDeleteBlock(i);     // mapper mi neumoznuje posilat long, jen int
        mscene->removeItem(block.get());
        mBlocks.erase(i);
    }
}


void PlayGroundView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        Debug::Events("PlayGroundView: left click");
        emit sigViewLeftClick(event);
    }
    else if(event->button() == Qt::RightButton)
    {
        Debug::Events("PlayGroundView: right click");
        emit sigViewRightClick(event);
    }

    QGraphicsView::mousePressEvent(event);

}

std::map<long,GuiBlockDescriptor> PlayGround::getBlockState()
{
    std::map<long,GuiBlockDescriptor> m;
    for(auto& it: mBlocks)
    {
        GuiBlockDescriptor d;
        d.type = it.second->getType();
        d.pos.first = it.second->x();
        d.pos.second = it.second->y();
        m.insert( std::make_pair(it.first,d) );
    }
    return m;
}

void PlayGround::setBlockState(std::map<long,GuiBlockDescriptor> m)
{
    for(auto& it: m)
    {
        QPointF pos(it.second.pos.first, it.second.pos.second);
        long id = it.first;
        long type = it.second.type;

        std::shared_ptr<GuiBlock> newBlock = std::make_shared<GuiBlock>(pos, type);
        mscene->addItem(newBlock.get());

        mmapper.setMapping(newBlock.get(), id);
        QObject::connect(newBlock.get(), SIGNAL(sigBlockClick()),
                         &mmapper, SLOT(map()));

        mBlocks.insert( std::make_pair(id,newBlock) );
    }
}
