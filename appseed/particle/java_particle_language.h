


// Criado 22/10/1998


class _TetrisLanguage
{

   int lang;

   static String comunicacao[][] =
   {
      {"Abrir Jogo","Open Game"}, 		//1
      {"Tetris","Tetris"},
      {"Jogo","Game"},
      {"Iniciar","Start"},
      {"Parar","Stop"},			//5
      {"Sair","Quit"},
      {"Editar","Edit"},
      {"Prefer�ncias...","Preferences..."},
      {"Tamanho da C�lula","Cell Size"},
      {"Menor","Smaller"},			//10
      {"Padr�o","Standard"},
      {"Maior","Bigger"},
      {"Tipo","Type"},
      {"Padr�o","Standard"},
      {"Menor","Smaller"},			//15
      {"Mais Largo","Wider"},
      {"Mais Alto","Taller"},
      {"Ajuda","Help"},
      {"Ajuda do Tetris","Tetris Help"},
      {"Pontos: ","Score: "},		//20
      {"N�vel: ","Level: "},
      {"Configura��o do Tetris","Tetris COnfiguration"},
      {"C�lulas Horizontais: ","Horizontal Cells: "},
      {"C�lulas Verticais: ","Vertical Cells: "},
      {"Tamanho da C�lula: ","Cell Size: "}, // 25
      {"OK","OK"},
      {"Cancelar","Cancel"},
      {"Teclas:\n\nMover � direita: Seta direita\nMover � esquerda: Seta � esquerda\nFor�ar descida: Seta para baixo\nRotacionar no sentido anti-hor�rio: < z >\nRotacionar no sentido hor�rio:  < x >",
      "Keys:\n\nMove right: Right arrow\nMove left: Left Arrow\nDrop: Down Arrow\nRotate counter clockwise: < z >\nRotate clockwise: < x >"},
      {"Sobre o Tetris","About Tetris"},
      {"Por Camilo Sasuke Tsumanuma 1998.","By Camilo Sasuke Tsumanuma 1998."} //

   };



   public _TetrisLanguage(String language)
   {

      lang = 0; // "br"
      if(language.equals("en")) lang = 1;

   }

   public String comunic(int index)
   {
      return comunicacao[index - 1][lang];
   }

}