


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
      {"Preferências...","Preferences..."},
      {"Tamanho da Célula","Cell Size"},
      {"Menor","Smaller"},			//10
      {"Padrão","Standard"},
      {"Maior","Bigger"},
      {"Tipo","Type"},
      {"Padrão","Standard"},
      {"Menor","Smaller"},			//15
      {"Mais Largo","Wider"},
      {"Mais Alto","Taller"},
      {"Ajuda","Help"},
      {"Ajuda do Tetris","Tetris Help"},
      {"Pontos: ","Score: "},		//20
      {"Nível: ","Level: "},
      {"Configuração do Tetris","Tetris COnfiguration"},
      {"Células Horizontais: ","Horizontal Cells: "},
      {"Células Verticais: ","Vertical Cells: "},
      {"Tamanho da Célula: ","Cell Size: "}, // 25
      {"OK","OK"},
      {"Cancelar","Cancel"},
      {"Teclas:\n\nMover à direita: Seta direita\nMover à esquerda: Seta à esquerda\nForçar descida: Seta para baixo\nRotacionar no sentido anti-horário: < z >\nRotacionar no sentido horário:  < x >",
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