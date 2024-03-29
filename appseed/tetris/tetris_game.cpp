﻿#include "framework.h"


#define  DRAW 1
#define  UNDRAW 0

#define  TOTALPOSITIONS 4
#define  TOTALSHIFTS 8
#define  TOTALFLASHES 15

#define  SCOREPERROW 100.0
#define  ADDPERROW 0.17
#define  ROWSPERLEVEL 20.0
#define  ADDROWSPERLEVEL 0.25
#define  DROPADDUNIT 0.2

#define  ROWTYPE 1
#define  DROPUNITTYPE 2

#define  DELAYPERLEVEL .85



namespace tetris
{


   game::Thread::Thread(::aura::application * papp) :
      ::object(papp),
      thread(papp)
   {
   }


   void game::Thread::run()
   {

      m_ptetris->run();


   }



   game::game(::aura::application * papp, int widthInCells_,
              int heightInCells_,
              int cellSizeInPixels_,
              ::tetris::view * pview) :
      ::object(papp),
      _TetrisInterface(papp),
      ::estamira::game(papp),
      m_pparent(pview)
   {

      m_uiCursorDelay = 200;
      //cells = null;
      //offCells = null;

      //colors = new Color[9];

      //colors[0] = Color.black;
      //colors[1] = Color.yellow;
      //colors[2] = Color.cyan;
      //colors[3] = Color.blue;
      //colors[4] = Color.green;
      //colors[5] = Color.lightGray;
      //colors[6] = Color.magenta;
      //colors[7] = Color.orange;
      //colors[8] = Color.white;

      //setBackground(colors[0]);

      init(widthInCells_, heightInCells_, cellSizeInPixels_);

      atGame = true;
      canMove = true;
      atPause = false;
      isDropping = false;
      isMoving = false;

   }

   void game::init(int widthInCells_,
                   int heightInCells_,
                   int cellSizeInPixels_)
   {
      atGame = false;
      canMove = false;

      widthInCells = widthInCells_;
      heightInCells = heightInCells_;
      cellSizeInPixels = cellSizeInPixels_;

      widthInPixels = widthInCells * cellSizeInPixels + 1;
      heightInPixels = heightInCells * cellSizeInPixels + 1;
      score = 0;
      level = 0;
      thisLevelFlashes = 0;
      atGame = false;
      delay = 500;

      cells.set_size(heightInCells);
      cellsOverride.set_size(heightInCells);
      offCells.set_size(heightInCells);

      for (index i = 0; i < heightInCells; i++)
      {
         cells[i].set_size(widthInCells);
         cellsOverride[i].set_size(heightInCells);
         offCells[i].set_size(widthInCells);
      }

      for (index i = 0; i < heightInCells; i++)
      {
         for (index j = 0; j < widthInCells; j++)
         {
            cellsOverride[i][j] = -1;
         }
      }

      m_sizePage.cx = widthInPixels;
      m_sizePage.cy = heightInPixels;


   }

   bool game::get_char_rect(LPRECT lprect, index iChar, bool bPlatformCall)
   {

      int testX, testY, shiftX, shiftY;
      string strShift = blocks[curType][curRotation];
      int i = 0;

      testX = curX;
      testY = curY;

      bool bFirst = true;

      rect rUnion;

      while (true)
      {
         rect r;
         r.left = testX * cellSizeInPixels;
         r.top = testY * cellSizeInPixels;
         r.right = r.left + cellSizeInPixels;
         r.bottom = r.top + cellSizeInPixels;

         if (bFirst)
         {
            rUnion = r;
            bFirst = false;
         }
         else
         {
            rUnion.unite(rUnion, r);

         }

         if (i >= strShift.length())
            break;

         shiftX = shiftsPositions[strShift[i] - '0'][0];
         shiftY = shiftsPositions[strShift[i] - '0'][1];
         testX += shiftX;
         testY += shiftY;
         i++;
      }

      *lprect = rUnion;

      return true;

   }

   int game::hit_test(point pt)
   {

      int testX, testY, shiftX, shiftY;
      string strShift = blocks[curType][curRotation];
      int i = 0;

      testX = curX;
      testY = curY;

      while (true)
      {

         rect r;
         r.left = testX * cellSizeInPixels;
         r.top = testY * cellSizeInPixels;
         r.right = r.left + cellSizeInPixels;
         r.bottom = r.top + cellSizeInPixels;

         if (r.contains(pt))
         {

            return 0;

         }

         if (i >= strShift.length())
            break;

         shiftX = shiftsPositions[strShift[i] - '0'][0];
         shiftY = shiftsPositions[strShift[i] - '0'][1];
         testX += shiftX;
         testY += shiftY;
         i++;
      }


      return -1;

   }

