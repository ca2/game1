#include "framework.h"


namespace sokoban
{


   level::level(::aura::application * papp) :
      object(papp)
   {
      m_iRedo = 0;
   }


   bool level::initialize()
   {

      m_iWidth = 0;
      
      for(index iLine = 0; iLine < m_stra.get_size(); iLine++)
      {

         string strLine = m_stra[iLine];

         m_iWidth = MAX(m_iWidth,strLine.get_length());

      }

      return true;
   }


   void level::draw(::draw2d::graphics * pgraphics, asset * passet, int yOffset)
   {
   
      int xOffset = 0;

      point ptViewport = pgraphics->GetViewportOrg();

      pgraphics->OffsetViewportOrg(xOffset,yOffset * passet->m_iSize);

      byte bA;

      if(m_iLevel == passet->m_iLevel)
         bA = 255;
      else
         bA = (byte) (255 * 0.33);

      for(index iLine = 0; iLine < m_stra.get_size(); iLine++)
      {
      
         string strLine = m_stra[iLine];
      
         for(index iChar = 0; iChar < strLine.get_length(); iChar++)
         {
            char ch = strLine[iChar];

            //if(m_iLevel != passet->m_iLevel)
            //{
            //   if(ch == '@')
            //      ch = ' ';
            //   else if(ch == '+')
            //      ch = '.';
            //}

            passet->draw(pgraphics,ch,iChar, iLine, bA);

         }

      }



      pgraphics->SetViewportOrg(ptViewport);

   }


   bool level::can_move_up()
   {
      
      int xPlayer;
      
      int yPlayer;
      
      if(!find_player(xPlayer,yPlayer))
         return false;

      yPlayer--;

      char ch = bl(xPlayer,yPlayer);

      if(ch == '#')
         return false;

      if(ch == '$' || ch == '*')
      {
         
         char ch2 = bl(xPlayer,yPlayer - 1);

         if(ch2 == '#' || ch2 == '$' || ch2 == '*')
            return false;

      }

      return true;
   }

   bool level::can_move_down()
   {

      int xPlayer;

      int yPlayer;

      if(!find_player(xPlayer,yPlayer))
         return false;

      yPlayer++;

      char ch = bl(xPlayer,yPlayer);

      if(ch == '#')
         return false;

      if(ch == '$' || ch == '*')
      {

         char ch2 = bl(xPlayer,yPlayer + 1);

         if(ch2 == '#' || ch2 == '$' || ch2 == '*')
            return false;

      }

      return true;
   }


   bool level::can_move_left()
   {

      int xPlayer;

      int yPlayer;

      if(!find_player(xPlayer,yPlayer))
         return false;

      xPlayer--;

      char ch = bl(xPlayer,yPlayer);

      if(ch == '#')
         return false;

      if(ch == '$' || ch == '*')
      {

         char ch2 = bl(xPlayer-1,yPlayer);

         if(ch2 == '#' || ch2 == '$' || ch2 == '*')
            return false;

      }

      return true;
   }


   bool level::can_move_right()
   {

      int xPlayer;

      int yPlayer;

      if(!find_player(xPlayer,yPlayer))
         return false;

      xPlayer++;

      char ch = bl(xPlayer,yPlayer);

      if(ch == '#')
         return false;

      if(ch == '$' || ch == '*')
      {

         char ch2 = bl(xPlayer +1,yPlayer);

         if(ch2 == '#' || ch2 == '$' || ch2 == '*')
            return false;

      }

      return true;
   }

   char level::bl(int iChar,int iLine)
   {

      if(iLine < 0)
         return '#';

      if(iLine >= m_stra.get_count())
         return '#';

      if(iChar < 0)
         return '#';

      if(iChar >= m_stra[iLine].get_length())
         return '#';

      return m_stra[iLine][iChar];
   
   }


   bool level::bl(int iChar,int iLine, char ch)
   {

      if(bl(iChar,iLine) == '#') // simple check
         return false;

      m_stra[iLine].set_at(iChar,ch);

      return true;

   }

