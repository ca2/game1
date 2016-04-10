#include "framework.h"


namespace tictactoe
{


   board::board(::aura::application * papp) :
      object(papp)
   {

   }


   board::~board()
   {


   }


   void board::reset()
   {

      set_size(3);

      for(index i = 0; i < get_size(); i++)
      {

         element_at(i).set_size(3);

         for(index j = 0; j < element_at(i).get_size(); j++)
         {

            element_at(i).element_at(j) = check_none;

         }

      }

   }


   bool board::is_free(int x,int y)
   {

      return (*this)[x][y] != check_none;

   }


   bool board::is_full()
   {

      for(index x = 0; x < get_size(); x++)
      {

         for(index y = 0; y < element_at(x).get_size(); y++)
         {

            if((*this)[x][y] == check_none)
            {

               return false;

            }

         }

      }

      return true;

   }


   // exchaustive
   e_check board::match()
   {
      
      int i;

      int j;

      e_check echeck;

      for(i = 0; i < get_size(); i++)
      {

         for(j = 0; j < (*this)[i].get_size(); j++)
         {

            echeck = match(i,j);

            if(echeck != check_none)
            {

               return echeck;

            }

         }

      }

      return check_none;

   }


   // exchaustive
   e_check board::match(int pi,int pj)
   {

      e_check c = (*this)[pi][pj];

      if(c == check_none)
         return check_none;

      bool bOk;

      bool bFind;

      bOk = true;

      int i;

      int j;

      // horizontal
      for(i = 0; i < get_size(); i++)
      {

         if((*this)[i][pj] != c)
         {
            bOk = false;
            break;
         }

      }

      if(bOk)
         return c;

      bOk = true;

      for(j = 0; j < (*this)[pi].get_size(); j++)
      {

         if((*this)[pi][j] != c)
         {
            bOk = false;
            break;
         }

      }

      if(bOk)
         return c;

      bOk = true;

      bFind = false;

      for(i = 0,j = 0; i < get_size() && j < (*this)[i].get_size(); i++,j++)
      {

         if((*this)[i][j] != c)
         {
            bOk = false;
            break;
         }

         if(i == pi && j == pj)
            bFind = true;

      }

      if(bOk && bFind)
         return c;

      bOk = true;

      bFind = false;

      for(i = 0,j = (*this)[i].get_upper_bound(); i < get_size() && j >= 0; i++,j--)
      {

         if((*this)[i][j] != c)
         {
            bOk = false;
            break;
         }

         if(i == pi && j == pj)
            bFind = true;

      }

      if(bOk && bFind)
         return c;


      return check_none;

   }



} // namespace tictactoe









