import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 初始化配置
 * @version 1.0
 * @author 聂延丰
 */
public class Initializer extends JFrame implements ActionListener {

    public JButton chooseCurrentDirectoryButton = new JButton("CHOOSE");
    public JLabel cdbLabel = new JLabel("Choose current directory: ");

    /**
     * 类加载器
     * @since 1.0
     */
    public Initializer(){
        this.setTitle("Initializer");
        this.setSize(500, 500);
        this.setResizable(false);

        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);

        this.setVisible(true);
    }

    /**
     * 加载基本控件
     * @description TODO
     * @since 1.0
     */
    public void loadSettingsToContentPane(){
        
    }

    /**
     * 监听窗口动作
     * @param e the event to be processed
     */
    @Override
    public void actionPerformed(ActionEvent e) {

    }
}