   bool level::move_up(bool bRedo)
   {

      if(!can_move_up())
         return false;

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x, y) == '+')
      {
         bl(x, y,'.');
      }
      else
      {
         bl(x,y,' ');
      }

      bool bPush = bl(x,y - 1) == '$' || bl(x,y - 1) == '*';

      if(bl(x,y - 1) == '*' || bl(x,y - 1) == '.')
      {
         bl(x,y-1,'+');
      }
      else
      {
         bl(x,y-1,'@');
      }

      if(bPush)
      {
         if(bl(x,y - 2) == '.')
         {
            bl(x,y - 2, '*');
         }
         else
         {
            bl(x,y - 2, '$');
         }


      }

      if(!bRedo)
      {

         if(bPush)
         {
            record('U');
         }
         else
         {
            record('u');
         }

      }

      return true;

   }


   bool level::move_down(bool bRedo)
   {

      if(!can_move_down())
         return false;

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x,y) == '+')
      {
         bl(x,y,'.');
      }
      else
      {
         bl(x,y,' ');
      }

      bool bPush = bl(x,y + 1) == '$' || bl(x,y + 1) == '*';

      if(bl(x,y + 1) == '*' || bl(x,y + 1) == '.')
      {
         bl(x,y + 1,'+');
      }
      else
      {
         bl(x,y + 1,'@');
      }

      if(bPush)
      {
         if(bl(x,y + 2) == '.')
         {
            bl(x,y + 2,'*');
         }
         else
         {
            bl(x,y + 2,'$');
         }


      }

      if(!bRedo)
      {

         if(bPush)
         {
            record('D');
         }
         else
         {
            record('d');
         }

         return true;

      }

      return false;

   }



   bool level::move_left(bool bRedo)
   {

      if(!can_move_left())
         return false;

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x,y) == '+')
      {
         bl(x,y,'.');
      }
      else
      {
         bl(x,y,' ');
      }

      bool bPush = bl(x - 1,y) == '$' || bl(x - 1,y) == '*';

      if(bl(x - 1,y) == '*' || bl(x - 1,y) == '.')
      {
         bl(x - 1,y,'+');
      }
      else
      {
         bl(x - 1,y,'@');
      }


      if(bPush)
      {
         if(bl(x - 2,y) == '.')
         {
            bl(x - 2,y,'*');
         }
         else
         {
            bl(x - 2,y,'$');
         }


      }

      if(!bRedo)
      {

         if(bPush)
         {
            record('L');
         }
         else
         {
            record('l');
         }

      }

      return true;

   }


         
   bool level::move_right(bool bRedo)
   {

      if(!can_move_right())
         return false;

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x,y) == '+')
      {
         bl(x,y,'.');
      }
      else
      {
         bl(x,y,' ');
      }

      bool bPush = bl(x+1, y) == '$' || bl(x+1,y) == '*';

      if(bl(x+1,y) == '*' || bl(x+1,y) == '.')
      {
         bl(x+1,y,'+');
      }
      else
      {
         bl(x+1,y,'@');
      }

      if(bPush)
      {
         if(bl(x+2,y) == '.')
         {
            bl(x+2,y,'*');
         }
         else
         {
            bl(x+2,y,'$');
         }


      }


      if(!bRedo)
      {

         if(bPush)
         {
            record('R');
         }
         else
         {
            record('r');
         }

      }

      return true;

   }

   bool level::find_player(int & iChar,int & iLine)
   {
      for(iLine = 0; iLine < m_stra.get_size(); iLine++)
      {

         string strLine = m_stra[iLine];

         for(iChar = 0; iChar < strLine.get_length(); iChar++)
         {
            char ch = strLine[iChar];

            if(ch == '@' || ch == '+')
            {
               return true;
            }

         }

      }

      iChar = -1;
      iLine = -1;

      return false;

   }

   bool level::is_solved()
   {

      for(index iLine = 0; iLine < m_stra.get_size(); iLine++)
      {

         if(m_stra[iLine].find('$') >= 0)
            return false;
         if(m_stra[iLine].find('.') >= 0)
            return false;

      }

      return true;

   }

   void level::record(char ch)
   {

      m_iRedo = MIN(m_iRedo,m_strMove.get_length());

      m_strMove = m_strMove.Left(m_iRedo) + ch;

      m_iRedo++;



   }

   void level::undo()
   {

      m_iRedo = MIN(m_iRedo,m_strMove.get_length());

      if(m_iRedo <= 0)
         return;

      m_iRedo--;

      _undo(m_strMove[m_iRedo]);

   }

   void level::redo()
   {
      
      if(m_iRedo >= m_strMove.get_length())
         return;

      move(m_strMove[m_iRedo], true);

      m_iRedo++;

   }

   bool level::move(char ch, bool bRedo)
   {
      ch = tolower(ch);
      if(ch == 'u')
      {
         return move_up(bRedo);
      }
      else if(ch == 'd')
      {
         return move_down(bRedo);
      }
      else if(ch == 'l')
      {
         return move_left(bRedo);
      }
      else if(ch == 'r')
      {
         return move_right(bRedo);
      }

      return false;

   }


   bool level::_undo(char ch)
   {
      
      bool bPush = ch >= 'A' && ch <= 'Z';
      
      ch = tolower(ch);

      if(ch == 'u')
      {
         return _undo_up(bPush);
      }
      else if(ch == 'd')
      {
         return _undo_down(bPush);
      }
      else if(ch == 'l')
      {
         return _undo_left(bPush);
      }
      else if(ch == 'r')
      {
         return _undo_right(bPush);
      }

      return false;

   }


   bool level::_undo_up(bool bPush)
   {

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x,y+1) == '.')
      {
         bl(x,y+1,'+');
      }
      else
      {
         bl(x,y+1,'@');
      }

      if(bPush)
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'*');
         }
         else
         {
            bl(x,y,'$');
         }
         if(bl(x,y - 1) == '*')
         {
            bl(x,y - 1,'.');
         }
         else
         {
            bl(x,y - 1,' ');
         }
      }
      else
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'.');
         }
         else
         {
            bl(x,y,' ');
         }
      }


      return true;

   }


   bool level::_undo_down(bool bPush)
   {

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x,y - 1) == '.')
      {
         bl(x,y - 1,'+');
      }
      else
      {
         bl(x,y - 1,'@');
      }

      if(bPush)
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'*');
         }
         else
         {
            bl(x,y,'$');
         }
         if(bl(x,y + 1) == '*')
         {
            bl(x,y + 1,'.');
         }
         else
         {
            bl(x,y + 1,' ');
         }
      }
      else
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'.');
         }
         else
         {
            bl(x,y,' ');
         }
      }


      return true;

   }
   bool level::_undo_left(bool bPush)
   {

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x+1,y) == '.')
      {
         bl(x+1,y,'+');
      }
      else
      {
         bl(x+1,y,'@');
      }

      if(bPush)
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'*');
         }
         else
         {
            bl(x,y,'$');
         }
         if(bl(x-1,y) == '*')
         {
            bl(x-1,y,'.');
         }
         else
         {
            bl(x-1,y,' ');
         }
      }
      else
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'.');
         }
         else
         {
            bl(x,y,' ');
         }
      }


      return true;

   }



   bool level::_undo_right(bool bPush)
   {

      int x;

      int y;

      if(!find_player(x,y))
         return false;

      if(bl(x - 1,y) == '.')
      {
         bl(x - 1,y,'+');
      }
      else
      {
         bl(x - 1,y,'@');
      }

      if(bPush)
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'*');
         }
         else
         {
            bl(x,y,'$');
         }
         if(bl(x + 1,y) == '*')
         {
            bl(x + 1,y,'.');
         }
         else
         {
            bl(x + 1,y,' ');
         }
      }
      else
      {
         if(bl(x,y) == '+')
         {
            bl(x,y,'.');
         }
         else
         {
            bl(x,y,' ');
         }
      }


      return true;

   }


} // namespace sokoban















