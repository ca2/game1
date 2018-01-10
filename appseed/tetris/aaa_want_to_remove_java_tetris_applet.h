import java.awt.*;
import java.applet.Applet;
import _TetrisLanguage;


//
//
//
//	By Camilo Sasuke Tsumanuma probably at the first semester of (certainly) 1998
//	Changed  28/09/1998
//	Modificado 22/10/1998
//	Modificado 26/10/1998
//	Modificado 09/11/1998	16:16
//

public class _Applet extends Applet
{
   _TetrisLanguage lang;
   _Frame frame;
   Button btFrame;

   public void init()
   {
      String param = getParameter("language");
      param = (param == null) ? "br" : param;

      lang = new _TetrisLanguage(param);

      setLayout(new BorderLayout());
      btFrame = new Button(lang.comunic(1)); // 1-Abrir Jogo
      add("Center",btFrame);
      frame = null;

   }


   public void start()
   {
      if(frame != null)
      {
         frame.show();
      }
   }

   public void stop()
   {
      if(frame != null)
      {
         frame.hide();
      }
   }

   public void destroy()
   {
      if(frame != null)
      {
         frame.dispose();
         frame = null;
      }
   }



   public bool handleEvent(Event evt)
   {

      if(evt.id == Event.WINDOW_DESTROY)
      {
         System.exit(0);
      }

      return super.handleEvent(evt);

   }

   public bool action(Event evt,Object arg)
   {
      if(evt.target == btFrame)
      {
         if(frame == null)
         {
            frame = new _Frame(this);
         }
         start();
         return true;
      }
      return false;
   }

   public static void main(String args[])
   {
      _Applet applet = new _Applet();
      applet.init();
      applet.start();
   }

}




class _Frame extends Frame
{

   Label score;
   Label level;
   _Tetris tetris;
   _TetrisPreview preview;
   _Applet parent;
   _ConfigForm configForm;
   MenuItem start;
   MenuItem config;
   MenuItem pause;
   MenuItem quit;
   MenuItem help;
   MenuItem about;
   MenuItem smallerCell;
   MenuItem standardCell;
   MenuItem biggerCell;
   MenuItem standard;
   MenuItem smaller;
   MenuItem wider;
   MenuItem taller;



   public _Frame(_Applet parent)
   {
      this.parent = parent;

      setTitle(parent.lang.comunic(2)); //2-Tetris

      setLayout(new BorderLayout());

      MenuBar menubar;
      menubar = new MenuBar();
      setMenuBar(menubar);

      Menu menu;
      menu = new Menu(parent.lang.comunic(3)); //3-Jogo
      menubar.add(menu);

      start = new MenuItem(parent.lang.comunic(4)); //4-Iniciar
      menu.add(start);

      pause = new MenuItem(parent.lang.comunic(5)); //5-Parar
      menu.add(pause);




      Menu subMenu = new Menu(parent.lang.comunic(9));//9-Tamanho da Célula
      menu.add(subMenu);

      smallerCell = new MenuItem(parent.lang.comunic(10)); //10-Menor
      subMenu.add(smallerCell);

      standardCell = new MenuItem(parent.lang.comunic(11)); //11-Padrão
      subMenu.add(standardCell);

      biggerCell = new MenuItem(parent.lang.comunic(12)); //12-Maior
      subMenu.add(biggerCell);




      subMenu = new Menu(parent.lang.comunic(13));//13-Tipo
      menu.add(subMenu);

      standard = new MenuItem(parent.lang.comunic(14)); //14-Padrão
      subMenu.add(standard);

      smaller = new MenuItem(parent.lang.comunic(15)); //15-Menor
      subMenu.add(smaller);

      wider = new MenuItem(parent.lang.comunic(16)); //16-Mais Largo
      subMenu.add(wider);

      taller = new MenuItem(parent.lang.comunic(17)); //17-Mais Alto
      subMenu.add(taller);


      menu.addSeparator();


      quit = new MenuItem(parent.lang.comunic(6)); //6-Sair
      menu.add(quit);

      menu = new Menu(parent.lang.comunic(7)); //7-Editar
      menubar.add(menu);

      config = new MenuItem(parent.lang.comunic(8));//8-Preferências
      menu.add(config);



      menu = new Menu(parent.lang.comunic(18)); //18-Ajuda
      //		menubar.setHelpMenu(menu);
      menubar.add(menu);

      help = new MenuItem(parent.lang.comunic(18)); //18-Ajuda
      menu.add(help);

      menu.addSeparator();

      about = new MenuItem(parent.lang.comunic(29)); //29-Sobre o Tetris
      menu.add(about);

      Panel parentPanel;
      parentPanel = new Panel();
      parentPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
      add("North",parentPanel);
      preview = new _TetrisPreview(this);
      parentPanel.add(preview);

      GridBagLayout grid = new GridBagLayout();
      GridBagConstraints constraints = new GridBagConstraints();
      Panel p;
      p = new Panel();
      parentPanel.add(p);
      p.setLayout(grid);

      constraints.fill = GridBagConstraints.BOTH;
      constraints.weightx = 1.0;
      constraints.weighty = 1.0;

      Label lb;
      lb = new Label(parent.lang.comunic(20)); //20-Pontos
      grid.setConstraints(lb,constraints);
      p.add(lb);

      score = new Label("                               ");
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      grid.setConstraints(score,constraints);
      p.add(score);

      constraints.gridwidth = GridBagConstraints.RELATIVE;
      lb = new Label(parent.lang.comunic(21)); //21-Nível
      grid.setConstraints(lb,constraints);
      p.add(lb);

      level = new Label("       ");
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      grid.setConstraints(level,constraints);
      p.add(level);


      configForm = new _ConfigForm(this);
      tetris = new _Tetris(10,20,24,this);
      add("Center",tetris);


      pack();



   }

