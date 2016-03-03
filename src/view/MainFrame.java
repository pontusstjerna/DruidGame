package view;

import javax.swing.*;

/**
 * Created by Pontus on 2016-03-03.
 */
public class MainFrame extends JFrame {
    private String title;
    private int width, height;
    private MainSurface surface;

    public MainFrame(String title, int width, int height){
        this.title = title;
        this.width = width;
        this.height = height;

        surface = new MainSurface();
    }

    public void init(){
        initWindow();
        initSurface();
    }

    private void initWindow(){
        setTitle(title);
        setSize(width, height);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void initSurface(){
        surface.init();
        add(surface);
    }
}