   void game::initPaint()
   {


      //if(m_dib->area() <= 0)
      //{
      //   int i;
      //   int j;

      //   m_dib->create(widthInPixels,heightInPixels);

      //   if(m_dib->area() <= 0)
      //   {
      //      TRACE("imagem nula\n");
      //   }
      //   else
      //   {
      //      TRACE("recriando imagem\n");
      //   }


      //   m_dib->get_graphics()->FillSolidRect(0,0,widthInPixels,heightInPixels,colors[0]);

      //   ::draw2d::pen_sp pen(allocer());

      //   pen->create_solid(1.0,ARGB(255,128,128,128));

      //   m_dib->get_graphics()->SelectObject(pen);

      //   for(i = 0; i <= widthInCells; i++)
      //   {
      //      m_dib->get_graphics()->DrawLine(i * cellSizeInPixels,0,i * cellSizeInPixels,heightInPixels - 1);
      //   }

      //   for(i = 0; i <= heightInCells; i++)
      //   {
      //      m_dib->get_graphics()->DrawLine(0,i * cellSizeInPixels,widthInPixels - 1,i * cellSizeInPixels);
      //   }
      //   for(i = 0; i < heightInCells; i++)
      //      for(j = 0; j < widthInCells; j++)
      //      {
      //         offCells[i][j] = cells[i][j];
      //         m_dib->get_graphics()->FillSolidRect((j * cellSizeInPixels) + 2,(i * cellSizeInPixels) + 2,
      //            cellSizeInPixels - 3,cellSizeInPixels - 3,colors[cells[i][j]]);
      //      }
      //   atGame = true;
      //   canMove = true;
      //}

   }



   void game::Score(int type, int arg)
   {


      double actual;

      switch (type)
      {
      case ROWTYPE:
         score += SCOREPERROW / TOTALFLASHES;
         actual = SCOREPERROW / TOTALFLASHES;
         while (arg > 0)
         {
            actual = actual * ADDPERROW;
            arg--;
         }
         score += actual;
         thisLevelFlashes++;
         break;
      case DROPUNITTYPE:
         score += DROPADDUNIT;
         break;
      }


      arg = level;
      actual = ROWSPERLEVEL * TOTALFLASHES;
      while (arg > 0)
      {
         actual += actual * ADDROWSPERLEVEL;
         arg--;
      }

      if (thisLevelFlashes > actual)
      {
         thisLevelFlashes = 0;
         level++;
         delay *= DELAYPERLEVEL;
      }


      m_pparent->m_strScore = ::str::from((int64_t)score);
      m_pparent->m_strLevel = ::str::from(level);


   }

   ::size game::preferredSize()
   {
      return ::size(widthInPixels, heightInPixels);
   }


   void game::run()
   {
      //      int i;
      aux++;
      while (atGame && ::get_thread_run())
      {
         Sleep(delay + 1);

         if (!atPause && atGame && !isMoving && !isDropping && !isKilling)
         {
            moveDown();
         }

      }

   }


   bool game::start(::user::impact * pview)
   {

      if (!estamira::game::start(pview))
         return false;

      int coordX, coordY;

      score = 0;
      level = 0;
      thisLevelFlashes = 0;
      atGame = false;
      delay = 500;

      if (m_pthread != NULL)
      {
         Sleep(delay);
      }

      //try { Thread.sleep(delay); }
      //catch(InterruptedException e){}

      if (atPause) atPause = false;


      if (m_pthread != NULL)
      {
         // thread.stop();
         m_pthread = NULL;
      }

      //if(image != null)
      //{
      // image = null;
      //}

      //if(imageGraph != null)
      //{
      // imageGraph.dispose();
      //imageGraph = null;
      //}


      for (coordX = 0; coordX < widthInCells; coordX++)
         for (coordY = 0; coordY < heightInCells; coordY++)
            drawCell(coordX, coordY, 0);
      isMoving = false;
      startBlock();

      m_pthread = new Thread(get_app());
      m_pthread->m_ptetris = this;
      atGame = true;
      m_pthread->begin();

      return true;
   }


   void game::startBlock()
   {
      curX = widthInCells / 2;
      curY = -2;
      m_pparent->m_ppreview->pickTypeAndRotation(&curType, &curRotation);
      //         parent.preview.redraw();

      //         System.gc();

      if (!canMoveDown(0))
      {
         atGame = false;
      }
      else
      {
         drawBlock(DRAW);
         canMove = true;
         refresh = true;
      }
   }









   void game::moveDown()
   {
      if (isMoving) return;
      isMoving = true;
      drawBlock(UNDRAW);
      if (canMoveDown(0))
      {
         curY++;
         drawBlock(DRAW);
         //paint();
      }
      else
      {
         canMove = false;
         drawBlock(DRAW);
         //            paint();
         killRows();

         if (delay < 0)
         {

            delay = 1;

         }

         startBlock();

      }

      isMoving = false;

   }


