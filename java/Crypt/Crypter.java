import java.io.*;
import javax.swing.*;
/**
 * 加解密类
 * @version 1.0
 * @author 聂延丰
 */
public class Crypter {

    public String outputPath;
    public String inputName;
    public String key;
    public char[] keyCharArray;
    public File encodedFile = null;
    public File originalFile = null;

    public Crypt parentFrame = null;

    /**
     * 类初始化
     * @param inputFile 源文件
     * @param outputFile 目标文件路径
     * @param s 密钥
     * @since 1.0
     */
    public Crypter(File inputFile, File outputFile, String s, Crypt frame){
        outputPath = outputFile.getAbsolutePath();
        inputName = inputFile.getName();
        originalFile = inputFile;
        key = s;
        keyCharArray = key.toCharArray();
        parentFrame = frame;
    }

    /**
     * 创建被加密文件
     * @return boolean 是否创建成功
     * @since 1.0
     */
    boolean createEncodedFile(){
        encodedFile = new File(outputPath + "\\" + "(Crypt)" + inputName);
        if(encodedFile.exists()) {
            encodedFile.delete();
        }
        try{
            if(encodedFile.createNewFile()){
                return true;
            }
        }catch(Exception e){
            e.printStackTrace();
        }
        return false;
    }

    /**
     * 进行文件加密
     * @return boolean 是否加密成功
     * @since 1.0
     */
    boolean crypt(){
        try(FileInputStream fis = new FileInputStream(originalFile);
            FileOutputStream fos = new FileOutputStream(encodedFile)){

            long bytesOfFile = originalFile.length();
            long latestValue = 0;

            byte[] buffer = new byte[1024];
            int bytesRead;
            int idx = 0;

            while((bytesRead = fis.read(buffer)) != -1){
                for(int i = 0; i < bytesRead; i++){
                    buffer[i] ^= keyCharArray[idx];
                    idx = (idx + 1) % keyCharArray.length;
                }
                latestValue += bytesRead;
                parentFrame.setProgressBarValue(latestValue, bytesOfFile);
                fos.write(buffer, 0, bytesRead);
            }

            fis.close();
            fos.close();
        }catch(IOException e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

}