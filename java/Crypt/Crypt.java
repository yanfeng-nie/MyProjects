import jdk.jfr.Description;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
import javax.swing.border.LineBorder;

import java.io.File;
import java.net.URI;

/**
 * 加密与解密文件，并提供加密解密历史记录
 * @version 1.1
 * @author 聂延丰
 */
public class Crypt extends JFrame implements ActionListener {
    //第一次启动初始化组件组，最后写
    public boolean isInitialized = false;
    public JPanel initializingPanel = new JPanel();
    public JButton chooseCurrentDirectoryButton = new JButton("CHOOSE");
        public JLabel cdbLabel = new JLabel("Choose current directory: ");

    //默认设置管理器，写完历史记录后再写

    public String defaultCurrentDirectory = System.getProperty("user.home") + "\\Desktop";
    public String defaultHistoryDirectory = System.getProperty("user.home") + "\\Desktop\\History";

    //菜单组件组
    public JMenuBar bar = new JMenuBar();
    public JMenu helpMenu = new JMenu("Help");
        public JMenuItem guidanceItem = new JMenuItem("Guidance");
        public JMenuItem sourceItem = new JMenuItem("Source");
            public String url = "https://github.com/Block-Oier/SFT2404";
    //确定密钥组件组
    public JLabel encoderLabel = new JLabel("ENCODER/DECODER");
    public JLabel keyLabel = new JLabel("Enter your key:");
    public JTextField keyField = new JTextField(30);
        private boolean isEditable = true;
        private String key = "1";
        private File keyFile;//无密钥时从默认文件读入，记得写
    public JButton fixKeyButton = new JButton("Fix");
    public JButton loadKeyButton = new JButton("Load");
    public JLabel currentKeyLabel = new JLabel("");
    //选择文件组件组
    public JFileChooser fc = new JFileChooser();
    public JButton chooseFileButton = new JButton("Choose File...");
        private File original_file = null;
    public JLabel selectedFileLabel = new JLabel();
    public JButton choosePathButton = new JButton("Choose Path...");
        private File encoded_file = null;
    public JLabel selectedPathLabel = new JLabel();
    //启动加密组件
    public JButton cryptButton = new JButton("CRYPT");
    public JProgressBar progressBar = new JProgressBar(0, 100);

    //历史记录列表
    public JList<String> historyList = new JList<>();
    public JLabel historyListLabel = new JLabel("History");

    /**
     * 类初始化，主要是加载组件
     * @since 1.0
     */
    public Crypt(){
        if(!isInitialized){
            System.out.println("INITIALIZE");
        }
        else{
            this.setTitle("CRYPT");
            this.setSize(1200, 800);
            this.setResizable(false);

            this.setLocationRelativeTo(null);
            this.setDefaultCloseOperation(EXIT_ON_CLOSE);

            loadFirstUsageLoaderToContentPane();
            loadBasicFunctionsToContentPane();
            loadHistoryCheckerToContentPane();
            loadDefaultSetterToContentPane();

            this.setVisible(true);
        }

    }

    /**
     * 加载加解密控件
     * @since 1.0
     */
    public void loadBasicFunctionsToContentPane(){
        getContentPane().setLayout(null);

        helpMenu.add(guidanceItem);
            guidanceItem.addActionListener(this);
        helpMenu.add(sourceItem);
            sourceItem.addActionListener(this);
        bar.add(helpMenu);
        this.setJMenuBar(bar);

        getContentPane().add(encoderLabel);
        encoderLabel.setBounds(30, 15, 200, 30);
        getContentPane().add(keyLabel);
        keyLabel.setBounds(50, 35, 100, 40);
        getContentPane().add(keyField);
        keyField.setBounds(150, 45, 100, 20);
        getContentPane().add(fixKeyButton);
        fixKeyButton.setBounds(250, 42, 70, 25);
        fixKeyButton.addActionListener(this);
        getContentPane().add(loadKeyButton);
        loadKeyButton.setBounds(323, 42, 70, 25);
        loadKeyButton.addActionListener(this);
        getContentPane().add(currentKeyLabel);
        currentKeyLabel.setBounds(400, 35, 800, 40);
        currentKeyLabel.setVisible(false);

        getContentPane().add(chooseFileButton);
        chooseFileButton.setBounds(30, 90, 120, 25);
        chooseFileButton.addActionListener(this);
        getContentPane().add(selectedFileLabel);
        selectedFileLabel.setBounds(155, 90, 700, 25);

        getContentPane().add(choosePathButton);
        choosePathButton.setBounds(30, 120, 120, 25);
        choosePathButton.addActionListener(this);
        getContentPane().add(selectedPathLabel);
        selectedPathLabel.setBounds(155, 120, 700, 25);

        getContentPane().add(cryptButton);
        cryptButton.setBounds(30, 150, 120, 50);
        cryptButton.addActionListener(this);
        getContentPane().add(progressBar);
        progressBar.setBounds(160, 161, 150, 30);

    }