   void game::moveLeft(index iChar)
   {
      if (isMoving) return;
      isMoving = true;
      if (atPause) atPause = false;

      //thread.resume();
      {
         drawBlock(UNDRAW);
         if (canMoveLeft(0))
         {
            curX--;
            drawBlock(DRAW);

         }
         else
         {
            drawBlock(DRAW);
         }
      }
      //paint();

      isMoving = false;

   }



   void game::moveRight(index iChar)
   {

      if (isMoving) return;
      isMoving = true;
      if (atPause) atPause = false;

      //         thread.resume();
      {
         drawBlock(UNDRAW);
         if (canMoveRight(0))
         {
            curX++;
            drawBlock(DRAW);
         }
         else
         {
            drawBlock(DRAW);
         }
      }
      //paint();
      isMoving = false;
   }


   void game::rotate(bool ClockWising)
   {
      if (isMoving) return;
      isMoving = true;
      if (atPause) atPause = false;

      //         thread.resume();
      {
         drawBlock(UNDRAW);
         if (canRotate(ClockWising))
         {
            if (ClockWising)
            {
               curRotation++;
               if (curRotation > 3) curRotation = 0;
            }
            else
            {
               curRotation--;
               if (curRotation < 0) curRotation = 3;
            }

            drawBlock(DRAW);
         }
         else
         {
            drawBlock(DRAW);
         }
      }
      //         paint();
      isMoving = false;
   }

   void game::drop()
   {
      if (isMoving || isDropping || isKilling) return;
      //atGame = false;
      isDropping = true;
      isMoving = true;

      ///         thread.stop();

      drawBlock(UNDRAW);
      while (canMoveDown(0))
      {
         curY++;
         Score(DROPUNITTYPE, 0);
         drawBlock(DRAW);
         //paint();
         drawBlock(UNDRAW);
      }
      drawBlock(DRAW);
      //paint();
      killRows();
      startBlock();
      isMoving = false;
      isDropping = false;
      //thread = new Thread(get_app());
      //atGame = true;
      //thread.start();
   }


   void game::killRows()
   {
      int coordY, coordX;
      int auxY, auxX;
      int x, y;
      bool filled;
      killed = 0;

      for (coordY = (heightInCells - 1); coordY >= 0; coordY--)
      {
         for (filled = true, coordX = 0; coordX < widthInCells; coordX++)
         {
            if (cells[coordY][coordX] == 0)
            {
               filled = false;
               break;
            }
         }

         if (filled)
         {

            isKilling = true;




            Toggle = true;
            flashLineOnly(coordY, 15, delay);

            killed++;

            for (y = coordY; y > 0; y--)
               for (x = 0; x < widthInCells; x++)
               {
                  auxX = x;
                  auxY = y;
                  cells[y][x] = cells[y - 1][x];
                  cellsOverride[y][x] = -1;
               }
            for (x = 0, y = 0; x < widthInCells; x++)
            {
               auxX = x;
               auxY = y;
               cells[y][x] = 0;
               cellsOverride[y][x] = -1;
            }
            coordY++;
            //               myPaint();
            //               paint();
            isKilling = false;

         }


      }

   }


   void game::flashLineOnly(int y, int times, float delay)
   {
      //         ::draw2d::graphics & imageGraph = *m_dib->get_graphics();

      if (times == 0) return;
      int coordX, coordY;
      int x = widthInCells - 1;

      coordY = y;


      while (x >= 0)
      {
         coordX = x;
         index i;
         if (Toggle)
         {
            i = 0;

         }
         else
         {
            i = cells[y][x];
         }
         cellsOverride[y][x] = i;
         //imageGraph.FillSolidRect((coordX * cellSizeInPixels) + 2,(coordY * cellSizeInPixels) + 2,
         // cellSizeInPixels - 3,cellSizeInPixels - 3, cr);
         x--;
      }


      Score(ROWTYPE, killed);
      //paint();
      Toggle = !Toggle;


      //image.flush();
      //Graphics g = getGraphics();
      //while(!g.drawImage(image,0,0,this)) {};
      //g.finalize();
      Sleep(delay + 1);
      flashLineOnly(y, times - 1, (float)(delay * .7));
   }

   bool game::canMoveDown(int iChar)
   {
      bool ok;

      ok = isValidPosition(curX, curY + 1, curType, curRotation);

      return ok;
   }

   bool game::canMoveLeft(int iChar)
   {
      bool ok;

      ok = isValidPosition(curX - 1, curY, curType, curRotation) && canMove;

      return ok;

   }

   bool game::canMoveRight(int iChar)
   {
      bool ok;

      ok = isValidPosition(curX + 1, curY, curType, curRotation) && canMove;

      return ok;

   }

