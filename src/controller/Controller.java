package controller;

import view.MainFrame;

/**
 * Created by Pontus on 2016-03-03.
 */
public class Controller {
    private MainFrame frame;

    public Controller(){
        frame = new MainFrame("Druid Game", 800, 600);
    }

    public void startGame(){
        initFrame();
    }

    private void initFrame(){
        frame.setVisible(true);
        frame.init();
    }

}