    /**
     * 加载历史记录查看器
     * @description TODO
     * @since 1.1
     */
    public void loadHistoryCheckerToContentPane(){
        getContentPane().add(historyListLabel);
        historyListLabel.setBounds(205, 225, 200, 25);
        JScrollPane listScrollPane = new JScrollPane(historyList);
        getContentPane().add(listScrollPane);
        listScrollPane.setBounds(30, 250, 400, 470);
        listScrollPane.setBorder(new LineBorder(Color.BLACK));
    }

    /**
     * 加载初次启动后的默认设置管理器
     * @description TODO
     * @since 1.2
     */
    public void loadDefaultSetterToContentPane(){

    }

    /**
     * 加载初次启动时的基本配置设置器
     * @description TODO
     * @since 1.3
     */
    public void loadFirstUsageLoaderToContentPane(){

    }

    /**
     * 动作监听器，接口重载
     * @param e the event to be processed
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == chooseFileButton){
            fc.setCurrentDirectory(new File(defaultCurrentDirectory));
            fc.setFileSelectionMode(JFileChooser.FILES_ONLY);
            int returnValue = fc.showOpenDialog(null);
            if(returnValue == JFileChooser.APPROVE_OPTION){
                original_file = fc.getSelectedFile();
                selectedFileLabel.setText(original_file.getAbsolutePath());
            }
            else if(original_file == null)
                selectedFileLabel.setText("No file selected!");
        }
        if(e.getSource() == choosePathButton){
            fc.setCurrentDirectory(new File(defaultCurrentDirectory));
            fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            int returnValue = fc.showOpenDialog(null);
            if(returnValue == JFileChooser.APPROVE_OPTION){
                encoded_file = fc.getSelectedFile();
                selectedPathLabel.setText(encoded_file.getAbsolutePath() + "\\");
            }
            else if(encoded_file == null)
                selectedPathLabel.setText("No directory selected!");
        }
        if(e.getSource() == fixKeyButton){
            isEditable = !isEditable;
            keyField.setEditable(isEditable);
            if(isEditable) fixKeyButton.setText("Fix");
            else fixKeyButton.setText("Unfix");
        }
        if(e.getSource() == loadKeyButton){
            String temp = keyField.getText();
            setKey(temp);
            currentKeyLabel.setText("Current Key: " + temp);
            if(!currentKeyLabel.isVisible()) currentKeyLabel.setVisible(true);
        }
        if(e.getSource() == cryptButton){
            if(original_file == null || encoded_file == null){
                JOptionPane.showMessageDialog(Crypt.this, "Unable to Crypt!");
                return;
            }
            Crypter c = new Crypter(original_file, encoded_file, key, this);
            if(c.createEncodedFile())
                if(c.crypt()){
                    JOptionPane.showMessageDialog(Crypt.this, "Succeeded!");
                    setProgressBarValue(0, 1);
                    original_file = null;
                    encoded_file = null;
                    selectedPathLabel.setText("");
                    selectedFileLabel.setText("");
                }
        }
        if(e.getSource() == guidanceItem) {
            System.out.println("guidance Menu Item");
        }
        if(e.getSource() == sourceItem){
            // 使用浏览器打开源代码网址
            try{
                URI link = new URI(url);
                if(Desktop.isDesktopSupported()){
                    Desktop desktop = Desktop.getDesktop();
                    desktop.browse(link);
                }
                else{
                    JOptionPane.showMessageDialog(Crypt.this, "Enter Failure!");
                }
            }catch (Exception exception){
                exception.printStackTrace();
            }
        }
    }

    /**
     * 设置密钥
     * @param s 待设置的密钥
     * @return 密钥是否设置成功
     * @since 1.0
     */
    public boolean setKey(String s){
        key = s;
        return key != null;
    }

    public void setProgressBarValue(long value, long totalValue){
        progressBar.setValue(100 * (int)(value / totalValue));
    }

}