   bool game::canRotate(bool ClockWise)
   {
      int testRotation;
      bool ok;

      if (ClockWise)
      {
         testRotation = curRotation + 1;
         if (testRotation > 3) testRotation = 0;
      }
      else
      {
         testRotation = curRotation - 1;
         if (testRotation < 0) testRotation = 3;
      }


      ok = isValidPosition(curX, curY, curType, testRotation) && canMove;

      return ok;

   }



   bool game::isValidPosition(int testX, int testY, int testType, int testRotation)
   {
      int shiftX, shiftY;
      string strShift = blocks[testType][testRotation];
      int i = 0;

      if ((testX < 0) ||
            (testX >= widthInCells) ||
            (testY >= heightInCells)) return false;

      while (true)
      {
         if (!isOutOfLimits(testX, testY))
            if (cells[testY][testX] != 0) return false;
         if (i >= strShift.length()) return true;
         shiftX = shiftsPositions[strShift[i] - '0'][0];
         shiftY = shiftsPositions[strShift[i] - '0'][1];
         testX += shiftX;
         testY += shiftY;
         if ((testX < 0) ||
               (testX >= widthInCells) ||
               (testY >= heightInCells)) return false;
         i++;
      }
   }

   bool game::isOutOfLimits(int testX, int testY)
   {
      if ((testX < 0) || (testX >= widthInCells) ||
            (testY < 0) || (testY >= heightInCells))
         return true;
      else
         return false;
   }



   void game::drawBlock(int mode)
   {
      int testX, testY, shiftX, shiftY;
      string strShift = blocks[curType][curRotation];
      int i = 0;

      testX = curX;
      testY = curY;

      while (true)
      {
         if (mode == DRAW)
         {
            drawCell(testX, testY, curType + 1);
         }
         else
         {
            drawCell(testX, testY, 0);
         }
         if (i >= strShift.length()) return;
         shiftX = shiftsPositions[strShift[i] - '0'][0];
         shiftY = shiftsPositions[strShift[i] - '0'][1];
         testX += shiftX;
         testY += shiftY;
         i++;
      }
   }

   void game::drawCell(int x, int y, int color)
   {
      if (!isOutOfLimits(x, y))
      {
         cells[y][x] = color;
      }
   }

   //void game::myPaint()
   //{
   //   Graphics g = getGraphics();
   //   paint(g);
   //   g.finalize();

   //}

   void game::on_key_down(::user::e_key ekey)
   {

      if (ekey == ::user::key_down)
      {
         Game.drop();
      }
      else if (ekey == ::user::key_left)
      {
         Game.moveLeft(0);
      }
      else if (ekey == ::user::key_right)
      {
         Game.moveRight(0);
      }
      else if (ekey == ::user::key_z)
      {
         Game.rotate(false);
      }
      else if (ekey == ::user::key_x)
      {
         Game.rotate(true);
      }


   }


   void game::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::graphics & imageGraph = *pgraphics;

      ::draw2d::savedc savedc(pgraphics);

      pgraphics->OffsetViewportOrg(m_ptOffset.x, m_ptOffset.y);

      initPaint();

      //if(atGame || (!atGame && isDropping))
      {
         int i;
         int j;

         for(i = 0; i < heightInCells; i++)
            for(j = 0; j < widthInCells; j++)
            {
               //if((offCells[i][j] != cells[i][j]) || (killed > 0))
               {
                  //offCells[i][j] = cells[i][j];
                  //imageGraph.setColor();
                  imageGraph.fill_solid_rect_dim((j * cellSizeInPixels), (i * cellSizeInPixels),
                                                 cellSizeInPixels, cellSizeInPixels, ARGB(255, 128, 128, 128));
                  imageGraph.fill_solid_rect_dim((j * cellSizeInPixels) + 1, (i * cellSizeInPixels) + 1,
                                                 cellSizeInPixels - 1, cellSizeInPixels - 1, ARGB(255, 0, 0, 0));
                  if (cellsOverride[i][j] >= 0)
                  {
                     imageGraph.fill_solid_rect_dim((j * cellSizeInPixels) + 2, (i * cellSizeInPixels) + 2,
                                                    cellSizeInPixels - 3, cellSizeInPixels - 3, colors[cellsOverride[i][j]]);
                  }
                  else
                  {
                     imageGraph.fill_solid_rect_dim((j * cellSizeInPixels) + 2, (i * cellSizeInPixels) + 2,
                                                    cellSizeInPixels - 3, cellSizeInPixels - 3, colors[cells[i][j]]);
                  }
               }
            }
      }

      killed = 0;


//      pgraphics->RestoreDC(iSaveDC);

      //image.flush();

      //while(!g.drawImage(image,0,0,this)) {};

   }








} // namespace tetris