   public bool action(Event evt,Object arg)
   {
      if(evt.target == start)
      {
         tetris.start();
      }
      if(evt.target == pause)
      {
         tetris.atPause = true;
      }
      if(evt.target == smallerCell)
      {
         if(tetris.cellSizeInPixels != 18)
         {
            tetris.init(tetris.widthInCells,tetris.heightInCells,18);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }
      if(evt.target == standardCell)
      {
         if(tetris.cellSizeInPixels != 24)
         {
            tetris.init(tetris.widthInCells,tetris.heightInCells,24);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }
      if(evt.target == biggerCell)
      {
         if(tetris.cellSizeInPixels != 30)
         {
            tetris.init(tetris.widthInCells,tetris.heightInCells,30);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }

      if(evt.target == standard)
      {
         if((tetris.widthInCells != 10) || (tetris.heightInCells != 20))
         {
            tetris.init(10,20,tetris.cellSizeInPixels);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }
      if(evt.target == smaller)
      {
         if((tetris.widthInCells != 10) || (tetris.heightInCells != 12))
         {
            tetris.init(10,12,tetris.cellSizeInPixels);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }
      if(evt.target == wider)
      {
         if((tetris.widthInCells != 20) || (tetris.heightInCells != 20))
         {
            tetris.init(20,20,tetris.cellSizeInPixels);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }
      if(evt.target == taller)
      {
         if((tetris.widthInCells != 10) || (tetris.heightInCells != 30))
         {
            tetris.init(10,30,tetris.cellSizeInPixels);
            tetris.resize(tetris.preferredSize());
            pack();
         }
      }
      if(evt.target == quit)
      {
         parent.frame = null;
         tetris.atGame = false;
         dispose();
      }
      if(evt.target == config)
      {
         configForm.show();
      }
      if(evt.target == help)
      {
         _Help dialog = new _Help(this);
         dialog.show();
      }
      if(evt.target == about)
      {
         _About dialog = new _About(this);
         dialog.show();
      }
      return false;
   }


   public bool handleEvent(Event evt)
   {

      if(evt.id == Event.WINDOW_DESTROY)
      {
         parent.frame = null;
         tetris.atGame = false;
         dispose();
      }

      if(evt.id == Event.KEY_ACTION)
      {
         if(evt.key == Event.RIGHT)
         {
            tetris.moveRight();
            return true;
         }
         if(evt.key == Event.LEFT)
         {
            tetris.moveLeft();
            return true;
         }
         if(evt.key == Event.DOWN)
         {
            tetris.drop();
            return true;
         }
      }
      if(evt.id == Event.KEY_PRESS)
      {
         if(evt.key == 'z')
         {
            tetris.rotate(false);
            return true;
         }
         if(evt.key == 'x')
         {
            tetris.rotate(true);
            return true;
         }
      }
      return super.handleEvent(evt);
   }


}


//
//	Criado 09/11/1998
//

class _Help extends Dialog
{

   _Frame parent;
   Button buttonOk;

   public _Help(_Frame parent)
   {
      super(parent,false);
      this.parent = parent;

      setTitle(parent.parent.lang.comunic(19)); //22-Ajuda do Tetris

      /*		Label label = new Label();
      Font f = new Font(FONT_SANS, Font.BOLD, 24);
      label.setFont(f);
      label.setText(parent.parent.lang.comunic(19)); //19-Ajuda do Tetris
      add("North", label);

      label = new Label(parent.parent.lang.comunic(28)); //28-{ajuda}
      f = new Font(FONT_SANS, Font.PLAIN, 12);
      label.setFont(f);
      label.setText(parent.parent.lang.comunic(28));
      add("Center", label);      */

      TextArea text = new TextArea();
      text.setEditable(false);
      Font f = new Font(FONT_SANS,Font.BOLD,24);
      text.setFont(f);
      text.appendText(parent.parent.lang.comunic(19));  //19-Ajuda do Tetris
      text.appendText("\n\n");

      f = new Font(FONT_SANS,Font.PLAIN,12);
      text.setFont(f);
      text.appendText(parent.parent.lang.comunic(28)); //28-{ajuda}
      add("Center",text);

      buttonOk = new Button(parent.parent.lang.comunic(26)); //26-OK
      add("South",buttonOk);

      pack();

   }

   public bool action(Event evt,Object arg)
   {

      if(evt.target == buttonOk)
      {
         dispose();
      }

      return false;
   }

   public bool handleEvent(Event evt)
   {

      if(evt.id == Event.WINDOW_DESTROY)
      {
         dispose();
      }

      return super.handleEvent(evt);
   }

}

//
//	Criado 09/11/1998
//

class _About extends Dialog
{

   _Frame parent;
   Button buttonOk;

   public _About(_Frame parent)
   {
      super(parent,false);
      this.parent = parent;

      setTitle(parent.parent.lang.comunic(29)); //22-Sobre o Tetris

      Label label = new Label();
      Font f = new Font(FONT_SANS,Font.BOLD,12);
      label.setFont(f);
      label.setText(parent.parent.lang.comunic(30)); //30-Por Camilo...
      add("Center",label);

      buttonOk = new Button(parent.parent.lang.comunic(26)); //26-OK
      add("South",buttonOk);

      pack();

   }

   public bool action(Event evt,Object arg)
   {

      if(evt.target == buttonOk)
      {
         dispose();
      }

      return false;
   }

   public bool handleEvent(Event evt)
   {

      if(evt.id == Event.WINDOW_DESTROY)
      {
         dispose();
      }

      return super.handleEvent(evt);
   }


}


class _ConfigForm extends Dialog
{

   _Frame parent;
   TextField fieldWidth;
   TextField fieldHeight;
   TextField fieldCellSize;
   Button buttonOk;
   Button buttonCancel;
   Button buttonHelp;

   public _ConfigForm(_Frame parent)
   {
      super(parent,false);
      this.parent = parent;

      setTitle(parent.parent.lang.comunic(22)); //22-Configuração do Tetris
      GridBagLayout grid = new GridBagLayout();
      GridBagConstraints constraints = new GridBagConstraints();
      Label lb;

      setLayout(new BorderLayout());


      Panel p;
      p = new Panel();
      add("North",p);
      p.setLayout(grid);

      constraints.fill = GridBagConstraints.BOTH;
      constraints.weightx = 1.0;
      constraints.weighty = 1.0;

      lb = new Label(parent.parent.lang.comunic(23)); //23-Células Horizontais
      grid.setConstraints(lb,constraints);
      p.add(lb);

      fieldWidth = new TextField(5);
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      grid.setConstraints(fieldWidth,constraints);
      p.add(fieldWidth);

      constraints.gridwidth = GridBagConstraints.RELATIVE;
      lb = new Label(parent.parent.lang.comunic(24)); //24-Células Verticais
      grid.setConstraints(lb,constraints);
      p.add(lb);

      fieldHeight = new TextField(5);
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      grid.setConstraints(fieldHeight,constraints);
      p.add(fieldHeight);

      constraints.gridwidth = GridBagConstraints.RELATIVE;
      lb = new Label(parent.parent.lang.comunic(25)); //25 -Tamanho da Céula
      grid.setConstraints(lb,constraints);
      p.add(lb);

      fieldCellSize = new TextField(5);
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      grid.setConstraints(fieldCellSize,constraints);
      p.add(fieldCellSize);

      constraints.gridwidth = GridBagConstraints.RELATIVE;
      constraints.ipadx = 3;
      constraints.ipady = 3;
      buttonOk = new Button(parent.parent.lang.comunic(26)); //26-OK
      grid.setConstraints(buttonOk,constraints);
      p.add(buttonOk);

      buttonCancel = new Button(parent.parent.lang.comunic(27)); //27-Cancelar
      grid.setConstraints(buttonCancel,constraints);
      p.add(buttonCancel);

      buttonHelp = new Button(parent.parent.lang.comunic(18));
      constraints.gridwidth = GridBagConstraints.REMAINDER;
      grid.setConstraints(buttonHelp,constraints);
      //		p.add(buttonHelp);

      pack();

   }

   public bool action(Event evt,Object arg)
   {
      if(evt.id == Event.WINDOW_DESTROY)
      {
         dispose();
      }
      if(evt.target == buttonOk)
      {
         try
         {
            int width = Integer.parseInt(fieldWidth.getText());
            int height = Integer.parseInt(fieldHeight.getText());
            int cellSize = Integer.parseInt(fieldCellSize.getText());
            if((width < 4) || (width > 33)) throw new NumberFormatException();
            if((height < 7) || (height > 33)) throw new NumberFormatException();
            if((cellSize < 4) || (cellSize > 33)) throw new NumberFormatException();
            parent.tetris.init(width,height,cellSize);
            parent.tetris.resize(parent.tetris.preferredSize());
            parent.pack();
            dispose();
         }
         catch(NumberFormatException e)
         {
            System.out.println("Valor inválido (Invalid Value).");
         }
      }
      if(evt.target == buttonCancel)
      {
         dispose();
      }
      if(evt.target == buttonHelp)
      {
         // nao faz nada por enquanto
      }
      return false;
   }

}







