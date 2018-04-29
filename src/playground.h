#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QObject>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QSignalMapper>        // map block signals
#include <QList>

#include "config.h"
#include "defs.h"
#include "guiblock.h"

class PlayGroundView;

class PlayGround: public QWidget
{
    Q_OBJECT
    public:

        PlayGround(QWidget* parent = 0);

	    PlayGroundView *getPlayGroundView() { return mview; }
        bool hasChoice() { return mchoice != -1; }

        void reinit();
        std::map<long,GuiBlockDescriptor> getBlockState();
        void setBlockState(std::map<long,GuiBlockDescriptor>);

        // slots and signals will have to be reworked
    public slots:
        /**
         * @brief   Slot for menu's signal, that choice was set/unset.
         * @param choice    New choice status.
         */
        void slotTypeChoice(long choice) { mchoice = choice; mwire = false; }
        void slotWireMode() { mchoice = -1; mwire = true; }    // wire choice

        /**
         * @brief   Slot for PlayGroundView's signal, left mouse press.
         */
        void slotViewLeftClick(QMouseEvent *event);

        /**
         * @brief   Slot for PlayGroundView's signal, right mouse press.
         */
        void slotViewRightClick(QMouseEvent *event);

        /**
         * @brief   Slot for Blocks's signal, mouse press.
         */
        void slotBlockClick(int);
        /**
         * @brief   Slot for Wire's signal, mouse press.
         */
        void slotForkWire(long, QPointF);

        void slotDeleteWire(long);
    signals:
        /**
         * @brief   Signal (to the menu), that choice is rejected.
         */
        void sigChoiceRejected();

        /**
         * @brief   Graphic's signal to the model, that block has been created.
         *          The generated id (in the model) is passed by key.
         * @param type      Type of created block.
         * @param key       Reference for passing a key (backwards).
         */
        void sigCreateBlock(long type, long& key);
        /**
         * @brief   Graphic's signal to the model, that block is deleted.
         * @param key       Key of deleted block.
         */
        void sigDeleteBlock(long key);
        /**
         * @brief   Graphic's signal to the model, that wire has been created.
         *          The generated id (in the model) is passed by key.
         * @param startkey  Start key (port id).
         * @param endkey    End key (port id)
         * @param key       Reference for passing a key (backwards).
         */
        void sigCreateWire(PortID startkey, PortID endkey, long& id, bool& success);
        /**
         * @brief   Graphic's signal to the model, that wire is deleted.
         * @param key       Key of deleted wire.
         */
        void sigDeleteWire(long key);

    private:
        long getIDFromBlock(std::shared_ptr<GuiBlock> block);
        bool createWireFunction();
        void deleteWireFunction(long i);

        long mchoice = -1; /**< Weather the block is being placed. */
        bool mwire = false;

        std::map<long, std::shared_ptr<GuiBlock>> mBlocks; /**< Placed blocks. */
        std::map<long, std::shared_ptr<MyWire>> mWires; /**< Placed wires. */

        QSignalMapper mmapper;

        QVBoxLayout *layout = nullptr;

        PlayGroundView *mview = nullptr;
        QGraphicsScene *mscene = nullptr;

        //QPointF drawLinePoint = QPointF();
        bool createWire = false;
        int connector1;
        int connector2;
        std::shared_ptr<GuiBlock> block1 = nullptr;
        std::shared_ptr<GuiBlock> block2 = nullptr;

};

// class for displaying playground and processing mouse interactions
class PlayGroundView: public QGraphicsView
{
    Q_OBJECT

    // borrowed constructor -> this class only overrides some methods and sends signals
    using QGraphicsView::QGraphicsView;

    public:

        //void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event/*, PlayGround *par*/);
        //void mouseReleaseEvent(QMouseEvent *event);
        //void paintEvent(QPaintEvent*);

    signals:
        /**
         * @brief   Signal to the PlayGround, left click.
         */
        void sigViewLeftClick(QMouseEvent *event);
        /**
         * @brief   Signal to the PlayGround, right click.
         */
        void sigViewRightClick(QMouseEvent *event);
};

#endif // PLAYGROUND_H
